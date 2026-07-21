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

for api in ("GenerateBuilding", "ClearGeneratedBuilding", "RebuildBuilding", "GenerateFromParameters", "GetGeneratedInstanceCount", "GetInstanceCountByCategory", "HasGeneratedBuilding"):
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

for core_api in ("BuildSimpleHouseLayout", "BuildTabernaLayout", "BuildTempleLayout", "BuildStreetSectionLayout", "ValidatePlacements", "EnforceMaximumModuleCount"):
    if core_api not in core_text:
        ERRORS.append(f"API core mancante: {core_api}")

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
for state in ("CORE_CPP_DEBUG_TESTS_PASSED", "CORE_CPP_RELEASE_TESTS_PASSED", "CORE_CPP_SANITIZERS_PASSED", "PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED", "UNREAL_BUILD_REQUIRED", "UNREAL_AUTOMATION_REQUIRED", "MANUAL_VERIFICATION_REQUIRED", "FAB_ASSET_IMPORT_NOT_STARTED"):
    if state not in status_docs:
        ERRORS.append(f"stato richiesto non documentato: {state}")

if ERRORS:
    print("FAILED_STATIC")
    print("\n".join(ERRORS))
    sys.exit(1)

print("PLACEHOLDER_RUNTIME_STATIC_CHECKS_PASSED")
print("PASSED_STATIC: validazione runtime placeholder modulare completata")
