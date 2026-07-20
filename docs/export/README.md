# Export editoriale della Game Bible

## Scopo

Questa cartella contiene l'edizione Word/PDF illustrata della Game Bible. I file Markdown nel resto del repository rimangono la fonte ufficiale e dettagliata.

## Artefatti

- `ROMA_AETERNA_GAME_BIBLE.docx`: documento Word editoriale.
- `ROMA_AETERNA_GAME_BIBLE.pdf`: esportazione PDF corrispondente.
- `IMAGE_CREDITS.md`: provenienza, licenze e modifiche delle figure.
- `GENERATION_REPORT.md`: metriche, validazioni, avvisi e limiti.
- `game_bible_config.json`: ordine dei capitoli, fonti, immagini e metadati.
- `build_game_bible.py`: generatore riproducibile.
- `export_word_pdf.ps1`: aggiornamento dei campi Word ed esportazione PDF.
- `render_pdf_qa.py`: rendering delle pagine e creazione dei contact sheet per il controllo visivo.

## Rigenerazione

Usare il runtime Python indicato dall'ambiente Codex oppure un Python con `python-docx`, `Pillow` e `pypdf`:

```powershell
python docs/export/build_game_bible.py
powershell -ExecutionPolicy Bypass -File docs/export/export_word_pdf.ps1
python docs/export/build_game_bible.py --report-only
```

Per la verifica visiva finale, dopo avere installato Poppler o configurato il relativo eseguibile:

```powershell
python docs/export/render_pdf_qa.py
```

Gli output temporanei della verifica sono salvati in `_generated/qa/` e non vengono versionati.

Le immagini esterne elencate nella configurazione devono essere presenti nei percorsi dichiarati. Non sostituirle con file dalla licenza incerta.

## Dipendenze

- Game Bible Markdown del repository;
- Microsoft Word per aggiornare indice, numerazione e generare il PDF;
- Poppler per il rendering PDF in immagini durante la verifica;
- font Calibri o fallback compatibile.

## Collegamenti

- [Indice generale](../../README.md)
- [Readiness](../../READY_FOR_IMPLEMENTATION.md)
- [Crediti](IMAGE_CREDITS.md)
- [Report](GENERATION_REPORT.md)

## Stato

Export editoriale automatizzato e verificato su tutte le pagine. Il documento non modifica il gate di implementazione e non rende canoniche le sintesi o le mappe progettuali.
