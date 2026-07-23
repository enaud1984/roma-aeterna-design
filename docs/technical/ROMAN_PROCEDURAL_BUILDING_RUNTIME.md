# Runtime placeholder del generatore modulare romano

Il Prompt 21 converte i placement astratti prodotti da `RomaAeternaCore` in primitive visibili a runtime, senza importare asset Fab e senza creare `.uasset` o `.umap`.

## Architettura

Il flusso è `core C++ standard → adapter Unreal → UInstancedStaticMeshComponent`. `ARARomanProceduralBuildingActor` normalizza e valida i parametri, chiama i layout esistenti per casa semplice, taberna, tempio e tratto di strada, valida i placement, controlla `MaximumModuleCount`, svuota le istanze precedenti e ricostruisce le istanze placeholder.

## Primitive Engine

Le soft reference usate sono:

- `/Engine/BasicShapes/Cube.Cube`;
- `/Engine/BasicShapes/Cylinder.Cylinder`;
- `/Engine/BasicShapes/Sphere.Sphere`;
- `/Engine/BasicShapes/Cone.Cone`.

Se una mesh non viene caricata, il runtime registra `MissingPlaceholderMesh` e fallisce la generazione visuale senza creare asset persistenti.

## Categorie visuali

Sono previste regole per `Wall`, `Door`, `Window`, `Corner`, `Column`, `Capital`, `Base`, `Arch`, `Beam`, `Floor`, `Roof`, `Stair`, `Podium`, `Portico`, `Prop`, `Vegetation` e `Decoration`. Le dimensioni sono centralizzate nelle regole placeholder dell'actor e adattate a campata, altezza piano e ingombro normalizzato.

## Batching e determinismo

Il batching è per categoria tramite una mappa `categoria → UInstancedStaticMeshComponent`. `ClearVisualInstances` distrugge componenti transient e azzera i conteggi, quindi `RebuildBuilding` non accumula istanze. Il determinismo resta nel core: l'adapter non riordina e non modifica il vettore dei placement.

## Colore debug

Il runtime imposta custom data per istanza, ma senza materiale dedicato il colore non è garantito visivamente. Per questo i placeholder restano distinguibili soprattutto tramite primitive e proporzioni geometriche. I debug bounds e le etichette runtime sono opzionali.

## Stati

- PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED
- UNREAL_BUILD_REQUIRED
- UNREAL_AUTOMATION_REQUIRED
- MANUAL_VERIFICATION_REQUIRED
- FAB_ASSET_IMPORT_NOT_STARTED

## Aggiornamento Prompt 22 — archetipi edilizi

Il runtime può richiamare sei generatori specializzati tramite API Blueprint (`GenerateAtriumDomus`, `GenerateThermopolium`, `GenerateFullonica`, `GeneratePistrinum`, `GeneratePublicLatrine`, `GenerateSmallTemple`). I nuovi placeholder restano primitive Engine transient: cubi per banconi, canali, altari e sedute; cilindri per dolia e macine; coni/cilindri per marker di statua. Le limitazioni visive restano `MANUAL_VERIFICATION_REQUIRED` e `UNREAL_AUTOMATION_REQUIRED`.


## Prompt 23 — Tessuto residenziale, commerciale e misto

Aggiunti sedici archetipi ordinari (DomusMedia, PeristyleDomus, RichDomus, PopularHouse, Insula, Cenaculum, MixedUseHouse, Taberna, Popina, Caupona, Bookshop, Brothel, MedicalShop, BarberShop, MensaArgentaria, Stabulum), profili RomanBuildingUrbanProfile, pesi GetRecommendedUrbanComposition e stati CORE_CPP_DEBUG_TESTS_PASSED, CORE_CPP_RELEASE_TESTS_PASSED, CORE_CPP_SANITIZERS_PASSED, RESIDENTIAL_COMMERCIAL_STATIC_CHECKS_PASSED, UNREAL_BUILD_REQUIRED, UNREAL_AUTOMATION_REQUIRED, MANUAL_VERIFICATION_REQUIRED, FAB_ASSET_IMPORT_NOT_STARTED. Le ricostruzioni ordinarie sono HISTORICAL_APPROXIMATION e usano placeholder, senza .uasset/.umap.
# Runtime Prompt 24

Il runtime espone venti generatori Blueprint e conteggi per utilities, pericoli, stadi produttivi e capacità. Le categorie senza asset dedicato usano primitive placeholder.
# Integrazione vertical slice Prompt 24-BIS

La mappa `/Game/Maps/RomaAeternaVerticalSlice` usa direttamente `ARARomanProceduralBuildingActor` per sei archetipi dei Prompt 23–24. Ogni actor conserva un seed esplicito, genera a `BeginPlay` e supporta `ClearGeneratedBuilding` e `RebuildBuilding`. Le istanze placeholder hanno collisione `QueryAndPhysics` e bloccano il canale Pawn; la strada resta libera perché i generatori sono disposti sui lati.

Prompt 25 introduce `URARomanVisualCatalog`: mesh e materiali diventano sostituibili tramite soft reference, mentre i fallback restano sicuri. La mappa consolidata usa dieci generatori e il runtime applica materiali tecnici per categoria senza duplicare gli algoritmi del core.
## Estensione interni Prompt 29

`ARARomanProceduralBuildingActor` costruisce gusci accessibili, decorazioni e pavimenti in componenti ISMC riutilizzati. La generazione avviene una volta, non usa `Tick` e conserva i fallback tecnici.

## Correzione Prompt 29-BIS

`BuildVisualInstances` ricentra il piano sui bounds, valida trasformazioni e impedisce che i placeholder astratti coprano gli interni accessibili. Ogni assegnazione materiale verifica la compatibilità ISMC. I conteggi distinguono binding locali e fallback, mentre cache hit/miss, invalidazioni e path irrisolti sono esposti nel riepilogo diagnostico.

## Composizione Prompt 30

Il guscio accessibile rispetta `FloorCount` fino a due piani e differenzia apertura commerciale, ingresso residenziale, finestre superiori, balconi, fasce e coperture. Pistrinum entra nell’insieme accessibile e aggiunge forno e area di lavoro; Taberna, Thermopolium e DomusMedia espongono arredi semantici verificabili. La rappresentazione resta transient e non duplica la generazione planimetrica del core.
