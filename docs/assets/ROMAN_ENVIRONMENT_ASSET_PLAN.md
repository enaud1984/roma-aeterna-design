# Roman environment asset plan — Prompt 19

## Current Content audit

`Content/RA` currently contains only development map material: `Content/RA/Dev/Maps/TechnicalSandbox.umap` and its README. No production Roman environment asset taxonomy exists yet. This prompt creates documentation only and does not add `.uasset` or `.umap` files.

## Stable taxonomy

Use the target taxonomy documented in `ROMAN_ASSET_NAMING_CONVENTION.md`. `Content/RA/Dev/` remains for technical/dev maps. `Content/RA/Maps/` is reserved for reviewed project maps such as the future local `RomanStreetPrototype`.

## RomanStreetPrototype plan

Creation of `RomanStreetPrototype` is a `LOCAL_UNREAL_TASK`; do not create it in cloud.

1. Duplicate `TechnicalSandbox` in Unreal Editor to a new local map, e.g. `Content/RA/Maps/L_RomanStreetPrototype.umap`.
2. Maintain one `PlayerStart` and validate spawn.
3. Maintain `RAGameModeBase`.
4. Maintain Prompt 18 Enhanced Input controls.
5. Replace technical road blocks with reviewed road/basoli modules.
6. Add raised sidewalks and stepping-stone crossings.
7. Add modular facades suitable for tabernae/domus/insulae.
8. Add botteghe thresholds and shop fronts.
9. Add terracotta roofs, doors and windows.
10. Add props: amphorae, dolia, crates, baskets, lamps and benches.
11. Apply materials: stone, plaster, brick, opus surfaces, roof tile and worn floor.
12. Add decals: dirt, repaired plaster, water staining, wheel wear and wall age.
13. Add Mediterranean vegetation cautiously: potted plants, vines, olives/cypress only where plausible.
14. Establish Mediterranean daylight and sky without hiding collision/readability.
15. Verify simple/blocking collision on walkable and boundary meshes.
16. Add occlusion/visibility checks for long street segments.
17. Enable Nanite only where supported and useful for high-poly static meshes.
18. Keep LODs for foliage, props and non-Nanite assets.
19. Test camera: first/third person toggle, spring-arm collision, wall proximity.
20. Test traversal: walk, sprint, jump, ramp/thresholds, no void fall.
21. Run historical review against canonical design principles before promoting assets.
22. Run performance review: stat unit, stat fps, shader/texture memory and collision complexity.

## Non-goals

- Do not modify `TechnicalSandbox.umap`.
- Do not import Fab assets in cloud.
- Do not create fake binary assets.

## Zero-budget modular RomanStreetPrototype update

The first Roman street must be built from individual compatible elements, not from a complete `Roman Street` marketplace pack. Required local-only elements: road material, basoli modules, sidewalks, raised crossings, modular walls, facades, doors, windows, roofs, shop fronts, props, vegetation and lighting. All work remains `LOCAL_UNREAL_TASK`; do not modify `TechnicalSandbox.umap` and do not create `RomanStreetPrototype.umap` in cloud.

Use free materials first, then internal modular geometry for missing pieces. A complete Roman forum/domus asset is not required; houses, tabernae, domus, temples and forum sections must be assembled from the Roman Modular Construction Kit.
