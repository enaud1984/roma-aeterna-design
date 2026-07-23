param(
    [string]$EngineRoot = "",
    [string]$ProjectPath = "RomaAeterna.uproject",
    [switch]$SkipLocalAssets,
    [switch]$OpenEditorAfterTests,
    [switch]$KeepEditorOpen
)

$ErrorActionPreference = "Stop"
$RepositoryRoot = Split-Path -Parent $PSScriptRoot
if (-not [IO.Path]::IsPathRooted($ProjectPath)) { $ProjectPath = Join-Path $RepositoryRoot $ProjectPath }
if (-not (Test-Path -LiteralPath $ProjectPath -PathType Leaf)) { Write-Error "File .uproject non trovato: $ProjectPath"; exit 2 }
$ResolvedProjectPath = (Resolve-Path -LiteralPath $ProjectPath).Path

if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $ProgramFilesPath = [Environment]::GetFolderPath("ProgramFiles")
    foreach ($Folder in @("UE_5.8", "UE_5.8EA")) {
        $Candidate = Join-Path $ProgramFilesPath "Epic Games/$Folder"
        if (Test-Path -LiteralPath $Candidate -PathType Container) { $EngineRoot = $Candidate; break }
    }
}
if ([string]::IsNullOrWhiteSpace($EngineRoot) -or -not (Test-Path -LiteralPath $EngineRoot -PathType Container)) {
    Write-Error "Unreal Engine 5.8 non trovato: specificare -EngineRoot."; exit 3
}
$ResolvedEngineRoot = (Resolve-Path -LiteralPath $EngineRoot).Path
$RunUAT = Join-Path $ResolvedEngineRoot "Engine/Build/BatchFiles/RunUAT.bat"
$EditorCmd = Join-Path $ResolvedEngineRoot "Engine/Binaries/Win64/UnrealEditor-Cmd.exe"
$Editor = Join-Path $ResolvedEngineRoot "Engine/Binaries/Win64/UnrealEditor.exe"
foreach ($Executable in @($RunUAT, $EditorCmd, $Editor)) {
    if (-not (Test-Path -LiteralPath $Executable -PathType Leaf)) { Write-Error "Eseguibile Unreal mancante: $Executable"; exit 4 }
}

$LogDirectory = Join-Path $RepositoryRoot "Saved/Logs"
New-Item -ItemType Directory -Force -Path $LogDirectory | Out-Null
$BuildLog = Join-Path $LogDirectory "Prompt29_Build.log"
$CoreLog = Join-Path $LogDirectory "Prompt29_Core.log"
$AssetLog = Join-Path $LogDirectory "Prompt29_LocalDecorationAssets.log"
$AuditLog = Join-Path $LogDirectory "Prompt29_AssetAudit.log"
$StaticLog = Join-Path $LogDirectory "Prompt29_StaticValidation.log"
$AutomationLog = Join-Path $LogDirectory "Prompt29_Automation.log"
$AutomationEditorLog = Join-Path $LogDirectory "Prompt29_Automation_Editor.log"
$PreviewLog = Join-Path $LogDirectory "Prompt29_Preview.log"
$PreviewEditorLog = Join-Path $LogDirectory "Prompt29_Preview_Editor.log"

$ParseErrors = $null
$ParseTokens = $null
[System.Management.Automation.Language.Parser]::ParseFile($PSCommandPath, [ref]$ParseTokens, [ref]$ParseErrors) | Out-Null
if ($ParseErrors.Count -gt 0) { $ParseErrors | Format-List; exit 5 }

$CMake = (Get-Command cmake -ErrorAction SilentlyContinue).Source
if (-not $CMake) {
    $CMake = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio/2022/BuildTools/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe"
}
$Ninja = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio/2022/BuildTools/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe"
$VsDevCmd = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio/2022/BuildTools/Common7/Tools/VsDevCmd.bat"
$CTest = Join-Path (Split-Path -Parent $CMake) "ctest.exe"
foreach ($Tool in @($CMake, $CTest, $Ninja, $VsDevCmd)) {
    if (-not (Test-Path -LiteralPath $Tool -PathType Leaf)) { Write-Error "Tool C++ mancante: $Tool"; exit 6 }
}

foreach ($Configuration in @(
    @{ Name = "Debug"; Directory = "build-local"; Sanitizers = "OFF" },
    @{ Name = "Release"; Directory = "build-local-release"; Sanitizers = "OFF" },
    @{ Name = "Debug"; Directory = "build-local-sanitize"; Sanitizers = "ON" }
)) {
    $BuildDirectory = Join-Path $RepositoryRoot $Configuration.Directory
    $CoreCommand = 'call "' + $VsDevCmd + '" -no_logo'
    $CoreCommand += ' && "' + $CMake + '" -S "' + $RepositoryRoot + '" -B "' + $BuildDirectory + '" -G Ninja -DCMAKE_MAKE_PROGRAM="' + $Ninja + '"'
    $CoreCommand += ' -DCMAKE_BUILD_TYPE=' + $Configuration.Name + ' -DROMA_AETERNA_ENABLE_SANITIZERS=' + $Configuration.Sanitizers
    $CoreCommand += ' && "' + $CMake + '" --build "' + $BuildDirectory + '" --parallel'
    $CoreCommand += ' && "' + $CTest + '" --test-dir "' + $BuildDirectory + '" --output-on-failure'
    cmd.exe /d /s /c $CoreCommand *>&1 | Tee-Object -FilePath $CoreLog -Append
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}

$BuildArguments = @(
    "BuildTarget", "-project=$ResolvedProjectPath", "-target=RomaAeternaEditor",
    "-platform=Win64", "-configuration=Development", "-notools", "-WaitMutex", "-utf8output"
)
& $RunUAT @BuildArguments *>&1 | Tee-Object -FilePath $BuildLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

if (-not $SkipLocalAssets) {
    $DecorationScript = Join-Path $PSScriptRoot "CreateRomanDecorationAssets.py"
    & $EditorCmd $ResolvedProjectPath "-run=pythonscript" "-script=$DecorationScript" "-unattended" "-nop4" "-nosplash" "-NullRHI" "-NoSound" "-log=Prompt29_LocalDecorationAssets_Editor.log" *>&1 | Tee-Object -FilePath $AssetLog
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $AssetEditorLog = Join-Path $LogDirectory "Prompt29_LocalDecorationAssets_Editor.log"
    if (-not (Select-String -LiteralPath $AssetEditorLog -SimpleMatch "ROMAN_DECORATION_LOCAL_ASSETS_CREATED" -Quiet)) { Write-Error "Firma creazione asset decorativi assente"; exit 7 }
}

& python (Join-Path $PSScriptRoot "AuditRomanAssets.py") --decoration-audit --interior-audit *>&1 | Tee-Object -FilePath $AuditLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& python (Join-Path $PSScriptRoot "ValidateRomanModularFoundation.py") *>&1 | Tee-Object -FilePath $StaticLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
$PythonExecutable = (Get-Command python -ErrorAction Stop).Source
$PythonTestStdOut = Join-Path $LogDirectory "Prompt29_PythonTests_stdout.log"
$PythonTestStdErr = Join-Path $LogDirectory "Prompt29_PythonTests_stderr.log"
Remove-Item -LiteralPath $PythonTestStdOut, $PythonTestStdErr -Force -ErrorAction SilentlyContinue
$PythonTestProcess = Start-Process -FilePath $PythonExecutable -ArgumentList @(
    "-m", "unittest", "discover",
    "-s", "`"$(Join-Path $PSScriptRoot 'tests')`"",
    "-p", "`"test_*.py`""
) -NoNewWindow -Wait -PassThru -RedirectStandardOutput $PythonTestStdOut -RedirectStandardError $PythonTestStdErr
Get-Content -LiteralPath $PythonTestStdOut, $PythonTestStdErr | Tee-Object -FilePath $StaticLog -Append
if ($PythonTestProcess.ExitCode -ne 0) { exit $PythonTestProcess.ExitCode }

$TrackedExternal = @(git -C $RepositoryRoot ls-files -- "Content/ThirdParty" "Content/LocalAssets" "Content/ImportedAssets")
if ($TrackedExternal.Count -gt 0) { Write-Error "Asset esterni tracciati: $($TrackedExternal -join ', ')"; exit 8 }
$StatusExternal = @(git -C $RepositoryRoot status --short --untracked-files=all -- "Content/ThirdParty" "Content/LocalAssets" "Content/ImportedAssets")
if ($StatusExternal.Count -gt 0) { Write-Error "Asset locali non ignorati: $($StatusExternal -join ', ')"; exit 9 }
$Attributes = Join-Path $RepositoryRoot ".gitattributes"
if ((Test-Path -LiteralPath $Attributes) -and (Select-String -LiteralPath $Attributes -SimpleMatch "filter=lfs" -Quiet)) { Write-Error "Git LFS rilevato"; exit 10 }
$ForbiddenPacks = @(Get-ChildItem -LiteralPath (Join-Path $RepositoryRoot "Content") -Recurse -File -ErrorAction SilentlyContinue | Where-Object { $_.FullName -match "Rome.?Empire.?Character|Roman.?Temple.?Ruins" })
if ($ForbiddenPacks.Count -gt 0) { Write-Error "Pack Fab rinviato rilevato"; exit 11 }
$ProtectedMaps = @(git -C $RepositoryRoot diff --name-only -- "Content/RA/Dev/Maps/TechnicalSandbox.umap")
if ($ProtectedMaps.Count -gt 0) { Write-Error "TechnicalSandbox.umap modificata"; exit 12 }

$AutomationArguments = @(
    $ResolvedProjectPath, "/Game/Maps/RomaAeternaVerticalSlice",
    "-ExecCmds=Automation RunTests RomaAeterna.Prompt29",
    "-TestExit=Automation Test Queue Empty", "-unattended", "-nop4", "-nosplash", "-NullRHI", "-NoSound",
    "-log=Prompt29_Automation_Editor.log"
)
& $EditorCmd @AutomationArguments *>&1 | Tee-Object -FilePath $AutomationLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
if (Select-String -LiteralPath $AutomationEditorLog -Pattern @("No automation tests matched", "0 tests performed", "Result={Fail}") -Quiet) { Write-Error "Automation Prompt 29 assente o fallita"; exit 13 }
$SuccessCount = @(Select-String -LiteralPath $AutomationEditorLog -SimpleMatch "Test Completed. Result={Success}").Count
if ($SuccessCount -lt 2) { Write-Error "Sono attesi due Automation Test Prompt 29, trovati $SuccessCount"; exit 14 }

if (-not $SkipLocalAssets) {
    $PreviewFile = Join-Path $RepositoryRoot "Content/LocalAssets/RomaAeterna/Maps/RomaAeternaDecorationPreview.umap"
    if (-not (Test-Path -LiteralPath $PreviewFile -PathType Leaf)) { Write-Error "Preview decorativa mancante"; exit 15 }
    $PreviewArguments = @(
        $ResolvedProjectPath, "/Game/LocalAssets/RomaAeterna/Maps/RomaAeternaDecorationPreview",
        "-ExecCmds=MAP CHECK,QUIT_EDITOR", "-unattended", "-nop4", "-nosplash", "-NoSound",
        "-log=Prompt29_Preview_Editor.log"
    )
    $QuotedPreviewArguments = @($PreviewArguments | ForEach-Object { if ($_ -match "\s") { '"' + $_.Replace('"', '\"') + '"' } else { $_ } })
    $PreviewProcess = Start-Process -FilePath $Editor -ArgumentList $QuotedPreviewArguments -Wait -PassThru -WindowStyle Hidden
    "ExitCode=$($PreviewProcess.ExitCode)" | Set-Content -LiteralPath $PreviewLog
    if ($PreviewProcess.ExitCode -ne 0) { exit $PreviewProcess.ExitCode }
    if (-not (Select-String -LiteralPath $PreviewEditorLog -Pattern "MapCheck:.*0 (Error|Errori).*0 (Warning|Avvisi)" -Quiet)) { Write-Error "Map Check preview non pulito"; exit 16 }
}

Write-Host "CORE_CPP_DEBUG_TESTS_PASSED"
Write-Host "CORE_CPP_RELEASE_TESTS_PASSED"
Write-Host "CORE_CPP_SANITIZERS_PASSED"
Write-Host "DECORATED_INTERIORS_ASSET_AUDIT_PASSED"
Write-Host "DECORATED_INTERIORS_STATIC_CHECKS_PASSED"
Write-Host "UNREAL_BUILD_PASSED"
Write-Host "UNREAL_AUTOMATION_PASSED"
Write-Host "INTERIOR_TRAVERSAL_AUTOMATION_PASSED"
Write-Host "MANUAL_GAMEPLAY_TRAVERSAL_REQUIRED"
if (-not $SkipLocalAssets) {
    Write-Host "LOCAL_DECORATION_TECHNICAL_PREVIEW_PASSED"
    Write-Host "MANUAL_DECORATION_VISUAL_REVIEW_REQUIRED"
}
Write-Host "EXTERNAL_ASSETS_NOT_VERSIONED"
Write-Host "GIT_LFS_NOT_USED"

if ($OpenEditorAfterTests) {
    $EditorArguments = @($ResolvedProjectPath, "/Game/Maps/RomaAeternaVerticalSlice", "-nop4", "-log=Prompt29_ManualPlaytest_Editor.log")
    $QuotedEditorArguments = @($EditorArguments | ForEach-Object { if ($_ -match "\s") { '"' + $_.Replace('"', '\"') + '"' } else { $_ } })
    if ($KeepEditorOpen) {
        Start-Process -FilePath $Editor -ArgumentList $QuotedEditorArguments | Out-Null
        Write-Host "EDITOR_OPENED_FOR_MANUAL_PLAYTEST"
        Write-Host "Premere Play. Controlli: WASD, mouse, Space, Shift, E, F7-F12."
    } else {
        $Process = Start-Process -FilePath $Editor -ArgumentList $QuotedEditorArguments -PassThru
        Write-Host "Editor avviato con PID $($Process.Id)."
    }
}
exit 0
