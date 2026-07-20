# Navigazione e simulazione delle folle

## Scopo

Definire movimento credibile e scalabile in strade, edifici ed eventi senza pathfinding globale per ogni NPC.

## Descrizione

Navigazione separa rete semantica di alto livello, path locale, steering/avoidance e animazione. Folle usano destinazioni e vincoli individuali con flow aggregation ai LOD lontani.

## Ambito

Navmesh, world-partitioned nav candidata, graph stradale, portal/entrance, Smart Objects candidati, avoidance, density, evacuation, Mass/Actor bridge e fallback.

## Livelli

N0 path dettagliato + avoidance; N1 path locale semplificato; N2 route segment/ETA; N3 flussi tra zone; N4/N5 matrici origine-destinazione statistiche. Promozione ricostruisce posizione valida da route/time/seed, senza teletrasporto visibile.

## Regole e failure

Accesso, status, orari, folla, incendio e edificio definiscono costo/blocco. Nessun NPC conosce uscite non apprese quando il comportamento dipende da conoscenza. Path fallito produce attesa, alternativa, richiesta o abbandono; replan usa backoff/isteresi. World Partition navmesh sperimentale non è requisito senza ADR; fallback: nav data per area caricata + graph semantico.

## Performance e test

Budget path requests/frame, cache, invalidation, agents N0/N1, avoidance neighbors e update rate. Test strettoie pompeiane, mercato, porta, terme, anfiteatro, incendio/panico, cell unload, 1k+ projections candidate e determinismo aggregato.

## Dipendenze

- [World Partition](world-partition.md)
- [Mass](mass-entity.md)
- [Crowd design](../../04-simulation/npc-population-ai/crowds.md)
- [Performance](../performance/npc-crowd-budget.md)

## Collegamenti agli altri documenti

- [Mondo](../../03-world/structures/roads.md)
- [Eventi](../../06-content/events/dynamic-event-framework.md)
- [Fonti UE5](official-sources.md)

## Definition of Done

LOD, access graph, local nav, avoidance, failure/fallback, streaming protocol e budget approvati; scenari P0 senza stallo, compenetrazione sistemica o knowledge leak.

## Decisioni ancora aperte

- Nav framework UE baseline e Smart Objects.
- Densità/avoidance solution per P0.

## TODO

- Definire benchmark e reti semantiche Pompei.
- Mappare invalidazioni edificio/evento.
