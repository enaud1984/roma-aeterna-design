param([string]$EngineRoot)
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
if (!(Test-Path $UBT)) { throw "UnrealBuildTool non trovato: $UBT" }
$LogDir = Join-Path $ProjectRoot "Saved\Logs"
New-Item -ItemType Directory -Force -Path $LogDir | Out-Null
$Log = Join-Path $LogDir "RomanModularFoundationBuild.log"
$Args = @("RomaAeternaEditor", "Win64", "Development", "-Project=`"$ProjectFile`"", "-WaitMutex", "-FromMsBuild")
Write-Host "Comando:" $UBT ($Args -join " ")
& $UBT @Args 2>&1 | Tee-Object -FilePath $Log
if ($LASTEXITCODE -ne 0) { throw "Compilazione fallita. Exit code: $LASTEXITCODE. Log: $Log" }
Write-Host "Compilazione completata da UnrealBuildTool. Log: $Log"
