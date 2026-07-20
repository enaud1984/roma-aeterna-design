param(
    [string]$EngineRoot = $env:UE_5_8_ROOT
)

$ErrorActionPreference = 'Stop'
if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $EngineRoot = 'C:\Program Files\Epic Games\UE_5.8'
}

$project = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot '..\RomaAeterna.uproject')).Path
$build = Join-Path $EngineRoot 'Engine\Build\BatchFiles\Build.bat'
if (-not (Test-Path -LiteralPath $build)) {
    throw "Build.bat non trovato: $build"
}

& $build RomaAeternaEditor Win64 Development $project -WaitMutex -NoHotReloadFromIDE
if ($LASTEXITCODE -ne 0) {
    throw "Build RomaAeternaEditor fallita con exit code $LASTEXITCODE"
}
