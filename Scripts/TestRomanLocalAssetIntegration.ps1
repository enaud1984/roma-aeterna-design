param(
    [string]$EngineRoot = "",
    [string]$ProjectPath = "RomaAeterna.uproject",
    [int]$Batch = 1,
    [switch]$SkipLocalAssets
)

$ErrorActionPreference = "Stop"
$RepositoryRoot = Split-Path -Parent $PSScriptRoot
if (-not [IO.Path]::IsPathRooted($ProjectPath)) { $ProjectPath = Join-Path $RepositoryRoot $ProjectPath }
if (-not (Test-Path -LiteralPath $ProjectPath -PathType Leaf)) { Write-Error "File .uproject non trovato: $ProjectPath"; exit 2 }
$ResolvedProjectPath = (Resolve-Path -LiteralPath $ProjectPath).Path

if ($Batch -ne 1) { Write-Error "Batch non supportato: $Batch"; exit 3 }
if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $ProgramFilesPath = [Environment]::GetFolderPath("ProgramFiles")
    foreach ($EngineFolder in @("UE_5.8", "UE_5.8EA")) {
        $Candidate = Join-Path $ProgramFilesPath "Epic Games/$EngineFolder"
        if (Test-Path -LiteralPath $Candidate -PathType Container) { $EngineRoot = $Candidate; break }
    }
}
if ([string]::IsNullOrWhiteSpace($EngineRoot) -or -not (Test-Path -LiteralPath $EngineRoot -PathType Container)) {
    Write-Error "Unreal Engine 5.8 non trovato: specificare -EngineRoot."
    exit 4
}
$ResolvedEngineRoot = (Resolve-Path -LiteralPath $EngineRoot).Path
$RunUAT = Join-Path $ResolvedEngineRoot "Engine/Build/BatchFiles/RunUAT.bat"
$EditorCmd = Join-Path $ResolvedEngineRoot "Engine/Binaries/Win64/UnrealEditor-Cmd.exe"
$Editor = Join-Path $ResolvedEngineRoot "Engine/Binaries/Win64/UnrealEditor.exe"
foreach ($Executable in @($RunUAT, $EditorCmd, $Editor)) {
    if (-not (Test-Path -LiteralPath $Executable -PathType Leaf)) { Write-Error "Eseguibile Unreal non trovato: $Executable"; exit 5 }
}

$LogDirectory = Join-Path $RepositoryRoot "Saved/Logs"
New-Item -ItemType Directory -Force -Path $LogDirectory | Out-Null
$BuildLog = Join-Path $LogDirectory "Prompt27_Build.log"
$ImportLog = Join-Path $LogDirectory "Prompt27_Import.log"
$AuditLog = Join-Path $LogDirectory "Prompt27_LocalAudit.log"
$StaticLog = Join-Path $LogDirectory "Prompt27_StaticValidation.log"
$AutomationLog = Join-Path $LogDirectory "Prompt27_Automation.log"
$AutomationEditorLogName = "Prompt27_Automation_Editor.log"
$AutomationEditorLog = Join-Path $LogDirectory $AutomationEditorLogName
$PreviewLog = Join-Path $LogDirectory "Prompt27_Preview.log"
$PreviewEditorLogName = "Prompt27_Preview_Editor.log"
$PreviewEditorLog = Join-Path $LogDirectory $PreviewEditorLogName
$ImportScript = Join-Path $PSScriptRoot "ImportRomanAssetBatch1.py"

Write-Host "Progetto: $ResolvedProjectPath"
Write-Host "RunUAT: $RunUAT"
Write-Host "Batch: $Batch"

$BuildArguments = @(
    "BuildTarget", "-project=$ResolvedProjectPath", "-target=RomaAeternaEditor",
    "-platform=Win64", "-configuration=Development", "-notools", "-WaitMutex", "-utf8output"
)
& $RunUAT @BuildArguments *>&1 | Tee-Object -FilePath $BuildLog
$BuildExitCode = $LASTEXITCODE
if ($BuildExitCode -ne 0) { Write-Error "Build RomaAeternaEditor fallita. Log: $BuildLog"; exit $BuildExitCode }

if (-not $SkipLocalAssets) {
    if (-not (Test-Path -LiteralPath $ImportScript -PathType Leaf)) { Write-Error "Script import mancante: $ImportScript"; exit 6 }
    $ImportArguments = @(
        $ResolvedProjectPath, "-run=pythonscript", "-script=$ImportScript",
        "-unattended", "-nop4", "-nosplash", "-NullRHI", "-NoSound", "-log=Prompt27_Import_Editor.log"
    )
    & $EditorCmd @ImportArguments *>&1 | Tee-Object -FilePath $ImportLog
    $ImportExitCode = $LASTEXITCODE
    if ($ImportExitCode -ne 0) { Write-Error "Import locale Batch 1 fallito. Log: $ImportLog"; exit $ImportExitCode }
    if (-not (Select-String -LiteralPath (Join-Path $LogDirectory "Prompt27_Import_Editor.log") -SimpleMatch "ASSET_BATCH_1_LOCAL_IMPORT_PASSED" -Quiet)) {
        Write-Error "Firma di import locale non trovata. Log: $ImportLog"
        exit 7
    }
}

$AuditArguments = @(
    (Join-Path $PSScriptRoot "AuditRomanAssets.py"), "--local-import-audit", "--batch", "$Batch", "--report-json", "--report-markdown"
)
& python @AuditArguments *>&1 | Tee-Object -FilePath $AuditLog
$AuditExitCode = $LASTEXITCODE
if ($AuditExitCode -ne 0) { Write-Error "Audit locale Batch 1 fallito. Log: $AuditLog"; exit $AuditExitCode }
if (-not $SkipLocalAssets -and -not (Select-String -LiteralPath $AuditLog -SimpleMatch "ASSET_BATCH_1_LOCAL_AUDIT_PASSED" -Quiet)) {
    Write-Error "Firma audit locale non trovata. Log: $AuditLog"
    exit 8
}

& python (Join-Path $PSScriptRoot "ValidateRomanModularFoundation.py") *>&1 | Tee-Object -FilePath $StaticLog
$StaticExitCode = $LASTEXITCODE
if ($StaticExitCode -ne 0) { Write-Error "Validazione statica Prompt 27 fallita. Log: $StaticLog"; exit $StaticExitCode }
if (-not (Select-String -LiteralPath $StaticLog -SimpleMatch "LOCAL_ASSET_INTEGRATION_STATIC_CHECKS_PASSED" -Quiet)) {
    Write-Error "Firma della validazione statica non trovata. Log: $StaticLog"
    exit 9
}

$TrackedExternal = @(git -C $RepositoryRoot ls-files -- "Content/ThirdParty" "Content/LocalAssets" "Content/ImportedAssets")
if ($TrackedExternal.Count -gt 0) { Write-Error "Asset esterni tracciati da Git: $($TrackedExternal -join ', ')"; exit 10 }
$StatusExternal = @(git -C $RepositoryRoot status --short --untracked-files=all -- "Content/ThirdParty" "Content/LocalAssets" "Content/ImportedAssets")
if ($StatusExternal.Count -gt 0) { Write-Error "Asset esterni visibili in git status: $($StatusExternal -join ', ')"; exit 11 }

$AutomationArguments = @(
    $ResolvedProjectPath,
    "/Game/Maps/RomaAeternaVerticalSlice",
    "-ExecCmds=Automation RunTests RomaAeterna.Prompt27.LocalAssetIntegration",
    "-TestExit=Automation Test Queue Empty", "-unattended", "-nop4", "-nosplash", "-NullRHI", "-NoSound",
    "-log=$AutomationEditorLogName"
)
& $EditorCmd @AutomationArguments *>&1 | Tee-Object -FilePath $AutomationLog
$AutomationExitCode = $LASTEXITCODE
if ($AutomationExitCode -ne 0) { Write-Error "Automation Test Prompt 27 fallito. Log: $AutomationEditorLog"; exit $AutomationExitCode }
$FailurePatterns = @("No automation tests matched", "0 tests performed", "Automation Test Failed", "Result={Fail}")
if (Select-String -LiteralPath $AutomationEditorLog -Pattern $FailurePatterns -Quiet) { Write-Error "Automation Test assente o fallito. Log: $AutomationEditorLog"; exit 12 }
$HasSuccess = Select-String -LiteralPath $AutomationEditorLog -SimpleMatch "Test Completed. Result={Success}" -Quiet
$HasExecutedTest = Select-String -LiteralPath $AutomationEditorLog -Pattern "Test Queue Empty [1-9][0-9]* tests performed" -Quiet
if (-not $HasSuccess -or -not $HasExecutedTest) { Write-Error "Firma Automation di successo non trovata. Log: $AutomationEditorLog"; exit 13 }

if (-not $SkipLocalAssets) {
    $PreviewMapFile = Join-Path $RepositoryRoot "Content/LocalAssets/RomaAeterna/Maps/RomaAeternaAssetBatch1Preview.umap"
    if (-not (Test-Path -LiteralPath $PreviewMapFile -PathType Leaf)) { Write-Error "Preview locale mancante: $PreviewMapFile"; exit 14 }
    $PreviewArguments = @(
        $ResolvedProjectPath, "/Game/LocalAssets/RomaAeterna/Maps/RomaAeternaAssetBatch1Preview",
        "-ExecCmds=MAP CHECK,QUIT_EDITOR", "-unattended", "-nop4", "-nosplash", "-NoSound", "-log=$PreviewEditorLogName"
    )
    # UnrealEditorServer può scrivere diagnostica non fatale su stderr: raccogliere il flusso,
    # poi valutare exit code e firme del log senza trasformarlo in eccezione PowerShell.
    $PreviousErrorActionPreference = $ErrorActionPreference
    $ErrorActionPreference = "Continue"
    $PreviewOutput = & $Editor @PreviewArguments *>&1
    $PreviewExitCode = $LASTEXITCODE
    $ErrorActionPreference = $PreviousErrorActionPreference
    $PreviewOutput | ForEach-Object { $_.ToString() } | Set-Content -LiteralPath $PreviewLog
    if ($PreviewExitCode -ne 0) { Write-Error "Apertura preview locale fallita. Log: $PreviewEditorLog"; exit $PreviewExitCode }
    $PreviewFailures = @("Fatal error", "Assertion failed", "Failed to load map", "Missing package")
    if (Select-String -LiteralPath $PreviewEditorLog -Pattern $PreviewFailures -Quiet) { Write-Error "Errore nella preview locale. Log: $PreviewEditorLog"; exit 15 }
}

Write-Host "ASSET_BATCH_1_LOCAL_AUDIT_PASSED"
Write-Host "LOCAL_ASSET_INTEGRATION_STATIC_CHECKS_PASSED"
Write-Host "UNREAL_BUILD_PASSED"
Write-Host "UNREAL_AUTOMATION_PASSED"
if (-not $SkipLocalAssets) { Write-Host "LOCAL_ASSET_PREVIEW_PASSED" }
Write-Host "EXTERNAL_ASSETS_NOT_VERSIONED"
Write-Host "GIT_LFS_NOT_USED"
Write-Host "Log build: $BuildLog"
Write-Host "Log import: $ImportLog"
Write-Host "Log audit: $AuditLog"
Write-Host "Log validazione statica: $StaticLog"
Write-Host "Log Automation: $AutomationLog"
Write-Host "Log preview: $PreviewLog"
exit 0
