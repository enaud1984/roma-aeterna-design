# Report test core C++ standard

## Ambiente cloud

I test sono stati eseguiti con CMake su Linux cloud usando C++17, warning elevati e nessuna dipendenza esterna obbligatoria.

| Controllo | Comando | Esito |
|---|---|---|
| Configurazione Debug | `cmake -S . -B build-cloud -DCMAKE_BUILD_TYPE=Debug` | CORE_CPP_DEBUG_TESTS_PASSED |
| Build Debug | `cmake --build build-cloud --parallel` | CORE_CPP_DEBUG_TESTS_PASSED |
| Test Debug | `ctest --test-dir build-cloud --output-on-failure` | CORE_CPP_DEBUG_TESTS_PASSED |
| Configurazione Release | `cmake -S . -B build-cloud-release -DCMAKE_BUILD_TYPE=Release` | CORE_CPP_RELEASE_TESTS_PASSED |
| Build Release | `cmake --build build-cloud-release --parallel` | CORE_CPP_RELEASE_TESTS_PASSED |
| Test Release | `ctest --test-dir build-cloud-release --output-on-failure` | CORE_CPP_RELEASE_TESTS_PASSED |
| Sanitizer | `cmake -S . -B build-cloud-sanitize -DCMAKE_BUILD_TYPE=Debug -DROMA_AETERNA_ENABLE_SANITIZERS=ON` più build e CTest | CORE_CPP_SANITIZERS_PASSED |
| Validatore statico Unreal | `python3 Scripts/ValidateRomanModularFoundation.py` | CORE_CPP_DEBUG_TESTS_PASSED |

## Casi coperti

Il test runner copre valori predefiniti, normalizzazione, campata, snap griglia, altezza edificio, stima moduli, `MaximumModuleCount`, dimensioni negative, larghezza zero, griglia zero, NaN, infinito positivo, infinito negativo, scala zero, scala negativa, determinismo stesso seed, variazione con seed diverso, layout casa, taberna, tempio, strada, transform finite, ripetizione coerente, nessun accumulo di stato e input estremamente grandi.

## Verifiche ancora locali

`UNREAL_BUILD_REQUIRED`: compilare il modulo Unreal con Unreal Engine 5.8.

`UNREAL_AUTOMATION_REQUIRED`: eseguire gli Automation Tests Unreal.

`MANUAL_VERIFICATION_REQUIRED`: verificare Play In Editor solo dopo build locale reale.
