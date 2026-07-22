import importlib.util
import json
import tempfile
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "AuditRomanAssets.py"
SPEC = importlib.util.spec_from_file_location("audit_roman_assets", SCRIPT)
AUDIT = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(AUDIT)


def candidate(asset_id="RA-FAB-ARCH-001", categories=None):
    item = {key: "NOT_VERIFIED" for key in AUDIT.REQUIRED}
    item.update({
        "asset_id": asset_id, "name": "Test", "author": "Autore", "source": "Fab",
        "url": "https://example.invalid/item", "verified_date": "2026-07-22",
        "intended_archetypes": ["Test"], "categories": categories or sorted(AUDIT.P0),
        "historical_grade": "B", "historical_risk": "review", "technical_risk": "review",
        "scores": {key: 3 for key in AUDIT.SCORE_KEYS},
    })
    return item


def populate_material_replacement(root: Path):
    for values in AUDIT.LOCAL_BATCH_1.values():
        relative_root, *files = values
        for filename in files:
            path = root / relative_root / filename
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(b"asset")
    instances = []
    for index, name in enumerate(AUDIT.LOCAL_MATERIAL_INSTANCES):
        path = root / f"Content/LocalAssets/RomaAeterna/Materials/{name}.uasset"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(b"local")
        instances.append({
            "name": name,
            "source_package": sorted(AUDIT.LOCAL_BATCH_1)[index % len(AUDIT.LOCAL_BATCH_1)],
            "uv_scale": 1.0,
            "roughness_multiplier": 1.0,
            "normal_strength": 1.0,
            "ao_intensity": 1.0,
            "weathering": 0.5,
        })
    # Garantisce che tutti i sette pacchetti siano rappresentati almeno una volta.
    for index, source in enumerate(sorted(AUDIT.LOCAL_BATCH_1)):
        instances[index]["source_package"] = source
    mapping = root / AUDIT.LOCAL_MAPPING_PATH
    mapping.parent.mkdir(parents=True, exist_ok=True)
    mapping.write_text(json.dumps({
        "batch": 1,
        "catalog": "/Game/LocalAssets/RomaAeterna/Data/DA_RA_VisualCatalog_Batch1",
        "material_instances": instances,
        "archetypes": sorted(AUDIT.PROMPT_28_ARCHETYPES),
        "surface_roles": sorted(AUDIT.PROMPT_28_SURFACE_ROLES),
        "mapping_count": 20,
    }), encoding="utf-8")
    for relative in (AUDIT.LOCAL_CATALOG_PATH, AUDIT.LOCAL_PREVIEW_PATH):
        path = root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(b"local")
    registry = root / "docs/assets/ROMAN_ASSET_SOURCE_REGISTRY.md"
    registry.parent.mkdir(parents=True, exist_ok=True)
    registry.write_text("\n".join((
        "RA-CC0-PH-PLASTERED-WALL-03", "RA-CC0-ACG-BRICKS-066",
        "RA-CC0-PH-COBBLESTONE-05", "RA-CC0-ACG-ROOFING-TILES-013A",
        "RA-CC0-ACG-BRICKS-042", "RA-CC0-PH-WOOD-PLANKS-GREY", "RA-CC0-ACG-GROUND-039",
    )), encoding="utf-8")


class AuditRomanAssetsTests(unittest.TestCase):
    def test_parsing_catalogo_materializza_default(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "catalog.json"
            path.write_text(json.dumps({"field_defaults": {"price_observed": "NOT_VERIFIED"}, "candidates": [{"asset_id": "RA-FAB-ARCH-001"}]}), encoding="utf-8")
            self.assertEqual(AUDIT.load_catalog(path)["candidates"][0]["price_observed"], "NOT_VERIFIED")

    def test_rileva_categoria_mancante(self):
        with tempfile.TemporaryDirectory() as directory:
            report = AUDIT.audit_catalog({"candidates": [candidate(categories=["materials"])]}, Path(directory), "RA-FAB-ARCH-001", 100)
            self.assertTrue(any("Categoria P0 mancante" in error for error in report["errors"]))

    def test_rileva_naming_errato(self):
        with tempfile.TemporaryDirectory() as directory:
            report = AUDIT.audit_catalog({"candidates": [candidate("bad id")]}, Path(directory), "bad id", 100)
            self.assertIn("Naming AssetId non valido: bad id", report["errors"])

    def test_rileva_file_grande(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "Content").mkdir()
            (root / "Content/large.bin").write_bytes(b"1234")
            report = AUDIT.audit_catalog({"candidates": [candidate()]}, root, "RA-FAB-ARCH-001", 3)
            self.assertEqual(report["large_files"][0]["path"], "Content/large.bin")

    def test_rileva_provenienza_mancante(self):
        with tempfile.TemporaryDirectory() as directory:
            report = AUDIT.audit_catalog({"candidates": [candidate()]}, Path(directory), "", 100)
            self.assertTrue(any("provenienza mancante" in error for error in report["errors"]))

    def test_report_deterministico(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            first = AUDIT.audit_catalog({"candidates": [candidate()]}, root, "RA-FAB-ARCH-001", 100)
            second = AUDIT.audit_catalog({"candidates": [candidate()]}, root, "RA-FAB-ARCH-001", 100)
            self.assertEqual(first, second)
            self.assertEqual(AUDIT.render_markdown(first), AUDIT.render_markdown(second))

    def test_funzione_audit_non_scrive(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            before = list(root.rglob("*"))
            AUDIT.audit_catalog({"candidates": [candidate()]}, root, "RA-FAB-ARCH-001", 100)
            self.assertEqual(before, list(root.rglob("*")))

    def test_asset_esterno_locale_non_tracciato_ammesso(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            asset = root / "Content/ThirdParty/Fab/Vendor/Test.uasset"
            asset.parent.mkdir(parents=True)
            asset.write_bytes(b"local")
            report = AUDIT.audit_catalog({"candidates": [candidate()]}, root, "RA-FAB-ARCH-001", 100)
            self.assertIn("Content/ThirdParty/Fab/Vendor/Test.uasset", report["local_external_files"])
            self.assertFalse(report["unauthorized_files"])

    def test_asset_esterno_locale_tracciato_rifiutato(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            relative = "Content/ThirdParty/Fab/Vendor/Test.uasset"
            asset = root / relative
            asset.parent.mkdir(parents=True)
            asset.write_bytes(b"tracked")
            report = AUDIT.audit_catalog(
                {"candidates": [candidate()]}, root, "RA-FAB-ARCH-001", 100,
                tracked_paths={relative},
            )
            self.assertEqual(report["unauthorized_files"], [relative])

    def test_batch_locale_assente_non_fallisce(self):
        with tempfile.TemporaryDirectory() as directory:
            report = AUDIT.audit_local_batch(Path(directory), 1, set())
            self.assertEqual(report["status"], "NOT_INSTALLED")
            self.assertFalse(report["installed"])

    def test_batch_locale_completo_e_deterministico(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for values in AUDIT.LOCAL_BATCH_1.values():
                relative_root, *files = values
                package_root = root / relative_root
                package_root.mkdir(parents=True)
                for filename in files:
                    path = package_root / filename
                    path.parent.mkdir(parents=True, exist_ok=True)
                    path.write_bytes(b"asset")
            mapping = root / AUDIT.LOCAL_MAPPING_PATH
            mapping.parent.mkdir(parents=True)
            mapping.write_text(json.dumps({"batch": 1, "catalog": "/Game/LocalAssets/Test"}), encoding="utf-8")
            for relative in (AUDIT.LOCAL_CATALOG_PATH, AUDIT.LOCAL_PREVIEW_PATH):
                path = root / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(b"local")
            first = AUDIT.audit_local_batch(root, 1, set())
            second = AUDIT.audit_local_batch(root, 1, set())
            self.assertEqual(first, second)
            self.assertEqual(first["status"], "PASSED")

    def test_batch_locale_rifiuta_mapping_assoluto(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for values in AUDIT.LOCAL_BATCH_1.values():
                relative_root, *files = values
                for filename in files:
                    path = root / relative_root / filename
                    path.parent.mkdir(parents=True, exist_ok=True)
                    path.write_bytes(b"asset")
            mapping = root / AUDIT.LOCAL_MAPPING_PATH
            mapping.parent.mkdir(parents=True)
            absolute_source = "C:" + "\\Users\\Test"
            mapping.write_text(json.dumps({"batch": 1, "source": absolute_source}), encoding="utf-8")
            for relative in (AUDIT.LOCAL_CATALOG_PATH, AUDIT.LOCAL_PREVIEW_PATH):
                path = root / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(b"local")
            report = AUDIT.audit_local_batch(root, 1, set())
            self.assertTrue(any("percorso assoluto" in error for error in report["errors"]))

    def test_material_replacement_completo(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            populate_material_replacement(root)
            report = AUDIT.audit_material_replacement(root, 1, set())
            self.assertEqual(report["status"], "PASSED", report["errors"])
            self.assertEqual(report["material_instance_count"], 11)
            self.assertEqual(report["normal_dx_count"], 7)

    def test_material_replacement_rifiuta_istanza_tracciata(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            populate_material_replacement(root)
            relative = f"Content/LocalAssets/RomaAeterna/Materials/{AUDIT.LOCAL_MATERIAL_INSTANCES[0]}.uasset"
            report = AUDIT.audit_material_replacement(root, 1, {relative})
            self.assertEqual(report["status"], "FAILED")
            self.assertTrue(any("tracciata da Git" in error for error in report["errors"]))

    def test_material_replacement_assente_supporta_fallback(self):
        with tempfile.TemporaryDirectory() as directory:
            report = AUDIT.audit_material_replacement(Path(directory), 1, set())
            self.assertEqual(report["status"], "NOT_INSTALLED")


if __name__ == "__main__":
    unittest.main()
