# Piano test integrazione asset locali

## Test automatici

1. `python Scripts/AuditRomanAssets.py --local-import-audit --batch 1 --report-json --report-markdown` verifica sette sorgenti, mapping locale, catalogo, preview e assenza di file tracciati.
2. La suite Python controlla batch assente, batch completo, determinismo, nessuna scrittura dell’audit e rifiuto di percorsi assoluti.
3. `ValidateRomanModularFoundation.py` controlla loader, template, documentazione, assenza di Git LFS, mappe protette e asset esterni tracciati.
4. `RomaAeterna.Prompt27.LocalAssetIntegration` disabilita il catalogo e verifica il fallback, poi abilita il catalogo. Se installato, risolve materiale e LicenseRegistryId; se assente, il test resta valido. Infine rigenera gli archetipi della vertical slice.
5. `TestRomanLocalAssetIntegration.ps1` compila RomaAeternaEditor, importa il Batch 1 quando richiesto, esegue audit e Automation, apre realmente la preview e conserva log separati.

## Preview e controllo manuale

Aprire `/Game/LocalAssets/RomaAeterna/Maps/RomaAeternaAssetBatch1Preview`. Verificare affiancamento placeholder/materiale, tiling, Normal DX, scala, collisione e illuminazione. Nella vertical slice usare F7 senza salvarla. Il controllo visuale umano resta richiesto se non viene ispezionata una cattura della sessione.

## Criteri di fallimento

- asset esterno tracciato o visibile in `git status`;
- mappa versionata modificata;
- catalogo hard-reference obbligatorio;
- materiale o licenza non risolvibile;
- nessun Automation Test eseguito;
- Map Check o log con errori critici;
- exit code non zero.
