# Piano test fondazione modulare romana

## Test automatici C++

`Source/RomaAeterna/Private/Tests/RARomanModularFoundationTests.cpp` copre: valori predefiniti, normalizzazione, campata, snap griglia, determinismo, layout casa/taberna/tempio/strada, dimensioni negative, valori non finiti, ID duplicati, compatibilità modulo, catalogo nullo, generazione senza asset reali, transform finite e `MaximumModuleCount`.

Stato: `LOCAL_UNREAL_TEST_REQUIRED` perché nel cloud non viene dichiarata esecuzione Unreal Engine.

## Controlli cloud

- `python3 -m py_compile Scripts/ValidateRomanModularFoundation.py`.
- `python3 Scripts/ValidateRomanModularFoundation.py`.
- `git diff --check`.
- controlli testuali per UnrealEd, mappe hard-coded, asset binari e documentazione.

## Verifiche manuali casa

Eseguire `Scripts/BuildRomanModularFoundation.ps1 -EngineRoot <UE_5.8>`, lanciare gli Automation Tests e aprire una mappa di prova non canonica. Play In Editor rimane `MANUAL_VERIFICATION_REQUIRED`.

## Aggiornamento Prompt 20-BIS — test core standard

Il core standard è testabile nel cloud con CMake e CTest. I risultati sono documentati in `docs/testing/ROMAN_MODULAR_CORE_CPP_TEST_REPORT.md` con stati `CORE_CPP_DEBUG_TESTS_PASSED`, `CORE_CPP_RELEASE_TESTS_PASSED` e `CORE_CPP_SANITIZERS_PASSED`.

La verifica del modulo Unreal resta separata: `UNREAL_BUILD_REQUIRED` e `UNREAL_AUTOMATION_REQUIRED`. Play In Editor resta `MANUAL_VERIFICATION_REQUIRED`.

## Aggiornamento Prompt 21 — placeholder runtime

Aggiunti test C++ standard per categorie, bounds, determinismo e idempotenza dei layout. Aggiunti Automation Tests Unreal locali marcati `LOCAL_UNREAL_TEST_REQUIRED` per l'actor procedurale, `GenerateBuilding`, `ClearGeneratedBuilding`, rigenerazione senza accumulo e categorie attese.

Stati cloud: `CORE_CPP_DEBUG_TESTS_PASSED`, `CORE_CPP_RELEASE_TESTS_PASSED`, `CORE_CPP_SANITIZERS_PASSED`, `PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED`. Stati locali: `UNREAL_BUILD_REQUIRED`, `UNREAL_AUTOMATION_REQUIRED`, `MANUAL_VERIFICATION_REQUIRED`.
