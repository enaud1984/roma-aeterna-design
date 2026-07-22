# Report di implementazione Prompt 28

## Perimetro

La sostituzione mantiene geometria procedurale, collisioni e batching ISMC. Il catalogo opzionale seleziona Material Instance locali per categoria, archetipo, ricchezza, distretto, ruolo e usura. Nessuna mappa versionata o risorsa esterna è una dipendenza obbligatoria.

## Audit iniziale

Il Prompt 27 risolveva una sola voce per categoria; scala UV e metadati non influivano sulla selezione, mentre non esistevano istanze cromatiche condivise. Il Prompt 28 introduce selezione pesata deterministica nel core, cache nel catalogo, fallback selettivo, conteggi HUD e undici istanze locali parametrizzate.

## Sicurezza Git

- `Content/ThirdParty/`, `Content/LocalAssets/` e `Content/ImportedAssets/` restano ignorati.
- `RomaAeternaVerticalSlice.umap` e `TechnicalSandbox.umap` non ricevono riferimenti locali.
- Nessuna texture, Material Instance, preview o screenshot è versionata.
- Git LFS non è usato.
- Rome Empire Character Pack e Roman Temple Ruins non sono importati.

## Stato test finale

- Core Debug e Release: 1/1 CTest superato in entrambi i profili.
- Python: 15 test superati.
- Audit: `ARCHITECTURAL_MATERIAL_REPLACEMENT_AUDIT_PASSED`.
- Statico: `ARCHITECTURAL_MATERIAL_REPLACEMENT_STATIC_CHECKS_PASSED` e `PASSED_STATIC`.
- UHT/UBT/build UE 5.8: superati; build iniziale completa e rilanci incrementali verdi.
- Import: 2,04 secondi, 1.787 MiB fisici di picco, 0 errori/0 warning.
- Automation: `RomaAeterna.Prompt28.ArchitecturalMaterialReplacement`, 1 test Success.
- Preview reale: caricata con RHI, Map Check 0 errori/0 avvisi, chiusura corretta.

## Metriche

Gli output locali sono 48 file, 89.732.295 byte: 28 texture, sette master, undici Material Instance, un catalogo e una preview. Il test sui dieci archetipi genera 164 istanze in 64 componenti ISMC di categoria: 27 categorie risolte localmente, 37 fallback selettivi e 26 associazioni di variante attive. Ogni archetipo usa almeno due categorie locali e conserva fallback coerenti.

Stati confermati: `UNREAL_BUILD_PASSED`, `UNREAL_AUTOMATION_PASSED`, `LOCAL_MATERIAL_REPLACEMENT_TECHNICAL_PREVIEW_PASSED`, `MANUAL_LOCAL_MATERIAL_REVIEW_REQUIRED`. La preview è stata caricata con RHI reale e Map Check 0/0; la cattura automatica del viewport non ha fornito una prova visuale affidabile, quindi non viene dichiarata conclusa la revisione estetica.
