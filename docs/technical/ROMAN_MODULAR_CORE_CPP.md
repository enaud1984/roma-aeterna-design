# Core C++ standard del sistema modulare romano

## Motivazione

Il Prompt 20-BIS separa gli algoritmi puri del sistema modulare romano dalle classi Unreal. La separazione consente di compilare e testare nel cloud normalizzazione, validazione, stime e layout astratti senza richiedere Unreal Engine 5.8.

## Architettura core/adapters

- `Source/RomaAeternaCore/include/RARomanModularCore.h`: libreria header-only C++17 senza dipendenze Unreal.
- `Source/RomaAeternaCore/tests/RARomanModularCoreTests.cpp`: test runner standard senza framework esterni.
- `Source/RomaAeterna/Private/World/Modular/RARomanBuildingRuleLibrary.cpp`: adapter Unreal che converte `FRARomanBuildingParameters` nei tipi core, invoca il core e riconverte i risultati Blueprint.
- `Source/RomaAeterna/Private/World/Modular/RARomanConstructionValidator.cpp`: adapter di validazione placement verso il core.

Il core non include `UObject`, `USTRUCT`, `UENUM`, `FVector`, `FTransform`, `TArray`, `FString`, `FName`, `TSoftObjectPtr`, macro Unreal o header Unreal Engine.

## Tipi standard

I tipi standard principali sono:

- `RomaAeternaCore::BuildingParameters`;
- `RomaAeternaCore::ModulePlacement`;
- `RomaAeternaCore::GenerationMessage`;
- `RomaAeternaCore::GenerationResult`;
- `RomaAeternaCore::Vector3`;
- `RomaAeternaCore::Transform`;
- `RomaAeternaCore::Bounds`.

Sono usati `std::string`, `std::vector`, `std::int32_t`, `std::uint32_t`, `enum class` e `double`. `double` è stato scelto per aumentare la stabilità dei calcoli dimensionali in centimetri e nei casi limite molto grandi.

## API core

Il core espone: `NormalizeBuildingParameters`, `ValidateBuildingParameters`, `CalculateBayWidth`, `CalculateFloorHeight`, `CalculateGridAlignedValue`, `CalculateGridAlignedTransform`, `CalculateBuildingBounds`, `EstimateRequiredModules`, `BuildSimpleHouseLayout`, `BuildTabernaLayout`, `BuildTempleLayout`, `BuildStreetSectionLayout`, `ValidatePlacements`, `IsFinite`, `IsScaleValid` ed `EnforceMaximumModuleCount`.

## Determinismo

Il core non usa generatori casuali globali. La variazione deterministica dipende da `RandomSeed` tramite una miscela intera locale; stessi parametri e stesso seed producono la stessa sequenza di placement, mentre seed diversi possono variare il bay dell'accesso e delle finestre.

## Integrazione Unreal

L'API Blueprint pubblica resta invariata. Le classi Unreal fungono da adapter e mantengono tipi, nomi e funzioni Blueprint già introdotti nel Prompt 20. La compilazione Unreal resta `UNREAL_BUILD_REQUIRED` e gli Automation Tests restano `UNREAL_AUTOMATION_REQUIRED` fino all'esecuzione su Unreal Engine 5.8 locale.

## Limiti

Il core produce layout astratti, non asset, non componenti e non collisioni. Play In Editor resta `MANUAL_VERIFICATION_REQUIRED`.

## Aggiornamento Prompt 21 — test determinismo e categorie

I test standard CMake/CTest sono stati ampliati per controllare categorie attese nei quattro layout, trasformazioni finite, bounds coerenti, ordine stabile, chiamate ripetute identiche e rispetto di `MaximumModuleCount`. Il core resta indipendente da Unreal e non contiene riferimenti a primitive Engine. Stati: CORE_CPP_DEBUG_TESTS_PASSED, CORE_CPP_RELEASE_TESTS_PASSED, CORE_CPP_SANITIZERS_PASSED.

## Aggiornamento Prompt 22 — BuildingPlan

Il core espone `GenerateBuildingPlan`, generatori per i sei archetipi, `ValidateBuildingPlan`, `ValidateRoomConnectivity`, `ValidateProductionFlow`, `ValidateWaterFlow`, `ValidateInteractionPoints`, `ValidateArchetypeRequirements`, `ConvertBuildingPlanToPlacements`, `GetImplementedArchetypes` e `IsArchetypeImplemented`. Stati cloud attesi dopo test: `CORE_CPP_DEBUG_TESTS_PASSED`, `CORE_CPP_RELEASE_TESTS_PASSED`, `CORE_CPP_SANITIZERS_PASSED`.


## Prompt 23 — Tessuto residenziale, commerciale e misto

Aggiunti sedici archetipi ordinari (DomusMedia, PeristyleDomus, RichDomus, PopularHouse, Insula, Cenaculum, MixedUseHouse, Taberna, Popina, Caupona, Bookshop, Brothel, MedicalShop, BarberShop, MensaArgentaria, Stabulum), profili RomanBuildingUrbanProfile, pesi GetRecommendedUrbanComposition e stati CORE_CPP_DEBUG_TESTS_PASSED, CORE_CPP_RELEASE_TESTS_PASSED, CORE_CPP_SANITIZERS_PASSED, RESIDENTIAL_COMMERCIAL_STATIC_CHECKS_PASSED, UNREAL_BUILD_REQUIRED, UNREAL_AUTOMATION_REQUIRED, MANUAL_VERIFICATION_REQUIRED, FAB_ASSET_IMPORT_NOT_STARTED. Le ricostruzioni ordinarie sono HISTORICAL_APPROXIMATION e usano placeholder, senza .uasset/.umap.
