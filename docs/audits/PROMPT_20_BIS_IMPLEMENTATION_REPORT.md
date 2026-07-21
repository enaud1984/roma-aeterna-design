# Report implementazione Prompt 20-BIS

## Audit

L'audit ha individuato in `URARomanBuildingRuleLibrary` e `URARomanConstructionValidator` gli algoritmi puri estraibili: normalizzazione, validazione numerica, calcolo campate, snap griglia, bounds, stima moduli, enforcement del limite moduli e layout astratti. Catalogo, stile e actor restano Unreal perché gestiscono reflection, data asset e componenti runtime.

## Implementazione

È stata creata la struttura `Source/RomaAeternaCore` con libreria C++17 standard e test runner. Gli adapter Unreal convertono i dati Blueprint verso il core e riconvertono i risultati senza duplicare la logica critica di layout.

## Stati

| Stato | Significato | Esito |
|---|---|---|
| CORE_CPP_DEBUG_TESTS_PASSED | CMake Debug, build e CTest completati | superato |
| CORE_CPP_RELEASE_TESTS_PASSED | CMake Release, build e CTest completati | superato |
| CORE_CPP_SANITIZERS_PASSED | AddressSanitizer e UndefinedBehaviorSanitizer completati | superato |
| UNREAL_BUILD_REQUIRED | Build Unreal locale richiesta | non eseguita nel cloud |
| UNREAL_AUTOMATION_REQUIRED | Automation Tests Unreal locali richiesti | non eseguiti nel cloud |
| MANUAL_VERIFICATION_REQUIRED | PIE/manuale locale richiesto | non eseguito nel cloud |

## Assenza dipendenze vietate

Il core non usa header o macro Unreal, non crea asset, non modifica mappe e non contiene percorsi assoluti. `TechnicalSandbox.umap` non è stato modificato.
