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


if __name__ == "__main__":
    unittest.main()
