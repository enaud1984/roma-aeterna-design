# Report implementazione Prompt 21

Il Prompt 21 aggiunge un adapter runtime per rendere visibili i layout astratti romani usando solo primitive Engine caricate tramite soft reference. Non sono stati importati asset Fab, non sono stati creati `.uasset` o `.umap` e `TechnicalSandbox.umap` non è stato modificato.

## Audit

Prerequisiti verificati: core `Source/RomaAeternaCore`, libreria regole, validatore, actor procedurale, layout per casa semplice, taberna, tempio e tratto di strada, documentazione Prompt 20/20-BIS e registro `FREE-027`–`FREE-036`.

## Implementazione

`ARARomanProceduralBuildingActor` espone API Blueprint per generare, cancellare, rigenerare e interrogare conteggi. Il batching usa componenti `UInstancedStaticMeshComponent` transient per categoria. Le mesh Engine sono cubo, cilindro, sfera e cono.

## Limiti

Il colore debug per istanza richiede materiale compatibile con custom data; senza materiale dedicato il fallback è geometrico. La verifica visuale non è dichiarata superata perché richiede Play In Editor locale.

## Stati

- CORE_CPP_DEBUG_TESTS_PASSED
- CORE_CPP_RELEASE_TESTS_PASSED
- CORE_CPP_SANITIZERS_PASSED
- PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED
- UNREAL_BUILD_REQUIRED
- UNREAL_AUTOMATION_REQUIRED
- MANUAL_VERIFICATION_REQUIRED
- FAB_ASSET_IMPORT_NOT_STARTED
