# Piano di test del runtime placeholder modulare romano

## Cloud

I test cloud compilano il core standard con CMake/CTest in Debug, Release e sanitizer. Verificano conteggi per categoria, trasformazioni finite, `MaximumModuleCount`, ordine deterministico, bounds coerenti, chiamate ripetute e layout diversi.

Stati attesi dopo esecuzione reale:

- CORE_CPP_DEBUG_TESTS_PASSED
- CORE_CPP_RELEASE_TESTS_PASSED
- CORE_CPP_SANITIZERS_PASSED
- PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED

## Unreal locale

Gli Automation Tests Unreal sono marcati `LOCAL_UNREAL_TEST_REQUIRED` e devono essere eseguiti localmente con `Scripts/TestRomanProceduralBuilding.ps1`. Coprono creazione actor, `GenerateBuilding`, conteggio istanze, clear, rigenerazione senza accumulo, seed uguale, categorie attese per casa/taberna/tempio/strada, limite massimo e catalogo nullo.

Questi test richiedono Unreal Engine 5.8 locale e non sono dichiarati superati nel cloud:

- UNREAL_BUILD_REQUIRED
- UNREAL_AUTOMATION_REQUIRED
- MANUAL_VERIFICATION_REQUIRED

## Verifica manuale

Aprire il progetto in Unreal, collocare `ARARomanProceduralBuildingActor`, cambiare tipo edificio e seed, avviare Play In Editor e verificare visivamente placeholder, bounds e assenza di accumulo dopo rebuild. La verifica PIE resta obbligatoria e locale.
