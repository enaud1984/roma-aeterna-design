param(
    [string]$EngineRoot = "",
    [string]$ProjectPath = "RomaAeterna.uproject"
)

$ErrorActionPreference = "Stop"
$RepositoryRoot = Split-Path -Parent $PSScriptRoot
if (-not [IO.Path]::IsPathRooted($ProjectPath)) { $ProjectPath = Join-Path $RepositoryRoot $ProjectPath }
if (-not (Test-Path -LiteralPath $ProjectPath -PathType Leaf)) { Write-Error "File .uproject non trovato: $ProjectPath"; exit 2 }
$ResolvedProjectPath = (Resolve-Path -LiteralPath $ProjectPath).Path

if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $ProgramFilesPath = [Environment]::GetFolderPath("ProgramFiles")
    foreach ($EngineFolder in @("UE_5.8", "UE_5.8EA")) {
        $Candidate = Join-Path $ProgramFilesPath "Epic Games/$EngineFolder"
        if (Test-Path -LiteralPath $Candidate -PathType Container) { $EngineRoot = $Candidate; break }
    }
}
if ([string]::IsNullOrWhiteSpace($EngineRoot) -or -not (Test-Path -LiteralPath $EngineRoot -PathType Container)) { Write-Error "Unreal Engine 5.8 non trovato: specificare -EngineRoot."; exit 3 }
$ResolvedEngineRoot = (Resolve-Path -LiteralPath $EngineRoot).Path
$RunUAT = Join-Path $ResolvedEngineRoot "Engine/Build/BatchFiles/RunUAT.bat"
$EditorCmd = Join-Path $ResolvedEngineRoot "Engine/Binaries/Win64/UnrealEditor-Cmd.exe"
if (-not (Test-Path -LiteralPath $RunUAT -PathType Leaf)) { Write-Error "RunUAT.bat non trovato: $RunUAT"; exit 4 }
if (-not (Test-Path -LiteralPath $EditorCmd -PathType Leaf)) { Write-Error "UnrealEditor-Cmd.exe non trovato: $EditorCmd"; exit 5 }

$MapFile = Join-Path $RepositoryRoot "Content/Maps/RomaAeternaVerticalSlice.umap"
if (-not (Test-Path -LiteralPath $MapFile -PathType Leaf)) { Write-Error "Mappa consolidata non trovata: $MapFile"; exit 6 }
$LogDirectory = Join-Path $RepositoryRoot "Saved/Logs"
New-Item -ItemType Directory -Force -Path $LogDirectory | Out-Null
$BuildLog = Join-Path $LogDirectory "Prompt25_Build.log"
$AutomationLog = Join-Path $LogDirectory "Prompt25_Automation.log"
$EditorLogName = "Prompt25_Automation_Editor.log"
$EditorLog = Join-Path $LogDirectory $EditorLogName

$BuildArguments = @("BuildTarget", "-project=$ResolvedProjectPath", "-target=RomaAeternaEditor", "-platform=Win64", "-configuration=Development", "-notools", "-WaitMutex", "-utf8output")
& $RunUAT @BuildArguments *>&1 | Tee-Object -FilePath $BuildLog
$BuildExitCode = $LASTEXITCODE
if ($BuildExitCode -ne 0) { Write-Error "Build RomaAeternaEditor fallita. Log: $BuildLog"; exit $BuildExitCode }

$TestName = "RomaAeterna.Prompt25.VisualConsolidation"
$AutomationArguments = @(
    $ResolvedProjectPath,
    "/Game/Maps/RomaAeternaVerticalSlice",
    "-ExecCmds=MAP CHECK,Automation RunTests $TestName",
    "-TestExit=Automation Test Queue Empty",
    "-unattended", "-nop4", "-nosplash", "-NullRHI", "-NoSound", "-log=$EditorLogName"
)
& $EditorCmd @AutomationArguments *>&1 | Tee-Object -FilePath $AutomationLog
$AutomationExitCode = $LASTEXITCODE
if ($AutomationExitCode -ne 0) { Write-Error "Automation Test Prompt 25 fallito. Log: $EditorLog"; exit $AutomationExitCode }

$FailurePatterns = @("No automation tests matched", "0 tests performed", "Automation Test Failed", "Result={Fail}")
if (Select-String -LiteralPath $EditorLog -Pattern $FailurePatterns -Quiet) { Write-Error "Automation Test assente o fallito. Log: $EditorLog"; exit 7 }
$HasSuccess = Select-String -LiteralPath $EditorLog -SimpleMatch "Test Completed. Result={Success}" -Quiet
$HasExecutedTest = Select-String -LiteralPath $EditorLog -Pattern "Test Queue Empty [1-9][0-9]* tests performed" -Quiet
$HasCleanMapCheck = Select-String -LiteralPath $EditorLog -Pattern "MapCheck:.*(0 Errori, 0 Avvisi|0 errors, 0 warnings)" -Quiet
$HasLightingWarning = Select-String -LiteralPath $EditorLog -Pattern "Lighting needs to be rebuilt|ILLUMINAZIONE DEVE ESSERE RICREATA" -Quiet
if (-not $HasSuccess -or -not $HasExecutedTest) { Write-Error "Firma di successo Automation non trovata. Log: $EditorLog"; exit 8 }
if (-not $HasCleanMapCheck) { Write-Error "Map Check pulito non rilevato. Log: $EditorLog"; exit 9 }
if ($HasLightingWarning) { Write-Error "Rilevato warning di illuminazione da ricostruire. Log: $EditorLog"; exit 10 }

Write-Host "UNREAL_BUILD_PASSED"
Write-Host "UNREAL_AUTOMATION_PASSED"
Write-Host "DYNAMIC_LIGHTING_PASSED"
Write-Host "MAP_CHECK_PASSED"
Write-Host "MANUAL_PIE_VERIFICATION_REQUIRED"
Write-Host "Log build: $BuildLog"
Write-Host "Log Automation: $AutomationLog"
exit 0
