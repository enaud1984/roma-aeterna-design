# Sistema visuale placeholder romano

## Obiettivo

Il Prompt 25 sostituisce la lettura “strada moderna con blocchi isolati” con un isolato urbano tecnico mediterraneo. Il risultato resta `PLACEHOLDER_VISUALS_ONLY`: forma, palette e densità guidano sviluppo e test, ma non costituiscono grafica finale o certezza archeologica.

## Catalogo centralizzato

`URARomanVisualCatalog` è un `UDataAsset` BlueprintType composto da `FRARomanVisualCatalogEntry`. Ogni voce associa `ERARomanModuleCategory` a soft reference mesh/materiale e a un futuro `ReplacementAssetId`. `ARARomanProceduralBuildingActor` consulta il catalogo opzionale; se assente usa fallback Engine BasicShapes e palette tecnica locale senza crash.

La sostituzione futura segue `categoria -> voce catalogo -> asset reale`, senza modificare algoritmi core o planimetrie.

## Palette e collisioni

`M_RA_TechnicalBase` espone BaseColor, Roughness e Metallic. Le istanze coprono pietra, basolato, marciapiede, intonaci, muratura, laterizio, legno, tegole, acqua, metallo, terreno, vegetazione, area tecnica e pericolo. Non usano texture esterne. Cube, Cylinder, Sphere e Cone Engine sono i fallback mesh. Le istanze edilizie bloccano il Pawn; decorazioni e vegetazione possono disattivare la collisione.
