# READY FOR IMPLEMENTATION — Pompei vertical slice

**ID:** GATE-READY-POMPEII-001
**Stato al 2026-07-20:** **NON READY — implementazione non autorizzata**

## Scopo

Stabilire il gate oggettivo, auditabile e binario dopo il quale sarà possibile iniziare a scrivere codice per la sola fondazione tecnica della vertical slice di Pompei.

## Descrizione

Tutte le condizioni `RFI-MUST` devono essere soddisfatte con evidenza collegata e approvazione. Una casella non selezionata, un'evidenza scaduta o una decisione blocker riporta lo stato a `NON READY`. Questa checklist non sostituisce l'autorizzazione esplicita dell'utente a iniziare il codice.

## Ambito

Primo prototipo tecnico: struttura UE5, moduli/plugin approvati, configurazione, logging/errori, test/CI, test map e ciclo minimo tempo–calendario–NPC–routine–interazione–inventario–save. Non autorizza l'intera demo, asset finali o sistemi post-slice.

## Regola di autorizzazione

Il codice può iniziare soltanto quando:

1. tutte le righe Must sono `PASS`;
2. nessun rischio blocker/critical è privo di mitigation e owner;
3. nessuna domanda indicata come blocker resta aperta;
4. Direction, Design, Historical, Technical, Production e QA firmano il gate;
5. l'utente invia successivamente un'istruzione esplicita che autorizza l'implementazione.

Waiver non ammessi per proprietà dati, corruzione save, sicurezza/credenziali, licenze, accuratezza/etica blocker, build riproducibile e separazione code/docs branch.

## Checklist di prodotto e scope

- [ ] **RFI-MUST-001** Mandato demo approvato: obiettivo, 5–7 ore, tre percorsi e non-obiettivi. Evidenza: [mandato](07-pompeii-demo/design/demo-charter.md).
- [ ] **RFI-MUST-002** Data 1 luglio 77 d.C. e assenza dell'eruzione revisionate e registrate. Evidenza: [snapshot](07-pompeii-demo/design/historical-date.md).
- [ ] **RFI-MUST-003** Poligono GIS PVS-1, bordi, scala e hub P0 approvati. Evidenza: [area](07-pompeii-demo/design/playable-area.md).
- [ ] **RFI-MUST-004** Edifici P0/P1/P2 identificati, costati e storicamente revisionati. Evidenza: [catalogo](07-pompeii-demo/design/accessible-buildings.md).
- [ ] **RFI-MUST-005** Scope sistemi/content lock approvato; ogni esclusione è esplicita. Evidenza: [sistemi](07-pompeii-demo/design/demo-systems-scope.md), [contenuti](07-pompeii-demo/design/demo-content-scope.md).
- [ ] **RFI-MUST-006** Tre percorsi e personaggi iniziali superano review storica, giuridica, etica e narrativa. Evidenza: [percorsi](07-pompeii-demo/design/playable-paths.md).

## Checklist di design dei sistemi

- [ ] **RFI-MUST-010** Tutti i sistemi P0 del [catalogo](00-governance/system-catalog.md) sono almeno S4 nella [matrice](11-production/roadmap-backlog/implementation-readiness-matrix.md).
- [ ] **RFI-MUST-011** Ownership dati, comandi/query/eventi e dipendenze sono completi, versionati e privi di cicli vietati.
- [ ] **RFI-MUST-012** Golden scenario definiti per tempo, persona, NPC, routine, interazione, inventario, economia e save.
- [ ] **RFI-MUST-013** Matrice status–capacità–atto–rimedio P0 approvata per cittadino, liberta e persona schiavizzata.
- [ ] **RFI-MUST-014** Successione, eredità, morte e continuazione con figlio/erede hanno casi nominali, alternativi e invalidi.
- [ ] **RFI-MUST-015** Acceptance DA-01–10 mappata a test, owner e ambiente. Evidenza: [criteri demo](07-pompeii-demo/design/demo-acceptance.md).

## Checklist storica, etica e contenuti

- [ ] **RFI-MUST-020** Ogni claim P0 ha periodo, area, fonte/licenza e classe A–E; nessun E è trattato come canonico.
- [ ] **RFI-MUST-021** Snapshot degli edifici, istituzioni, calendario, moneta, nomi e professioni è coerente con luglio 77.
- [ ] **RFI-MUST-022** Schiavitù, coercizione, violenza, religione, genere e famiglia superano Historical e Sensitivity review.
- [ ] **RFI-MUST-023** Rating target, pubblico e content policy sono approvati.
- [ ] **RFI-MUST-024** Lingue, pronuncia, sottotitoli e policy di localizzazione sono approvati.
- [ ] **RFI-MUST-025** Provenienza e licenza di ogni source asset/dataset P0 sono registrate.

## Checklist tecnica

- [ ] **RFI-MUST-030** Versione UE5, SDK/toolchain, piattaforme, camera e input baseline sono approvati.
- [ ] **RFI-MUST-031** Moduli/plugin, fallback e dependency graph hanno ADR; nessun plugin non approvato.
- [ ] **RFI-MUST-032** Formato fisico schema/store, ID, indici, partizionamento e migrazione sono decisi.
- [ ] **RFI-MUST-033** Formato save, checksum, compressione, slot, support window, recovery e migrazione sono decisi.
- [ ] **RFI-MUST-034** Hardware target e budget CPU/GPU/RAM/VRAM/I/O/NPC/load-save sono approvati.
- [ ] **RFI-MUST-035** Benchmark scene e workload con criteri pass/fail sono specificati prima del codice di produzione.
- [ ] **RFI-MUST-036** Sicurezza, secrets, logging, privacy e telemetria locale hanno policy approvata.
- [ ] **RFI-MUST-037** Accessibilità e matrice input/piattaforma P0 sono requisiti nativi.

## Checklist di strumenti, pipeline e produzione

- [ ] **RFI-MUST-040** Owner/reviewer e capacità minima del team sono assegnati per EP-01, EP-02 e EP-11.
- [ ] **RFI-MUST-041** Branch `main`/base protetto e branch separato di implementazione sono configurati; il branch documentale resta privo di codice.
- [ ] **RFI-MUST-042** Git LFS/pattern/quote/locking, ignore policy e artifact storage sono provati oppure formalmente non necessari al PT.
- [ ] **RFI-MUST-043** Runner CI/build, licenze, cache, retention e secret store sono disponibili.
- [ ] **RFI-MUST-044** Validator documentali/dati/storici minimi e test harness P0 hanno specifica e backlog.
- [ ] **RFI-MUST-045** Backlog PT è stimato, dipendenze ordinate, owner assegnati e capacity-constrained. Evidenza: [backlog](11-production/roadmap-backlog/demo-backlog.md).
- [ ] **RFI-MUST-046** Definition of Ready e Done integrate nella pipeline/review.
- [ ] **RFI-MUST-047** Piano di rollback del repository e degli artifact verificato.

## Checklist di rischio e approvazione

- [ ] **RFI-MUST-050** Tutti i blocker hanno owner, mitigation, trigger e contingency nel [registro rischi](11-production/risk-register.md).
- [ ] **RFI-MUST-051** Q-003–007, Q-101–113, Q-203–205, Q-207, Q-211–220, Q-223–234 e Q-235–252 sono chiuse o esplicitamente non bloccanti per PT con motivazione approvata.
- [ ] **RFI-MUST-052** Audit interdisciplinare non rileva decisioni bloccanti non documentate.
- [ ] **RFI-MUST-053** Technical Direction firma che PT può fallire in sicurezza e non vincola l'intero gioco.
- [ ] **RFI-MUST-054** Production firma scope, budget, team e milestone PT.
- [ ] **RFI-MUST-055** Utente/Project Owner autorizza esplicitamente l'inizio del codice in un prompt successivo.

## Evidenze attuali e blocker

| Area | Stato | Blocco principale |
|---|---|---|
| visione/scope | Documented S3 | approvazioni nominali |
| data/area/edifici | Partial | GIS e snapshot edificio 77 |
| sistemi | Mostly S3 | promozione P0 a S4 e valori |
| storia/etica | Partial | review percorsi e contenuti P0 |
| tecnologia | Partial S3 | UE/platform/plugin/store/save decisions |
| performance | Provisional D | hardware e benchmark |
| tools/pipeline | Designed S3 | infrastruttura, owner e proof |
| produzione | Planned | team, stime e finanziamento |

**Verdetto corrente: NON READY.** La documentazione permette di vedere cosa manca, ma non soddisfa ancora le condizioni per scrivere codice.

## Processo di firma

| Disciplina | Responsabilità | Nome/data | Esito |
|---|---|---|---|
| Game Direction | promessa, scope, tagli | da assegnare | Pending |
| Lead Design | sistemi, percorsi, acceptance | da assegnare | Pending |
| Historical/Sensitivity | snapshot e rappresentazione | da assegnare | Pending |
| Technical Direction | architettura, budget, rischio | da assegnare | Pending |
| Production | team, backlog, milestone | da assegnare | Pending |
| QA/Accessibility | testabilità e accesso | da assegnare | Pending |
| Project Owner | autorizzazione finale | utente | Pending |

## Dipendenze

- [Master Prompt](MASTER_PROMPT.md)
- [Principi di design](DESIGN_PRINCIPLES.md)
- [Architettura tecnica](10-technical/technical-architecture.md)
- [Mandato demo](07-pompeii-demo/design/demo-charter.md)
- [Definition of Ready](11-production/roadmap-backlog/definition-of-ready.md)

## Collegamenti agli altri documenti

- [Milestone](11-production/roadmap-backlog/milestones.md)
- [Definition of Done](11-production/roadmap-backlog/definition-of-done.md)
- [Questioni aperte](00-governance/open-questions.md)
- [Decisioni](00-governance/decision-log.md)

## Decisioni ancora aperte

Le caselle non selezionate e Q indicate in RFI-MUST-051 costituiscono il registro completo dei blocker correnti. Nuovi blocker devono essere aggiunti qui e nel registro prima di proseguire.

## Criteri di completamento

Tutte le caselle Must selezionate con evidenza, firme complete, audit pulito e nuova autorizzazione esplicita dell'utente.

## TODO

- Assegnare owner e raccogliere evidenze.
- Riesaminare a ogni chiusura di decisione fondazionale.
- Non modificare lo stato in READY tramite sola decisione automatica dell'assistente.
