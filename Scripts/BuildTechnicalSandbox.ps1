param(
    [string]$EngineRoot = $env:UE_5_8_ROOT
)

$ErrorActionPreference = 'Stop'
if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $EngineRoot = 'C:\Program Files\Epic Games\UE_5.8'
}

$repository = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot '..')).Path
$project = Join-Path $repository 'RomaAeterna.uproject'
$editor = Join-Path $EngineRoot 'Engine\Binaries\Win64\UnrealEditor-Cmd.exe'
$generator = Join-Path $PSScriptRoot 'CreateTechnicalSandbox.py'
$validator = Join-Path $PSScriptRoot 'ValidatePlayableFoundation.py'

if (-not (Test-Path -LiteralPath $editor)) {
    throw "UnrealEditor-Cmd.exe non trovato: $editor"
}

& $editor $project -run=pythonscript "-script=$generator" -unattended -nop4 -nosplash -NullRHI -NoSound
if ($LASTEXITCODE -ne 0) {
    throw "Generazione TechnicalSandbox fallita con exit code $LASTEXITCODE"
}

& $editor $project -run=pythonscript "-script=$validator" -unattended -nop4 -nosplash -NullRHI -NoSound
if ($LASTEXITCODE -ne 0) {
    throw "Validazione TechnicalSandbox fallita con exit code $LASTEXITCODE"
}
