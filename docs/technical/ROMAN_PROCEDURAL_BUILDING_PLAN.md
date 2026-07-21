# Roman procedural building plan — future system

## Scope

This is a future architecture plan only. It does not implement the procedural system in Prompt 19.

## Parameters

The generator should accept: building type, width, depth, floors, bays, roof type, architectural order, wall type, portico, courtyard, atrium, peristyle, door count, window count, floor type, wealth level, degradation level, period, city and function.

## Architecture

1. `DA_Roman_BuildingStyle_*`: regional style, palette, wall types, roof rules and historical constraints.
2. `DA_Roman_ArchitecturalOrder_*`: column diameter, height ratio, base/capital/entablature module references.
3. `DT_Roman_ModularPieces`: rows for wall, roof, floor, column, arch, prop and vegetation modules.
4. `BP_Roman_ModularBuildingBase`: validates parameters and spawns/places modules.
5. `BP_Roman_ModularHouse`, `BP_Roman_ModularShop`, `BP_Roman_ModularTemple`: specialized rule sets.
6. `GS_Roman_ModuleBuilder`: future Geometry Script support for simple walls, arches, stairs, roofs and trim.
7. `PCG_Roman_StreetDressing`: scatters props, decals and vegetation within constraints.

## Buildable outputs

- Simple house.
- Taberna.
- Domus.
- Insula.
- Temple.
- Basilica.
- Portico.
- Administrative building.
- Road segment.
- Plaza.
- Forum section.

## Rules and validation

- Enforce grid snap and pivot metadata.
- Require one accessible entrance for playable spaces.
- Validate traversal capsule clearance and camera clearance.
- Use historical gates: no fantasy forms, no anachronistic materials, no unreviewed monumental claims.
- Performance gates: module count, material slots, texture memory, collision complexity, foliage density and draw calls.

## Tests

- Unit/data validation for missing module references.
- Editor utility validation for grid/pivot conventions.
- PIE traversal through generated door, stair, sidewalk and street transitions.
- Visual/manual review for historical plausibility.
- Performance smoke with `stat unit`, `stat fps`, collision view and shader/material stats.

## Roadmap

1. Documentation and free-source research.
2. Local import of zero-budget materials and a few columns/props.
3. Internal parametric wall/floor/roof prototype.
4. Data Assets for modular pieces.
5. Blueprint assembly for simple house and taberna.
6. Geometry Script arches/stairs/roof variants.
7. PCG dressing for streets and courtyards.
8. RomanStreetPrototype local map.
9. Domus/temple/forum section prototypes.
