# Mappatura proposta del visual catalog

La tabella è progettuale: nessun riferimento runtime è stato modificato. Il fallback resta quello tecnico di `URARomanVisualCatalog`; i pesi sono `HISTORICAL_APPROXIMATION` e saranno tarati dopo import.

| RomanModuleCategory | CandidateAssetId | FallbackAsset | Grade | Distretti | WealthTier | VariationWeight |
|---|---|---|---|---|---|---:|
| Wall | RA-FAB-ARCH-001, RA-FAB-MAT-001 | Engine Cube + MI_RA_PlasterLight | B | tutti | Low–High | 4 |
| WallWithDoor | RA-FAB-ARCH-001/002 | Engine Cube + MI_RA_Wood | B | residenziale/commerciale | Low–High | 3 |
| WallWithWindow | RA-FAB-ARCH-001/002 | Engine Cube + MI_RA_PlasterLight | B | residenziale | Low–High | 3 |
| Corner | RA-FAB-ARCH-001/003 | Engine Cube | B | tutti | tutti | 2 |
| Column | RA-FAB-ARCH-004/005 | Engine Cylinder + MI_RA_Stone | B | civico/religioso/ricco | High | 3 |
| Arch | RA-FAB-ARCH-003/004 | Engine Cube + MI_RA_Stone | B | civico/utilità | Medium–High | 2 |
| Roof | RA-FAB-ARCH-001, RA-FAB-ROOF-001 | Engine Cube + MI_RA_RoofTile | C | tutti | tutti | 4 |
| Floor | RA-FAB-ARCH-004, RA-FAB-MAT-001 | Engine Cube + technical material | B | tutti | tutti | 3 |
| RoadStone | RA-FAB-ROAD-001 | Engine Cube + MI_RA_RoadStone | C | assi/vicoli | tutti | 5 |
| Sidewalk | RA-FAB-ARCH-001/003 | Engine Cube + MI_RA_Sidewalk | C | assi commerciali | tutti | 3 |
| Counter | RA-FAB-PROP-001 | Engine Cube + MI_RA_Stone | B | commerciale | Low–Medium | 4 |
| Basin | RA-FAB-ARCH-004 | Engine Cylinder + MI_RA_Water | B | terme/pubblico | Medium–High | 2 |
| Furnace | RA-FAB-ARCH-003 | Engine Cube + MI_RA_Hazard | C | produttivo | Low–Medium | 2 |
| Oven | RA-FAB-ARCH-003 | Engine Cube + MI_RA_Brick | C | pistrinum/commercio | Low–Medium | 2 |
| Press | RA-FAB-PROP-001 | Engine Cube + MI_RA_Wood | C | produttivo | Medium | 1 |
| Storage | RA-FAB-PROP-002/003 | Engine Cylinder + MI_RA_RoofTile | A/B | tutti | tutti | 5 |
| AqueductArch | RA-FAB-ARCH-003/004 | Engine Cube + MI_RA_Stone | B | periferia/utilità | Medium–High | 2 |
| SewerChannel | RA-FAB-ARCH-003 | Engine Cube + MI_RA_RoughMasonry | C | utilità | tutti | 1 |
| Vegetation | RA-FAB-VEG-001/002/003 | Engine Cone + MI_RA_Vegetation | B/C | giardini/periferia | tutti | 5 |
| Props | RA-FAB-PROP-001/002/003 | primitive tecniche | A/B | domestico/commerciale | tutti | 5 |

Prima della promozione: licenza, path, scala, collisione, performance, contesto storico e alias `ReplacementAssetId` devono essere approvati.

## Mapping locale effettivo Batch 1

Il Batch 1 gratuito mappa materiali CC0 sulle primitive procedurali: Wall→PlasteredWall03, Corner→Bricks066, Floor→Cobblestone05, Roof→RoofingTiles013A, Dolium→Bricks042, Door/Beam→WoodPlanksGrey, GardenFeature→Ground039. Il Data Asset locale non è versionato; schema, grade e LicenseRegistryId sono descritti in `ROMAN_ASSET_BATCH_1_LOCAL_MAPPING.md`. La mappatura precedente dei candidati Fab resta storica e non è operativa.
