#!/usr/bin/env python3
"""Audit non distruttivo del catalogo e degli asset romani."""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ID_PATTERN = re.compile(r"^RA-(FAB|EPIC)-[A-Z]+-\d{3}$")
ABSOLUTE_PATTERN = re.compile(r"(?:(?<![A-Za-z])[A-Za-z]:[\\/]|/(?:Users|home|workspace)/)")
P0 = {
    "architecture_kit", "materials", "road", "roof", "doors_windows",
    "commercial_props", "vegetation", "human_character", "locomotion",
}
REQUIRED = {
    "asset_id", "name", "author", "source", "url", "verified_date",
    "price_observed", "price_type", "license_declared", "unreal_compatibility",
    "ue_versions", "content_type", "package_size", "mesh_count", "material_count",
    "texture_count", "lod", "nanite", "collisions", "animations", "skeleton",
    "dependencies", "plugins", "add_to_project", "intended_use",
    "intended_archetypes", "categories", "historical_grade", "historical_risk",
    "technical_risk", "scores",
}
SCORE_KEYS = {
    "modularity", "visual_quality", "ue58_compatibility", "performance",
    "collisions", "lod_nanite", "ease_of_integration", "variation",
    "visual_catalog_compatibility", "value_for_money", "TechnicalScore",
    "HistoricalScore", "IntegrationScore", "PriorityScore",
}
IGNORED_PARTS = {".git", "Binaries", "DerivedDataCache", "Intermediate", "Saved"}
LOCAL_EXTERNAL_ROOTS = (
    "Content/ThirdParty/Fab/", "Content/ThirdParty/Megascans/",
    "Content/ThirdParty/Marketplace/", "Content/ThirdParty/External/",
    "Content/LocalAssets/", "Content/ImportedAssets/",
)
LOCAL_BATCH_1 = {
    "PlasteredWall03": (
        "Content/ThirdParty/External/PolyHaven/PlasteredWall03",
        "textures/plastered_wall_03_diff_2k.jpg",
        "textures/plastered_wall_03_nor_dx_2k.jpg",
        "textures/plastered_wall_03_rough_2k.exr",
        "textures/plastered_wall_03_ao_2k.jpg",
    ),
    "Bricks066": (
        "Content/ThirdParty/External/AmbientCG/Bricks066",
        "Bricks066_2K-JPG_Color.jpg",
        "Bricks066_2K-JPG_NormalDX.jpg",
        "Bricks066_2K-JPG_Roughness.jpg",
        "Bricks066_2K-JPG_AmbientOcclusion.jpg",
    ),
    "Cobblestone05": (
        "Content/ThirdParty/External/PolyHaven/Cobblestone05",
        "textures/cobblestone_05_diff_2k.jpg",
        "textures/cobblestone_05_nor_dx_2k.jpg",
        "textures/cobblestone_05_rough_2k.exr",
        "textures/cobblestone_05_ao_2k.jpg",
    ),
    "RoofingTiles013A": (
        "Content/ThirdParty/External/AmbientCG/RoofingTiles013A",
        "RoofingTiles013A_2K-JPG_Color.jpg",
        "RoofingTiles013A_2K-JPG_NormalDX.jpg",
        "RoofingTiles013A_2K-JPG_Roughness.jpg",
        "RoofingTiles013A_2K-JPG_AmbientOcclusion.jpg",
    ),
    "Bricks042": (
        "Content/ThirdParty/External/AmbientCG/Bricks042",
        "Bricks042_2K-JPG_Color.jpg",
        "Bricks042_2K-JPG_NormalDX.jpg",
        "Bricks042_2K-JPG_Roughness.jpg",
        "Bricks042_2K-JPG_AmbientOcclusion.jpg",
    ),
    "WoodPlanksGrey": (
        "Content/ThirdParty/External/PolyHaven/WoodPlanksGrey",
        "textures/wood_planks_grey_diff_2k.jpg",
        "textures/wood_planks_grey_nor_dx_2k.jpg",
        "textures/wood_planks_grey_rough_2k.exr",
        "textures/wood_planks_grey_ao_2k.jpg",
    ),
    "Ground039": (
        "Content/ThirdParty/External/AmbientCG/Ground039",
        "Ground039_2K-JPG_Color.jpg",
        "Ground039_2K-JPG_NormalDX.jpg",
        "Ground039_2K-JPG_Roughness.jpg",
        "Ground039_2K-JPG_AmbientOcclusion.jpg",
    ),
}
LOCAL_MAPPING_PATH = "Saved/LocalAssetConfig/roman_asset_batch_1.json"
LOCAL_CATALOG_PATH = "Content/LocalAssets/RomaAeterna/Data/DA_RA_VisualCatalog_Batch1.uasset"
LOCAL_PREVIEW_PATH = "Content/LocalAssets/RomaAeterna/Maps/RomaAeternaAssetBatch1Preview.umap"
LOCAL_MATERIAL_INSTANCES = (
    "MI_RA_Local_Plaster_Light", "MI_RA_Local_Plaster_Ochre", "MI_RA_Local_Plaster_Red",
    "MI_RA_Local_Brick_Popular", "MI_RA_Local_Brick_Thermal",
    "MI_RA_Local_Road_Secondary", "MI_RA_Local_Roof_Terracotta",
    "MI_RA_Local_Wood_Dark", "MI_RA_Local_Wood_Worn",
    "MI_RA_Local_Ground_Dry", "MI_RA_Local_Ground_Productive",
)
PROMPT_28_ARCHETYPES = {
    "POPULAR_HOUSE", "DOMUS_MEDIA", "TABERNA", "THERMOPOLIUM", "BATH_COMPLEX",
    "PUBLIC_FOUNTAIN", "METAL_WORKSHOP", "AQUEDUCT_SECTION", "URBAN_GARDEN", "SERVICE_YARD",
}
PROMPT_28_SURFACE_ROLES = {
    "EXTERIOR_WALL", "STRUCTURAL_BRICK", "SECONDARY_PAVING", "ROOF", "TIMBER",
    "GROUND", "PRODUCTIVE_FLOOR", "UTILITY_SURFACE",
}


def load_catalog(path: Path) -> dict:
    """Carica e materializza i campi dichiarati come NOT_VERIFIED."""
    raw = json.loads(path.read_text(encoding="utf-8"))
    defaults = raw.get("field_defaults", {})
    raw["candidates"] = [{**defaults, **item} for item in raw.get("candidates", [])]
    return raw


def audit_catalog(
    catalog: dict, root: Path, registry_text: str, large_limit: int,
    tracked_paths: set[str] | None = None,
) -> dict:
    """Restituisce un report deterministico e non modifica il filesystem."""
    errors: list[str] = []
    warnings: list[str] = []
    candidates = catalog.get("candidates", [])
    ids = [item.get("asset_id", "") for item in candidates]
    duplicate_ids = sorted(name for name, count in Counter(ids).items() if count > 1)
    for asset_id in duplicate_ids:
        errors.append(f"AssetId duplicato: {asset_id}")

    category_counts: Counter[str] = Counter()
    for item in sorted(candidates, key=lambda value: value.get("asset_id", "")):
        asset_id = item.get("asset_id", "<senza-id>")
        missing = sorted(REQUIRED - item.keys())
        if missing:
            errors.append(f"{asset_id}: campi mancanti: {', '.join(missing)}")
        if not ID_PATTERN.fullmatch(asset_id):
            errors.append(f"Naming AssetId non valido: {asset_id}")
        if not str(item.get("url", "")).startswith("https://"):
            errors.append(f"{asset_id}: URL non HTTPS o mancante")
        if item.get("historical_grade") not in {"A", "B", "C", "D"}:
            errors.append(f"{asset_id}: HistoricalGrade non valido")
        scores = item.get("scores", {})
        if SCORE_KEYS - scores.keys():
            errors.append(f"{asset_id}: punteggi incompleti")
        if any(not isinstance(value, (int, float)) or not 0 <= value <= 5 for value in scores.values()):
            errors.append(f"{asset_id}: punteggio fuori intervallo 0-5")
        category_counts.update(item.get("categories", []))
        if asset_id not in registry_text:
            errors.append(f"{asset_id}: provenienza mancante nel registro")
        if ABSOLUTE_PATTERN.search(json.dumps(item, ensure_ascii=False)):
            errors.append(f"{asset_id}: percorso assoluto nel catalogo")

    for category in sorted(P0 - category_counts.keys()):
        errors.append(f"Categoria P0 mancante: {category}")
    for category in sorted(P0):
        if 0 < category_counts[category] < 3:
            warnings.append(f"Categoria P0 con meno di tre candidati: {category}")

    large_files: list[dict] = []
    unauthorized: list[str] = []
    local_external: list[str] = []
    tracked_paths = tracked_paths or set()
    content = root / "Content"
    if content.exists():
        for path in sorted(content.rglob("*")):
            if path.is_dir() or any(part in IGNORED_PARTS for part in path.parts):
                continue
            relative = path.relative_to(root).as_posix()
            size = path.stat().st_size
            if size > large_limit:
                large_files.append({"path": relative, "size_bytes": size})
                warnings.append(f"File oltre soglia: {relative} ({size} byte)")
            if relative.startswith(LOCAL_EXTERNAL_ROOTS):
                local_external.append(relative)
                if relative in tracked_paths:
                    unauthorized.append(relative)
                    errors.append(f"Asset esterno locale tracciato da Git: {relative}")

    return {
        "status": "PASSED" if not errors else "FAILED",
        "candidate_count": len(candidates),
        "category_counts": dict(sorted(category_counts.items())),
        "duplicate_ids": duplicate_ids,
        "large_files": large_files,
        "local_external_files": local_external,
        "unauthorized_files": unauthorized,
        "errors": sorted(set(errors)),
        "warnings": sorted(set(warnings)),
    }


def render_markdown(report: dict) -> str:
    lines = [
        "# Audit asset romani",
        "",
        f"Stato: **{report['status']}**",
        f"Candidati: **{report['candidate_count']}**",
        "",
        "## Copertura categorie",
        "",
        "| Categoria | Candidati |",
        "|---|---:|",
    ]
    lines.extend(f"| {name} | {count} |" for name, count in report["category_counts"].items())
    for title, key in (("Errori", "errors"), ("Avvisi", "warnings")):
        lines.extend(["", f"## {title}", ""])
        lines.extend(f"- {item}" for item in report[key]) if report[key] else lines.append("- Nessuno.")
    return "\n".join(lines) + "\n"


def audit_local_batch(root: Path, batch: int, tracked_paths: set[str]) -> dict:
    """Verifica in sola lettura sorgenti, import locale, mapping e isolamento Git."""
    errors: list[str] = []
    warnings: list[str] = []
    if batch != 1:
        return {
            "status": "FAILED", "batch": batch, "installed": False,
            "packages": [], "file_count": 0, "size_bytes": 0,
            "errors": [f"Batch non supportato: {batch}"], "warnings": [],
        }

    packages = []
    all_roots_absent = True
    total_files = 0
    total_size = 0
    for name, values in sorted(LOCAL_BATCH_1.items()):
        relative_root, *required_files = values
        package_root = root / relative_root
        present = package_root.is_dir()
        all_roots_absent &= not present
        package_files = sorted(path for path in package_root.rglob("*") if path.is_file()) if present else []
        package_size = sum(path.stat().st_size for path in package_files)
        missing = [item for item in required_files if not (package_root / item).is_file()]
        if present and missing:
            errors.append(f"{name}: file richiesti mancanti: {', '.join(missing)}")
        if not present:
            warnings.append(f"{name}: pacchetto locale non installato")
        for path in package_files:
            relative = path.relative_to(root).as_posix()
            if relative in tracked_paths:
                errors.append(f"Asset esterno tracciato da Git: {relative}")
        total_files += len(package_files)
        total_size += package_size
        packages.append({
            "name": name,
            "path": relative_root,
            "present": present,
            "file_count": len(package_files),
            "size_bytes": package_size,
            "missing_required_files": missing,
        })

    installed = not all_roots_absent
    mapping_path = root / LOCAL_MAPPING_PATH
    catalog_path = root / LOCAL_CATALOG_PATH
    preview_path = root / LOCAL_PREVIEW_PATH
    mapping = None
    if installed:
        if not mapping_path.is_file():
            errors.append(f"Mapping locale mancante: {LOCAL_MAPPING_PATH}")
        else:
            try:
                mapping = json.loads(mapping_path.read_text(encoding="utf-8"))
            except (OSError, json.JSONDecodeError) as exc:
                errors.append(f"Mapping locale non valido: {exc}")
            if mapping and mapping.get("batch") != 1:
                errors.append("Mapping locale riferito a un batch diverso da 1")
            if mapping and ABSOLUTE_PATTERN.search(json.dumps(mapping, ensure_ascii=False)):
                errors.append("Mapping locale contiene un percorso assoluto")
        if not catalog_path.is_file():
            errors.append(f"Catalogo Unreal locale mancante: {LOCAL_CATALOG_PATH}")
        if not preview_path.is_file():
            errors.append(f"Mappa preview locale mancante: {LOCAL_PREVIEW_PATH}")

    for relative in (LOCAL_CATALOG_PATH, LOCAL_PREVIEW_PATH):
        if relative in tracked_paths:
            errors.append(f"Output locale tracciato da Git: {relative}")

    if all_roots_absent:
        status = "NOT_INSTALLED"
    else:
        status = "PASSED" if not errors and all(item["present"] for item in packages) else "FAILED"
    return {
        "status": status,
        "batch": batch,
        "installed": installed,
        "packages": packages,
        "file_count": total_files,
        "size_bytes": total_size,
        "mapping_path": LOCAL_MAPPING_PATH,
        "catalog_path": LOCAL_CATALOG_PATH,
        "preview_path": LOCAL_PREVIEW_PATH,
        "errors": sorted(set(errors)),
        "warnings": sorted(set(warnings)),
    }


def render_local_markdown(report: dict) -> str:
    lines = [
        "# Audit locale Asset Batch 1",
        "",
        f"Stato: **{report['status']}**",
        f"File sorgente: **{report['file_count']}**",
        f"Dimensione sorgenti: **{report['size_bytes']} byte**",
        "",
        "| Pacchetto | Presente | File | Byte | Mancanze |",
        "|---|---|---:|---:|---|",
    ]
    for item in report["packages"]:
        missing = ", ".join(item["missing_required_files"]) or "nessuna"
        lines.append(f"| {item['name']} | {item['present']} | {item['file_count']} | {item['size_bytes']} | {missing} |")
    for title, key in (("Errori", "errors"), ("Avvisi", "warnings")):
        lines.extend(["", f"## {title}", ""])
        lines.extend(f"- {item}" for item in report[key]) if report[key] else lines.append("- Nessuno.")
    return "\n".join(lines) + "\n"


def audit_material_replacement(root: Path, batch: int, tracked_paths: set[str]) -> dict:
    """Estende l'audit locale con istanze, mapping, licenze e protezioni Prompt 28."""
    report = audit_local_batch(root, batch, tracked_paths)
    if report["status"] == "NOT_INSTALLED":
        return report
    errors = list(report["errors"])
    mapping_path = root / LOCAL_MAPPING_PATH
    mapping: dict = {}
    if mapping_path.is_file():
        try:
            mapping = json.loads(mapping_path.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError) as exc:
            errors.append(f"Mapping Prompt 28 non valido: {exc}")

    mapped_instances = {item.get("name") for item in mapping.get("material_instances", [])}
    missing_mapped = sorted(set(LOCAL_MATERIAL_INSTANCES) - mapped_instances)
    if missing_mapped:
        errors.append(f"Material Instance assenti dal mapping: {', '.join(missing_mapped)}")
    missing_files = []
    for name in LOCAL_MATERIAL_INSTANCES:
        relative = f"Content/LocalAssets/RomaAeterna/Materials/{name}.uasset"
        if not (root / relative).is_file():
            missing_files.append(name)
        if relative in tracked_paths:
            errors.append(f"Material Instance locale tracciata da Git: {relative}")
    if missing_files:
        errors.append(f"Material Instance locali mancanti: {', '.join(missing_files)}")

    archetypes = set(mapping.get("archetypes", []))
    missing_archetypes = sorted(PROMPT_28_ARCHETYPES - archetypes)
    if missing_archetypes:
        errors.append(f"Archetipi Prompt 28 non mappati: {', '.join(missing_archetypes)}")
    surface_roles = set(mapping.get("surface_roles", []))
    missing_roles = sorted(PROMPT_28_SURFACE_ROLES - surface_roles)
    if missing_roles:
        errors.append(f"SurfaceRole non mappati: {', '.join(missing_roles)}")
    if mapping.get("mapping_count", 0) < 20:
        errors.append("Mapping Prompt 28 insufficiente: servono almeno 20 regole selettive")
    if len(mapped_instances) != len(mapping.get("material_instances", [])):
        errors.append("Material Instance duplicate nel mapping locale")
    if ABSOLUTE_PATTERN.search(json.dumps(mapping, ensure_ascii=False)):
        errors.append("Mapping Prompt 28 contiene percorsi assoluti")

    source_names = []
    for item in mapping.get("material_instances", []):
        source_names.append(item.get("source_package"))
        for key in ("uv_scale", "roughness_multiplier", "normal_strength", "ao_intensity", "weathering"):
            if not isinstance(item.get(key), (int, float)):
                errors.append(f"{item.get('name', '<istanza>')}: parametro {key} mancante")
    if set(source_names) != set(LOCAL_BATCH_1):
        errors.append("I sette pacchetti sorgente non sono tutti referenziati dalle istanze")

    normal_files = []
    for _, values in LOCAL_BATCH_1.items():
        normal_files.extend(item for item in values[1:] if "nor_dx" in item.lower() or "normaldx" in item.lower())
        if any(re.search(r"(?:^|[_-])(?:4k|8k|16k)(?:[_\-.]|$)", item.lower()) for item in values[1:]):
            errors.append("Texture oltre 2K rilevata tra i file operativi")
    if len(normal_files) != 7:
        errors.append("Normal map DirectX non rilevata per tutti i sette pacchetti")

    registry = (root / "docs/assets/ROMAN_ASSET_SOURCE_REGISTRY.md").read_text(encoding="utf-8")
    license_ids = {
        "RA-CC0-PH-PLASTERED-WALL-03", "RA-CC0-ACG-BRICKS-066",
        "RA-CC0-PH-COBBLESTONE-05", "RA-CC0-ACG-ROOFING-TILES-013A",
        "RA-CC0-ACG-BRICKS-042", "RA-CC0-PH-WOOD-PLANKS-GREY", "RA-CC0-ACG-GROUND-039",
    }
    missing_licenses = sorted(item for item in license_ids if item not in registry)
    if missing_licenses:
        errors.append(f"Licenze mancanti dal registro: {', '.join(missing_licenses)}")

    attributes = (root / ".gitattributes").read_text(encoding="utf-8") if (root / ".gitattributes").is_file() else ""
    if "filter=lfs" in attributes.replace(" ", "").lower():
        errors.append("Git LFS rilevato, vietato dalla strategia locale")
    preview_tracked = any(path.startswith("Content/LocalAssets/") and path.endswith(".umap") for path in tracked_paths)
    if preview_tracked:
        errors.append("Preview locale tracciata da Git")

    report.update({
        "status": "PASSED" if not errors else "FAILED",
        "errors": sorted(set(errors)),
        "material_instance_count": len(mapped_instances),
        "mapped_archetypes": sorted(archetypes),
        "surface_roles": sorted(surface_roles),
        "normal_dx_count": len(normal_files),
    })
    return report


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--catalog", type=Path, default=ROOT / "docs/assets/roman_asset_catalog.json")
    parser.add_argument("--registry", type=Path, default=ROOT / "docs/assets/ROMAN_ASSET_SOURCE_REGISTRY.md")
    parser.add_argument("--output-dir", type=Path, default=ROOT / "Saved/AssetAudit")
    parser.add_argument("--large-limit-mib", type=int, default=50)
    parser.add_argument("--check-only", action="store_true")
    parser.add_argument("--local-import-audit", action="store_true")
    parser.add_argument("--material-replacement-audit", action="store_true")
    parser.add_argument("--batch", type=int, default=1)
    parser.add_argument("--report-json", action="store_true")
    parser.add_argument("--report-markdown", action="store_true")
    args = parser.parse_args(argv)

    try:
        catalog = load_catalog(args.catalog)
        registry = args.registry.read_text(encoding="utf-8")
        tracked = set(subprocess.run(
            ["git", "ls-files"], cwd=ROOT, check=True, capture_output=True, text=True,
        ).stdout.splitlines())
        if args.material_replacement_audit:
            report = audit_material_replacement(ROOT, args.batch, tracked)
        elif args.local_import_audit:
            report = audit_local_batch(ROOT, args.batch, tracked)
        else:
            report = audit_catalog(catalog, ROOT, registry, args.large_limit_mib * 1024 * 1024, tracked)
    except (OSError, ValueError, json.JSONDecodeError, subprocess.CalledProcessError) as exc:
        print(f"ASSET_AUDIT_FAILED: {exc}")
        return 1

    if not args.check_only:
        args.output_dir.mkdir(parents=True, exist_ok=True)
        local_mode = args.local_import_audit or args.material_replacement_audit
        json_name = "roman_architectural_material_replacement_audit.json" if args.material_replacement_audit else ("roman_asset_batch_1_local_audit.json" if args.local_import_audit else "roman_asset_audit.json")
        markdown_name = "roman_architectural_material_replacement_audit.md" if args.material_replacement_audit else ("roman_asset_batch_1_local_audit.md" if args.local_import_audit else "roman_asset_audit.md")
        write_both = not args.report_json and not args.report_markdown
        if write_both or args.report_json:
            (args.output_dir / json_name).write_text(
            json.dumps(report, indent=2, ensure_ascii=False) + "\n", encoding="utf-8"
            )
        if write_both or args.report_markdown:
            renderer = render_local_markdown if local_mode else render_markdown
            (args.output_dir / markdown_name).write_text(renderer(report), encoding="utf-8")

    if args.material_replacement_audit:
        if report["status"] == "NOT_INSTALLED":
            print("LOCAL_ASSET_CATALOG_NOT_FOUND_USING_FALLBACKS")
            return 0
        if report["status"] == "PASSED":
            print("ARCHITECTURAL_MATERIAL_REPLACEMENT_AUDIT_PASSED")
            print(f"LOCAL_MATERIAL_INSTANCE_COUNT={report['material_instance_count']}")
            return 0
        print("ARCHITECTURAL_MATERIAL_REPLACEMENT_AUDIT_FAILED")
        for error in report["errors"]:
            print(f"ERROR: {error}")
        return 1

    if args.local_import_audit:
        if report["status"] == "NOT_INSTALLED":
            print("LOCAL_ASSET_BATCH_NOT_INSTALLED")
            return 0
        if report["status"] == "PASSED":
            print("ASSET_BATCH_1_LOCAL_AUDIT_PASSED")
            print(f"LOCAL_ASSET_BATCH_SIZE_BYTES={report['size_bytes']}")
            return 0
        print("ASSET_BATCH_1_LOCAL_AUDIT_FAILED")
        for error in report["errors"]:
            print(f"ERROR: {error}")
        return 1

    print(f"ASSET_AUDIT_{report['status']}: {report['candidate_count']} candidati")
    for error in report["errors"]:
        print(f"ERROR: {error}")
    for warning in report["warnings"]:
        print(f"WARNING: {warning}")
    return 0 if report["status"] == "PASSED" else 1


if __name__ == "__main__":
    sys.exit(main())
