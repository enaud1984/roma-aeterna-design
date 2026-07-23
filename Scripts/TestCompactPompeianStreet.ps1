param(
    [string]$EngineRoot = "",
    [string]$ProjectPath = "RomaAeterna.uproject",
    [switch]$OpenEditorAfterTests
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
if (@(Get-Process UnrealEditor, UnrealEditor-Cmd, LiveCodingConsole -ErrorAction SilentlyContinue).Count -gt 0) {
    Write-Error "Chiudere Unreal Editor e Live Coding prima del gate Prompt 30."; exit 5
}

$LogDirectory = Join-Path $RepositoryRoot "Saved/Logs"
New-Item -ItemType Directory -Force -Path $LogDirectory | Out-Null
$AuditLog = Join-Path $LogDirectory "Prompt30_Audit.log"
$StaticLog = Join-Path $LogDirectory "Prompt30_Static.log"
$CoreLog = Join-Path $LogDirectory "Prompt30_Core.log"
$BuildLog = Join-Path $LogDirectory "Prompt30_Build.log"
$MapGenerationLog = Join-Path $LogDirectory "Prompt30_MapGeneration.log"
$AutomationLog = Join-Path $LogDirectory "Prompt30_Automation.log"
$AutomationEditorLog = Join-Path $LogDirectory "Prompt30_Automation_Editor.log"
$MapCheckLog = Join-Path $LogDirectory "Prompt30_MapCheck_Editor.log"
$PieLog = Join-Path $LogDirectory "Prompt30_PIE_Editor.log"

$ParseErrors = $null
$ParseTokens = $null
[System.Management.Automation.Language.Parser]::ParseFile($PSCommandPath, [ref]$ParseTokens, [ref]$ParseErrors) | Out-Null
if ($ParseErrors.Count -gt 0) { $ParseErrors | Format-List; exit 6 }

& python (Join-Path $PSScriptRoot "AuditRomanAssets.py") --compact-urban-audit *>&1 | Tee-Object -FilePath $AuditLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& python (Join-Path $PSScriptRoot "ValidateRomanModularFoundation.py") *>&1 | Tee-Object -FilePath $StaticLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
$PythonExecutable = (Get-Command python -ErrorAction Stop).Source
$PythonTestDirectory = Join-Path $PSScriptRoot "tests"
$PythonTestCommand = '"' + $PythonExecutable + '" -m unittest discover -s "' + $PythonTestDirectory + '" -p "test_*.py" 2>&1'
cmd.exe /d /s /c $PythonTestCommand | Tee-Object -FilePath $StaticLog -Append
$PythonTestExitCode = $LASTEXITCODE
if ($PythonTestExitCode -ne 0) { exit $PythonTestExitCode }

$CMake = (Get-Command cmake -ErrorAction SilentlyContinue).Source
if (-not $CMake) { $CMake = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio/2022/BuildTools/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" }
$Ninja = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio/2022/BuildTools/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe"
$VsDevCmd = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio/2022/BuildTools/Common7/Tools/VsDevCmd.bat"
$CTest = Join-Path (Split-Path -Parent $CMake) "ctest.exe"
foreach ($Tool in @($CMake, $CTest, $Ninja, $VsDevCmd)) {
    if (-not (Test-Path -LiteralPath $Tool -PathType Leaf)) { Write-Error "Tool C++ mancante: $Tool"; exit 7 }
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

$MapScript = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot "CreateRomaAeternaVerticalSlice.py")).Path
& $EditorCmd $ResolvedProjectPath "-run=pythonscript" "-script=$MapScript" "-unattended" "-nop4" "-nosplash" "-NullRHI" "-NoSound" "-NoLiveCoding" "-log=Prompt30_MapGeneration_Editor.log" *>&1 | Tee-Object -FilePath $MapGenerationLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

$AutomationArguments = @(
    $ResolvedProjectPath, "/Game/Maps/RomaAeternaVerticalSlice",
    "-ExecCmds=Automation RunTests RomaAeterna.Prompt30",
    "-TestExit=Automation Test Queue Empty", "-unattended", "-nop4", "-nosplash", "-NullRHI", "-NoSound", "-NoLiveCoding",
    "-log=Prompt30_Automation_Editor.log"
)
& $EditorCmd @AutomationArguments *>&1 | Tee-Object -FilePath $AutomationLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
if (Select-String -LiteralPath $AutomationEditorLog -Pattern @("No automation tests matched", "0 tests performed", "Result={Fail}") -Quiet) {
    Write-Error "Automation Prompt 30 assente o fallita"; exit 8
}
$SuccessCount = @(Select-String -LiteralPath $AutomationEditorLog -SimpleMatch "Test Completed. Result={Success}").Count
if ($SuccessCount -lt 3) { Write-Error "Sono attesi tre Automation Test Prompt 30, trovati $SuccessCount"; exit 9 }

& $EditorCmd $ResolvedProjectPath "/Game/Maps/RomaAeternaVerticalSlice" "-ExecCmds=MAP CHECK,QUIT_EDITOR" "-unattended" "-nop4" "-nosplash" "-NullRHI" "-NoSound" "-NoLiveCoding" "-log=Prompt30_MapCheck_Editor.log"
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
if (-not (Select-String -LiteralPath $MapCheckLog -Pattern "MapCheck:.*0 (Error|Errori).*0 (Warning|Avvisi)" -Quiet)) {
    Write-Error "Map Check Prompt 30 non pulito"; exit 10
}

$PieScript = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot "RunCompactPompeianStreetPIE.py")).Path.Replace("\", "/")
$PieCommandLine = '"' + $ResolvedProjectPath + '" "-ExecCmds=py ' + $PieScript + '" -nop4 -nosplash -NoSound -NoLiveCoding -log=Prompt30_PIE_Editor.log'
$PieProcess = Start-Process -FilePath $Editor -ArgumentList $PieCommandLine -Wait -PassThru -WindowStyle Hidden
if ($PieProcess.ExitCode -ne 0) { exit $PieProcess.ExitCode }
foreach ($Marker in @(
    "PROMPT30_REAL_PIE_STARTED", "PROMPT30_PLAYER_POSSESSED", "PROMPT30_WASD_MOVEMENT_VALIDATED",
    "PROMPT30_F5_REBUILD_EXECUTED", "PROMPT30_F7_FALLBACK_EXECUTED", "PROMPT30_F7_LOCAL_EXECUTED",
    "PROMPT30_F9_CAMERA_TOGGLE_VALIDATED", "PROMPT30_F10_ROOFS_HIDDEN", "PROMPT30_F10_ROOFS_VISIBLE",
    "PROMPT30_F11_DECORATION_TOGGLE_VALIDATED", "PROMPT30_REAL_PIE_COMPLETED"
)) {
    if (-not (Select-String -LiteralPath $PieLog -SimpleMatch $Marker -Quiet)) { Write-Error "Verifica PIE mancante: $Marker"; exit 11 }
}
$ScreenshotDirectory = Join-Path $RepositoryRoot "Saved/Diagnostics/Prompt30/FinalScreenshots"
if (@(Get-ChildItem -LiteralPath $ScreenshotDirectory -Filter "*.png" -File -ErrorAction SilentlyContinue).Count -lt 8) {
    Write-Error "Screenshot Prompt 30 insufficienti"; exit 12
}

$TrackedExternal = @(git -C $RepositoryRoot ls-files -- "Content/ThirdParty" "Content/LocalAssets" "Content/ImportedAssets")
if ($TrackedExternal.Count -gt 0) { Write-Error "Asset esterni tracciati: $($TrackedExternal -join ', ')"; exit 13 }
if ((git -C $RepositoryRoot diff --name-only -- "Content/RA/Dev/Maps/TechnicalSandbox.umap").Count -gt 0) {
    Write-Error "TechnicalSandbox modificata"; exit 14
}

Write-Host "CORE_CPP_DEBUG_TESTS_PASSED"
Write-Host "CORE_CPP_RELEASE_TESTS_PASSED"
Write-Host "CORE_CPP_SANITIZERS_PASSED"
Write-Host "COMPACT_POMPEIAN_STREET_AUDIT_PASSED"
Write-Host "COMPACT_POMPEIAN_STREET_STATIC_CHECKS_PASSED"
Write-Host "UNREAL_BUILD_PASSED"
Write-Host "COMPACT_POMPEIAN_STREET_AUTOMATION_PASSED"
Write-Host "PROMPT30_REAL_PIE_PASSED"
Write-Host "LOCAL_ASSET_ONLY_STRATEGY"
Write-Host "EXTERNAL_ASSETS_NOT_VERSIONED"

if ($OpenEditorAfterTests) {
    Start-Process -FilePath $Editor -ArgumentList @($ResolvedProjectPath, "/Game/Maps/RomaAeternaVerticalSlice", "-nop4", "-NoLiveCoding", "-log=Prompt30_ManualReview_Editor.log") | Out-Null
    Write-Host "EDITOR_OPENED_FOR_PROMPT30_REVIEW"
}
exit 0
