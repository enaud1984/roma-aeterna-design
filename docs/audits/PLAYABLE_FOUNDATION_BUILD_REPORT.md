# Playable foundation build report

- **Date:** 2026-07-20
- **Branch:** `codex/unreal-project-foundation`
- **Engine:** Unreal Engine 5.8.0
**Outcome:** build and automation succeeded; manual PIE verification pending

## Scope

Audit evidence for the first controllable foundation: Enhanced Input, locomotion, first/third-person cameras, debug HUD and Technical Roman Street Prototype.

## Build

Command:

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\Scripts\BuildEditor.ps1
```

Resolved UnrealBuildTool invocation:

```text
UnrealBuildTool.dll RomaAeternaEditor Win64 Development <repository>\RomaAeterna.uproject -WaitMutex -NoHotReloadFromIDE
```

| Evidence | Result |
|---|---|
| Toolchain | Visual Studio 2022 MSVC 14.44.35228 (tools 14.44.35207) |
| Windows SDK | 10.0.26100.0 |
| Final UBT result | `Result: Succeeded` |
| Compile/link execution time | 5.59 s |
| Final clean verification | `Result: Succeeded`, target up to date, 0.93 s |
| Compile/link errors | 0 |
| Build warnings introduced | 0 |

## Map generation and validation

`Scripts/BuildTechnicalSandbox.ps1` ran two independent `UnrealEditor-Cmd` Python commandlets. The final generator saved the binary map; the validator reloaded it, found all required tagged actors and exited with `Success - 0 error(s), 0 warning(s)`.

## Editor startup smoke

`UnrealEditor.exe` was launched against `RomaAeterna.uproject` with unattended automatic exit. The real Editor process returned exit code 0, initialized the `RomaAeterna` runtime module, loaded `TechnicalSandbox` and completed Map Check with 0 errors and 0 warnings. This proves project/map startup, but not physical controls or visual acceptance.

A second real-RHI `-game` smoke loaded the default map, selected `RAGameModeBase`, brought the world up for play, spawned the player and logged `Player camera mode: ThirdPerson`. It returned exit code 0 with no fatal, critical, assertion or ensure signature. Automatic exit occurred after startup, so this remains distinct from the manual traversal test.

## Automation

Command:

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\Scripts\RunPlayableFoundationTests.ps1
```

The generated JSON report recorded:

| Test | Result |
|---|---|
| `CameraToggle` | Success |
| `CharacterConfiguration` | Success |
| `GameModeDefaults` | Success |
| `TechnicalSandboxPackage` | Success |

Summary: 4 succeeded, 0 succeeded with warnings, 0 failed, 0 not run, 0 in process.

## Residual warnings and limitations

UE platform discovery reports absent SDKs for non-target platforms such as LinuxArm64 and VisionOS. Win64 is valid and these messages do not affect the Windows-only target. A prior generator attempt failed on an invalid Engine material path and a second on an unavailable TextRender enum; both were corrected before the successful final run and no failing artifact was accepted.

Headless tests do not establish physical keyboard/mouse behavior or visual quality. These remain `MANUAL_VERIFICATION_REQUIRED` in the [manual checklist](../testing/PLAYABLE_FOUNDATION_MANUAL_TEST.md).

## Definition of Done assessment

Code compilation, map structure, class defaults, camera state transition and package presence are verified. The milestone cannot be described as fully playtested until the manual PIE checklist passes; the broader Game Bible readiness gate remains unchanged.
