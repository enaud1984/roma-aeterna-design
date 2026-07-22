# Rapporto di importazione locale Asset Batch 1

## Ambito

Il Batch 1 sostituisce la precedente proposta a pagamento con sette materiali PBR CC0. Gli archivi sorgente sono stati acquisiti il 22 luglio 2026 in `Content/ThirdParty/External`, percorso esclusivamente locale e ignorato da Git. Costo complessivo: **0 euro**.

| AssetId | Pacchetto | Fonte | File | Dimensione sorgente | Stato |
|---|---|---|---:|---:|---|
| RA-CC0-PH-PLASTERED-WALL-03 | Plastered Wall 03 | Poly Haven | 9 | 13.912.049 byte | acquisito, import locale richiesto |
| RA-CC0-ACG-BRICKS-066 | Bricks 066 | ambientCG | 11 | 28.708.023 byte | acquisito, import locale richiesto |
| RA-CC0-PH-COBBLESTONE-05 | Cobblestone 05 | Poly Haven | 10 | 22.495.430 byte | acquisito, import locale richiesto |
| RA-CC0-ACG-ROOFING-TILES-013A | Roofing Tiles 013 A | ambientCG | 12 | 11.890.524 byte | acquisito, import locale richiesto |
| RA-CC0-ACG-BRICKS-042 | Bricks 042 | ambientCG | 11 | 32.610.787 byte | acquisito, import locale richiesto |
| RA-CC0-PH-WOOD-PLANKS-GREY | Wood Planks Grey | Poly Haven | 9 | 14.597.783 byte | acquisito, import locale richiesto |
| RA-CC0-ACG-GROUND-039 | Ground 039 | ambientCG | 11 | 34.077.294 byte | acquisito, import locale richiesto |

Totale sorgenti: 73 file, 158.291.890 byte (150,96 MiB). Tutte le texture operative sono 2048×2048. Lo script `ImportRomanAssetBatch1.py` importa soltanto Base Color, Normal DX, Roughness e Ambient Occlusion; `.blend`, `.gltf`, `.bin`, `.usdc`, `.mtlx`, `.tres`, displacement e Normal GL restano sorgenti locali non importate.

## Isolamento

Gli originali rimangono sotto `Content/ThirdParty/External`. Texture, materiali, catalogo e preview Unreal vengono creati sotto `Content/LocalAssets/RomaAeterna`; il mapping macchina viene scritto in `Saved/LocalAssetConfig`. Tutti questi percorsi sono ignorati. Nessun asset esterno è ammesso nel commit.

La mappa versionata `/Game/Maps/RomaAeternaVerticalSlice` e `TechnicalSandbox` non vengono salvate o modificate. Il catalogo locale è opzionale e il progetto continua a usare primitive Engine e materiali tecnici quando è assente.

## Stati

- `ASSET_BATCH_1_FREE_ACQUIRED`
- `LOCAL_ASSET_ONLY_STRATEGY_CONFIRMED`
- `GIT_LFS_NOT_USED`
- `EXTERNAL_ASSETS_NOT_VERSIONED`
- `ASSET_BATCH_1_LOCAL_AUDIT_PASSED`
- `LOCAL_ASSET_INTEGRATION_STATIC_CHECKS_PASSED`
- `UNREAL_BUILD_PASSED`
- `UNREAL_AUTOMATION_PASSED`
- `LOCAL_ASSET_PREVIEW_PASSED`

L’import UE 5.8 si è concluso con 0 errori e 0 warning. Sono stati creati localmente 36 `.uasset` e una `.umap`, per 89.535.085 byte complessivi; nessuno è tracciato.
