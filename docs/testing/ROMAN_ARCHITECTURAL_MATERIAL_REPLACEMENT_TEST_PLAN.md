# Piano test sostituzione materiali architettonici

## Core

Configurare, compilare ed eseguire CTest in Debug e Release. La suite verifica tassonomie visuali, selezione pesata, seed identico, varianti entro limite e regressioni Prompt 20–24.

## Python e controlli statici

Eseguire:

```powershell
python .\Scripts\AuditRomanAssets.py --material-replacement-audit --batch 1
python -m unittest Scripts.tests.test_audit_roman_assets -v
python .\Scripts\ValidateRomanModularFoundation.py
```

L'audit verifica sette sorgenti, mappe PBR, normal DX, limite 2K, undici istanze, mapping di dieci archetipi, licenze, assenza di duplicazioni, percorsi assoluti, Git LFS e asset tracciati.

## Unreal Engine 5.8

`RomaAeterna.Prompt28.ArchitecturalMaterialReplacement` prova fallback forzato e catalogo locale, dieci archetipi, determinismo, clear/rebuild, assenza di accumulo e fallback selettivo.

```powershell
powershell -ExecutionPolicy Bypass -File .\Scripts\TestRomanArchitecturalMaterialReplacement.ps1 -EngineRoot "<UE_5.8>"
```

La preview reale deve aprirsi con RHI, completare Map Check senza errori e chiudersi. Questo consente lo stato `LOCAL_MATERIAL_REPLACEMENT_TECHNICAL_PREVIEW_PASSED`; finché non è disponibile una prova visuale affidabile del viewport resta richiesto `MANUAL_LOCAL_MATERIAL_REVIEW_REQUIRED`. I log separati sono salvati in `Saved/Logs/Prompt28_*.log`.

Non dichiarare `LOCAL_MATERIAL_REPLACEMENT_PREVIEW_PASSED`, `UNREAL_BUILD_PASSED` o `UNREAL_AUTOMATION_PASSED` senza esecuzione reale e, per il primo stato, senza una verifica visuale affidabile.
