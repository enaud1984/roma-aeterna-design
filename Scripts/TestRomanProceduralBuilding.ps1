param(
    [string]$EngineRoot
)

$ErrorActionPreference = "Stop"
$ProjectRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
$ProjectFile = Join-Path $ProjectRoot "RomaAeterna.uproject"
if (!(Test-Path $ProjectFile)) { throw "RomaAeterna.uproject non trovato." }

if (-not $EngineRoot) {
    $Candidates = @("C:\Program Files\Epic Games\UE_5.8", "C:\Program Files\Epic Games\UE_5.8EA")
    $EngineRoot = ($Candidates | Where-Object { Test-Path $_ } | Select-Object -First 1)
}
if (-not $EngineRoot) { throw "Unreal Engine 5.8 non trovato. Passare -EngineRoot." }

$UBT = Join-Path $EngineRoot "Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
$Editor = Join-Path $EngineRoot "Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
if (!(Test-Path $UBT)) { throw "UnrealBuildTool non trovato: $UBT" }
if (!(Test-Path $Editor)) { throw "UnrealEditor-Cmd non trovato: $Editor" }

$LogDir = Join-Path $ProjectRoot "Saved\Logs"
New-Item -ItemType Directory -Force -Path $LogDir | Out-Null
$BuildLog = Join-Path $LogDir "RomanProceduralBuildingBuild.log"
$TestLog = Join-Path $LogDir "RomanProceduralBuildingAutomation.log"

$BuildArgs = @("RomaAeternaEditor", "Win64", "Development", "-Project=`"$ProjectFile`"", "-WaitMutex", "-FromMsBuild")
Write-Host "Build:" $UBT ($BuildArgs -join " ")
& $UBT @BuildArgs 2>&1 | Tee-Object -FilePath $BuildLog
if ($LASTEXITCODE -ne 0) { throw "Build fallita. Exit code: $LASTEXITCODE. Log: $BuildLog" }

$Automation = "RomaAeterna.ModularFoundation"
$EditorArgs = @("`"$ProjectFile`"", "-unattended", "-nop4", "-nosplash", "-nullrhi", "-ExecCmds=`"Automation RunTests $Automation; Quit`"", "-log=`"$TestLog`"")
Write-Host "Automation:" $Editor ($EditorArgs -join " ")
& $Editor @EditorArgs
if ($LASTEXITCODE -ne 0) { throw "Automation Tests falliti. Exit code: $LASTEXITCODE. Log: $TestLog" }

Write-Host "Automation Tests completati. PIE non eseguito e non dichiarato superato. Log: $TestLog"
