param(
    [string]$EngineRoot = "",
    [string]$ProjectPath = "RomaAeterna.uproject"
)
$ErrorActionPreference = "Stop"
$LogDir = Join-Path (Get-Location) "Saved/Logs"
New-Item -ItemType Directory -Force -Path $LogDir | Out-Null
if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $Candidates = @("C:/Program Files/Epic Games/UE_5.8", "C:/Program Files/Epic Games/UE_5.8EA")
    foreach ($Candidate in $Candidates) { if (Test-Path $Candidate) { $EngineRoot = $Candidate; break } }
}
if ([string]::IsNullOrWhiteSpace($EngineRoot) -or -not (Test-Path $EngineRoot)) { Write-Error "UE 5.8 non trovato: usare -EngineRoot."; exit 2 }
$UAT = Join-Path $EngineRoot "Engine/Build/BatchFiles/RunUAT.bat"
$Editor = Join-Path $EngineRoot "Engine/Binaries/Win64/UnrealEditor-Cmd.exe"
if (-not (Test-Path $UAT) -or -not (Test-Path $Editor)) { Write-Error "Installazione Unreal incompleta."; exit 3 }
& $UAT BuildCookRun -project=$ProjectPath -noP4 -build -target=RomaAeternaEditor -clientconfig=Development -utf8output *>&1 | Tee-Object (Join-Path $LogDir "Prompt23_Build.log")
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
$Tests = "RomaAeterna.Prompt23.ResidentialCommercial"
& $Editor $ProjectPath -ExecCmds="Automation RunTests $Tests; Quit" -unattended -nop4 -nosplash -NullRHI -log=Prompt23_Automation.log *>&1 | Tee-Object (Join-Path $LogDir "Prompt23_Automation.log")
exit $LASTEXITCODE
