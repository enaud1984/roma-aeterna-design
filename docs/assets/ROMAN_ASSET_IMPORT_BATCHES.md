# Piano incrementale di importazione

Questo piano non autorizza acquisizione o import. Ogni batch avrà un commit separato nel Prompt 27, dopo approvazione, licenza catturata e staging UE 5.8.

| Batch | Contenuti/candidati | Destinazione | Controlli e test | Dimensione / Git / rollback |
|---|---|---|---|---|
| 1 | intonaco, basolato, murature e tetti; MAT-001, ROAD-001, ARCH-004/003, ROOF-001 | `Content/ThirdParty/{Fab,Megascans}/<Vendor>`; wrapper in `Content/RomaAeterna/{Materials,Roads,Architecture}` | licenza, UE 5.8, scala, pivot, tile, collisione, LOD/Nanite, memoria, audit, build e Automation | totale `NOT_VERIFIED`; LFS prima del batch; rollback del solo commit batch |
| 2 | porte, finestre, colonne e archi dai kit approvati | Architecture; vendor intatto | snap, aperture ACharacter, ordine/proporzioni, collisioni e catalog mapping | `NOT_VERIFIED`; revert del commit, mai cancellazione vendor parziale |
| 3 | props domestici/commerciali/produttivi; PROP-001/002/003 | Props e Production | scala, collisioni, istanze, accuratezza tipologica, materiali e densità | `NOT_VERIFIED`; manifest per file e rollback batch |
| 4 | VEG-001/002/003 selezionati | Vegetation | specie, esclusione agave, wind, LOD/Nanite, overdraw, collisioni | `NOT_VERIFIED`; rimuovere wrapper e commit batch |
| 5 | MetaHuman/Mannequins, personaggio romano approvato, ANIM-001/002 | Characters e Animations | skeleton, IK/retarget, abiti, clipping, locomotion, folla e licenza | `NOT_VERIFIED`; storage potenzialmente alto, rollback atomico |

Ogni commit deve includere registro provenienza aggiornato, ricevuta/licenza non sensibile se redistribuibile, report audit JSON/Markdown, alias `ReplacementAssetId`, test visuali e confronto prestazioni. I vendor asset non si rinominano in-place; i placeholder restano fallback. Stato: `ASSET_IMPORT_PLAN_COMPLETED`.
