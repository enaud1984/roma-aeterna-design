# Roman asset naming convention — Prompt 19

## Aggiornamento Prompt 26

I file vendor non vengono rinominati in-place; queste regole valgono per asset e wrapper di proprietà Roma Aeterna.

## Prefixes

| Prefix | Meaning |
|---|---|
| `SM_` | Static Mesh |
| `SK_` | Skeletal Mesh |
| `M_` | Material |
| `MI_` | Material Instance |
| `T_` | Texture |
| `BP_` | Blueprint |
| `DA_` | Data Asset |
| `DT_` | Data Table |
| `PCG_` | PCG Graph |
| `GS_` | Geometry Script |
| `FX_` | Effect |
| `S_` | Suono |
| `SC_` | Sound Cue |
| `AN_` | Animation |
| `ABP_` | Animation Blueprint |
| `NS_` | Niagara System |
| `PC_` | Physics Control |
| `IK_` | IK Rig |
| `RTG_` | IK Retargeter |
| `L_` | Level |
| `WBP_` | Widget Blueprint |

## Third-party asset policy

Do not automatically rename imported third-party assets. Vendor updates, redirectors and references can break if assets are renamed in place.

Preferred strategy:

1. Keep the original vendor folder intact after import.
2. Create Roma Aeterna wrapper Blueprints or Data Assets with project prefixes.
3. Use `MI_RA_*` material instances when a vendor material must be tuned.
4. Migrate only reviewed assets into `Content/RA/Environment/Roman/...` through Unreal Editor, not through Explorer.
5. Keep an alias table in documentation when a vendor asset is promoted to canonical project use.

## Target taxonomy

- `Content/RA/Environment/Roman/Architecture/`
- `Content/RA/Environment/Roman/Roads/`
- `Content/RA/Environment/Roman/Sidewalks/`
- `Content/RA/Environment/Roman/Walls/`
- `Content/RA/Environment/Roman/Roofs/`
- `Content/RA/Environment/Roman/Doors/`
- `Content/RA/Environment/Roman/Windows/`
- `Content/RA/Environment/Roman/Shops/`
- `Content/RA/Environment/Roman/Props/`
- `Content/RA/Environment/Roman/Materials/`
- `Content/RA/Environment/Roman/Decals/`
- `Content/RA/Environment/Roman/Vegetation/`
- `Content/RA/Environment/Roman/Lighting/`
- `Content/RA/Dev/`
- `Content/RA/Maps/`

## Roman modular examples

- `SM_Roman_Wall_Plain_300x300`
- `SM_Roman_Wall_Door_300x300`
- `SM_Roman_Column_Doric_300`
- `SM_Roman_RoofTile_Tegula_A`
- `SM_Roman_RoofTile_Imbrex_A`
- `SM_Roman_Arch_300`
- `BP_Roman_ModularHouse`
- `BP_Roman_ModularTemple`
- `BP_Roman_ModularShop`
- `DA_Roman_BuildingStyle_Pompeii`
- `DA_Roman_ArchitecturalOrder_Corinthian`

Use wrappers, controlled duplicates or a migration layer for third-party assets; do not rename vendor files in place.

## Formato Roma Aeterna

`<Tipo>_RA_<Categoria>_<Descrizione>_<Variante>` con ASCII, PascalCase per le parole e variante a due cifre. Esempi: `SM_RA_Wall_Plaster_01`, `SM_RA_Road_Basalt_01`, `SM_RA_Roof_Tegula_01`, `SM_RA_Prop_Amphora_01`, `MI_RA_Plaster_Ochre_01`. Gli identificatori documentali usano `RA-FAB-<GRUPPO>-NNN` o `RA-EPIC-<GRUPPO>-NNN`.

## Proposed modular Content structure

- `Content/RA/Environment/Roman/Modular/`
- `Content/RA/Environment/Roman/Modular/Walls/`
- `Content/RA/Environment/Roman/Modular/Columns/`
- `Content/RA/Environment/Roman/Modular/Arches/`
- `Content/RA/Environment/Roman/Modular/Roofs/`
- `Content/RA/Environment/Roman/Modular/Doors/`
- `Content/RA/Environment/Roman/Modular/Windows/`
- `Content/RA/Environment/Roman/Modular/Floors/`
- `Content/RA/Environment/Roman/Modular/Stairs/`
- `Content/RA/Environment/Roman/Modular/Porticos/`
- `Content/RA/Environment/Roman/Modular/Temples/`
- `Content/RA/Environment/Roman/Modular/Shops/`
- `Content/RA/Environment/Roman/Materials/`
- `Content/RA/Environment/Roman/Props/`
- `Content/RA/Environment/Roman/Vegetation/`
- `Content/RA/Environment/Roman/Decals/`
- `Content/RA/Environment/Roman/Procedural/`
- `Content/RA/Environment/Roman/Data/`
- `Content/RA/Environment/Roman/Prefabs/`
- `Content/RA/Maps/`
