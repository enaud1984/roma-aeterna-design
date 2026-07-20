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
$report = Join-Path $repository 'Saved\Automation\PlayableFoundation'
$reportJson = Join-Path $report 'index.json'

if (-not (Test-Path -LiteralPath $editor)) {
    throw "UnrealEditor-Cmd.exe non trovato: $editor"
}

$runStarted = Get-Date
& $editor $project `
    '-ExecCmds=Automation RunTests RomaAeterna.PlayableFoundation; Quit' `
    '-TestExit=Automation Test Queue Empty' `
    "-ReportOutputPath=$report" `
    -unattended -nop4 -nosplash -NullRHI -NoSound

if ($LASTEXITCODE -ne 0) {
    throw "Test automatici PlayableFoundation falliti con exit code $LASTEXITCODE"
}

if (-not (Test-Path -LiteralPath $reportJson)) {
    throw "Report JSON dei test non generato: $reportJson"
}

$reportFile = Get-Item -LiteralPath $reportJson
if ($reportFile.LastWriteTime -lt $runStarted.AddSeconds(-2)) {
    throw "Il report dei test non appartiene all'esecuzione corrente: $reportJson"
}

$result = Get-Content -LiteralPath $reportJson -Raw | ConvertFrom-Json
if ($result.failed -ne 0 -or $result.notRun -ne 0 -or $result.inProcess -ne 0 -or $result.succeeded -lt 1) {
    throw "Suite PlayableFoundation non superata: succeeded=$($result.succeeded), failed=$($result.failed), notRun=$($result.notRun), inProcess=$($result.inProcess)"
}

Write-Host "PlayableFoundation tests succeeded: $($result.succeeded)/$($result.succeeded + $result.succeededWithWarnings + $result.failed + $result.notRun + $result.inProcess)"
