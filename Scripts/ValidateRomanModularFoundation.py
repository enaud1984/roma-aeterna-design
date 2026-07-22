#!/usr/bin/env python3
"""Validazione statica della fondazione modulare e del runtime placeholder romano."""
from pathlib import Path
import json
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
ERRORS = []
CONFLICT_MARKERS = ("<" * 7, "=" * 7, ">" * 7)
FORBIDDEN_CODE_TOKENS = ("UnrealEd", "GEditor", "AssetTools", "SavePackage", "/workspace/", "C:\\")
BASIC_SHAPES = ("/Engine/BasicShapes/Cube.Cube", "/Engine/BasicShapes/Cylinder.Cylinder", "/Engine/BasicShapes/Sphere.Sphere", "/Engine/BasicShapes/Cone.Cone")
LOCAL_EXTERNAL_ROOTS = (
    "Content/ThirdParty/", "Content/LocalAssets/", "Content/ImportedAssets/",
)

REQUIRED_FILES = [
    "Source/RomaAeterna/Public/World/Modular/RARomanModularTypes.h",
    "Source/RomaAeterna/Public/World/Modular/RARomanProceduralBuildingActor.h",
    "Source/RomaAeterna/Private/World/Modular/RARomanProceduralBuildingActor.cpp",
    "Source/RomaAeterna/Private/Tests/RARomanProceduralBuildingRuntimeTests.cpp",
    "Source/RomaAeterna/Private/Tests/RARomanBuildingArchetypeTests.cpp",
    "docs/technical/ROMAN_BUILDING_ARCHETYPE_SYSTEM.md",
    "docs/technical/POMPEIAN_BUILDING_TYPOLOGIES.md",
    "docs/technical/ROMAN_PRODUCTION_BUILDINGS.md",
    "docs/technical/ROMAN_BUILDING_INTERACTION_POINTS.md",
    "docs/testing/ROMAN_BUILDING_ARCHETYPES_TEST_PLAN.md",
    "docs/audits/PROMPT_22_IMPLEMENTATION_REPORT.md",
    "docs/audits/PROMPT_23_IMPLEMENTATION_REPORT.md",
    "docs/technical/ROMAN_RESIDENTIAL_ARCHETYPES.md",
    "docs/technical/ROMAN_COMMERCIAL_ARCHETYPES.md",
    "docs/technical/ROMAN_MIXED_USE_BUILDINGS.md",
    "docs/technical/ROMAN_URBAN_ARCHETYPE_PROFILES.md",
    "docs/technical/ROMAN_INSULA_AND_CENACULA.md",
    "docs/testing/ROMAN_RESIDENTIAL_COMMERCIAL_TEST_PLAN.md",
    "Scripts/TestRomanResidentialCommercialArchetypes.ps1",
    "Source/RomaAeternaCore/include/RARomanModularCore.h",
    "Source/RomaAeternaCore/tests/RARomanModularCoreTests.cpp",
    "Source/RomaAeterna/RomaAeterna.Build.cs",
    "docs/assets/FREE_ASSET_REGISTER.md",
    "IMPLEMENTATION_STATUS.md",
    "Scripts/TestRomanUtilitiesAndProduction.ps1",
    "Source/RomaAeterna/Private/Tests/RARomanUtilitiesProductionTests.cpp",
    "docs/technical/ROMAN_BATH_COMPLEX.md",
    "docs/technical/ROMAN_WATER_AND_SEWER_SYSTEM.md",
    "docs/technical/ROMAN_PRODUCTION_ARCHETYPES.md",
    "docs/technical/ROMAN_UTILITY_CONNECTIONS.md",
    "docs/testing/ROMAN_UTILITIES_PRODUCTION_TEST_PLAN.md",
    "docs/audits/PROMPT_24_IMPLEMENTATION_REPORT.md",
    "Content/Maps/RomaAeternaVerticalSlice.umap",
    "Scripts/CreateRomaAeternaVerticalSlice.py",
    "Scripts/TestRomaAeternaVerticalSlice.ps1",
    "Source/RomaAeterna/Public/Game/RAVerticalSliceGameMode.h",
    "Source/RomaAeterna/Private/Game/RAVerticalSliceGameMode.cpp",
    "Source/RomaAeterna/Private/Tests/RAVerticalSliceTests.cpp",
    "docs/technical/ROMA_AETERNA_VERTICAL_SLICE.md",
    "docs/testing/ROMA_AETERNA_VERTICAL_SLICE_TEST_PLAN.md",
    "docs/audits/PROMPT_24_BIS_IMPLEMENTATION_REPORT.md",
    "Scripts/TestRomaAeternaVisualConsolidation.ps1",
    "Source/RomaAeterna/Public/World/Modular/RARomanVisualCatalog.h",
    "Source/RomaAeterna/Private/World/Modular/RARomanVisualCatalog.cpp",
    "Source/RomaAeterna/Private/Tests/RAVisualConsolidationTests.cpp",
    "docs/technical/ROMAN_VISUAL_PLACEHOLDER_SYSTEM.md",
    "docs/technical/ROMAN_ASSET_INTEGRATION_ARCHITECTURE.md",
    "docs/assets/ROMAN_ASSET_CATALOG_TEMPLATE.md",
    "docs/testing/ROMA_AETERNA_VISUAL_CONSOLIDATION_TEST_PLAN.md",
    "docs/audits/PROMPT_25_IMPLEMENTATION_REPORT.md",
    "Scripts/AuditRomanAssets.py",
    "Scripts/tests/test_audit_roman_assets.py",
    "docs/assets/roman_asset_catalog.json",
    "docs/assets/ROMAN_ASSET_REQUIREMENTS.md",
    "docs/assets/ROMAN_ASSET_CANDIDATES.md",
    "docs/assets/ROMAN_ASSET_SHORTLISTS.md",
    "docs/assets/ROMAN_ASSET_IMPORT_BATCHES.md",
    "docs/assets/ROMAN_ASSET_SOURCE_REGISTRY.md",
    "docs/assets/ROMAN_ASSET_FOLDER_STRUCTURE.md",
    "docs/assets/ROMAN_ASSET_NAMING_CONVENTION.md",
    "docs/assets/ROMAN_ASSET_VISUAL_CATALOG_MAPPING.md",
    "docs/assets/ROMAN_ASSET_GIT_STRATEGY.md",
    "docs/assets/ROMAN_LOCAL_ASSET_INSTALLATION.md",
    "docs/testing/ROMAN_ASSET_AUDIT_TEST_PLAN.md",
    "docs/audits/PROMPT_26_IMPLEMENTATION_REPORT.md",
    "Scripts/ImportRomanAssetBatch1.py",
    "Scripts/TestRomanLocalAssetIntegration.ps1",
    "Source/RomaAeterna/Private/Tests/RALocalAssetIntegrationTests.cpp",
    "Config/LocalAssets/RomanAssetBatch1.template.json",
    "docs/assets/ROMAN_ASSET_BATCH_1_IMPORT_REPORT.md",
    "docs/assets/ROMAN_ASSET_BATCH_1_LOCAL_MAPPING.md",
    "docs/assets/ROMAN_ASSET_BATCH_1_TECHNICAL_AUDIT.md",
    "docs/assets/ROMAN_ASSET_BATCH_1_HISTORICAL_REVIEW.md",
    "docs/testing/ROMAN_LOCAL_ASSET_INTEGRATION_TEST_PLAN.md",
    "docs/audits/PROMPT_27_IMPLEMENTATION_REPORT.md",
]


def read(rel):
    path = ROOT / rel
    if not path.exists():
        ERRORS.append(f"file mancante: {rel}")
        return ""
    return path.read_text(encoding="utf-8", errors="ignore")


def all_text(paths):
    return "\n".join(read(path) for path in paths)


for required in REQUIRED_FILES:
    read(required)

source_paths = [str(path.relative_to(ROOT)) for base in (ROOT / "Source").rglob("*") if base.suffix in {".h", ".cpp", ".cs"} for path in [base]]
source_text = all_text(source_paths)
actor_h = read("Source/RomaAeterna/Public/World/Modular/RARomanProceduralBuildingActor.h")
actor_cpp = read("Source/RomaAeterna/Private/World/Modular/RARomanProceduralBuildingActor.cpp")
core_text = read("Source/RomaAeternaCore/include/RARomanModularCore.h") + read("Source/RomaAeternaCore/tests/RARomanModularCoreTests.cpp")

for token in FORBIDDEN_CODE_TOKENS:
    if token in source_text:
        ERRORS.append(f"token vietato nel codice sorgente: {token}")

for token in ("UInstancedStaticMeshComponent", "CategoryInstanceComponents", "BuildVisualInstances", "ClearVisualInstances"):
    if token not in actor_h + actor_cpp:
        ERRORS.append(f"runtime placeholder incompleto: {token}")

for api in ("GenerateBuilding", "ClearGeneratedBuilding", "RebuildBuilding", "GenerateFromParameters", "GetGeneratedInstanceCount", "GetInstanceCountByCategory", "HasGeneratedBuilding", "GenerateBuildingByType", "GenerateAtriumDomus", "GenerateThermopolium", "GenerateFullonica", "GeneratePistrinum", "GeneratePublicLatrine", "GenerateSmallTemple", "GenerateDomusMedia", "GeneratePeristyleDomus", "GenerateRichDomus", "GeneratePopularHouse", "GenerateInsula", "GenerateCenaculum", "GenerateMixedUseHouse", "GenerateTaberna", "GeneratePopina", "GenerateCaupona", "GenerateBookshop", "GenerateBrothel", "GenerateMedicalShop", "GenerateBarberShop", "GenerateMensaArgentaria", "GenerateStabulum", "GetResidentCapacity", "GetWorkerCapacity", "GetCustomerCapacity", "GetApartmentCount", "GetCommercialUnitCount", "GetResidentialUnitCount", "GetUrbanProfileSummary", "GetFrequencyClass", "GetCompatibleUrbanZones", "GetGeneratedRoomCount", "GetGeneratedZoneCount", "GetGeneratedInteractionPointCount", "GetProductionDeviceCount", "GetWaterFeatureCount", "GetBuildingPlanSummary", "GetImplementedArchetypes", "IsArchetypeImplemented"):
    if api not in actor_h:
        ERRORS.append(f"API Blueprint/runtime mancante: {api}")

for shape in BASIC_SHAPES:
    if shape not in actor_cpp:
        ERRORS.append(f"soft reference Engine BasicShapes mancante: {shape}")

if "ConstructorHelpers" in actor_cpp:
    ERRORS.append("ConstructorHelpers non deve essere usato dal runtime placeholder")

if re.search(r"NewObject\s*<\s*UStaticMeshComponent\s*>", actor_cpp):
    ERRORS.append("creazione per-modulo di UStaticMeshComponent rilevata")

for unreal_token in ("UObject", "USTRUCT", "UENUM", "FVector", "FTransform", "TArray", "FString", "FName", "CoreMinimal.h", "Engine/"):
    if unreal_token in core_text:
        ERRORS.append(f"dipendenza Unreal nel core standard: {unreal_token}")

for core_api in ("BuildSimpleHouseLayout", "BuildTabernaLayout", "BuildTempleLayout", "BuildStreetSectionLayout", "ValidatePlacements", "EnforceMaximumModuleCount", "GenerateBuildingPlan", "GenerateAtriumDomusPlan", "GenerateThermopoliumPlan", "GenerateFullonicaPlan", "GeneratePistrinumPlan", "GeneratePublicLatrinePlan", "GenerateSmallTemplePlan", "GenerateDomusMediaPlan", "GeneratePeristyleDomusPlan", "GenerateRichDomusPlan", "GeneratePopularHousePlan", "GenerateInsulaPlan", "GenerateCenaculumPlan", "GenerateMixedUseHousePlan", "GenerateTabernaPlan", "GeneratePopinaPlan", "GenerateCauponaPlan", "GenerateBookshopPlan", "GenerateBrothelPlan", "GenerateMedicalShopPlan", "GenerateBarberShopPlan", "GenerateMensaArgentariaPlan", "GenerateStabulumPlan", "GetUrbanProfileForBuildingType", "GetRecommendedUrbanComposition", "ValidateCompositeBuildingPlan", "CalculateResidentCapacity", "CalculateWorkerCapacity", "CalculateCustomerCapacity", "ValidateBuildingPlan", "ValidateRoomConnectivity", "ValidateProductionFlow", "ValidateWaterFlow", "ValidateInteractionPoints", "ValidateArchetypeRequirements", "ConvertBuildingPlanToPlacements", "GetImplementedArchetypes", "IsArchetypeImplemented"):
    if core_api not in core_text:
        ERRORS.append(f"API core mancante: {core_api}")


for enum_token in ("BuildingFunction", "BuildingScale", "AccessType", "ZoneFunction", "RoomType", "InteractionPointType", "FrequencyClass", "UrbanZone", "StreetClass", "ImpactLevel"):
    if enum_token not in core_text:
        ERRORS.append(f"enum Prompt 22 mancante: {enum_token}")

for struct_token in ("BuildingZone", "RoomDefinition", "RoomConnection", "CourtyardDefinition", "OpenSpaceDefinition", "WorkAreaDefinition", "CommercialCounterDefinition", "ProductionDeviceDefinition", "WaterFeatureDefinition", "ReligiousFeatureDefinition", "MonumentFeatureDefinition", "BuildingInteractionPoint", "BuildingPlan", "BuildingPlanParameters", "BuildingPlanResult", "BuildingPlanMessage", "RomanBuildingUrbanProfile", "ApartmentUnitDefinition", "BuildingSubArchetype", "CompositeBuildingPlan", "BuildingUseUnit"):
    if struct_token not in core_text:
        ERRORS.append(f"tipo core Prompt 22 mancante: {struct_token}")

for archetype in ("AtriumDomus", "Thermopolium", "Fullonica", "Pistrinum", "PublicLatrine", "SmallTemple", "DomusMedia", "PeristyleDomus", "RichDomus", "PopularHouse", "Insula", "Cenaculum", "MixedUseHouse", "Taberna", "Popina", "Caupona", "Bookshop", "Brothel", "MedicalShop", "BarberShop", "MensaArgentaria", "Stabulum"):
    if archetype not in core_text + actor_h + actor_cpp:
        ERRORS.append(f"archetipo implementato mancante: {archetype}")

for planned in ("PeristyleDomus", "RichDomus", "UrbanVilla", "SuburbanVilla", "Insula", "Taberna", "Popina", "Caupona", "Bookshop", "Brothel", "Macellum", "Market", "Horrea", "BathComplex", "Forum", "Basilica", "Curia", "Theatre", "Odeon", "Amphitheatre", "LargeTemple", "Sanctuary", "CityGate", "CityWall", "MonumentalArch", "PublicFountain", "FountainMonument", "Library", "School", "Stable", "MedicalShop", "BarberShop"):
    if planned not in core_text or "ARCHETYPE_PLANNED" not in core_text:
        ERRORS.append(f"archetipo pianificato non registrato: {planned}")

for category in ("Bed", "Table", "Bench", "WritingDesk", "ScrollStorage", "MirrorMarker", "StablePartition", "FeedingTrough", "WateringTrough", "Balcony", "SharedStair", "ApartmentDoor", "ShopOpening", "ValueStorageMarker", "Counter", "Dolium", "Basin", "WaterChannel", "Millstone", "Oven", "Furnace", "Workbench", "Seat", "LatrineSeat", "Drain", "Altar", "Shrine", "StatueMarker", "AnimalPath", "ShopSign", "Shelf", "StorageContainer", "GardenFeature", "Fountain", "MosaicZone", "FrescoZone", "DryingRack", "WorkPlatform", "RotationArm", "ServiceBasin", "InteractionMarker"):
    if category not in core_text + read("Source/RomaAeterna/Public/World/Modular/RARomanModularTypes.h"):
        ERRORS.append(f"categoria modulare Prompt 22 mancante: {category}")

for tag in ("public_room", "private_room", "service_room", "commercial_area", "production_area", "customer_area", "animal_work_area", "fire_hazard_area", "water_required", "drainage_required", "food_preparation", "food_sales", "textile_processing", "grain_processing", "religious_area", "monumental_area", "fresco_candidate", "mosaic_candidate", "statue_candidate", "fountain_candidate", "shop_sign_candidate", "npc_workstation", "npc_customer_position", "npc_queue_position", "npc_service_route", "npc_animal_route", "restricted_area", "storage_area", "open_court", "street_facing", "upper_floor", "adult_service_area", "medical_service", "medicine_storage", "preparation_area", "customer_area", "financial_service", "waste_area", "HISTORICAL_APPROXIMATION"):
    if tag not in core_text:
        ERRORS.append(f"tag semantico mancante: {tag}")

for prompt24_type in ("UtilityType", "WaterSourceType", "DrainageType", "HeatSourceType", "ProductionFlowType", "UtilityConnection", "WaterNetworkNode", "DrainageNetworkNode", "HeatSourceDefinition", "HazardZoneDefinition", "ProductionStageDefinition", "ProductionFlowDefinition", "StorageUnitDefinition", "BathRoomDefinition", "HypocaustDefinition", "AqueductSegmentDefinition", "SewerSegmentDefinition"):
    if prompt24_type not in core_text:
        ERRORS.append(f"tipo utilities Prompt 24 mancante: {prompt24_type}")

for prompt24_archetype in ("BathComplex", "Palaestra", "CastellumAquae", "AqueductSection", "SewerSection", "PublicFountain", "Cistern", "Well", "Tinctoria", "Tannery", "TextileWorkshop", "MetalWorkshop", "PotteryWorkshop", "OilWorkshop", "Winery", "PressingWorkshop", "StandaloneOven", "Horrea", "UrbanGarden", "ServiceYard"):
    if f"Generate{prompt24_archetype}Plan" not in core_text:
        ERRORS.append(f"generatore core Prompt 24 mancante: {prompt24_archetype}")
    if f"Generate{prompt24_archetype}" not in actor_h:
        ERRORS.append(f"API Blueprint Prompt 24 mancante: {prompt24_archetype}")

for prompt24_api in ("ConnectBuildingToWater", "ConnectBuildingToDrainage", "ConnectBuildingToSewer", "ConnectBuildingToHeat", "ValidateUtilityConnections", "CalculateWaterDemand", "CalculateDrainageDemand", "CalculateHeatDemand", "CalculateStorageCapacity"):
    if prompt24_api not in core_text:
        ERRORS.append(f"API utility Prompt 24 mancante: {prompt24_api}")

for prompt24_category in ("AqueductArch", "AqueductChannel", "SewerChannel", "Manhole", "WaterOutlet", "FountainBasin", "WellHead", "CisternTank", "HypocaustPillar", "Furnace", "Boiler", "Press", "Loom", "PotteryWheel", "Anvil", "DryingFrame", "StorageCell", "CargoArea", "FuelStorage", "WasteArea", "IrrigationChannel"):
    if prompt24_category not in core_text + read("Source/RomaAeterna/Public/World/Modular/RARomanModularTypes.h"):
        ERRORS.append(f"categoria placeholder Prompt 24 mancante: {prompt24_category}")

vertical_character = read("Source/RomaAeterna/Public/Player/RACharacter.h") + read("Source/RomaAeterna/Private/Player/RACharacter.cpp")
vertical_game_mode = read("Source/RomaAeterna/Public/Game/RAVerticalSliceGameMode.h") + read("Source/RomaAeterna/Private/Game/RAVerticalSliceGameMode.cpp")
vertical_test = read("Source/RomaAeterna/Private/Tests/RAVerticalSliceTests.cpp")
vertical_script = read("Scripts/TestRomaAeternaVerticalSlice.ps1")
vertical_generator = read("Scripts/CreateRomaAeternaVerticalSlice.py")
engine_config = read("Config/DefaultEngine.ini")

for token in ("ACharacter", "ThirdPersonSpringArm", "ThirdPersonCamera", "CharacterMovement", "IA_Move", "IA_Look", "IA_Jump", "IA_Sprint", "IMC_Player", "UEnhancedInputLocalPlayerSubsystem"):
    if token not in vertical_character:
        ERRORS.append(f"fondazione Character vertical slice mancante: {token}")
for token in ("ARAVerticalSliceGameMode", "DefaultPawnClass", "ARACharacter", "ARAPlayerController"):
    if token not in vertical_game_mode:
        ERRORS.append(f"GameMode vertical slice incompleto: {token}")
for token in ("RomaAeterna.Prompt24Bis.VerticalSlice", "AutomationOpenMap", "RA_RESIDENTIAL", "RA_COMMERCIAL", "RA_BATH", "RA_WATER", "RA_PRODUCTIVE", "RA_UTILITY", "RebuildBuilding", "QueryAndPhysics"):
    if token not in vertical_test:
        ERRORS.append(f"Automation Test vertical slice incompleto: {token}")
for token in ("RunUAT.bat", "BuildTarget", "RomaAeternaEditor", "Prompt24Bis.VerticalSlice", "Test Completed. Result={Success}", "MANUAL_PIE_VERIFICATION_REQUIRED"):
    if token not in vertical_script:
        ERRORS.append(f"script locale vertical slice incompleto: {token}")
for token in ("RA_PlayerStart_VerticalSlice", "RA_RomanRoad", "generate_popular_house", "generate_taberna", "generate_bath_complex", "generate_public_fountain", "generate_metal_workshop", "generate_aqueduct_section"):
    if token not in vertical_generator:
        ERRORS.append(f"generatore mappa vertical slice incompleto: {token}")
for token in ("/Game/Maps/RomaAeternaVerticalSlice", "/Script/RomaAeterna.RAVerticalSliceGameMode"):
    if token not in engine_config:
        ERRORS.append(f"configurazione vertical slice mancante: {token}")

authorized_binary_assets = {
    "Content/RA/Dev/Maps/TechnicalSandbox.umap",
    "Content/Maps/RomaAeternaVerticalSlice.umap",
}
authorized_binary_assets.update({
    f"Content/Technical/Materials/{name}.uasset"
    for name in (
        "M_RA_TechnicalBase", "MI_RA_Stone", "MI_RA_RoadStone", "MI_RA_Sidewalk",
        "MI_RA_PlasterLight", "MI_RA_PlasterColor", "MI_RA_RoughMasonry", "MI_RA_Brick",
        "MI_RA_Wood", "MI_RA_RoofTile", "MI_RA_Water", "MI_RA_Metal", "MI_RA_Ground",
        "MI_RA_Vegetation", "MI_RA_Technical", "MI_RA_Hazard",
    )
})
for binary_asset in ROOT.joinpath("Content").rglob("*"):
    if binary_asset.is_file() and binary_asset.suffix.lower() in {".uasset", ".umap"}:
        relative_asset = binary_asset.relative_to(ROOT).as_posix()
        if relative_asset.startswith(LOCAL_EXTERNAL_ROOTS):
            continue
        if relative_asset not in authorized_binary_assets:
            ERRORS.append(f"asset binario Unreal non autorizzato: {relative_asset}")

for rel, text in (("Scripts/TestRomaAeternaVerticalSlice.ps1", vertical_script), ("Scripts/CreateRomaAeternaVerticalSlice.py", vertical_generator)):
    if re.search(r"[A-Za-z]:[\\/]", text):
        ERRORS.append(f"percorso assoluto hardcoded nello script vertical slice: {rel}")

visual_catalog = read("Source/RomaAeterna/Public/World/Modular/RARomanVisualCatalog.h") + read("Source/RomaAeterna/Private/World/Modular/RARomanVisualCatalog.cpp")
visual_test = read("Source/RomaAeterna/Private/Tests/RAVisualConsolidationTests.cpp")
visual_script = read("Scripts/TestRomaAeternaVisualConsolidation.ps1")
visual_docs = all_text([
    "docs/technical/ROMAN_VISUAL_PLACEHOLDER_SYSTEM.md",
    "docs/technical/ROMAN_ASSET_INTEGRATION_ARCHITECTURE.md",
    "docs/assets/ROMAN_ASSET_CATALOG_TEMPLATE.md",
    "docs/testing/ROMA_AETERNA_VISUAL_CONSOLIDATION_TEST_PLAN.md",
    "docs/audits/PROMPT_25_IMPLEMENTATION_REPORT.md",
])
for token in ("URARomanVisualCatalog", "FRARomanVisualCatalogEntry", "TSoftObjectPtr", "GetFallbackMeshPath", "GetTechnicalMaterialPath", "ReplacementAssetId"):
    if token not in visual_catalog:
        ERRORS.append(f"catalogo visuale incompleto: {token}")
for token in ("RA_ROMAN_ROAD", "RA_SIDEWALK", "RA_CROSSING_STONE", "RA_ALLEY", "RA_PLAZA", "RA_URBAN_FRONT_NORTH", "RA_URBAN_FRONT_SOUTH", "RA_DYNAMIC_LIGHT"):
    if token not in vertical_generator + visual_test:
        ERRORS.append(f"elemento consolidamento visuale mancante: {token}")
for token in ("RomaAeterna.Prompt25.VisualConsolidation", "MovableLightCount", "Materiale tecnico assegnato", "RebuildBuilding", "RA_TECHNICAL_LABEL"):
    if token not in visual_test:
        ERRORS.append(f"Automation Test Prompt 25 incompleto: {token}")
for token in ("MAP CHECK,Automation RunTests", "Lighting needs to be rebuilt", "DYNAMIC_LIGHTING_PASSED", "MAP_CHECK_PASSED", "MANUAL_PIE_VERIFICATION_REQUIRED"):
    if token not in visual_script:
        ERRORS.append(f"script consolidamento visuale incompleto: {token}")
for token in ("F1", "F2", "F3", "F4", "F5", "F6", "PlaceholderLeftArm", "PlaceholderRightLeg"):
    if token not in source_text:
        ERRORS.append(f"HUD/personaggio consolidato incompleto: {token}")
for token in ("AssetId", "License", "HistoricalCompatibility", "Pivot", "Nanite", "LOD", "MaterialSlots", "PerformanceTier", "IntendedArchetypes"):
    if token not in visual_docs:
        ERRORS.append(f"template/catalogazione asset incompleto: {token}")
if re.search(r"[A-Za-z]:[\\/]", visual_script):
    ERRORS.append("percorso assoluto hardcoded nello script Prompt 25")

asset_prompt26_files = [
    "docs/assets/ROMAN_ASSET_REQUIREMENTS.md",
    "docs/assets/ROMAN_ASSET_CANDIDATES.md",
    "docs/assets/ROMAN_ASSET_SHORTLISTS.md",
    "docs/assets/ROMAN_ASSET_IMPORT_BATCHES.md",
    "docs/assets/ROMAN_ASSET_SOURCE_REGISTRY.md",
    "docs/assets/ROMAN_ASSET_FOLDER_STRUCTURE.md",
    "docs/assets/ROMAN_ASSET_NAMING_CONVENTION.md",
    "docs/assets/ROMAN_ASSET_VISUAL_CATALOG_MAPPING.md",
    "docs/assets/ROMAN_ASSET_GIT_STRATEGY.md",
    "docs/testing/ROMAN_ASSET_AUDIT_TEST_PLAN.md",
    "docs/audits/PROMPT_26_IMPLEMENTATION_REPORT.md",
]
asset_prompt26_text = all_text(asset_prompt26_files)
for token in (
    "ASSET_REQUIREMENTS_COMPLETED", "FAB_RESEARCH_COMPLETED", "ASSET_CANDIDATES_VERIFIED",
    "ASSET_SHORTLIST_COMPLETED", "ASSET_IMPORT_PLAN_COMPLETED", "ASSET_LICENSE_REVIEW_REQUIRED",
    "FAB_ASSET_IMPORT_NOT_STARTED", "MANUAL_ACQUISITION_REQUIRED", "LOCAL_ASSET_ONLY_STRATEGY",
    "GIT_LFS_NOT_USED", "EXTERNAL_ASSETS_NOT_VERSIONED",
    "NOT_VERIFIED", "RA-FAB-ARCH-004", "Content/ThirdParty", "URARomanVisualCatalog",
):
    if token not in asset_prompt26_text + read("IMPLEMENTATION_STATUS.md"):
        ERRORS.append(f"documentazione Prompt 26 incompleta: {token}")

try:
    raw_asset_catalog = json.loads(read("docs/assets/roman_asset_catalog.json"))
except json.JSONDecodeError as exc:
    ERRORS.append(f"catalogo asset JSON non valido: {exc}")
    raw_asset_catalog = {"candidates": []}
asset_candidates = raw_asset_catalog.get("candidates", [])
if len(asset_candidates) < 24:
    ERRORS.append("catalogo Prompt 26 con meno di 24 candidati")
asset_ids = [candidate.get("asset_id") for candidate in asset_candidates]
if len(asset_ids) != len(set(asset_ids)):
    ERRORS.append("AssetId duplicati nel catalogo Prompt 26")
for candidate in asset_candidates:
    asset_id = candidate.get("asset_id", "NOT_VERIFIED")
    if not re.fullmatch(r"RA-(?:FAB|EPIC)-[A-Z]+-\d{3}", asset_id):
        ERRORS.append(f"AssetId Prompt 26 non valido: {asset_id}")
    if not str(candidate.get("url", "")).startswith("https://"):
        ERRORS.append(f"URL candidato Prompt 26 non valido: {asset_id}")
    if candidate.get("historical_grade") not in {"A", "B", "C", "D"}:
        ERRORS.append(f"classe storica Prompt 26 non valida: {asset_id}")

asset_audit_script = read("Scripts/AuditRomanAssets.py")
asset_audit_tests = read("Scripts/tests/test_audit_roman_assets.py")
for token in ("ASSET_AUDIT_", "roman_asset_audit.json", "roman_asset_audit.md", "--check-only", "Content/ThirdParty", "provenienza mancante", "git", "ls-files", "Asset esterno locale tracciato da Git"):
    if token not in asset_audit_script:
        ERRORS.append(f"AuditRomanAssets incompleto: {token}")
for token in ("test_parsing_catalogo", "test_rileva_categoria_mancante", "test_rileva_naming_errato", "test_rileva_file_grande", "test_rileva_provenienza_mancante", "test_report_deterministico", "test_funzione_audit_non_scrive", "test_asset_esterno_locale_non_tracciato_ammesso", "test_asset_esterno_locale_tracciato_rifiutato"):
    if token not in asset_audit_tests:
        ERRORS.append(f"test AuditRomanAssets mancante: {token}")
for rel in ("Scripts/AuditRomanAssets.py", "Scripts/tests/test_audit_roman_assets.py"):
    if re.search(r"(?<![A-Za-z])[A-Za-z]:[\\/]", read(rel)):
        ERRORS.append(f"percorso assoluto hardcoded nel Prompt 26: {rel}")

prompt27_files = [
    "Scripts/ImportRomanAssetBatch1.py",
    "Scripts/TestRomanLocalAssetIntegration.ps1",
    "Source/RomaAeterna/Public/World/Modular/RARomanVisualCatalog.h",
    "Source/RomaAeterna/Private/World/Modular/RARomanVisualCatalog.cpp",
    "Source/RomaAeterna/Private/Tests/RALocalAssetIntegrationTests.cpp",
    "Config/LocalAssets/RomanAssetBatch1.template.json",
    "docs/assets/ROMAN_ASSET_BATCH_1_IMPORT_REPORT.md",
    "docs/assets/ROMAN_ASSET_BATCH_1_LOCAL_MAPPING.md",
    "docs/assets/ROMAN_ASSET_BATCH_1_TECHNICAL_AUDIT.md",
    "docs/assets/ROMAN_ASSET_BATCH_1_HISTORICAL_REVIEW.md",
    "docs/testing/ROMAN_LOCAL_ASSET_INTEGRATION_TEST_PLAN.md",
    "docs/audits/PROMPT_27_IMPLEMENTATION_REPORT.md",
]
prompt27_text = all_text(prompt27_files) + read("IMPLEMENTATION_STATUS.md")
for token in (
    "--local-import-audit", "--batch", "--report-json", "--report-markdown",
    "ASSET_BATCH_1_LOCAL_AUDIT_PASSED", "LOCAL_ASSET_BATCH_NOT_INSTALLED",
    "LOCAL_ASSET_CATALOG_LOADED", "LOCAL_ASSET_CATALOG_NOT_FOUND_USING_FALLBACKS",
    "RomaAeterna.Prompt27.LocalAssetIntegration", "DA_RA_VisualCatalog_Batch1",
    "RomaAeternaAssetBatch1Preview", "F7", "Soft Object", "HISTORICAL_APPROXIMATION",
    "LOCAL_ASSET_ONLY_STRATEGY_CONFIRMED", "GIT_LFS_NOT_USED", "EXTERNAL_ASSETS_NOT_VERSIONED",
):
    if token not in asset_audit_script + prompt27_text:
        ERRORS.append(f"integrazione locale Prompt 27 incompleta: {token}")
for token in (
    "HistoricalGrade", "DistrictCompatibility", "WealthTiers", "VariationWeight",
    "ScaleCorrection", "RotationCorrection", "CollisionProfile", "bPreferNanite",
    "MaterialOverrides", "SourcePackage", "LicenseRegistryId", "GetLocalCatalogPath",
    "LoadLocalCatalog", "AreLocalAssetsEnabled",
):
    if token not in visual_catalog:
        ERRORS.append(f"metadato catalogo locale mancante: {token}")
for token in (
    "PlasteredWall03", "Bricks066", "Cobblestone05", "RoofingTiles013A",
    "Bricks042", "WoodPlanksGrey", "Ground039", "ASSET_BATCH_1_LOCAL_IMPORT_PASSED",
):
    if token not in read("Scripts/ImportRomanAssetBatch1.py"):
        ERRORS.append(f"import Batch 1 incompleto: {token}")
for rel in ("Scripts/ImportRomanAssetBatch1.py", "Scripts/TestRomanLocalAssetIntegration.ps1", "Config/LocalAssets/RomanAssetBatch1.template.json"):
    if re.search(r"(?<![A-Za-z])[A-Za-z]:[\\/]", read(rel)):
        ERRORS.append(f"percorso assoluto hardcoded nel Prompt 27: {rel}")

prompt28_files = [
    "Scripts/TestRomanArchitecturalMaterialReplacement.ps1",
    "Source/RomaAeterna/Private/Tests/RAArchitecturalMaterialReplacementTests.cpp",
    "docs/assets/ROMAN_BATCH_1_MATERIAL_ASSIGNMENT.md",
    "docs/assets/ROMAN_BATCH_1_ARCHETYPE_MAPPING.md",
    "docs/assets/ROMAN_BATCH_1_HISTORICAL_LIMITS.md",
    "docs/testing/ROMAN_ARCHITECTURAL_MATERIAL_REPLACEMENT_TEST_PLAN.md",
    "docs/audits/PROMPT_28_IMPLEMENTATION_REPORT.md",
]
prompt28_text = all_text(prompt28_files) + visual_catalog + read("Scripts/ImportRomanAssetBatch1.py") + read("IMPLEMENTATION_STATUS.md")
for token in (
    "ERARomanSurfaceRole", "ERARomanWeatheringLevel", "BuildingArchetypes",
    "SurfaceRole", "MaterialVariant", "WeatheringLevels", "UVScale", "UVRotation",
    "ColorTint", "RoughnessMultiplier", "NormalStrength", "AOIntensity", "FallbackMaterial",
    "ResolveEntry", "ResolutionCache", "SelectDeterministicWeightedIndex",
    "RomaAeterna.Prompt28.ArchitecturalMaterialReplacement",
    "--material-replacement-audit", "ARCHITECTURAL_MATERIAL_REPLACEMENT_AUDIT_PASSED",
    "ARCHITECTURAL_MATERIAL_REPLACEMENT_STATIC_CHECKS_PASSED",
    "LOCAL_MATERIAL_REPLACEMENT_PREVIEW_PASSED",
):
    if token not in prompt28_text + asset_audit_script:
        ERRORS.append(f"integrazione materiali Prompt 28 incompleta: {token}")
for instance_name in (
    "MI_RA_Local_Plaster_Light", "MI_RA_Local_Plaster_Ochre", "MI_RA_Local_Plaster_Red",
    "MI_RA_Local_Brick_Popular", "MI_RA_Local_Brick_Thermal", "MI_RA_Local_Road_Secondary",
    "MI_RA_Local_Roof_Terracotta", "MI_RA_Local_Wood_Dark", "MI_RA_Local_Wood_Worn",
    "MI_RA_Local_Ground_Dry", "MI_RA_Local_Ground_Productive",
):
    if instance_name not in prompt28_text:
        ERRORS.append(f"Material Instance Prompt 28 non configurata: {instance_name}")
for archetype in (
    "PopularHouse", "DomusMedia", "Taberna", "Thermopolium", "BathComplex",
    "PublicFountain", "MetalWorkshop", "AqueductSection", "UrbanGarden", "ServiceYard",
):
    if archetype not in prompt28_text:
        ERRORS.append(f"mapping archetipo Prompt 28 mancante: {archetype}")
for rel in ("Scripts/ImportRomanAssetBatch1.py", "Scripts/TestRomanArchitecturalMaterialReplacement.ps1", "Config/LocalAssets/RomanAssetBatch1.template.json"):
    if re.search(r"(?<![A-Za-z])[A-Za-z]:[\\/]", read(rel)):
        ERRORS.append(f"percorso assoluto hardcoded nel Prompt 28: {rel}")
for token in ("test_material_replacement_completo", "test_material_replacement_rifiuta_istanza_tracciata", "test_material_replacement_assente_supporta_fallback"):
    if token not in asset_audit_tests:
        ERRORS.append(f"test audit Prompt 28 mancante: {token}")

try:
    tracked_files = subprocess.run(
        ["git", "ls-files"], cwd=ROOT, check=True, capture_output=True, text=True,
    ).stdout.splitlines()
    external_tracked = [path for path in tracked_files if path.startswith(LOCAL_EXTERNAL_ROOTS)]
    if external_tracked:
        ERRORS.append(f"asset esterni tracciati: {', '.join(external_tracked)}")
    changed_files = subprocess.run(
        ["git", "diff", "--name-only", "HEAD"], cwd=ROOT, check=True, capture_output=True, text=True,
    ).stdout.splitlines()
    for protected_map in ("Content/Maps/RomaAeternaVerticalSlice.umap", "Content/RA/Dev/Maps/TechnicalSandbox.umap"):
        if protected_map in changed_files:
            ERRORS.append(f"mappa versionata modificata dal Prompt 27: {protected_map}")
except subprocess.CalledProcessError as exc:
    ERRORS.append(f"verifica Git Prompt 27 fallita: {exc}")

gitignore_text = read(".gitignore")
for ignored_local_asset_path in (
    "Content/ThirdParty/Fab/", "Content/ThirdParty/Megascans/",
    "Content/ThirdParty/Marketplace/", "Content/ThirdParty/External/",
    "Content/LocalAssets/", "Content/ImportedAssets/",
):
    if ignored_local_asset_path not in gitignore_text:
        ERRORS.append(f"cartella asset locale non ignorata: {ignored_local_asset_path}")
for required_tracked_path in ("Content/Technical/", "Content/Maps/RomaAeternaVerticalSlice.umap"):
    if required_tracked_path in gitignore_text:
        ERRORS.append(f"asset tecnico necessario escluso per errore: {required_tracked_path}")
if "GIT_LFS_" + "RECOMMENDED" in asset_prompt26_text + read("IMPLEMENTATION_STATUS.md"):
    ERRORS.append("strategia Git LFS obsoleta ancora documentata")

free_register = read("docs/assets/FREE_ASSET_REGISTER.md")
for idx in range(27, 37):
    if f"FREE-{idx:03d}" not in free_register:
        ERRORS.append(f"voce asset gratuita mancante: FREE-{idx:03d}")

tracked_binary_names = [line for line in (ROOT / ".git").exists() and [] or []]
for path in ROOT.rglob("*"):
    relative_parts = path.relative_to(ROOT).parts
    if any(part in {".git", "Binaries", "Intermediate", "Saved"} for part in relative_parts) or path.is_dir():
        continue
    rel = str(path.relative_to(ROOT))
    if path.suffix in {".uasset", ".umap"} and path.stat().st_mtime_ns > 0:
        # I file binari preesistenti sono ammessi solo se già tracciati: verifica demandata a git diff --name-only nel test finale.
        pass
    if path.suffix in {".h", ".cpp", ".cs", ".py", ".ps1", ".md", ".txt"}:
        text = path.read_text(encoding="utf-8", errors="ignore")
        for marker in CONFLICT_MARKERS:
            if marker in text:
                ERRORS.append(f"marcatore conflitto Git in {rel}: {marker}")

status_docs = all_text([
    "IMPLEMENTATION_STATUS.md",
    "docs/technical/ROMAN_MODULAR_FOUNDATION_IMPLEMENTATION.md",
    "docs/technical/ROMAN_MODULAR_CORE_CPP.md",
    "docs/testing/ROMAN_MODULAR_FOUNDATION_TEST_PLAN.md",
])
for state in ("CORE_CPP_DEBUG_TESTS_PASSED", "CORE_CPP_RELEASE_TESTS_PASSED", "CORE_CPP_SANITIZERS_PASSED", "PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED", "BUILDING_ARCHETYPE_STATIC_CHECKS_PASSED", "RESIDENTIAL_COMMERCIAL_STATIC_CHECKS_PASSED", "UNREAL_BUILD_REQUIRED", "UNREAL_AUTOMATION_REQUIRED", "MANUAL_VERIFICATION_REQUIRED", "FAB_ASSET_IMPORT_NOT_STARTED"):
    if state not in status_docs:
        ERRORS.append(f"stato richiesto non documentato: {state}")

if ERRORS:
    print("FAILED_STATIC")
    print("\n".join(ERRORS))
    sys.exit(1)

print("PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED")
print("BUILDING_ARCHETYPE_STATIC_CHECKS_PASSED")
print("RESIDENTIAL_COMMERCIAL_STATIC_CHECKS_PASSED")
print("UTILITIES_PRODUCTION_STATIC_CHECKS_PASSED")
print("VERTICAL_SLICE_STATIC_CHECKS_PASSED")
print("VISUAL_CONSOLIDATION_STATIC_CHECKS_PASSED")
print("ASSET_CATALOG_STATIC_CHECKS_PASSED")
print("LOCAL_ASSET_INTEGRATION_STATIC_CHECKS_PASSED")
print("ARCHITECTURAL_MATERIAL_REPLACEMENT_STATIC_CHECKS_PASSED")
print("PASSED_STATIC: validazione archetipi edilizi romani completata")
