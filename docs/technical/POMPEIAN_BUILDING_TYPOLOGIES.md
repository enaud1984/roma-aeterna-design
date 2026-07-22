# Tipologie edilizie pompeiane

Il catalogo copre categorie residenziali, commerciali, produttive, civiche, religiose, sanitarie, idrauliche, monumentali e urbane. Le tipologie implementate in questa fase sono sei; le altre restano `ARCHETYPE_PLANNED`.

## Rapporto con Pompei

Gli archetipi modellano funzioni frequenti nella città vesuviana: domus ad atrio, thermopolia, fullonicae, pistrina, latrine pubbliche e piccoli luoghi cultuali. La ricostruzione rimane modulare per consentire futuri raffinamenti basati su isolati, fronti stradali, decorazioni parietali e asset Fab verificati.


## Prompt 23 — Tessuto residenziale, commerciale e misto

Aggiunti sedici archetipi ordinari (DomusMedia, PeristyleDomus, RichDomus, PopularHouse, Insula, Cenaculum, MixedUseHouse, Taberna, Popina, Caupona, Bookshop, Brothel, MedicalShop, BarberShop, MensaArgentaria, Stabulum), profili RomanBuildingUrbanProfile, pesi GetRecommendedUrbanComposition e stati CORE_CPP_DEBUG_TESTS_PASSED, CORE_CPP_RELEASE_TESTS_PASSED, CORE_CPP_SANITIZERS_PASSED, RESIDENTIAL_COMMERCIAL_STATIC_CHECKS_PASSED, UNREAL_BUILD_REQUIRED, UNREAL_AUTOMATION_REQUIRED, MANUAL_VERIFICATION_REQUIRED, FAB_ASSET_IMPORT_NOT_STARTED. Le ricostruzioni ordinarie sono HISTORICAL_APPROXIMATION e usano placeholder, senza .uasset/.umap.
