# Pipeline e Gestione Asset

## Scopo

Definire l'architettura documentale del dominio **Pipeline e Gestione Asset**.

## Descrizione

Indice delle specifiche modulari della futura Game Bible e Technical Design Bible.

## Ambito

Include i documenti elencati; nessuna scelta implementativa è autorizzata dalla sola presenza di questi scheletri.

## Documenti contenuti

- [Panoramica delle Pipeline](pipeline-overview.md)
- [Fonti ufficiali GitHub e Git LFS](pipeline-official-sources.md)
- [Gestione degli Asset](asset-management.md)
- [Naming degli Asset](asset-naming.md)
- [Pipeline Contenuti](content-pipeline.md)
- [Pipeline Artistica](art-pipeline.md)
- [Pipeline Audio](audio-pipeline.md)
- [Pipeline di Localizzazione](localization-pipeline.md)
- [Pipeline di Build](build-pipeline.md)
- [Pipeline di Release](release-pipeline.md)

## Dipendenze

- [Visione creativa](../../01-vision/creative-vision.md)
- [Standard documentale](../../00-governance/documentation-standard.md)

## Collegamenti con le altre aree

- [Indice generale](../../README.md)
- [Mappa documentale](../../00-governance/documentation-map.md)
- [Matrice delle dipendenze](../../00-governance/system-dependency-matrix.md)

## Stato di avanzamento

**Stato:** S3 per governance, CI, asset pesanti e release; infrastruttura e policy amministrative da approvare.

## Decisioni ancora aperte

- Branch `main`, runner, storage, Git LFS, retention e owner definitivi.

## TODO

- Approvare branch model, required checks, LFS e release policy.
- Assegnare owner/reviewer e provare rollback su fondazione tecnica futura.
