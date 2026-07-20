# TechnicalSandbox — Technical Roman Street Prototype

## Objective

Provide a lightweight binary UE map where locomotion, camera behavior, collision, lighting and spawn can be validated before historically reviewed Pompeii production work begins.

## Asset and configuration

- Package: `/Game/RA/Dev/Maps/TechnicalSandbox`
- File: `Content/RA/Dev/Maps/TechnicalSandbox.umap`
- Editor and game default map: configured in `Config/DefaultEngine.ini`
- GameMode: `/Script/RomaAeterna.RAGameModeBase`
- Generator: `Scripts/CreateTechnicalSandbox.py`
- Validator: `Scripts/ValidatePlayableFoundation.py`

## Scene inventory

The route uses a broad collision floor, three joined road blocks, paired sidewalks, lateral wall masses, a narrowing, a low obstacle, a ramp, terminal barriers and one `PlayerStart`. A directional light, Skylight and Sky Atmosphere prevent an unlit scene. A TextRender marker identifies the scene as **Technical Roman Street Prototype**.

All milestone actors carry the tag `RA_TechnicalStreet`. The validator requires the critical actor labels, exactly one tagged PlayerStart and at least twenty tagged actors.

## Placeholder declaration

Geometry, materials, dimensions, buildings, pavement and decoration are technical placeholders. They are neither a final reconstruction of Pompeii nor archaeological evidence. Plausible human-scale proportions are used only to make movement tests meaningful and remain unvalidated design assumptions.

## Reproduction

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\Scripts\BuildTechnicalSandbox.ps1
```

The wrapper runs generation and a separate headless reload/validation. It must return a non-zero exit code on either failure.

## Acceptance and limits

Headless validation proves map load, required structure, lighting actors and boundaries. It does not prove visual quality, player input or a complete traversal; those checks are explicitly [manual](../testing/PLAYABLE_FOUNDATION_MANUAL_TEST.md).

## Related documents

- [Player Character](PLAYER_CHARACTER.md)
- [Build report](../audits/PLAYABLE_FOUNDATION_BUILD_REPORT.md)
- [Pompeii vertical slice](../../07-pompeii-demo/pompeii-vertical-slice.md)
