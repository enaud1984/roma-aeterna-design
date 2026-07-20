# Implementation status

## Scope

Unreal Engine 5.8 C++ foundation for the Pompei vertical slice. The current authorization covers project initialization and the first controllable technical prototype; it does not authorize the production systems of the full demo.

## Current state

- **Branch:** `codex/unreal-project-foundation`
- **Engine:** Unreal Engine 5.8.0
- **Target:** `RomaAeternaEditor Win64 Development`
- **Readiness gate:** remains `NON READY` for the broader gameplay implementation
- **Build:** `SUCCEEDED` on 2026-07-20 (`RomaAeternaEditor Win64 Development`)
- **Automation:** `4/4 SUCCEEDED`, zero warning, zero error
- **TechnicalSandbox:** Technical Roman Street Prototype generated and validated headlessly
- **Manual PIE validation:** `MANUAL_VERIFICATION_REQUIRED`

## Implemented foundation

- Root-level `RomaAeterna.uproject` without a nested project directory.
- Runtime module `RomaAeterna`.
- Base GameMode, GameInstance, PlayerController and Character classes.
- Desktop/scalable configuration, ray tracing and Starter Content disabled.
- Rider and editor-only map-generation tooling.
- Binary technical map at `/Game/RA/Dev/Maps/TechnicalSandbox`.
- Enhanced Input context `IMC_Player` and actions `IA_Move`, `IA_Look`, `IA_Jump`, `IA_Sprint`, `IA_ToggleView`.
- Camera-relative movement, walk, sprint, jump and mouse look.
- Configurable first-person and third-person cameras on the same persistent Character; `F9` toggles the active view.
- Collision-aware third-person spring arm and a lightweight visible placeholder body.
- Canvas-based prototype HUD with the current view mode and controls.
- Reproducible scene generator, structural validator and C++ automation suite.

## Verification evidence

- UnrealBuildTool generated the Rider model and recognized `RomaAeternaEditor`.
- `RomaAeternaEditor Win64 Development` compiled and linked successfully.
- Unreal Editor's Python commandlet created and reloaded `TechnicalSandbox.umap` with zero reported errors or warnings.
- Generated binaries, caches, IDE metadata and local logs remain excluded by `.gitignore`.
- The generated scene validator found all required tagged actors and reported zero errors or warnings.
- The automation report recorded four successful tests: GameMode defaults, Character configuration, repeated camera toggle and map package existence.
- A real `UnrealEditor.exe` startup smoke initialized the project, loaded `TechnicalSandbox` and completed Map Check with 0 errors and 0 warnings before automatic exit.
- A real-RHI game smoke selected `RAGameModeBase`, brought the map up for play, spawned the Character in third-person mode and shut down without critical, fatal, assertion or ensure signatures.

## Play instructions

Open `RomaAeterna.uproject`, load `TechnicalSandbox` and select **Play In Editor**. Use `WASD` to move, the mouse to look, left `Shift` to sprint, `Space` to jump and `F9` to switch between third and first person.

The scene geometry, materials, dimensions, buildings, pavement and decoration are technical placeholders. They are not an archaeologically validated reconstruction of Pompeii.

## Remaining verification

The Editor and commandlets opened and loaded the project and map successfully. Physical input, visual lighting quality and an uninterrupted full traversal still require the operator checklist in [PLAYABLE_FOUNDATION_MANUAL_TEST](docs/testing/PLAYABLE_FOUNDATION_MANUAL_TEST.md); they are not recorded as passed.

## Environment remediation

The initial build exposed a missing `.NET Framework SDK` dependency required by UE 5.8 `SwarmInterface`. Visual Studio Build Tools was supplemented with the Microsoft .NET Framework 4.8 SDK and Targeting Pack; the subsequent build succeeded.

## Explicitly excluded

Pompeii production geometry, economy, advanced NPC simulation, missions, combat, religion, politics, production UI and final assets are not implemented.
