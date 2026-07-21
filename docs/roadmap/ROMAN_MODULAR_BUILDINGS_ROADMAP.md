# Roman modular buildings roadmap — zero-budget asset path

| Phase | Target | Required modules | Free assets needed | Internally generable assets | Tests | Difficulty | Dependencies | Historical risk | Performance risk |
|---|---|---|---|---|---|---|---|---|---|
| 1 | Roman technical street | basoli, sidewalks, crossings, wall bays, doors, windows, roof tiles, props, vegetation | CC0 cobblestone/stone/roof materials, columns optional, plants optional | road blocks, sidewalk, crossings, simple facades | traversal, camera, collision, material scale | Medium | Prompt 18 PIE still pending | Medium | Low/medium |
| 2 | Simple house | wall, door, window, floor, roof, beams | plaster/brick/roof textures | walls, simple doors/windows, beams | enter/exit, scale, roof silhouette | Medium | modular wall standard | Medium | Low |
| 3 | Taberna | open facade, counter, shelves, amphorae, sign, sidewalk | amphora/ceramic references, wood/stone materials | counter, shelves, sign, crates | shop frontage traversal | Medium | props pipeline | Medium | Low/medium |
| 4 | Domus | atrium, compluvium, impluvium, peristyle, mosaic/fresco, garden | mosaic/tile/plaster materials, columns, plants | room layout, impluvium, simple peristyle | courtyard traversal, camera | High | column/patio modules | High | Medium |
| 5 | Small temple | podium, stair, columns, base, capital, architrave, fronton, cella | columns, stone materials, sculpture references | podium, stairs, fronton, cella walls | stair/collision, silhouette review | High | architectural order Data Assets | High | Medium |
| 6 | Portico | repeated columns, architraves, roof, pavement | columns, stone/roof materials | bays, roof, trim | repeated snap, draw calls | Medium | column modules | Medium | Medium |
| 7 | Piazza | large paving, fountains, bases, statues, portico edges | paving, statue references | fountain basin, bases, cippi | scale, occlusion | Medium | urban props | Medium | Medium |
| 8 | Basilica | large hall bays, columns, roof, clerestory, admin facade | columns/materials | wall/roof spans | interior traversal, visibility | High | performance budget | High | High |
| 9 | Forum section | plaza, portico, basilica slice, temple slice, tabernae, statues | all previous | composition prefabs | camera vistas, historical review | High | phases 1-8 | High | High |
| 10 | Complete forum | repeated forum sections and monuments | broader library | procedural composition | streaming, occlusion | Very high | world partition plan | Very high | Very high |
| 11 | District | streets, houses, shops, domus, services | vegetation/props variety | PCG street dressing | streaming/traversal loops | Very high | PCG rules | High | Very high |
| 12 | City | districts, monuments, LOD, simulation hooks | curated reusable kit | procedural city blocks | performance, memory, navigation | Very high | production pipeline | Very high | Very high |
