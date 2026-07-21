# Roman Modular Construction Kit — technical standard

## Goal

The Roman Modular Construction Kit is a future content system for assembling Roman buildings from small free or internally generated reusable components. It is documentation-only in this prompt: no assets, Blueprints, Geometry Script tools, PCG graphs or maps are created.

## Unreal modular standard

- Unreal unit: 1 cm.
- Detail snap: 10 cm for trim, decals, tile offsets and props.
- Small module snap: 50 cm for doors, windows, benches, crates and roof tiles.
- Main building snap: 100 cm for walls, floors and facades because it maps cleanly to UE centimeters and human-scale layouts.
- Bay/campata snap: 300 cm for small domestic bays and 400 cm for portico/forum/temple bays; these values keep doors, columns and wall spans divisible by 100 cm.
- Parametric defaults: floor height 300 cm domestic / 400 cm monumental; door width 100-140 cm; window width 80-120 cm; wall thickness 30-60 cm; column diameter module 40-80 cm.
- Pivot: bottom-front-left or bottom-center depending module family; document per asset in Data Asset metadata.
- Axes: +X forward/depth, +Y right/width, +Z up.
- Tolerance: leave 0.5-1.0 cm hidden overlap to avoid light leaks; visible seams are covered by trim/cornice/plaster variants.
- Intersections: use corner modules, pilasters, columns or trim pieces rather than non-manifold overlaps.

## Component families

| Family | Module | Function | Indicative size | Pivot | Snap | Scale/orientation | Collision | Materials | Reuse/historical use | Variants | Detail | Nanite | LOD | Performance |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Structure | Wall plain | enclosure/load-bearing visual | 300x40x300 cm | bottom-left | 100 cm | +X thickness, +Y span | simple box | plaster, brick, stone | houses, insulae, shops | clean, damaged, painted | medium | no unless high-poly | yes | low |
| Structure | Wall door | doorway bay | 300x40x300 cm, 100-140 cm opening | bottom-left | 100 cm | opening faces -X/+X variant | simple per-side boxes | plaster/stone | houses, tabernae | lintel/arched | medium | no | yes | low |
| Structure | Wall window | window bay | 300x40x300 cm, 80-120 cm opening | bottom-left | 100 cm | sill height parameter | simple boxes | plaster/brick | upper floors, domus | shutter/grill | medium | no | yes | low |
| Structure | Internal/external corner | joins two wall runs | 40x40x300 cm plus returns | bottom-corner | 100 cm | 90-degree variants | simple | same wall family | all buildings | damaged/trimmed | medium | no | yes | low |
| Structure | Pillar/column/semicolumn | vertical support and rhythm | 40-80 cm diameter, 300-600 cm high | bottom-center | 50/100 cm | Z up | capsule/simple convex | stone, marble, plaster | porticos, temples, peristyles | Doric/Ionic/Corinthian/plain | high | yes for scans | yes | low/medium |
| Structure | Base/capital/architrave | architectural order pieces | 50-400 cm spans | bottom-center | 50/100 cm | align to columns | simple | stone/marble | temples, porticos | order-specific | high | yes if sculpted | yes | medium |
| Structure | Arch/volta | opening/covered span | 300-400 cm span | bottom-center | 100 cm | arch plane along Y | custom simple | stone/brick/plaster | gates, shops, aqueduct-like features | round/segmental | high | yes | yes | medium |
| Structure | Beam/floor/stair/foundation/podium | structural supports and traversal | 100-400 cm modules | bottom-left | 50/100 cm | +Z up | simple boxes/stair collision | wood/stone/brick | houses, temples, shops | straight/landing/damaged | medium | no | yes | low |
| Roofs | tegula/imbrex/falda/colmo/gronda | roof surface and silhouette | tile 30-60 cm; roof bay 300x400 cm | bottom/edge | 10/50 cm | slope parameter | usually no/player-block roof optional | terracotta, aged ceramic | houses, shops, temples | clean/broken/mossy | medium | no | yes | low/medium |
| Roofs | tympanum/fronton/truss/compluvium/impluvium | monumental/domus roof features | 300-1200 cm spans | bottom-center | 100 cm | align to bay | simple | stone/wood/terracotta | temples/domus | plain/decorated | high | yes for sculpted | yes | medium |
| Facades | plaster/brick/opus materials/trim/niche/opening | visual surfaces and identity | material tiles 100-400 cm | surface pivot | 10/50 cm | UV scale metadata | no except protrusions | opus reticulatum/incertum/latericium/mixtum, fresco | all buildings | wealth/degradation variants | medium/high | material only | n/a | low |
| Floors | basoli/sidewalk/crossing/opus signinum/mosaic | walkable ground | 100-400 cm modules | bottom-left | 50/100 cm | +Z up | simple box | stone, cocciopesto, mosaic | streets, shops, domus | worn/wet/dirty | medium | no/yes for scans | yes | low |
| Urban | fountains/altars/statues/bases/cippi/banks/channels/parapets | street function and landmarks | varied 50-400 cm | bottom-center | 10/50 cm | +Z up | simple/custom | stone/bronze/wood | streets, fora, sanctuaries | wealth/regional variants | medium/high | yes for scans | yes | medium |
| Props | amphorae/dolia/ceramics/lamps/crates/baskets/furniture/tools/merchandise | life and economy dressing | 10-200 cm | bottom-center | 10/50 cm | +Z up | simple/no collision for small items | ceramic, wood, cloth, metal | shops/domus/storage | full/broken/stacked | low/medium | yes only scans | yes | low/medium |
| Vegetation | olive/cypress/vine/fig/palm/laurel/shrub/grass/flowers | courtyard and street ecology | varied | base | 10/50 cm | +Z up | simple/no collision | foliage materials | gardens, courtyards, roadside | seasonal/trimmed | medium | no | yes mandatory | medium/high |

## Assemblies

- Simple house: four wall modules, one door bay, two window bays, beams, roof tile modules, floor material, plaster, few props.
- Taberna: open facade, counter, rear room, door, shelves, amphorae, sign, sidewalk module.
- Domus: atrium, compluvium, impluvium, cubicula, tablino, peristyle columns, mosaics/frescoes, garden plants.
- Temple: podium, stair, columns, bases, capitals, architraves, frieze, fronton, cella walls and roof.
- Forum: paved plaza, porticos, columns, basilica modules, temple modules, curia/admin blocks, tabernae, arches, statues, fountains and bases.

## Missing components strategy

If a free asset is unavailable, prefer: existing-module assembly, simple parametric modeling, procedural generation, Unreal Modeling Tools, Geometry Script, Blueprint construction, PCG scattering, Blender scripting, procedural materials, decals, public-domain photogrammetry reference, or historically plausible simplification. Purchases are forbidden.

## Aggiornamento Prompt 20 — fondazione C++

La fondazione runtime del sistema modulare è stata introdotta con enumerazioni Blueprint, strutture dati, catalogo moduli, stile architettonico, libreria regole, validatore e actor procedurale. I layout ora disponibili sono astratti e deterministici per casa semplice, taberna, tempio e tratto di strada. Non vengono creati asset, mappe o dipendenze UnrealEd; i riferimenti a mesh e materiali restano soft e sicuri in assenza di contenuti importati.

Le verifiche Unreal restano `LOCAL_UNREAL_TEST_REQUIRED`; Play In Editor resta `MANUAL_VERIFICATION_REQUIRED`.
