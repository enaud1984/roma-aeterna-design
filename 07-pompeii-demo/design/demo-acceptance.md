# Criteri di accettazione della demo

**ID:** DEM-ACCEPT-001
**Stato:** S3 — criteri definiti, soglie finali soggette a benchmark

## Scopo

Stabilire prove oggettive per dichiarare completa la vertical slice, la demo interna e la demo pubblicabile.

## Descrizione

L'accettazione misura la promessa sistemica, non soltanto assenza di crash o quantità di contenuto. Ogni requisito ha evidenza riproducibile e owner.

## Ambito

Gameplay, storia, simulazione, contenuti, UX/accessibilità, audio, performance, save, stabilità e produzione.

## Gate funzionali

| ID | Criterio | Prova | Soglia |
|---|---|---|---|
| DA-01 | tre percorsi completi e distinti | golden playthrough | 3/3 senza comando debug |
| DA-02 | loop lavoro-economia end-to-end | ledger e replay | zero creazione/perdita ingiustificata |
| DA-03 | mondo autonomo | soak 30 giorni | nessun collasso/invariante violato |
| DA-04 | conoscenza situata | leak test | zero informazione onnisciente P0 |
| DA-05 | conseguenze persistenti | save/load e recap | identiche prima/dopo reload |
| DA-06 | status differenziato | matrice capacità | tutte le azioni P0 rispettano status |
| DA-07 | famiglia/eredità | succession golden | diritti/debiti trasferiti, identità no |
| DA-08 | crimine non onnisciente | casi furto/frode/aggressione | risposta solo da fonte/prova/autorità |
| DA-09 | eventi non invasivi | run 30 giorni | frequenze entro catalogo e aftermath |
| DA-10 | recovery | scenari debito/ferita/arresto | almeno una via valida non-reset |

## Gate storici ed etici

- 100% degli elementi P0 con periodo, area, classe A–E e fonte/licenza.
- Zero anacronismi blocker nel campione critico.
- Nessuna fonte inventata e nessun E presentato come fatto.
- Schiavitù, coercizione, genere, religione e violenza approvati da Historical/Sensitivity.
- I compositi fittizi sono dichiarati D e non usurpano identità reali.

## Gate UX e contenuti

| Area | Criterio iniziale |
|---|---|
| onboarding | almeno 80% dei tester completa il primo obbligo senza aiuto esterno |
| causalità | almeno 80% identifica causa prossima e una risposta per tre eventi P0 |
| indicatori | zero marker che rivelano fatti o luoghi non conosciuti |
| notifiche | nessun messaggio P0 perso; overload entro soglie del test plan |
| accessibilità | tutti i flussi P0 completabili con preset e input target approvati |
| ripetizione | nessuna sequenza bark/audio dominante oltre la soglia catalogata |

Le percentuali D richiedono piano campione e revisione UX Research prima del gate finale.

## Gate tecnici

- frame time, memoria, streaming, NPC, pathfinding e caricamento entro i [budget](../../10-technical/performance/performance-strategy.md) sull'hardware target;
- zero crash blocker, corruzione save, soft-lock o perdita di progresso nei golden scenario;
- save manuale/autosave/recovery/migrazione verificati con fault injection;
- CI riproducibile da clone pulito e artifact riconducibile al commit;
- trace e telemetria locale entro privacy/retention/disco;
- 30 giorni accelerati e 8 ore soak senza divergenze irreparabili.

## Severità e release

| Severità | Esempio | Demo interna | Demo pubblicabile |
|---|---|---|---|
| Blocker | crash, corruzione, violazione etica/storica critica | vietata | vietata |
| Critical | soft-lock, duplicazione, percorso impossibile | waiver eccezionale | vietata |
| Major | conseguenza/UX/audio errati con workaround | soglia concordata | solo entro cap e senza P0 |
| Minor | polish non bloccante | ammesso | cap e triage |

## Definition of Done della demo pubblicabile

Tutti i DA-01–10 e gate disciplinari superati; contenuti P0 chiusi e localizzati; performance/save/accessibilità su matrice target; rischi residui accettati nominativamente; build firmata e riproducibile; documentazione/as-built aggiornata; nessun blocker o critical aperto; rollback provato.

## Dipendenze

- [Mandato](demo-charter.md)
- [Scope sistemi](demo-systems-scope.md)
- [Scope contenuti](demo-content-scope.md)
- [Strategia test](../../11-production/testing/test-strategy.md)

## Collegamenti agli altri documenti

- [Milestone](../../11-production/roadmap-backlog/milestones.md)
- [Definition of Done](../../11-production/roadmap-backlog/definition-of-done.md)
- [READY](../../READY_FOR_IMPLEMENTATION.md)
- [Rischi](../../11-production/risk-register.md)

## Decisioni ancora aperte

- Hardware, piattaforme/input, campione playtest e rating.
- Soglie finali di bug, performance, overload e ripetizione.
- Requisiti di distribuzione/certificazione.

## Criteri di completamento

Ogni criterio ha owner, test case, ambiente, soglia, evidenza e reviewer; tutti sono tracciati nel backlog e nella release readiness.

## TODO

- Assegnare ID ai test case e definire dashboard.
- Sostituire soglie D dopo prototype e user research.
