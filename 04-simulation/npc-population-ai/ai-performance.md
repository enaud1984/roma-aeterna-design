# Budget, degradazione e osservabilità AI

## Scopo

Stabilire come misurare e limitare costo di percezione, decisione, routine, memoria, relazioni e folle.

## Descrizione

Il sistema degrada frequenza e dettaglio attraverso N0–N5 preservando eventi hard e invarianti. I budget assoluti attendono piattaforme e popolazione.

## Ambito

CPU, memoria, scheduler, query spaziali, backlog, save e strumenti di debug della simulazione sociale.

## Budget relativi

| Area | Metrica | Degradazione ammessa | Mai degradare |
|---|---|---|---|
| percezione | stimoli/query per intervallo | frequenza/raggio/dettaglio | evento critico già esposto |
| decisione | deliberazioni/candidati | backoff e candidate cap | deadline hard |
| routine | appuntamenti processati | batching | presenza impossibile/duplicata |
| memoria | record/byte | sintesi e top-K | debiti, crimini, identità |
| relazioni | edge attivi | aggregare conoscenze deboli | parentela/obbligo attivo |
| folle | agenti/path query | gruppi/flussi | capacità e morti/ferite |

## SLO progettuali

- backlog critico sempre sotto una finestra configurata;
- nessun frame spike da promozione massiva;
- transizioni rate-limited e prioritarie;
- salvataggio proporzionale a individui persistenti, non ai frame simulati;
- inspector identifica top consumer, agenti bloccati e tempeste evento.

## Strategie

Event-driven scheduling, time wheel, batching, spatial index, cache versionate, coalescenza autorizzata, sampling di telemetria, job prioritari e load shedding solo per eventi soft.

## Stress profiles

Small: giornata ordinaria. Recommended: mercato + terme + consegne. Crowd: gioco pubblico. Crisis: incendio con folla. Longitudinal: 30 giorni. Generational: anni aggregati. Recovery: load durante crisi.

## Test

Profiling per livello, percentile non sola media, soak, spike, promotion storm, memory leak, save size, event backlog, determinismo e qualità degradata comparata.

## Dipendenze

- [Livelli](simulation-levels.md)
- [Performance globale](../../10-technical/performance-budgets.md)
- [Folle](crowds.md)

## Collegamenti agli altri documenti

- [AI](ai-architecture.md)
- [Popolazione demo](../../07-pompeii-demo/demo-population.md)
- [Debug](../../10-technical/tools-and-observability.md)

## Criteri di accettazione

Metriche, degradazione e profili definiti; eventi hard mai persi; qualità cross-level entro tolleranza; nessun backlog senza telemetria.

## Definition of Done

Q-003/Q-102 chiuse, budget numerici approvati, benchmark e alert progettati.

## Decisioni ancora aperte

- Target numerici e hardware.

## TODO

- Compilare budget dopo benchmark vertical slice.
