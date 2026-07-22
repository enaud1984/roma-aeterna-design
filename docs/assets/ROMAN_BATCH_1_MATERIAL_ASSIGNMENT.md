# Assegnazione dei materiali architettonici Batch 1

## Scopo

Il Batch 1 sostituisce esclusivamente i materiali delle primitive procedurali. Mesh, collisioni, trasformazioni e composizione ISMC/HISMC restano prodotti dai generatori. Ogni percorso `/Game/LocalAssets/` è opzionale e ignorato da Git.

## Modello

`FRARomanVisualCatalogEntry` combina categoria modulare, archetipo, ricchezza, distretto, `ERARomanSurfaceRole`, `ERARomanWeatheringLevel`, peso, correzioni UV e parametri PBR. `ERARomanWealthLevel` è riutilizzato come livello di ricchezza per evitare una tassonomia duplicata.

Ruoli disponibili: `ExteriorWall`, `InteriorWall`, `StructuralBrick`, `RoadSurface`, `SecondaryPaving`, `Sidewalk`, `Kerb`, `Roof`, `Timber`, `Ground`, `Courtyard`, `ProductiveFloor`, `ServiceArea`, `WaterEdge`, `UtilitySurface`.

## Material Instance locali

| Istanza | Sorgente | Uso principale |
|---|---|---|
| MI_RA_Local_Plaster_Light | PlasteredWall03 | domus media, terme, superfici curate |
| MI_RA_Local_Plaster_Ochre | PlasteredWall03 | case popolari e commercio |
| MI_RA_Local_Plaster_Red | PlasteredWall03 | variante cromatica, non affresco |
| MI_RA_Local_Brick_Popular | Bricks066 | muratura popolare e cortili |
| MI_RA_Local_Brick_Thermal | Bricks042 | terme, fornaci e utilities |
| MI_RA_Local_Road_Secondary | Cobblestone05 | strade secondarie e fronti commerciali |
| MI_RA_Local_Roof_Terracotta | RoofingTiles013A | coperture temporanee |
| MI_RA_Local_Wood_Dark | WoodPlanksGrey | porte e banchi meno usurati |
| MI_RA_Local_Wood_Worn | WoodPlanksGrey | travi, scaffali e servizio |
| MI_RA_Local_Ground_Dry | Ground039 | giardini e cortili asciutti |
| MI_RA_Local_Ground_Productive | Ground039 | officine e aree di servizio |

Le istanze condividono sette master e 28 texture operative. I parametri sono `UVScale`, `UVRotation`, `ColorTint`, `RoughnessMultiplier`, `NormalStrength`, `AOIntensity` e `Weathering`. Non vengono create istanze dinamiche per singolo modulo.

## Selezione e fallback

Il core puro espone `SelectDeterministicWeightedIndex`; stesso seed e stesso contesto producono la stessa variante. Il catalogo cachea l'indice per categoria, archetipo, ricchezza, usura e distretto. Se nessuna regola è compatibile o il catalogo manca, viene usato `GetTechnicalMaterialPath`.

Stati: `LOCAL_ASSET_ONLY_STRATEGY_CONFIRMED`, `GIT_LFS_NOT_USED`, `EXTERNAL_ASSETS_NOT_VERSIONED`, `HISTORICAL_APPROXIMATION`.
