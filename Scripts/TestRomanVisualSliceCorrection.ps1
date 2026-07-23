param(
    [string]$EngineRoot = "",
    [string]$ProjectPath = "RomaAeterna.uproject",
    [switch]$OpenEditorAfterTests,
    [switch]$KeepEditorOpen,
    [switch]$SkipLocalAssets
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
$InitialUnrealProcesses = @(Get-Process UnrealEditor, UnrealEditor-Cmd, LiveCodingConsole -ErrorAction SilentlyContinue)
if ($InitialUnrealProcesses.Count -gt 0) {
    Write-Error "Chiudere Unreal Editor e Live Coding prima del gate Prompt 29-BIS."; exit 4
}

$LogDirectory = Join-Path $RepositoryRoot "Saved/Logs"
New-Item -ItemType Directory -Force -Path $LogDirectory | Out-Null
$CoreLog = Join-Path $LogDirectory "Prompt29Bis_Core.log"
$AuditLog = Join-Path $LogDirectory "Prompt29Bis_Audit.log"
$StaticLog = Join-Path $LogDirectory "Prompt29Bis_Static.log"
$BuildLog = Join-Path $LogDirectory "Prompt29Bis_Build.log"
$AutomationLog = Join-Path $LogDirectory "Prompt29Bis_Automation.log"
$AutomationEditorLog = Join-Path $LogDirectory "Prompt29Bis_Automation_Editor.log"
$MapCheckLog = Join-Path $LogDirectory "Prompt29Bis_MapCheck_Editor.log"
$PieLog = Join-Path $LogDirectory "Prompt29Bis_VisualPIE_Editor.log"

$ParseErrors = $null
$ParseTokens = $null
[System.Management.Automation.Language.Parser]::ParseFile($PSCommandPath, [ref]$ParseTokens, [ref]$ParseErrors) | Out-Null
if ($ParseErrors.Count -gt 0) { $ParseErrors | Format-List; exit 5 }

& python (Join-Path $PSScriptRoot "AuditRomanAssets.py") --visual-slice-audit --material-runtime-audit --transform-audit *>&1 | Tee-Object -FilePath $AuditLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& python (Join-Path $PSScriptRoot "ValidateRomanModularFoundation.py") *>&1 | Tee-Object -FilePath $StaticLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
$PythonTestDirectory = Join-Path $PSScriptRoot "tests"
$PythonExecutable = (Get-Command python -ErrorAction Stop).Source
$PythonTestCommand = '"' + $PythonExecutable + '" -m unittest discover -s "' + $PythonTestDirectory + '" -p "test_*.py" 2>&1'
cmd.exe /d /s /c $PythonTestCommand | Tee-Object -FilePath $StaticLog -Append
$PythonTestExitCode = $LASTEXITCODE
if ($PythonTestExitCode -ne 0) { exit $PythonTestExitCode }

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

if (-not $SkipLocalAssets) {
    foreach ($LocalScriptName in @("ImportRomanAssetBatch1.py", "CreateRomanDecorationAssets.py")) {
        $LocalScript = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot $LocalScriptName)).Path
        & $EditorCmd $ResolvedProjectPath "-run=pythonscript" "-script=$LocalScript" "-unattended" "-nop4" "-nosplash" "-NullRHI" "-NoSound" "-NoLiveCoding" "-log=Prompt29Bis_$($LocalScriptName.Replace('.py', ''))_Editor.log"
        if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    }
}

$ResidualCommandletProcesses = @(Get-Process UnrealEditor, UnrealEditor-Cmd, LiveCodingConsole -ErrorAction SilentlyContinue)
if ($ResidualCommandletProcesses.Count -gt 0) {
    $ResidualCommandletProcesses | Stop-Process -Force
    Start-Sleep -Seconds 2
}

$BuildArguments = @(
    "BuildTarget", "-project=$ResolvedProjectPath", "-target=RomaAeternaEditor",
    "-platform=Win64", "-configuration=Development", "-notools", "-WaitMutex", "-utf8output"
)
& $RunUAT @BuildArguments *>&1 | Tee-Object -FilePath $BuildLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

$TrackedExternal = @(git -C $RepositoryRoot ls-files -- "Content/ThirdParty" "Content/LocalAssets" "Content/ImportedAssets")
if ($TrackedExternal.Count -gt 0) { Write-Error "Asset esterni tracciati: $($TrackedExternal -join ', ')"; exit 7 }
$StatusExternal = @(git -C $RepositoryRoot status --short --untracked-files=all -- "Content/ThirdParty" "Content/LocalAssets" "Content/ImportedAssets")
if ($StatusExternal.Count -gt 0) { Write-Error "Asset locali non ignorati: $($StatusExternal -join ', ')"; exit 8 }
$Attributes = Join-Path $RepositoryRoot ".gitattributes"
if ((Test-Path -LiteralPath $Attributes) -and (Select-String -LiteralPath $Attributes -SimpleMatch "filter=lfs" -Quiet)) { Write-Error "Git LFS rilevato"; exit 9 }
if ((git -C $RepositoryRoot diff --name-only -- "Content/RA/Dev/Maps/TechnicalSandbox.umap").Count -gt 0) { Write-Error "TechnicalSandbox modificata"; exit 10 }
$Forbidden = @(Get-ChildItem -LiteralPath (Join-Path $RepositoryRoot "Content") -Recurse -File -ErrorAction SilentlyContinue | Where-Object { $_.FullName -match "Rome.?Empire.?Character|Roman.?Temple.?Ruins" })
if ($Forbidden.Count -gt 0) { Write-Error "Pack Fab rinviato rilevato"; exit 11 }

$AutomationArguments = @(
    $ResolvedProjectPath, "/Game/Maps/RomaAeternaVerticalSlice",
    "-ExecCmds=Automation RunTests RomaAeterna.Prompt29Bis",
    "-TestExit=Automation Test Queue Empty", "-unattended", "-nop4", "-nosplash", "-NullRHI", "-NoSound", "-NoLiveCoding",
    "-log=Prompt29Bis_Automation_Editor.log"
)
& $EditorCmd @AutomationArguments *>&1 | Tee-Object -FilePath $AutomationLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
if (Select-String -LiteralPath $AutomationEditorLog -Pattern @("No automation tests matched", "0 tests performed", "Result={Fail}") -Quiet) { Write-Error "Automation Prompt 29-BIS assente o fallita"; exit 12 }
$SuccessCount = @(Select-String -LiteralPath $AutomationEditorLog -SimpleMatch "Test Completed. Result={Success}").Count
if ($SuccessCount -lt 7) { Write-Error "Sono attesi sette Automation Test Prompt 29-BIS, trovati $SuccessCount"; exit 13 }

& $EditorCmd $ResolvedProjectPath "/Game/Maps/RomaAeternaVerticalSlice" "-ExecCmds=MAP CHECK,QUIT_EDITOR" "-unattended" "-nop4" "-nosplash" "-NullRHI" "-NoSound" "-NoLiveCoding" "-log=Prompt29Bis_MapCheck_Editor.log"
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
if (-not (Select-String -LiteralPath $MapCheckLog -Pattern "MapCheck:.*0 (Error|Errori).*0 (Warning|Avvisi)" -Quiet)) { Write-Error "Map Check Prompt 29-BIS non pulito"; exit 14 }

$PieScript = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot "RunRomanVisualSlicePIE.py")).Path
$PieScriptForward = $PieScript.Replace("\", "/")
$PieCommandLine = '"' + $ResolvedProjectPath + '" "-ExecCmds=py ' + $PieScriptForward + '" -nop4 -nosplash -NoSound -NoLiveCoding -log=Prompt29Bis_VisualPIE_Editor.log'
$PieProcess = Start-Process -FilePath $Editor -ArgumentList $PieCommandLine -Wait -PassThru -WindowStyle Hidden
if ($PieProcess.ExitCode -ne 0) { exit $PieProcess.ExitCode }
foreach ($Marker in @(
    "PROMPT29BIS_REAL_PIE_STARTED", "PROMPT29BIS_PLAYER_POSSESSED", "PROMPT29BIS_F5_REBUILD_EXECUTED",
    "PROMPT29BIS_F7_FALLBACK_EXECUTED", "PROMPT29BIS_F7_LOCAL_EXECUTED",
    "PROMPT29BIS_F10_HIDE_EXECUTED", "PROMPT29BIS_F10_SHOW_EXECUTED",
    "PROMPT29BIS_F11_FALLBACK_EXECUTED", "PROMPT29BIS_F11_DECORATIONS_EXECUTED",
    "PROMPT29BIS_F9_FIRST_PERSON_EXECUTED",
    "PROMPT29BIS_REAL_PIE_COMPLETED"
)) {
    if (-not (Select-String -LiteralPath $PieLog -SimpleMatch $Marker -Quiet)) { Write-Error "Verifica PIE mancante: $Marker"; exit 15 }
}
$ScreenshotDirectory = Join-Path $RepositoryRoot "Saved/Diagnostics/Prompt29Bis/FinalScreenshots"
if (@(Get-ChildItem -LiteralPath $ScreenshotDirectory -Filter "*.png" -File -ErrorAction SilentlyContinue).Count -lt 6) {
    Write-Error "Screenshot PIE insufficienti"; exit 16
}

Write-Host "CORE_CPP_DEBUG_TESTS_PASSED"
Write-Host "CORE_CPP_RELEASE_TESTS_PASSED"
Write-Host "CORE_CPP_SANITIZERS_PASSED"
Write-Host "VISUAL_SLICE_CORRECTION_AUDIT_PASSED"
Write-Host "VISUAL_SLICE_CORRECTION_STATIC_CHECKS_PASSED"
Write-Host "UNREAL_BUILD_PASSED"
Write-Host "UNREAL_AUTOMATION_PASSED"
Write-Host "MAP_CHECK_PASSED"
Write-Host "PLAYER_SPAWN_VALIDATED"
Write-Host "BUILDING_TRANSFORMS_VALIDATED"
Write-Host "RUNTIME_MATERIAL_BINDINGS_VALIDATED"
Write-Host "F5_REBUILD_VALIDATED"
Write-Host "F7_MATERIAL_TOGGLE_VALIDATED"
Write-Host "F10_ROOF_TOGGLE_VALIDATED"
Write-Host "LUMEN_CONFIGURATION_VALIDATED"
Write-Host "EXTERNAL_ASSETS_NOT_VERSIONED"
Write-Host "GIT_LFS_NOT_USED"

if ($OpenEditorAfterTests) {
    $EditorArguments = @($ResolvedProjectPath, "/Game/Maps/RomaAeternaVerticalSlice", "-nop4", "-log=Prompt29Bis_ManualPlaytest_Editor.log")
    $QuotedEditorArguments = @($EditorArguments | ForEach-Object { if ($_ -match "\s") { '"' + $_.Replace('"', '\"') + '"' } else { $_ } })
    if ($KeepEditorOpen) {
        Start-Process -FilePath $Editor -ArgumentList $QuotedEditorArguments | Out-Null
        Write-Host "EDITOR_OPENED_FOR_MANUAL_PLAYTEST"
    } else {
        Start-Process -FilePath $Editor -ArgumentList $QuotedEditorArguments | Out-Null
    }
}
exit 0
