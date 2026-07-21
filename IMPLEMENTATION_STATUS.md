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

## Prompt 19 — Fab Roman asset research and import planning

- **Status:** `PARTIAL_COMPLETE_DOCUMENTATION_ONLY`.
- **Branch:** `codex/prompt-19-fab-roman-assets`.
- **Fab research:** `PARTIAL_COMPLETE`; public Fab pages were reviewed without login, purchase, download or import.
- **Assets found:** 18.
- **APPROVED:** 0; no asset was promoted because per-asset license/price evidence must be captured locally before approval.
- **CANDIDATE:** 0.
- **REJECTED:** 4; bundle/temple/fantasy assets are not suitable for the first free/manual Roman street import pass.
- **MANUAL_REVIEW_REQUIRED:** 14; public pages did not expose all required price, license, UE 5.8, download-size, LOD, collision or material data.
- **Asset import:** none performed; no new `.uasset` or `.umap` files were created.
- **Manual import:** must be executed at home/local Unreal Engine 5.8 through Fab after license and price confirmation.
- **License verification:** still required per asset where marked `MANUAL_REVIEW_REQUIRED`.
- **Unreal Editor tests:** still required after any real asset import.
- **Prompt 18 PIE test:** remains `MANUAL_VERIFICATION_REQUIRED` and is not changed by Prompt 19.
- **Next recommended prompt:** local Fab import dry run for the first five priority assets, followed by Unreal Editor scale/collision/material validation and a local-only `RomanStreetPrototype` map duplication plan.

## Prompt 19 revision — zero-budget multi-library modular assets

- **Status:** `PARTIAL_COMPLETE_DOCUMENTATION_ONLY`, expanded after review comments.
- **Budget:** `0 euro`; paid assets are excluded from operational import lists.
- **Research scope:** multi-library free sources: Fab free/manual review, Poly Haven, ambientCG, Sketchfab downloadable/free, Kenney, OpenGameArt, Wikimedia Commons, Smithsonian Open Access, The Met Open Access, NASA/media references and other CC0-compatible sources.
- **Assets/sources analyzed:** 26.
- **Free verified assets/sources:** 13 `APPROVED_FREE` entries; 22 entries remain zero-budget usable, manual-review or reference-only; 4 paid/fantasy entries are rejected.
- **CC0 entries:** 9.
- **Public Domain entries:** 5.
- **CC BY entries:** 3.
- **Fab free entries:** 2, both still require local per-asset license capture before import.
- **Paid assets rejected:** 3; one additional fantasy-style entry is rejected for historical accuracy.
- **Modular strategy:** Roman Modular Construction Kit documented for walls, roofs, facades, floors, urban elements, props and vegetation.
- **Asset import:** none performed; no `.uasset`, `.umap` or downloaded binary asset files were created.
- **Local implementation:** RomanStreetPrototype and all real imports remain `LOCAL_UNREAL_TASK`.
- **Licenses:** verify locally before import where marked `UNKNOWN`, `FREE_MANUAL_REVIEW_REQUIRED` or per-file license.
- **Prompt 18 PIE test:** remains `MANUAL_VERIFICATION_REQUIRED`.

## Prompt 20 — Fondazione sistema modulare romano

Stato: implementazione C++ e controlli statici cloud completati.

Aggiunto modello dati Blueprint per tipologie edilizie, materiali murari, coperture, ordini architettonici, categorie modulo, ricchezza e degrado. Aggiunti catalogo moduli, dati stile, libreria regole, validatore e actor runtime predisposto a placeholder tecnici. Layout astratti supportati: casa semplice, taberna, tempio e tratto di strada.

Test C++ Automation aggiunti ma marcati `LOCAL_UNREAL_TEST_REQUIRED`. Play In Editor resta `MANUAL_VERIFICATION_REQUIRED`. Nessun file `.uasset` o `.umap` creato o modificato.

## Prompt 20-BIS — Core C++ standard testabile nel cloud

Stato: completato nel cloud per il core standard.

Creato `Source/RomaAeternaCore` con API C++17 indipendente da Unreal per normalizzazione, validazione, snap griglia, bounds, stime, determinismo e layout astratti. Aggiornati gli adapter Unreal in modo che `URARomanBuildingRuleLibrary` e `URARomanConstructionValidator` richiamino il core senza duplicare la logica critica.

Esiti cloud: `CORE_CPP_DEBUG_TESTS_PASSED`, `CORE_CPP_RELEASE_TESTS_PASSED`, `CORE_CPP_SANITIZERS_PASSED`. Restano locali: `UNREAL_BUILD_REQUIRED`, `UNREAL_AUTOMATION_REQUIRED`, `MANUAL_VERIFICATION_REQUIRED`.
