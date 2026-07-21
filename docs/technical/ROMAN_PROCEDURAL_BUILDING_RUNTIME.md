# Generatore visuale runtime di edifici romani

## Obiettivo

Il Prompt 21 collega i placement astratti prodotti dal core modulare a componenti runtime Unreal visibili. `ARARomanProceduralBuildingActor` genera layout tramite `URARomanBuildingRuleLibrary`, valida i placement e crea placeholder tecnici usando solo primitive incluse nell'Engine.

## Flusso core → adapter → istanze

1. `GenerateBuilding` normalizza i parametri.
2. Il validator controlla parametri e placement.
3. La rule library seleziona il layout: casa semplice, taberna, tempio o tratto di strada.
4. `BuildVisualInstances` converte ogni `FRARomanModulePlacement` in un transform visuale relativo all'actor.
5. `UInstancedStaticMeshComponent` raggruppa le istanze per categoria e mesh.
6. `LastGenerationResult`, conteggi e warning/errori vengono aggiornati.

## Categorie e primitive Engine

Le categorie visuali supportate sono `Wall`, `Door`, `Window`, `Corner`, `Column`, `Capital`, `Base`, `Arch`, `Beam`, `Floor`, `Roof`, `Stair`, `Podium`, `Portico`, `Prop`, `Vegetation` e `Decoration`.

Le soft reference runtime usate sono:

- `/Engine/BasicShapes/Cube.Cube`;
- `/Engine/BasicShapes/Cylinder.Cylinder`;
- `/Engine/BasicShapes/Sphere.Sphere`;
- `/Engine/BasicShapes/Cone.Cone`.

## Batching

Il batching usa una chiave categoria+mesh e crea un `UInstancedStaticMeshComponent` transient per gruppo. `ClearVisualInstances` svuota istanze, distrugge componenti runtime e azzera le mappe di conteggio per evitare accumulo dopo `RebuildBuilding`.

## Determinismo

La geometria astratta resta nel core C++ standard. L'actor non modifica il risultato astratto per adattarlo alle primitive: applica solo dimensionamento visuale centralizzato in `CalculatePlaceholderSizeCm` e `CalculateVisualTransform`.

## Limiti placeholder

I colori debug non creano materiali persistenti. Senza materiale dedicato il colore per istanza non è garantito; la distinzione è affidata soprattutto a forma, scala e categoria. La verifica visuale richiede `MANUAL_VERIFICATION_REQUIRED`.

## Stati

`PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED` copre i controlli statici cloud del runtime placeholder. `UNREAL_BUILD_REQUIRED` e `UNREAL_AUTOMATION_REQUIRED` restano locali. `FAB_ASSET_IMPORT_NOT_STARTED` conferma che nessun asset Fab è stato importato.
