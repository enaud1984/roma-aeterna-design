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
