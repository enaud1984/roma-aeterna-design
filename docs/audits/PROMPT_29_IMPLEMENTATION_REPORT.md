# Report di implementazione Prompt 29

Il Prompt 29 introduce piani decorativi deterministici nel core, sei gusci interni runtime accessibili, stili pompeiani tecnici, pavimenti, palette, fallback, controlli da F8 a F12 e interazione tecnica `E`.

Gli asset binari sono generati esclusivamente sotto `Content/LocalAssets/RomaAeterna/Decoration/`. Nessuna texture, Material Instance, preview o pack Fab viene versionato. Git LFS non è usato.

La mappa versionata conserva gli attori procedurali esistenti e non riceve hard reference locali. La geometria interna è costruita a runtime.

## Limiti

- `HISTORICAL_APPROXIMATION`;
- `FIGURATIVE_FRESCO_ART_NOT_STARTED`;
- arte figurativa, serrature e porte definitive rinviate;
- `MANUAL_DECORATION_VISUAL_REVIEW_REQUIRED`;
- `MANUAL_GAMEPLAY_TRAVERSAL_REQUIRED`;
- Roman Temple Ruins e Rome Empire Character Pack non importati.

I risultati finali di build, test e Map Check vengono registrati in `Saved/Logs/Prompt29_*.log`.

## Risultati

- core Debug, Release e sanitizer: CTest 1/1;
- Python: 18 test;
- audit e validatore: superati;
- UHT/UBT e `RomaAeternaEditor`: superati;
- `DecoratedInteriors` e `InteriorTraversal`: Success;
- metriche: sei edifici, tredici stanze accessibili, quattro stili;
- preview tecnica: Map Check 0 errori, 0 avvisi;
- 13 Material Instance e una mappa preview locali, ignorate da Git.
