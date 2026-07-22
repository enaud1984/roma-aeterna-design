param(
    [string]$EngineRoot = "",
    [string]$ProjectPath = "RomaAeterna.uproject",
    [switch]$SkipLocalAssets
)

$ErrorActionPreference = "Stop"
$RepositoryRoot = Split-Path -Parent $PSScriptRoot
if (-not [IO.Path]::IsPathRooted($ProjectPath)) { $ProjectPath = Join-Path $RepositoryRoot $ProjectPath }
if (-not (Test-Path -LiteralPath $ProjectPath -PathType Leaf)) { Write-Error "File .uproject non trovato: $ProjectPath"; exit 2 }
$ResolvedProjectPath = (Resolve-Path -LiteralPath $ProjectPath).Path

if ([string]::IsNullOrWhiteSpace($EngineRoot)) {
    $ProgramFilesPath = [Environment]::GetFolderPath("ProgramFiles")
    foreach ($Folder in @("UE_5.8", "UE_5.8EA")) {
        $Candidate = Join-Path $ProgramFilesPath "Epic Games/$Folder"
        if (Test-Path -LiteralPath $Candidate -PathType Container) { $EngineRoot = $Candidate; break }
    }
}
if ([string]::IsNullOrWhiteSpace($EngineRoot) -or -not (Test-Path -LiteralPath $EngineRoot -PathType Container)) {
    Write-Error "Unreal Engine 5.8 non trovato: specificare -EngineRoot."
    exit 3
}
$ResolvedEngineRoot = (Resolve-Path -LiteralPath $EngineRoot).Path
$RunUAT = Join-Path $ResolvedEngineRoot "Engine/Build/BatchFiles/RunUAT.bat"
$EditorCmd = Join-Path $ResolvedEngineRoot "Engine/Binaries/Win64/UnrealEditor-Cmd.exe"
$Editor = Join-Path $ResolvedEngineRoot "Engine/Binaries/Win64/UnrealEditor.exe"
foreach ($Executable in @($RunUAT, $EditorCmd, $Editor)) {
    if (-not (Test-Path -LiteralPath $Executable -PathType Leaf)) { Write-Error "Eseguibile Unreal non trovato: $Executable"; exit 4 }
}

$LogDirectory = Join-Path $RepositoryRoot "Saved/Logs"
New-Item -ItemType Directory -Force -Path $LogDirectory | Out-Null
$BuildLog = Join-Path $LogDirectory "Prompt28_Build.log"
$ImportLog = Join-Path $LogDirectory "Prompt28_Import.log"
$AuditLog = Join-Path $LogDirectory "Prompt28_MaterialAudit.log"
$StaticLog = Join-Path $LogDirectory "Prompt28_StaticValidation.log"
$AutomationLog = Join-Path $LogDirectory "Prompt28_Automation.log"
$AutomationEditorLog = Join-Path $LogDirectory "Prompt28_Automation_Editor.log"
$PreviewLog = Join-Path $LogDirectory "Prompt28_Preview.log"
$PreviewEditorLog = Join-Path $LogDirectory "Prompt28_Preview_Editor.log"
$ImportScript = Join-Path $PSScriptRoot "ImportRomanAssetBatch1.py"

Write-Host "Progetto: $ResolvedProjectPath"
Write-Host "RunUAT: $RunUAT"
Write-Host "Modalita fallback: $SkipLocalAssets"

$BuildArguments = @(
    "BuildTarget", "-project=$ResolvedProjectPath", "-target=RomaAeternaEditor",
    "-platform=Win64", "-configuration=Development", "-notools", "-WaitMutex", "-utf8output"
)
& $RunUAT @BuildArguments *>&1 | Tee-Object -FilePath $BuildLog
$BuildExitCode = $LASTEXITCODE
if ($BuildExitCode -ne 0) { Write-Error "Build RomaAeternaEditor fallita. Log: $BuildLog"; exit $BuildExitCode }

if (-not $SkipLocalAssets) {
    if (-not (Test-Path -LiteralPath $ImportScript -PathType Leaf)) { Write-Error "Script import mancante: $ImportScript"; exit 5 }
    $ImportArguments = @(
        $ResolvedProjectPath, "-run=pythonscript", "-script=$ImportScript",
        "-unattended", "-nop4", "-nosplash", "-NullRHI", "-NoSound", "-log=Prompt28_Import_Editor.log"
    )
    & $EditorCmd @ImportArguments *>&1 | Tee-Object -FilePath $ImportLog
    $ImportExitCode = $LASTEXITCODE
    if ($ImportExitCode -ne 0) { Write-Error "Import materiali Prompt 28 fallito. Log: $ImportLog"; exit $ImportExitCode }
    $ImportEditorLog = Join-Path $LogDirectory "Prompt28_Import_Editor.log"
    if (-not (Select-String -LiteralPath $ImportEditorLog -SimpleMatch "ARCHITECTURAL_MATERIAL_REPLACEMENT_LOCAL_IMPORT_PASSED" -Quiet)) {
        Write-Error "Firma import Prompt 28 non trovata. Log: $ImportEditorLog"; exit 6
    }
}

$AuditArguments = @(
    (Join-Path $PSScriptRoot "AuditRomanAssets.py"), "--material-replacement-audit", "--batch", "1",
    "--report-json", "--report-markdown"
)
& python @AuditArguments *>&1 | Tee-Object -FilePath $AuditLog
$AuditExitCode = $LASTEXITCODE
if ($AuditExitCode -ne 0) { Write-Error "Audit sostituzione materiali fallito. Log: $AuditLog"; exit $AuditExitCode }
if (-not $SkipLocalAssets -and -not (Select-String -LiteralPath $AuditLog -SimpleMatch "ARCHITECTURAL_MATERIAL_REPLACEMENT_AUDIT_PASSED" -Quiet)) {
    Write-Error "Firma audit Prompt 28 non trovata. Log: $AuditLog"; exit 7
}

& python (Join-Path $PSScriptRoot "ValidateRomanModularFoundation.py") *>&1 | Tee-Object -FilePath $StaticLog
$StaticExitCode = $LASTEXITCODE
if ($StaticExitCode -ne 0) { Write-Error "Validazione statica Prompt 28 fallita. Log: $StaticLog"; exit $StaticExitCode }
if (-not (Select-String -LiteralPath $StaticLog -SimpleMatch "ARCHITECTURAL_MATERIAL_REPLACEMENT_STATIC_CHECKS_PASSED" -Quiet)) {
    Write-Error "Firma validazione Prompt 28 non trovata. Log: $StaticLog"; exit 8
}

$TrackedExternal = @(git -C $RepositoryRoot ls-files -- "Content/ThirdParty" "Content/LocalAssets" "Content/ImportedAssets")
if ($TrackedExternal.Count -gt 0) { Write-Error "Asset esterni tracciati: $($TrackedExternal -join ', ')"; exit 9 }
$StatusExternal = @(git -C $RepositoryRoot status --short --untracked-files=all -- "Content/ThirdParty" "Content/LocalAssets" "Content/ImportedAssets")
if ($StatusExternal.Count -gt 0) { Write-Error "Asset locali non ignorati: $($StatusExternal -join ', ')"; exit 10 }
$StagedLocalMaps = @(git -C $RepositoryRoot diff --cached --name-only -- "Content/LocalAssets/*.umap" "Content/LocalAssets/**/*.umap")
if ($StagedLocalMaps.Count -gt 0) { Write-Error "Preview locale in staging: $($StagedLocalMaps -join ', ')"; exit 11 }
$ProtectedMaps = @(git -C $RepositoryRoot diff --name-only -- "Content/Maps/RomaAeternaVerticalSlice.umap" "Content/Technical/Maps/TechnicalSandbox.umap")
if ($ProtectedMaps.Count -gt 0) { Write-Error "Mappa versionata modificata: $($ProtectedMaps -join ', ')"; exit 12 }
$Attributes = Join-Path $RepositoryRoot ".gitattributes"
if ((Test-Path -LiteralPath $Attributes) -and (Select-String -LiteralPath $Attributes -SimpleMatch "filter=lfs" -Quiet)) {
    Write-Error "Git LFS rilevato, incompatibile con il Prompt 28"; exit 13
}
$ForbiddenPacks = @(Get-ChildItem -LiteralPath (Join-Path $RepositoryRoot "Content/LocalAssets"),(Join-Path $RepositoryRoot "Content/ThirdParty") -Recurse -File -ErrorAction SilentlyContinue | Where-Object { $_.FullName -match "Rome.?Empire.?Character|Roman.?Temple.?Ruins" })
if ($ForbiddenPacks.Count -gt 0) { Write-Error "Pack Fab rinviato rilevato nell'import locale"; exit 14 }

$AutomationArguments = @(
    $ResolvedProjectPath, "/Game/Maps/RomaAeternaVerticalSlice",
    "-ExecCmds=Automation RunTests RomaAeterna.Prompt28.ArchitecturalMaterialReplacement",
    "-TestExit=Automation Test Queue Empty", "-unattended", "-nop4", "-nosplash", "-NullRHI", "-NoSound",
    "-log=Prompt28_Automation_Editor.log"
)
& $EditorCmd @AutomationArguments *>&1 | Tee-Object -FilePath $AutomationLog
$AutomationExitCode = $LASTEXITCODE
if ($AutomationExitCode -ne 0) { Write-Error "Automation Test Prompt 28 fallito. Log: $AutomationEditorLog"; exit $AutomationExitCode }
$FailurePatterns = @("No automation tests matched", "0 tests performed", "Automation Test Failed", "Result={Fail}")
if (Select-String -LiteralPath $AutomationEditorLog -Pattern $FailurePatterns -Quiet) { Write-Error "Automation Test assente o fallito. Log: $AutomationEditorLog"; exit 15 }
if (-not (Select-String -LiteralPath $AutomationEditorLog -SimpleMatch "Test Completed. Result={Success}" -Quiet)) {
    Write-Error "Firma Automation di successo non trovata. Log: $AutomationEditorLog"; exit 16
}

if (-not $SkipLocalAssets) {
    $PreviewMap = "/Game/LocalAssets/RomaAeterna/Maps/RomaAeternaAssetBatch1Preview"
    $PreviewFile = Join-Path $RepositoryRoot "Content/LocalAssets/RomaAeterna/Maps/RomaAeternaAssetBatch1Preview.umap"
    if (-not (Test-Path -LiteralPath $PreviewFile -PathType Leaf)) { Write-Error "Preview locale mancante: $PreviewFile"; exit 17 }
    $PreviewArguments = @(
        $ResolvedProjectPath, $PreviewMap, "-ExecCmds=MAP CHECK,QUIT_EDITOR",
        "-unattended", "-nop4", "-nosplash", "-NoSound", "-log=Prompt28_Preview_Editor.log"
    )
    $QuotedPreviewArguments = @($PreviewArguments | ForEach-Object {
        if ($_ -match '\s') { '"' + $_.Replace('"', '\"') + '"' } else { $_ }
    })
    $PreviewProcess = Start-Process -FilePath $Editor -ArgumentList $QuotedPreviewArguments -Wait -PassThru -WindowStyle Hidden
    $PreviewExitCode = $PreviewProcess.ExitCode
    "ExitCode=$PreviewExitCode" | Set-Content -LiteralPath $PreviewLog
    if ($PreviewExitCode -ne 0) { Write-Error "Preview Prompt 28 fallita. Log: $PreviewEditorLog"; exit $PreviewExitCode }
    if (Select-String -LiteralPath $PreviewEditorLog -Pattern @("Fatal error", "Assertion failed", "Failed to load map", "Missing package") -Quiet) {
        Write-Error "Errore nella preview Prompt 28. Log: $PreviewEditorLog"; exit 18
    }
    if (-not (Select-String -LiteralPath $PreviewEditorLog -Pattern "MapCheck:.*0 (Error|Errori)" -Quiet)) {
        Write-Error "Map Check pulito non confermato. Log: $PreviewEditorLog"; exit 19
    }
}

Write-Host "ARCHITECTURAL_MATERIAL_REPLACEMENT_AUDIT_PASSED"
Write-Host "ARCHITECTURAL_MATERIAL_REPLACEMENT_STATIC_CHECKS_PASSED"
Write-Host "UNREAL_BUILD_PASSED"
Write-Host "UNREAL_AUTOMATION_PASSED"
if (-not $SkipLocalAssets) {
    Write-Host "LOCAL_MATERIAL_REPLACEMENT_TECHNICAL_PREVIEW_PASSED"
    Write-Host "MANUAL_LOCAL_MATERIAL_REVIEW_REQUIRED"
}
Write-Host "EXTERNAL_ASSETS_NOT_VERSIONED"
Write-Host "GIT_LFS_NOT_USED"
Write-Host "Log build: $BuildLog"
Write-Host "Log import: $ImportLog"
Write-Host "Log audit: $AuditLog"
Write-Host "Log validazione: $StaticLog"
Write-Host "Log Automation: $AutomationLog"
Write-Host "Log preview: $PreviewLog"
exit 0
