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
