# Audit del piano eseguibile della demo di Pompei — 2026-07-20

**ID:** AUD-POMPEII-PLAN-2026-07-20
**Stato:** Completato; implementazione NON READY

## Scopo

Verificare che la Game Bible sia stata trasformata in un piano eseguibile per una vertical slice rappresentativa e che ogni blocker all'avvio sia documentato.

## Descrizione

L'audit confronta mandato, percorsi, sistemi, contenuti, epic, feature, user story, milestone, acceptance, rischi e checklist finale. Non valuta codice o asset, che non esistono e non sono autorizzati.

## Ambito

Demo di Pompei, baseline 1 luglio 77 d.C., PVS-1, tre origini, roadmap PT–DP e gate READY.

## Risultati

| Area | Esito | Evidenza |
|---|---|---|
| obiettivo/durata/data/area | definito S3 | [mandato](../../07-pompeii-demo/design/demo-charter.md) |
| tre percorsi | flussi end-to-end S3 | [percorsi](../../07-pompeii-demo/design/playable-paths.md) |
| sistemi attivi/semplificati/esclusi | classificati | [scope sistemi](../../07-pompeii-demo/design/demo-systems-scope.md) |
| professioni/contenuti | portfolio e cap D | [professioni](../../07-pompeii-demo/design/demo-professions.md), [contenuti](../../07-pompeii-demo/design/demo-content-scope.md) |
| backlog | 12 epic, 44 feature, 12 user story | [backlog](../roadmap-backlog/demo-backlog.md) |
| fasi | PT, PG, PA, VS, DI, DP | [milestone](../roadmap-backlog/milestones.md) |
| qualità | DA-01–10 e DoD | [acceptance](../../07-pompeii-demo/design/demo-acceptance.md) |
| gate codice | binario e auditabile | [READY](../../READY_FOR_IMPLEMENTATION.md) |

## Decisioni consolidate

- Data di design: 1 luglio 77 d.C.; eruzione esclusa.
- PVS-1 come topologia di pianificazione, poligono GIS ancora blocker.
- 5–7 ore per origine e 30 giorni diegetici.
- Tre professioni complete: pane, tessile/fullonica, servizio-consegna.
- Una situazione grano condivisa collega i percorsi senza diventare quest lineare.
- Successione tramite erede già esistente/epilogo o scenario accelerato, senza accelerare la crescita di un figlio.
- Il codice parte solo dopo checklist completa e nuova autorizzazione esplicita.

## Copertura dei requisiti utente

Obiettivo, durata, area, epoca, data, personaggi, status, loop, professioni, edifici, sistemi, eventi, missioni, combattimento, economia, famiglia, religione, politica, crimini, reputazione, dialoghi, audio, UI e save sono mappati nei documenti della demo. Progressione, lavoro, guadagno/spesa, errori, conseguenze, status, famiglia ed eredità sono presenti nei tre percorsi.

## Blocker documentati

La checklist READY registra: GIS/edifici; review storico-giuridico-etica; piattaforme, camera e rating; versione UE/plugin; formati dati/save; hardware e benchmark; accessibilità/input; owner/team/stime; branch `main`, CI, LFS e artifact; licenze e autorizzazioni. Nessun blocker individuato dall'audit resta soltanto in prosa non indicizzata.

## Verdetto

Il piano è eseguibile come struttura di produzione, ma **NON READY per il codice**. Le feature possono essere stimate e revisionate; nessuna attività implementativa può iniziare finché tutte le condizioni RFI-MUST non sono PASS.

## Dipendenze

- [ADR-0022](../../00-governance/decision-log.md)
- [Questioni aperte](../../00-governance/open-questions.md)
- [Rischi](../risk-register.md)

## Collegamenti agli altri documenti

- [Roadmap prodotto](../roadmap-backlog/product-roadmap.md)
- [Epic](../roadmap-backlog/epics.md)
- [Definition of Done](../roadmap-backlog/definition-of-done.md)

## Decisioni ancora aperte

Quelle elencate in READY e nel registro delle questioni; sono esplicite e impediscono lo stato Ready quando pertinenti al PT.

## Criteri di completamento

Copertura integrale dei requisiti, tracciabilità a backlog/milestone/acceptance, registro completo dei blocker e controlli repository senza errori.

## TODO

- Rieseguire al candidate gate Ready.
- Allegare firme ed evidenze quando disponibili.
