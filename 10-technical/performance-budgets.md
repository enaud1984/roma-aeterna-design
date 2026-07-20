# Budget prestazionali — panoramica canonica

## Scopo

Fornire l'accesso sintetico ai budget iniziali della vertical slice.

## Descrizione

La specifica autoritativa è [Strategia e budget prestazionali](performance/performance-strategy.md). I target sono provvisori D fino all'approvazione della piattaforma e dei benchmark.

## Ambito

CPU/GPU, memoria, streaming, NPC, animazioni, pathfinding, traffico, folla, save e caricamenti.

## Baseline sintetica

60 fps/16,67 ms; GPU 13,5 ms target; processo 10 GiB steady; VRAM 6,5 GiB; demo ≤30 GiB; 40 NPC high fidelity, 120 Actor addizionali e 800 low/Mass candidati; save ≤256 MiB worst-case; cold load ≤30 s. Tutti richiedono hardware e build dichiarati.

## Dipendenze

- [Strategia completa](performance/performance-strategy.md)
- [Hardware targets](../11-production/platform-release/hardware-targets.md)

## Collegamenti agli altri documenti

- [Benchmark](performance/benchmark-scenes.md)
- [Readiness](../11-production/roadmap-backlog/implementation-readiness-matrix.md)

## Test e Definition of Done

Nessun numero è promosso a requisito S4 senza capture su scena/hardware/build versionati.

## Decisioni ancora aperte

- Q-229 e Q-243–Q-247.

## TODO

- Sincronizzare dopo ogni benchmark gate.
