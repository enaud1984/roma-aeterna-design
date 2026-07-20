param(
    [string]$DocxPath = (Join-Path $PSScriptRoot 'ROMA_AETERNA_GAME_BIBLE.docx'),
    [string]$PdfPath = (Join-Path $PSScriptRoot 'ROMA_AETERNA_GAME_BIBLE.pdf')
)

$ErrorActionPreference = 'Stop'
$word = $null
$document = $null
try {
    $word = New-Object -ComObject Word.Application
    $word.Visible = $false
    $word.DisplayAlerts = 0
    $document = $word.Documents.Open((Resolve-Path -LiteralPath $DocxPath).Path)
    foreach ($toc in $document.TablesOfContents) { $toc.Update() }
    foreach ($tof in $document.TablesOfFigures) { $tof.Update() }
    $document.Fields.Update() | Out-Null
    $document.Repaginate()
    $document.Save()
    $wdExportFormatPDF = 17
    $wdExportOptimizeForPrint = 0
    $wdExportAllDocument = 0
    $wdExportDocumentContent = 0
    $wdExportCreateHeadingBookmarks = 1
    $document.ExportAsFixedFormat(
        $PdfPath,
        $wdExportFormatPDF,
        $false,
        $wdExportOptimizeForPrint,
        $wdExportAllDocument,
        1,
        1,
        $wdExportDocumentContent,
        $true,
        $true,
        $wdExportCreateHeadingBookmarks,
        $true,
        $true,
        $false
    )
}
finally {
    if ($document) { $document.Close($false) }
    if ($word) { $word.Quit() }
    if ($document) { [System.Runtime.InteropServices.Marshal]::ReleaseComObject($document) | Out-Null }
    if ($word) { [System.Runtime.InteropServices.Marshal]::ReleaseComObject($word) | Out-Null }
    [GC]::Collect()
    [GC]::WaitForPendingFinalizers()
}

Write-Output "Exported: $PdfPath"
