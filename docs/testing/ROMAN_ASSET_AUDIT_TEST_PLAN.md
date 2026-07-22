# Piano di test dell'audit asset romano

## Ambito

`Scripts/AuditRomanAssets.py` è un controllo documentale non distruttivo. Materializza i campi `NOT_VERIFIED`, valida schema/ID/URL/punteggi, copertura P0 e registro provenienza; ispeziona `Content` per file oltre soglia e rifiuta asset esterni locali presenti nell'indice Git; genera report deterministici in `Saved/AssetAudit`.

## Comandi

```powershell
python .\Scripts\AuditRomanAssets.py
python -m unittest discover -s Scripts\tests -p "test_*.py"
python .\Scripts\ValidateRomanModularFoundation.py
```

I test coprono parsing, categorie mancanti, naming errato, file grandi, provenienza mancante, determinismo, assenza di scritture dalla funzione di audit e distinzione fra asset locale ignorato (ammesso) e asset esterno tracciato (errore). `--check-only` non genera report. I report ordinari sono ignorati da Git perché collocati in `Saved`.

## Criteri di uscita

- `ASSET_AUDIT_PASSED` e exit code 0;
- tutti gli unittest passati;
- `ASSET_CATALOG_STATIC_CHECKS_PASSED` e `PASSED_STATIC`;
- nessuna modifica alle mappe, nessun nuovo `.uasset`, nessun binario esterno;
- `git diff --check` pulito.

La suite non prova licenze, accuratezza archeologica, qualità visuale o compatibilità runtime UE 5.8: tali verifiche restano manuali nel Prompt 27.
