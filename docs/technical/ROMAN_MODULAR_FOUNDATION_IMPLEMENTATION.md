# Implementazione fondazione modulare romana

Obiettivo: introdurre una fondazione C++ runtime per generare layout astratti di edifici romani senza creare asset binari, mappe o dipendenze UnrealEd.

## Architettura

Il codice vive in `Source/RomaAeterna/Public/World/Modular` e `Source/RomaAeterna/Private/World/Modular`.

Classi principali:
- `URARomanModuleCatalog`: catalogo C++ di moduli con ricerca per ID, categoria e tag.
- `URARomanBuildingStyleData`: data asset primario per stili storici, solo classe C++.
- `URARomanBuildingRuleLibrary`: regole deterministiche e layout astratti.
- `URARomanConstructionValidator`: validazione di parametri, cataloghi e placement.
- `ARARomanProceduralBuildingActor`: actor runtime predisposto a layout e placeholder tecnici.

Enumerazioni: `ERARomanBuildingType`, `ERARomanWallType`, `ERARomanRoofType`, `ERARomanArchitecturalOrder`, `ERARomanModuleCategory`, `ERARomanWealthLevel`, `ERARomanDegradationLevel`.

Strutture: `FRARomanModuleDimensions`, `FRARomanModuleDefinition`, `FRARomanBuildingParameters`, `FRARomanModulePlacement`, `FRARomanGenerationMessage`, `FRARomanGenerationResult`.

## Flusso dati e determinismo

I parametri vengono normalizzati, validati e trasformati in `FRARomanModulePlacement`. Le funzioni non usano generatori casuali globali; a parità di input e `RandomSeed` l'ordine dei placement resta deterministico.

## Asset mancanti e placeholder

Il catalogo usa `TSoftObjectPtr` per mesh e materiali. Asset assenti generano warning controllati. L'actor può usare placeholder runtime basati su primitive Engine, disattivabili con `bUseDebugPlaceholders`; non vengono creati file `.uasset` o `.umap`.

## Layout supportati

- casa semplice;
- taberna;
- tempio;
- tratto di strada.

Alcune regole contengono `HISTORICAL_APPROXIMATION` perché la forma storica è volutamente semplificata per questa fondazione.

## Limiti

`LOCAL_UNREAL_TEST_REQUIRED`: compilazione UBT, UHT e Automation Tests richiedono Unreal Engine 5.8 locale. `MANUAL_VERIFICATION_REQUIRED`: Play In Editor resta manuale.

## Prompt 21

Collegare cataloghi reali, scegliere moduli per stile, raffinare le regole di facciata, introdurre domus/insula/foro e verificare collisioni in editor.

## Aggiornamento Prompt 20-BIS — core C++ standard

Gli algoritmi puri sono stati estratti in `Source/RomaAeternaCore/include/RARomanModularCore.h`. `URARomanBuildingRuleLibrary` e `URARomanConstructionValidator` ora agiscono da adapter verso il core, mantenendo invariata l'API Blueprint pubblica e riducendo la duplicazione della logica critica.

Stati cloud: `CORE_CPP_DEBUG_TESTS_PASSED`, `CORE_CPP_RELEASE_TESTS_PASSED`, `CORE_CPP_SANITIZERS_PASSED`. Stati locali ancora richiesti: `UNREAL_BUILD_REQUIRED`, `UNREAL_AUTOMATION_REQUIRED`, `MANUAL_VERIFICATION_REQUIRED`.

## Aggiornamento Prompt 21 — runtime placeholder visibile

Il sistema modulare dispone ora di un adapter runtime in `ARARomanProceduralBuildingActor`: i placement astratti restano prodotti dal core e vengono convertiti in istanze tecniche solo nell'actor Unreal. Il batching è per categoria con `UInstancedStaticMeshComponent`; le primitive Engine usate sono cubo, cilindro, sfera e cono via soft reference. Stati: PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED, UNREAL_BUILD_REQUIRED, UNREAL_AUTOMATION_REQUIRED, MANUAL_VERIFICATION_REQUIRED, FAB_ASSET_IMPORT_NOT_STARTED.
