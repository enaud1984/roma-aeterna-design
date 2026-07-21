# Piano test generatore visuale runtime

## Test cloud

I test CMake/CTest standard verificano conteggi per categoria, bounds, determinismo, ordine stabile dei placement, transform finite, chiamate ripetute e layout diversi con categorie attese.

Stati attesi: `CORE_CPP_DEBUG_TESTS_PASSED`, `CORE_CPP_RELEASE_TESTS_PASSED`, `CORE_CPP_SANITIZERS_PASSED` e `PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED`.

## Test Unreal locali

`Source/RomaAeterna/Private/Tests/RARomanModularFoundationTests.cpp` include test marcati `LOCAL_UNREAL_TEST_REQUIRED` per creazione actor, `GenerateBuilding`, conteggio istanze, clear, seconda generazione senza accumulo, categorie attese e catalogo nullo.

Eseguire localmente con `Scripts/TestRomanProceduralBuilding.ps1 -EngineRoot <UE_5.8>`.

## Verifica manuale

Collocare `ARARomanProceduralBuildingActor` in una mappa di test non canonica, cambiare tipo edificio e seed, chiamare generate/clear/rebuild e verificare visivamente i placeholder. Play In Editor resta `MANUAL_VERIFICATION_REQUIRED`.

## Asset Fab

`FAB_ASSET_IMPORT_NOT_STARTED`: nessun asset Fab deve essere importato in questa fase.
