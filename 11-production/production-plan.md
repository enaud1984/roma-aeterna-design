# Piano di produzione documentale e pre-produzione

**ID:** PRD-001
**Stato:** Draft

## Fase corrente — Game Bible Baseline

Obiettivo: trasformare visione e ambizioni in specifiche approvabili, rischi misurabili e scope del vertical slice. Nessun codice di gioco è previsto da questa attività.

## Milestone documentali e di esecuzione

| Milestone | Risultato | Gate |
|---|---|---|
| M0 Foundation | tassonomia, visione, framework storico, registri | review direzione |
| M1 Domain Bible | sistemi completi con scenari e dipendenze | review interdisciplinare |
| M2 Pompeii Definition | data, perimetro, popolazione, catene, contenuti | scope firmato |
| M3 Technical Discovery | ADR tecnici e benchmark progettati | rischi principali testabili |
| M4 Readiness | scope, backlog, architettura e checklist READY | autorizzazione esplicita al codice |
| M5 Esecuzione demo | PT → PG → PA → VS → DI → DP | gate definiti nelle milestone eseguibili |

La sequenza operativa canonica è in [milestone della demo](roadmap-backlog/milestones.md). La fase corrente termina con `READY_FOR_IMPLEMENTATION` documentata ma non ancora superata.

## Workstream

Direction; historical research; systems design; narrative/content; world/art/audio; UX/accessibility; architecture/tools; production/QA. Ogni workstream mantiene owner, backlog di domande e dipendenze.

## Stime

Nessuna stima affidabile precede: piattaforme, data della demo, densità misurata, strategia audio, perimetro topografico e benchmark di authoring. La produzione deve stimare range e confidenza, non singole date premature.

## Change control

Qualunque feature che altera un pilastro, aggiunge un sistema core o cambia il perimetro passa da ADR e analisi di costo totale: implementazione, contenuti, strumenti, QA, localizzazione, accessibilità e mantenimento.

Collegamenti: [rischi](risk-register.md), [QA](qa-strategy.md), [scope](../01-vision/scope-and-non-goals.md).

## Scopo

Conservare e sviluppare la responsabilità canonica descritta da questo documento all'interno della Game Bible.

## Descrizione

Il contenuto preesistente costituisce la baseline del dominio. Questa sezione normalizza il documento secondo il contratto minimo della nuova architettura senza sostituirne le informazioni.

## Ambito

Il perimetro è quello definito nelle sezioni precedenti; implementazione e asset restano esclusi finché non saranno autorizzati da milestone e decisioni formali.

## Dipendenze

- [Standard documentale](../00-governance/documentation-standard.md)
- [Visione creativa](../01-vision/creative-vision.md)

## Collegamenti agli altri documenti

- [Indice generale](../README.md)
- [Mappa documentale](../00-governance/documentation-map.md)
- [Registro decisioni](../00-governance/decision-log.md)
- [Questioni aperte](../00-governance/open-questions.md)

## Decisioni ancora aperte

- Owner e reviewer nominali.
- Stato di approvazione e profondità richiesta dalla roadmap documentale.
- Eventuali confini da riallineare con i nuovi sottodomini canonici.

## TODO

- Collegare il contenuto ai nuovi documenti specializzati pertinenti.
- Assegnare ownership, versione e milestone.
- Aggiungere requisiti, fonti, rischi, test e Definition of Done durante l'approfondimento.
