# Architettura di integrazione degli asset romani

## Flusso futuro

1. Registrare provenienza e License nel catalogo.
2. Verificare HistoricalCompatibility e CityCompatibility.
3. Normalizzare Dimensions, Pivot, snap e Collision.
4. Importare nella cartella della Category.
5. Registrare l’asset in `URARomanVisualCatalog` senza cambiare il core.
6. Confrontare placeholder e sostituzione reale.
7. Eseguire controllo qualità e performance.

## Convenzioni

- Scala: centimetri Unreal, import scale `1.0`; snap 10/50 cm.
- Naming: `SM_RA_<Category>_<Name>`, `M_RA_<Name>`, `MI_RA_<Name>`, `DA_RA_VisualCatalog_<Tier>`.
- Pivot alla base; bordo di aggancio documentato per moduli lineari.
- Collision semplice esplicita; complex-as-simple solo se misurata.
- Nanite verificato per piattaforma; LOD e fallback sempre documentati.
- MaterialSlots stabili e nominati per funzione.
- Cartelle: Architecture, Infrastructure, Props, Vegetation, Materials.
- Source, autore e License provati localmente prima del versionamento.

Categorie prioritarie: Wall, WallWithDoor, WallWithWindow, Column, Arch, Roof, Floor, RoadStone, Sidewalk, FountainBasin, Furnace, Counter, Storage, Press, AqueductArch e SewerChannel. Ogni sostituzione deve preservare PerformanceTier e IntendedArchetypes. Valori plausibili ma non certi restano `HISTORICAL_APPROXIMATION`.

## Gate di integrazione Prompt 26

Il catalogo machine-readable è `docs/assets/roman_asset_catalog.json`; il registro fonti è il gate legale/provenienza, mentre `ROMAN_ASSET_VISUAL_CATALOG_MAPPING.md` propone gli alias senza cambiare il runtime. La pipeline approvata è: scoperta → verifica scheda → shortlist → approvazione utente → cattura licenza/account → staging UE 5.8 → audit scala/pivot/collisione/LOD/materiali → wrapper Roma Aeterna → soft reference nel catalogo → build e test → commit atomico.

Gli asset vendor restano esclusivamente locali sotto le cartelle ignorate `Content/ThirdParty/<Fonte>/<Vendor>` senza rename. Il repository conserva soltanto cataloghi, registri, mapping/configurazioni testuali e i fallback tecnici già autorizzati. Il fallback non viene rimosso e il progetto deve funzionare senza librerie locali. L'importazione si arresta se compatibilità, licenza o provenienza non sono verificate. Stati: `LOCAL_ASSET_ONLY_STRATEGY`, `GIT_LFS_NOT_USED`, `EXTERNAL_ASSETS_NOT_VERSIONED`.

## Loader locale Prompt 27

`URARomanVisualCatalog::LoadLocalCatalog` cerca esclusivamente il Soft Object Path `/Game/LocalAssets/RomaAeterna/Data/DA_RA_VisualCatalog_Batch1`. L’assenza è intenzionale nel CI e produce `LOCAL_ASSET_CATALOG_NOT_FOUND_USING_FALLBACKS`, senza errori di package mancanti. Il catalogo presente produce `LOCAL_ASSET_CATALOG_LOADED`. F7 modifica uno stato runtime transitorio, aggiorna i generatori e non salva riferimenti nella mappa versionata.

Il template JSON è condivisibile ma non obbligatorio. Texture, materiali, Data Asset e preview sono generati sotto percorsi ignorati. La strategia mantiene `Soft Object Reference`, fallback sicuro e assemblaggio procedurale; non usa Git LFS.

## Assegnazione Prompt 28

Il core puro fornisce il selettore pesato deterministico; l'adapter Unreal applica i risultati a una componente ISMC per categoria. La cache usa seed, categoria, archetipo, ricchezza, usura e distretto. Le Material Instance sono asset locali condivisi: non esiste una MID per modulo. L'HUD espone categorie locali, categorie in fallback, seed e varianti attive.
