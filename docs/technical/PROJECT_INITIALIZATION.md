# Project initialization

## Objective

Create a minimal, reproducible Unreal Engine 5.8 C++ project directly in the repository root while preserving the Markdown Game Bible.

## Baseline

| Setting | Value |
|---|---|
| Project type | Games / C++ |
| Engine | Unreal Engine 5.8.0 |
| Platform | Desktop, Windows 64-bit |
| Graphics preset | Scalable |
| Ray tracing | Disabled |
| Starter Content | Disabled |
| Preferred source editor | Rider |
| Runtime module | `RomaAeterna` |

## Layout

- `Config/`: project, renderer, maps and editor defaults.
- `Content/`: Unreal assets; only the technical map is permitted in this milestone.
- `Source/RomaAeterna/`: minimal runtime composition root.
- `Plugins/`: reserved for approved first-party plugins.
- `Tests/`: external fixtures and future automation support.
- `Scripts/`: reproducible generation, build and editor automation.
- `docs/`: existing documentation plus implementation evidence.

## Base classes

| Class | Responsibility |
|---|---|
| `ARAGameModeBase` | Select the base pawn and player controller. |
| `URAGameInstance` | Stable future session-level extension point; currently stateless. |
| `ARAPlayerController` | Stable future input/interaction adapter; currently minimal. |
| `ARACharacter` | Minimal playable pawn with Tick disabled by default. |

No gameplay domain state is owned by these classes in this milestone.

## Reproduction

```powershell
powershell -ExecutionPolicy Bypass -File Scripts/GenerateProjectFiles.ps1
powershell -ExecutionPolicy Bypass -File Scripts/BuildEditor.ps1
```

The scripts accept `-EngineRoot` or use `UE_5_8_ROOT`; the standard launcher path is the fallback. Generated IDE, binary, cache and intermediate files are ignored by Git.

## Map policy

`TechnicalSandbox.umap` was generated through `UnrealEditor-Cmd` and the editor-only Python API, then reopened by a second commandlet run. Both the editor startup map and game default map now point to `/Game/RA/Dev/Maps/TechnicalSandbox`. The asset is a real binary Unreal map, not a textual placeholder.

The creation script is idempotent: it creates and saves the map when absent, otherwise it loads the existing asset and fails if validation is unsuccessful.

## Toolchain notes

UE 5.8 ships a private .NET 10 runtime. `GenerateProjectFiles.ps1` invokes that bundled runtime explicitly so project generation does not depend on a globally registered .NET installation. `Build.bat` performs the equivalent setup for compilation.

The installed engine also requires a .NET Framework SDK for the editor's `SwarmInterface` rules. The local Build Tools installation was completed with Microsoft .NET Framework 4.8 SDK and Targeting Pack after the first build exposed the missing dependency.

## Constraints

- Markdown files remain canonical and are not moved.
- Editor automation plugins do not create runtime gameplay dependencies.
- No absolute user-profile path is committed.
- The global readiness gate is not promoted by this initialization.

## Acceptance result

- Root-level project layout: pass.
- UE 5.8 association and Windows target: pass.
- Rider project model generation: pass.
- Runtime module and base classes: pass.
- Development Editor compilation: pass.
- Binary technical map creation and reload: pass.
- Gameplay systems outside the milestone: absent as required.
