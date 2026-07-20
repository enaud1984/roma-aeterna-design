# Technical Design

## Scopo

Fornire l'indice canonico dell'area **Technical Design**.

## Descrizione

Architettura, UE5, dati, salvataggi, performance, strumenti, pipeline e sicurezza.

## Ambito

La cartella contiene documenti fondativi e sottodomini specializzati. Gli approfondimenti futuri devono essere inseriti nel documento canonico pertinente.

## Documenti contenuti

- [architecture](architecture/README.md)
- [unreal engine 5](unreal-engine-5/README.md)
- [data](data/README.md)
- [save system](save-system/README.md)
- [performance](performance/README.md)
- [tools](tools/README.md)
- [pipelines](pipelines/README.md)
- [security](security/README.md)

I documenti presenti direttamente nella cartella costituiscono le specifiche di sintesi già avviate e restano consultabili dalla [mappa completa](../00-governance/documentation-map.md).

Documenti di sintesi diretti: [architettura tecnica](technical-architecture.md), [modello dati — panoramica](data-model.md), [budget prestazionali](performance-budgets.md) e [strumenti e osservabilità](tools-and-observability.md).

## Dipendenze

- [Visione creativa](../01-vision/creative-vision.md)
- [Standard documentale](../00-governance/documentation-standard.md)

## Collegamenti con le altre aree

- [Indice generale](../README.md)
- [Mappa documentale](../00-governance/documentation-map.md)
- [Matrice delle dipendenze](../00-governance/system-dependency-matrix.md)

## Stato di avanzamento

**Stato:** architettura UE5 e fondazioni trasversali a S3; restano aperte scelte fisiche, hardware, infrastruttura, owner e benchmark per il gate S4.

## Decisioni ancora aperte

- Formati dati/save, hardware target, runner, Git LFS e owner nominali.
- Approvazione dei budget provvisori tramite benchmark PVS-1.

## TODO

- Assegnare owner/reviewer e risolvere Q-235–Q-252.
- Produrre spike e benchmark soltanto dopo il gate che autorizza l'implementazione.
- Mantenere indice, registri e collegamenti sincronizzati.
