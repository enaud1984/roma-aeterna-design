# Mapping locale Asset Batch 1

Il mapping condivisibile è descritto da `Config/LocalAssets/RomanAssetBatch1.template.json`; il mapping effettivo è generato localmente in `Saved/LocalAssetConfig/roman_asset_batch_1.json`. Tutti i riferimenti sono Soft Object Path `/Game`, mai percorsi Windows.

| Categoria runtime | Materiale locale | Grade | Licenza | Riusi principali |
|---|---|---|---|---|
| Wall | M_RA_Local_PlasteredWall03 | B | RA-CC0-PH-PLASTERED-WALL-03 | domus, insula, taberna, terme, basilica |
| Corner | M_RA_Local_Bricks066 | B | RA-CC0-ACG-BRICKS-066 | case popolari, cortili, magazzini, officine |
| Floor | M_RA_Local_Cobblestone05 | C | RA-CC0-PH-COBBLESTONE-05 | vicoli, cortili, strade secondarie |
| Roof | M_RA_Local_RoofingTiles013A | C | RA-CC0-ACG-ROOFING-TILES-013A | domus, botteghe, horrea, officine |
| Dolium | M_RA_Local_Bricks042 | B | RA-CC0-ACG-BRICKS-042 | commercio e produzione; fallback geometrico cilindrico |
| Door, Beam | M_RA_Local_WoodPlanksGrey | B | RA-CC0-PH-WOOD-PLANKS-GREY | porte, travi, banchi e scaffali |
| GardenFeature | M_RA_Local_Ground039 | C | RA-CC0-ACG-GROUND-039 | cortili, giardini, suburbio e aree produttive |

`FRARomanVisualCatalogEntry` conserva HistoricalGrade, DistrictCompatibility, WealthTiers, VariationWeight, ScaleCorrection, RotationCorrection, CollisionProfile, NanitePreference, MaterialOverrides, SourcePackage e LicenseRegistryId. Le mesh restano primitive procedurali istanziabili; il Batch 1 non sostituisce il generatore con edifici monolitici.

## Fallback

Il catalogo atteso è `/Game/LocalAssets/RomaAeterna/Data/DA_RA_VisualCatalog_Batch1`. Se il package non esiste, il runtime emette `LOCAL_ASSET_CATALOG_NOT_FOUND_USING_FALLBACKS`. Se viene caricato, emette `LOCAL_ASSET_CATALOG_LOADED`. F7 alterna local assets e placeholder e rigenera gli edifici; l’HUD mostra `LOCAL ASSETS ACTIVE` oppure `PLACEHOLDER FALLBACK ACTIVE`.
