# Audit architettura tecnica Unreal Engine 5 — 2026-07-20

## Scopo

Registrare copertura, decisioni, rischi e blocchi della traduzione Game Bible → software UE5.

## Descrizione

L'audit verifica piani architetturali, moduli/plugin, policy C++/Blueprint, dati/tag, componenti/subsystem, AI/Mass, streaming/navigazione, mappa sistemi e convenzioni trasversali.

## Ambito

Documentazione in `10-technical/architecture` e `10-technical/unreal-engine-5`, registri di governance e fonti ufficiali Epic. Nessun file sorgente, Blueprint o asset è stato creato.

## Risultati

| Area | Esito | Bloccante S4 |
|---|---|---|
| piani/authority | S3 | review interdisciplinare P0 |
| progetto/moduli/plugin | S3 | packaging, owner e build benchmark |
| C++/Blueprint | S3 | soglie lint e API exposure |
| dati/tag/config | S3 | dataset map e ruleset manifest |
| componenti/subsystem/eventi | S3/S4 | lifecycle matrix e fault injection |
| AI/StateTree/BT/Mass | S3 | spike e benchmark Q-230/Q-231 |
| World Partition/nav | S3 | PVS-1 benchmark e baseline UE |
| sistemi gameplay | S3 | API/event/save contract puntuali |
| convenzioni/quality | S3 | tooling fitness e ownership |

## Decisioni applicate

Domain record persistenti indipendenti dagli Actor; quattro piani; moduli aciclici; C++ autoritativo e Blueprint bounded; dati read-only separati dal save; Mass/StateTree/plugin dietro adapter e fallback; World Partition non governa esistenza; logging/errori/config/test documentati.

## Fonti e accuratezza tecnica

Le capacità UE5 sono state verificate contro documentazione Epic elencata in [fonti ufficiali](../../10-technical/unreal-engine-5/official-sources.md). La documentazione corrente segnala World Partition Navmesh come sperimentale: non è dipendenza core. Ogni decisione definitiva richiede versione UE baseline.

## Rischi e verifiche

R-064–R-071 coprono stato fragile, accoppiamento, dipendenze sperimentali, streaming, Blueprint, upgrade, memoria e save. Gate editoriale: link, README, sezioni minime, `git diff --check`; gate S4: Q-229–Q-234 e benchmark.

## Dipendenze

- [Architettura](../../10-technical/technical-architecture.md)
- [Moduli](../../10-technical/unreal-engine-5/modules.md)
- [Mappa sistemi](../../10-technical/unreal-engine-5/system-implementation-map.md)
- [Principi](../../10-technical/architecture/architecture-principles.md)

## Collegamenti agli altri documenti

- [Readiness](../roadmap-backlog/implementation-readiness-matrix.md)
- [Rischi](../risk-register.md)
- [Questioni aperte](../../00-governance/open-questions.md)

## Decisioni ancora aperte

- Q-229–Q-234.
- Owner nominali Technical Architecture, AI, World, Build, Data e Performance.

## TODO

- Ripetere audit dopo macroarea dati/save/performance/tools/pipeline.
- Rieseguire review fonti sulla versione UE baseline approvata.
