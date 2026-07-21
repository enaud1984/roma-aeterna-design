param(
    [string]$EngineRoot = "",
    [string]$ProjectPath = "RomaAeterna.uproject"
)

$ErrorActionPreference = "Stop"
$RepoRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $Candidates = @(
        "C:\Program Files\Epic Games\UE_5.8",
        "C:\Program Files\Epic Games\UE_5.8EA",
        "$env:ProgramFiles\Epic Games\UE_5.8"
    )
    foreach ($Candidate in $Candidates) {
        if ($Candidate -and (Test-Path $Candidate)) { $EngineRoot = $Candidate; break }
    }
}
if ([string]::IsNullOrWhiteSpace($EngineRoot) -or -not (Test-Path $EngineRoot)) {
    Write-Error "UE 5.8 non trovato. Passare -EngineRoot."
    exit 2
}
$ProjectFullPath = Join-Path $RepoRoot $ProjectPath
$EditorCmd = Join-Path $EngineRoot "Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
$BuildBat = Join-Path $EngineRoot "Engine\Build\BatchFiles\Build.bat"
$LogDir = Join-Path $RepoRoot "Saved\Logs"
New-Item -ItemType Directory -Force -Path $LogDir | Out-Null
$BuildLog = Join-Path $LogDir "RomanBuildingArchetypes_Build.log"
$TestLog = Join-Path $LogDir "RomanBuildingArchetypes_Automation.log"

& $BuildBat RomaAeternaEditor Win64 Development $ProjectFullPath -WaitMutex -NoHotReloadFromIDE *> $BuildLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

$Tests = "RomaAeterna.BuildingArchetypes"
& $EditorCmd $ProjectFullPath -unattended -nop4 -nosplash -NullRHI -ExecCmds="Automation RunTests $Tests; Quit" -log=$TestLog
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
Write-Host "LOCAL_UNREAL_TEST_REQUIRED completato localmente; nessuna verifica PIE dichiarata. Log: $TestLog"
