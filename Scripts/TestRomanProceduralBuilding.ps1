param(
    [string]$EngineRoot = ""
)
$ErrorActionPreference = "Stop"
$ProjectRoot = Split-Path -Parent $PSScriptRoot
$ProjectFile = Join-Path $ProjectRoot "RomaAeterna.uproject"
$LogDir = Join-Path $ProjectRoot "Saved\Logs"
New-Item -ItemType Directory -Force -Path $LogDir | Out-Null

if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $Candidates = @(
        "C:\Program Files\Epic Games\UE_5.8",
        "C:\Program Files\Epic Games\UE_5.8EA"
    )
    foreach ($Candidate in $Candidates) { if (Test-Path $Candidate) { $EngineRoot = $Candidate; break } }
}
if ([string]::IsNullOrWhiteSpace($EngineRoot) -or -not (Test-Path $EngineRoot)) { throw "UE 5.8 non trovato: passare -EngineRoot." }

$EditorCmd = Join-Path $EngineRoot "Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
$BuildBat = Join-Path $EngineRoot "Engine\Build\BatchFiles\Build.bat"
if (-not (Test-Path $EditorCmd)) { throw "UnrealEditor-Cmd.exe non trovato: $EditorCmd" }
if (-not (Test-Path $BuildBat)) { throw "Build.bat non trovato: $BuildBat" }

& $BuildBat RomaAeternaEditor Win64 Development $ProjectFile -WaitMutex -NoHotReloadFromIDE | Tee-Object -FilePath (Join-Path $LogDir "RomanProceduralBuilding_Build.log")
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

$TestLog = Join-Path $LogDir "RomanProceduralBuilding_Automation.log"
& $EditorCmd $ProjectFile -ExecCmds="Automation RunTests RomaAeterna.Modular.PlaceholderRuntime; Quit" -unattended -nop4 -nosplash -NullRHI -NoSound -log=$TestLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
Write-Host "UNREAL_AUTOMATION_REQUIRED completabile localmente: lo script non dichiara PIE superato. Log: $LogDir"
