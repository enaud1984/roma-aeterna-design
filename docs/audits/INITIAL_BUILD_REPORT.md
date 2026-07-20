# Initial build report

## Scope

Evidence for toolchain discovery, UnrealBuildTool project recognition, Rider project generation and the first `RomaAeternaEditor Win64 Development` build.

## Environment discovered

| Component | Result |
|---|---|
| Unreal Engine | 5.8.0, launcher installation detected |
| UnrealBuildTool | Present and executed with bundled .NET 10 runtime |
| MSVC | v143 toolset 14.44.35207, x64 compiler present |
| Windows SDK | 10.0.26100.0 present |
| Rider | 2026.1.4 present |

Machine-specific absolute paths are intentionally omitted from committed configuration. The exact local commands and outcomes are recorded after execution below.

| .NET Framework SDK | Initial absence corrected by installing SDK/Targeting Pack 4.8 |

## Verification results

- **UBT project recognition:** pass; `RomaAeternaEditor` rules compiled and target metadata generated.
- **Rider project generation:** pass; model written to `Intermediate/ProjectFiles/.Rider`.
- **Editor build:** pass; UHT, compilation, library/DLL link and target receipt completed.
- **TechnicalSandbox asset:** pass; binary `.umap` created and reloaded by Unreal Editor commandlet.

## Commands executed

Project model:

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File Scripts\GenerateProjectFiles.ps1
```

Build:

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File Scripts\BuildEditor.ps1
```

The build script resolves to the equivalent Unreal command:

```text
Build.bat RomaAeternaEditor Win64 Development <repository>\RomaAeterna.uproject -WaitMutex -NoHotReloadFromIDE
```

Map creation and validation:

```text
UnrealEditor-Cmd.exe RomaAeterna.uproject -run=pythonscript -script=Scripts\CreateTechnicalSandbox.py -unattended -nop4 -nosplash -NullRHI -NoSound
```

## Build history

1. First attempt: failed before source compilation with `RulesError`; `SwarmInterface` could not locate a .NET Framework SDK.
2. Remediation: installed Microsoft .NET Framework 4.8 SDK and Targeting Pack through Visual Studio Installer.
3. Second attempt: `Result: Succeeded`; 12 build actions completed, including UHT-generated code, C++ compilation and DLL link.
4. Security cleanup: the editor-generated Android File Server token was removed and the unused plugin was disabled; a final UBT build succeeded afterward.

The successful build used Visual Studio v143 toolchain 14.44 and Windows SDK 10.0.26100.0. One compile action was automatically retried by Unreal Build Accelerator after a low-memory threshold; the retry succeeded and did not affect the final result.

## Residual manual steps

None required to open the project or load the technical map. Rider can open `RomaAeterna.uproject` directly. Gameplay implementation remains blocked outside the explicitly authorized foundation milestone.

## Result

**PASS — the Unreal Engine foundation is recognized, compilable and headlessly loadable.**
