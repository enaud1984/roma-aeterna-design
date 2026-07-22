#!/usr/bin/env python3
"""Audit non distruttivo del catalogo e degli asset romani."""

from __future__ import annotations

import argparse
import json
import re
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


def load_catalog(path: Path) -> dict:
    """Carica e materializza i campi dichiarati come NOT_VERIFIED."""
    raw = json.loads(path.read_text(encoding="utf-8"))
    defaults = raw.get("field_defaults", {})
    raw["candidates"] = [{**defaults, **item} for item in raw.get("candidates", [])]
    return raw


def audit_catalog(catalog: dict, root: Path, registry_text: str, large_limit: int) -> dict:
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
            if relative.startswith("Content/ThirdParty/"):
                unauthorized.append(relative)
                errors.append(f"Asset esterno non autorizzato: {relative}")

    return {
        "status": "PASSED" if not errors else "FAILED",
        "candidate_count": len(candidates),
        "category_counts": dict(sorted(category_counts.items())),
        "duplicate_ids": duplicate_ids,
        "large_files": large_files,
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


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--catalog", type=Path, default=ROOT / "docs/assets/roman_asset_catalog.json")
    parser.add_argument("--registry", type=Path, default=ROOT / "docs/assets/ROMAN_ASSET_SOURCE_REGISTRY.md")
    parser.add_argument("--output-dir", type=Path, default=ROOT / "Saved/AssetAudit")
    parser.add_argument("--large-limit-mib", type=int, default=50)
    parser.add_argument("--check-only", action="store_true")
    args = parser.parse_args(argv)

    try:
        catalog = load_catalog(args.catalog)
        registry = args.registry.read_text(encoding="utf-8")
        report = audit_catalog(catalog, ROOT, registry, args.large_limit_mib * 1024 * 1024)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"ASSET_AUDIT_FAILED: {exc}")
        return 1

    if not args.check_only:
        args.output_dir.mkdir(parents=True, exist_ok=True)
        (args.output_dir / "roman_asset_audit.json").write_text(
            json.dumps(report, indent=2, ensure_ascii=False) + "\n", encoding="utf-8"
        )
        (args.output_dir / "roman_asset_audit.md").write_text(render_markdown(report), encoding="utf-8")

    print(f"ASSET_AUDIT_{report['status']}: {report['candidate_count']} candidati")
    for error in report["errors"]:
        print(f"ERROR: {error}")
    for warning in report["warnings"]:
        print(f"WARNING: {warning}")
    return 0 if report["status"] == "PASSED" else 1


if __name__ == "__main__":
    sys.exit(main())
