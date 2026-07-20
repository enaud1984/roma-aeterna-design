# Audit della progettazione tecnica trasversale — 2026-07-20

**ID:** AUD-TECH-TRANSVERSAL-2026-07-20
**Stato:** Completato con blocker S4 registrati

## Scopo

Verificare che dati, salvataggi, performance, strumenti e pipeline traducano l'architettura UE5 in contratti coerenti e testabili senza introdurre codice o asset.

## Descrizione

L'audit valuta copertura, ownership, dipendenze, recovery, scalabilità, test e readiness. I numeri prestazionali sono classificati come target di design D, non misure o promesse definitive.

## Ambito

- 21 famiglie dati richieste;
- salvataggio manuale/autosave, migrazione, recovery e successione;
- CPU, GPU, memoria, disco, streaming, NPC, animazione, pathfinding, traffico, folla e load/save;
- editor, validator, generatore NPC, debug, telemetria, profiling e test;
- Git, branch, commit, PR, CI, build, asset, LFS, release e documentazione.

## Metodo

1. Confronto con [architettura UE5](../../10-technical/technical-architecture.md) e ownership dei sistemi.
2. Verifica di ID stabili, dati posseduti/letti/modificati ed eventi.
3. Failure analysis per salvataggio, tooling e pipeline.
4. Allocazione di budget iniziali e scenari benchmark.
5. Registrazione di decisioni, rischi e questioni non risolvibili senza spike o autorità amministrativa.
6. Controllo automatico di link, README, sezioni minime e whitespace.

## Risultati

| Area | Stato | Evidenza | Blocco successivo |
|---|---|---|---|
| Modello dati | S3 | [architettura](../../10-technical/data/data-architecture.md), [catalogo](../../10-technical/data/domain-schema-catalog.md) | formato fisico, indici e benchmark |
| Save system | S3 | [save architecture](../../10-technical/save-system/save-architecture.md) | formato, compatibilità e failure injection |
| Performance | S3 | [strategia](../../10-technical/performance/performance-strategy.md), [sintesi](../../10-technical/performance-budgets.md) | hardware e scene benchmark |
| Tooling | S3 | [strategia](../../10-technical/tools/tools-strategy.md), [contratti](../../10-technical/tools/designer-tool-contracts.md) | owner, tecnologia e UX prototype |
| Pipeline | S3 | [panoramica](../../10-technical/pipelines/pipeline-overview.md), [fonti](../../10-technical/pipelines/pipeline-official-sources.md) | `main`, runner, LFS e artifact storage |

## Decisioni consolidate

- Record di dominio persistenti indipendenti da Actor/UObject e path asset.
- ID stabili tipizzati, owner unico, tombstone e schema versionato.
- Save composto da manifest, snapshot segmentati e journal selettivo con promozione atomica.
- Successione che trasferisce diritti e responsabilità, non identità, memoria o abilità del defunto.
- Budget D iniziali con margini, scenari e gate di regressione.
- Tool che producono change set e usano gli stessi schema/validator del runtime.
- Sorgenti testuali, binary pesanti, derivati e artifact in classi di storage distinte.

## Correzioni e lacune chiuse

- Copertura dati estesa da principi generici a tutte le famiglie richieste.
- Recovery del save reso esplicito per checksum, segmenti, backup e migrazioni.
- Conteggi e frequenze di simulazione collegati ai tier NPC e militari esistenti.
- Editor ed osservabilità convertiti da lista aspirazionale a contratti P0.
- Pipeline completata con review, gate CI, supply chain, release e rollback.
- Duplicazioni evitate mantenendo i documenti di sintesi come puntatori verso le autorità specializzate.

## Questioni e rischi residui

Le questioni Q-235–Q-252 nel [registro](../../00-governance/open-questions.md) coprono formato fisico, support window, hardware, strumenti, telemetria, runner, branch e LFS. I rischi R-072–R-082 nel [registro rischi](../risk-register.md) coprono deriva schema, corruzione save, budget, tooling, privacy e delivery.

Il repository remoto corrente usa il branch documentale come default; la pipeline desiderata con `main` protetta richiede un atto amministrativo futuro. Nessuna modifica alle impostazioni remote è stata effettuata.

## Validazione richiesta prima di S4

- spike del registry/store e migrazioni su dataset rappresentativo;
- golden saves multi-versione con fault injection;
- benchmark PVS-1 su hardware target;
- prototype UX dei tool P0 con designer e QA;
- clone/build/release proof con LFS, runner e rollback;
- security/privacy review per artifact, segreti e telemetria.

## Dipendenze

- [Decisione ADR-0021](../../00-governance/decision-log.md)
- [Matrice di readiness](../roadmap-backlog/implementation-readiness-matrix.md)
- [Roadmap](../roadmap-backlog/documentation-roadmap.md)

## Collegamenti agli altri documenti

- [Technical Design](../../10-technical/README.md)
- [Matrice dipendenze](../../00-governance/system-dependency-matrix.md)
- [Audit UE5](ue5-technical-architecture-audit-2026-07-20.md)

## Decisioni ancora aperte

Tutte le scelte fisiche e di piattaforma elencate in Q-235–Q-252. Non impediscono S3, ma impediscono il gate S4/Ready.

## Criteri di completamento

Audit completo quando le cinque aree hanno autorità canonica, dipendenze, rischi, test, DoD e blocker registrati, e i controlli repository terminano senza errori.

## TODO

- Rieseguire dopo gli spike tecnici autorizzati.
- Sostituire target D con misure versionate.
- Allegare report CI e benchmark quando esisteranno.
