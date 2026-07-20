# Fonti ufficiali Unreal Engine 5

## Scopo

Registrare le fonti Epic utilizzate per decisioni UE5 e imporre verifica della versione prima dell'implementazione.

## Descrizione

Le tecnologie engine cambiano. Ogni ADR deve indicare versione UE, data di revisione, stato Stable/Beta/Experimental dichiarato da Epic e fallback.

## Ambito

Fonti primarie ufficiali per World Partition, MassEntity, dati, Gameplay Tags, Behavior Tree e tecnologie correlate. Ultima revisione: 2026-07-20; documentazione Epic visualizzata come UE 5.8.

## Registro iniziale

| Area | Fonte ufficiale | Uso |
|---|---|---|
| World Partition | [Epic — World Partition](https://dev.epicgames.com/documentation/unreal-engine/world-partition-in-unreal-engine?lang=en-US) | celle, streaming sources, OFPA, Data Layers, HLOD |
| HLOD | [Epic — World Partition HLOD](https://dev.epicgames.com/documentation/unreal-engine/world-partition---hierarchical-level-of-detail-in-unreal-engine) | proxy celle non caricate |
| Navigation | [Epic — World Partitioned Navigation Mesh](https://dev.epicgames.com/documentation/en-us/unreal-engine/world-partitioned-navigation-mesh) | candidato sperimentale; cautela shipping |
| MassEntity | [Epic — Mass Entity Overview](https://dev.epicgames.com/documentation/en-us/unreal-engine/overview-of-mass-entity-in-unreal-engine) | frammenti, archetipi, processori/subsystem |
| MassGameplay | [Epic — Mass Gameplay Overview](https://dev.epicgames.com/documentation/en-us/unreal-engine/overview-of-mass-gameplay-in-unreal-engine) | representation LOD, StateTree, signals, movement |
| Data Assets | [Epic — Data Assets](https://dev.epicgames.com/documentation/en-us/unreal-engine/data-assets-in-unreal-engine) | Primary Asset ID, bundle, load/unload |
| Data Registry | [Epic — Data Registries](https://dev.epicgames.com/documentation/en-us/unreal-engine/data-registries-in-unreal-engine) | dati read-only, cache e accesso async |
| Gameplay Tags | [Epic — Gameplay Tags](https://dev.epicgames.com/documentation/en-us/unreal-engine/using-gameplay-tags-in-unreal-engine) | tassonomia gerarchica e sorgenti config/table/C++ |
| Behavior Tree | [Epic — Behavior Tree Overview](https://dev.epicgames.com/documentation/en-us/unreal-engine/behavior-tree-in-unreal-engine---overview) | tattica visuale e Blackboard |

## Policy di verifica

Nessuna pagina “latest” è sufficiente da sola: bloccare versione engine, controllare pagina della versione, release notes e stato plugin. Screenshot/blog/forum non sono autorità architetturale. Cambi di stato o API aprono ADR upgrade e regression plan.

## Dipendenze

- [Decisione engine](engine-decision.md)
- [Upgrade](engine-upgrades.md)
- [ADR](../architecture/technical-adr.md)

## Collegamenti agli altri documenti

- [Mappa sistemi](system-implementation-map.md)
- [Plugin](plugins.md)
- [Rischi](../../11-production/risk-register.md)

## Test e Definition of Done

Ogni tecnologia P0 ha URL Epic versionato, stato, owner, data review, spike, benchmark, fallback e decisione.

## Decisioni ancora aperte

- Versione UE baseline.
- Cadenza review delle fonti ufficiali.

## TODO

- Integrare fonti ufficiali per StateTree, Smart Objects, CommonUI/MVVM, Enhanced Input, MetaSounds, localization e automation dopo selezione P0.
