# Piano test archetipi edilizi romani

## Cloud C++

Eseguire Debug, Release e sanitizer con CMake/CTest. Quando superati, documentare `CORE_CPP_DEBUG_TESTS_PASSED`, `CORE_CPP_RELEASE_TESTS_PASSED` e `CORE_CPP_SANITIZERS_PASSED`.

## Unreal locale

Automation Tests aggiunti come `LOCAL_UNREAL_TEST_REQUIRED`: generazione sei archetipi, istanze > 0, categorie specifiche, clear/rebuild, nessun accumulo, stesso seed, `MaximumModuleCount`, catalogo nullo, primitive mancanti, conteggi e punti interazione. Non dichiarare PIE superato.


## Prompt 23 — Tessuto residenziale, commerciale e misto

Aggiunti sedici archetipi ordinari (DomusMedia, PeristyleDomus, RichDomus, PopularHouse, Insula, Cenaculum, MixedUseHouse, Taberna, Popina, Caupona, Bookshop, Brothel, MedicalShop, BarberShop, MensaArgentaria, Stabulum), profili RomanBuildingUrbanProfile, pesi GetRecommendedUrbanComposition e stati CORE_CPP_DEBUG_TESTS_PASSED, CORE_CPP_RELEASE_TESTS_PASSED, CORE_CPP_SANITIZERS_PASSED, RESIDENTIAL_COMMERCIAL_STATIC_CHECKS_PASSED, UNREAL_BUILD_REQUIRED, UNREAL_AUTOMATION_REQUIRED, MANUAL_VERIFICATION_REQUIRED, FAB_ASSET_IMPORT_NOT_STARTED. Le ricostruzioni ordinarie sono HISTORICAL_APPROXIMATION e usano placeholder, senza .uasset/.umap.
# Regressione Prompt 24

La suite mantiene i controlli Prompt 22–23 e aggiunge venti archetipi utilities/produttivi in core e Unreal locale.
