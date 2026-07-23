# Sistema degli archetipi edilizi romani

Il Prompt 22 introduce un modello planimetrico C++ standard per descrivere archetipi edilizi romani senza dipendenze Unreal. Il sistema genera `BuildingPlan`, valida topologia, flussi produttivi, acqua, drenaggio e punti NPC, poi converte la planimetria in `ModulePlacement` riusabili dal runtime placeholder.

Stati: `BUILDING_ARCHETYPE_STATIC_CHECKS_PASSED`, `UNREAL_BUILD_REQUIRED`, `UNREAL_AUTOMATION_REQUIRED`, `MANUAL_VERIFICATION_REQUIRED`, `FAB_ASSET_IMPORT_NOT_STARTED`.

## Archetipi implementati

- `AtriumDomus`: asse strada → fauces → atrium → tablinum → peristilio/hortus; supporta impluvium, cubicula laterali, alae, culina, latrina, servizi, piano superiore e tabernae frontali.
- `Thermopolium`: shopfront, counter, dolia, retrobottega, deposito, preparazione, zona fuoco separata e posizioni cliente/venditore/coda.
- `Fullonica`: ricezione, lavaggio, trattamento, asciugatura, deposito, vasche, canali e drenaggio.
- `Pistrinum`: deposito grano, macina, percorso animale semanticamente circolare, forno, impasto e deposito/vendita pane.
- `PublicLatrine`: sedute, canale di scarico, canaletta d'acqua, vasca di servizio e capacità positiva.
- `SmallTemple`: podio, scala frontale, pronao, cella, colonne, trave, tetto, statua cultuale futura e altare opzionale.

## Archetipi pianificati

Gli archetipi non implementati sono registrati nel catalogo con `ARCHETYPE_PLANNED`, categoria, scala, funzione, requisiti e priorità futura. Non sono dichiarati completati.

## Limiti

Le regole marcate `HISTORICAL_APPROXIMATION` sono plausibili ma semplificate. I placeholder usano primitive Engine temporanee e non sostituiscono asset artistici finali.


## Prompt 23 — Tessuto residenziale, commerciale e misto

Aggiunti sedici archetipi ordinari (DomusMedia, PeristyleDomus, RichDomus, PopularHouse, Insula, Cenaculum, MixedUseHouse, Taberna, Popina, Caupona, Bookshop, Brothel, MedicalShop, BarberShop, MensaArgentaria, Stabulum), profili RomanBuildingUrbanProfile, pesi GetRecommendedUrbanComposition e stati CORE_CPP_DEBUG_TESTS_PASSED, CORE_CPP_RELEASE_TESTS_PASSED, CORE_CPP_SANITIZERS_PASSED, RESIDENTIAL_COMMERCIAL_STATIC_CHECKS_PASSED, UNREAL_BUILD_REQUIRED, UNREAL_AUTOMATION_REQUIRED, MANUAL_VERIFICATION_REQUIRED, FAB_ASSET_IMPORT_NOT_STARTED. Le ricostruzioni ordinarie sono HISTORICAL_APPROXIMATION e usano placeholder, senza .uasset/.umap.
# Estensione Prompt 24

Il catalogo include terme, reti idriche/fognarie e strutture produttive ordinarie; tutte usano la stessa pipeline `BuildingPlan` → placeholder.
# Lettura visuale Prompt 25

PopularHouse, DomusMedia, BathComplex, MetalWorkshop, UrbanGarden, Taberna, Thermopolium, PublicFountain, AqueductSection e ServiceYard sono riuniti in due fronti urbani. Il catalogo visuale associa categorie modulari a fallback sostituibili; planimetrie, seed e validazione restano nel core Prompt 22–24.
## Accessibilità Prompt 29

PopularHouse, DomusMedia, Taberna, Thermopolium, BathComplex e MetalWorkshop sono classificati come archetipi accessibili nella vertical slice. Funzione, ricchezza e usura guidano stile e pavimento.
