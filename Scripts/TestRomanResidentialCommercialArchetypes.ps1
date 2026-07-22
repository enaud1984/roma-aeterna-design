param(
    [string]$EngineRoot = "",
    [string]$ProjectPath = "RomaAeterna.uproject"
)
$ErrorActionPreference = "Stop"

$RepositoryRoot = Split-Path -Parent $PSScriptRoot
if (-not [System.IO.Path]::IsPathRooted($ProjectPath)) {
    $ProjectPath = Join-Path $RepositoryRoot $ProjectPath
}
if (-not (Test-Path -LiteralPath $ProjectPath -PathType Leaf)) {
    Write-Error "File di progetto Unreal non trovato: $ProjectPath"
    exit 2
}
$ResolvedProjectPath = (Resolve-Path -LiteralPath $ProjectPath).Path

$LogDir = Join-Path $RepositoryRoot "Saved/Logs"
New-Item -ItemType Directory -Force -Path $LogDir | Out-Null
if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $Candidates = @("C:/Program Files/Epic Games/UE_5.8", "C:/Program Files/Epic Games/UE_5.8EA")
    foreach ($Candidate in $Candidates) {
        if (Test-Path -LiteralPath $Candidate -PathType Container) {
            $EngineRoot = $Candidate
            break
        }
    }
}
if ([string]::IsNullOrWhiteSpace($EngineRoot) -or -not (Test-Path -LiteralPath $EngineRoot -PathType Container)) {
    Write-Error "UE 5.8 non trovato: usare -EngineRoot."
    exit 3
}
$ResolvedEngineRoot = (Resolve-Path -LiteralPath $EngineRoot).Path
$UAT = Join-Path $ResolvedEngineRoot "Engine/Build/BatchFiles/RunUAT.bat"
$Editor = Join-Path $ResolvedEngineRoot "Engine/Binaries/Win64/UnrealEditor-Cmd.exe"
if (-not (Test-Path -LiteralPath $UAT -PathType Leaf)) {
    Write-Error "RunUAT.bat non trovato: $UAT"
    exit 4
}
if (-not (Test-Path -LiteralPath $Editor -PathType Leaf)) {
    Write-Error "UnrealEditor-Cmd.exe non trovato: $Editor"
    exit 5
}

$BuildArguments = @(
    "BuildTarget"
    "-project=$ResolvedProjectPath"
    "-target=RomaAeternaEditor"
    "-platform=Win64"
    "-configuration=Development"
    "-notools"
    "-WaitMutex"
    "-utf8output"
)
& $UAT @BuildArguments *>&1 | Tee-Object (Join-Path $LogDir "Prompt23_Build.log")
$BuildExitCode = $LASTEXITCODE
if ($BuildExitCode -ne 0) { exit $BuildExitCode }

$Tests = "RomaAeterna.Prompt23.ResidentialCommercial"
$AutomationArguments = @(
    $ResolvedProjectPath
    "-ExecCmds=Automation RunTests $Tests"
    "-TestExit=Automation Test Queue Empty"
    "-unattended"
    "-nop4"
    "-nosplash"
    "-NullRHI"
    "-log=Prompt23_Automation_Editor.log"
)
& $Editor @AutomationArguments *>&1 | Tee-Object (Join-Path $LogDir "Prompt23_Automation.log")
$AutomationExitCode = $LASTEXITCODE
if ($AutomationExitCode -eq 0) {
    $EditorLog = Join-Path $LogDir "Prompt23_Automation_Editor.log"
    $InvalidAutomationResult = Select-String -LiteralPath $EditorLog -Pattern "No automation tests matched", "0 tests performed", "Automation Test Failed" -Quiet
    $SuccessfulTest = Select-String -LiteralPath $EditorLog -SimpleMatch "Test Completed. Result={Success}" -Quiet
    $PositiveTestCount = Select-String -LiteralPath $EditorLog -Pattern "Test Queue Empty [1-9][0-9]* tests performed" -Quiet
    if ($InvalidAutomationResult -or -not $SuccessfulTest -or -not $PositiveTestCount) {
        Write-Error "Gli Automation Tests del Prompt 23 non sono stati eseguiti o sono falliti. Consultare $EditorLog"
        exit 6
    }
}
exit $AutomationExitCode
