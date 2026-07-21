#!/usr/bin/env python3
"""Validazione statica della fondazione modulare e del runtime placeholder romano."""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
ERRORS = []
CONFLICT_MARKERS = ("<" * 7, "=" * 7, ">" * 7)
FORBIDDEN_CODE_TOKENS = ("UnrealEd", "GEditor", "AssetTools", "SavePackage", "/workspace/", "C:\\")
BASIC_SHAPES = ("/Engine/BasicShapes/Cube.Cube", "/Engine/BasicShapes/Cylinder.Cylinder", "/Engine/BasicShapes/Sphere.Sphere", "/Engine/BasicShapes/Cone.Cone")

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
    "Source/RomaAeternaCore/include/RARomanModularCore.h",
    "Source/RomaAeternaCore/tests/RARomanModularCoreTests.cpp",
    "Source/RomaAeterna/RomaAeterna.Build.cs",
    "docs/assets/FREE_ASSET_REGISTER.md",
    "IMPLEMENTATION_STATUS.md",
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

for api in ("GenerateBuilding", "ClearGeneratedBuilding", "RebuildBuilding", "GenerateFromParameters", "GetGeneratedInstanceCount", "GetInstanceCountByCategory", "HasGeneratedBuilding", "GenerateBuildingByType", "GenerateAtriumDomus", "GenerateThermopolium", "GenerateFullonica", "GeneratePistrinum", "GeneratePublicLatrine", "GenerateSmallTemple", "GetGeneratedRoomCount", "GetGeneratedZoneCount", "GetGeneratedInteractionPointCount", "GetProductionDeviceCount", "GetWaterFeatureCount", "GetBuildingPlanSummary", "GetImplementedArchetypes", "IsArchetypeImplemented"):
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

for core_api in ("BuildSimpleHouseLayout", "BuildTabernaLayout", "BuildTempleLayout", "BuildStreetSectionLayout", "ValidatePlacements", "EnforceMaximumModuleCount", "GenerateBuildingPlan", "GenerateAtriumDomusPlan", "GenerateThermopoliumPlan", "GenerateFullonicaPlan", "GeneratePistrinumPlan", "GeneratePublicLatrinePlan", "GenerateSmallTemplePlan", "ValidateBuildingPlan", "ValidateRoomConnectivity", "ValidateProductionFlow", "ValidateWaterFlow", "ValidateInteractionPoints", "ValidateArchetypeRequirements", "ConvertBuildingPlanToPlacements", "GetImplementedArchetypes", "IsArchetypeImplemented"):
    if core_api not in core_text:
        ERRORS.append(f"API core mancante: {core_api}")


for enum_token in ("BuildingFunction", "BuildingScale", "AccessType", "ZoneFunction", "RoomType", "InteractionPointType"):
    if enum_token not in core_text:
        ERRORS.append(f"enum Prompt 22 mancante: {enum_token}")

for struct_token in ("BuildingZone", "RoomDefinition", "RoomConnection", "CourtyardDefinition", "OpenSpaceDefinition", "WorkAreaDefinition", "CommercialCounterDefinition", "ProductionDeviceDefinition", "WaterFeatureDefinition", "ReligiousFeatureDefinition", "MonumentFeatureDefinition", "BuildingInteractionPoint", "BuildingPlan", "BuildingPlanParameters", "BuildingPlanResult", "BuildingPlanMessage"):
    if struct_token not in core_text:
        ERRORS.append(f"tipo core Prompt 22 mancante: {struct_token}")

for archetype in ("AtriumDomus", "Thermopolium", "Fullonica", "Pistrinum", "PublicLatrine", "SmallTemple"):
    if archetype not in core_text + actor_h + actor_cpp:
        ERRORS.append(f"archetipo implementato mancante: {archetype}")

for planned in ("PeristyleDomus", "RichDomus", "UrbanVilla", "SuburbanVilla", "Insula", "Taberna", "Popina", "Caupona", "Bookshop", "Brothel", "Macellum", "Market", "Horrea", "BathComplex", "Forum", "Basilica", "Curia", "Theatre", "Odeon", "Amphitheatre", "LargeTemple", "Sanctuary", "CityGate", "CityWall", "MonumentalArch", "PublicFountain", "FountainMonument", "Library", "School", "Stable", "MedicalShop", "BarberShop"):
    if planned not in core_text or "ARCHETYPE_PLANNED" not in core_text:
        ERRORS.append(f"archetipo pianificato non registrato: {planned}")

for category in ("Counter", "Dolium", "Basin", "WaterChannel", "Millstone", "Oven", "Furnace", "Workbench", "Seat", "LatrineSeat", "Drain", "Altar", "Shrine", "StatueMarker", "AnimalPath", "ShopSign", "Shelf", "StorageContainer", "GardenFeature", "Fountain", "MosaicZone", "FrescoZone", "DryingRack", "WorkPlatform", "RotationArm", "ServiceBasin", "InteractionMarker"):
    if category not in core_text + read("Source/RomaAeterna/Public/World/Modular/RARomanModularTypes.h"):
        ERRORS.append(f"categoria modulare Prompt 22 mancante: {category}")

for tag in ("public_room", "private_room", "service_room", "commercial_area", "production_area", "customer_area", "animal_work_area", "fire_hazard_area", "water_required", "drainage_required", "food_preparation", "food_sales", "textile_processing", "grain_processing", "religious_area", "monumental_area", "fresco_candidate", "mosaic_candidate", "statue_candidate", "fountain_candidate", "shop_sign_candidate", "npc_workstation", "npc_customer_position", "npc_queue_position", "npc_service_route", "npc_animal_route", "restricted_area", "storage_area", "open_court", "street_facing", "upper_floor"):
    if tag not in core_text:
        ERRORS.append(f"tag semantico mancante: {tag}")

free_register = read("docs/assets/FREE_ASSET_REGISTER.md")
for idx in range(27, 37):
    if f"FREE-{idx:03d}" not in free_register:
        ERRORS.append(f"voce asset gratuita mancante: FREE-{idx:03d}")

tracked_binary_names = [line for line in (ROOT / ".git").exists() and [] or []]
for path in ROOT.rglob("*"):
    if ".git" in path.parts or path.is_dir():
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
for state in ("CORE_CPP_DEBUG_TESTS_PASSED", "CORE_CPP_RELEASE_TESTS_PASSED", "CORE_CPP_SANITIZERS_PASSED", "PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED", "BUILDING_ARCHETYPE_STATIC_CHECKS_PASSED", "UNREAL_BUILD_REQUIRED", "UNREAL_AUTOMATION_REQUIRED", "MANUAL_VERIFICATION_REQUIRED", "FAB_ASSET_IMPORT_NOT_STARTED"):
    if state not in status_docs:
        ERRORS.append(f"stato richiesto non documentato: {state}")

if ERRORS:
    print("FAILED_STATIC")
    print("\n".join(ERRORS))
    sys.exit(1)

print("PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED")
print("BUILDING_ARCHETYPE_STATIC_CHECKS_PASSED")
print("PASSED_STATIC: validazione archetipi edilizi romani completata")
