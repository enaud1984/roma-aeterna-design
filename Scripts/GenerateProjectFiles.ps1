param(
    [string]$EngineRoot = $env:UE_5_8_ROOT
)

$ErrorActionPreference = 'Stop'
if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $EngineRoot = 'C:\Program Files\Epic Games\UE_5.8'
}

$project = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot '..\RomaAeterna.uproject')).Path
$dotnet = Join-Path $EngineRoot 'Engine\Binaries\ThirdParty\DotNet\10.0\win-x64\dotnet.exe'
$ubt = Join-Path $EngineRoot 'Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll'
if (-not (Test-Path -LiteralPath $dotnet)) {
    throw "Runtime .NET incluso in Unreal Engine non trovato: $dotnet"
}
if (-not (Test-Path -LiteralPath $ubt)) {
    throw "UnrealBuildTool non trovato: $ubt"
}

$env:DOTNET_ROOT = Split-Path -Parent $dotnet

& $dotnet $ubt -Mode=GenerateProjectFiles "-Project=$project" -Game -Engine -Rider
if ($LASTEXITCODE -ne 0) {
    throw "Generazione Rider fallita con exit code $LASTEXITCODE"
}
