# Strategia e budget prestazionali iniziali

## Scopo

Definire target provvisori, ownership, misurazione, margini e degradazione per la vertical slice di Pompei.

## Descrizione

Baseline di lavoro: PC 60 fps, frame 16,67 ms, preset target ancora da fissare. I budget sono massimi di sottosistema nel worst-case rappresentativo, non obiettivi da saturare. Ogni numero è D tecnico e sarà ricalibrato dopo hardware matrix/benchmark.

## Ambito

CPU, GPU, RAM/VRAM, disco/install, streaming, NPC/folle, animazione, pathfinding, traffico, save/load e startup/travel.

## Budget frame iniziale

| Area | Target | Hard gate provvisorio | Note |
|---|---:|---:|---|
| frame totale | 16,67 ms | p99 ≤ 20 ms in scena target | 60 fps; hitch separato |
| game thread | 5,5 ms | 7 ms | gameplay, Actor, orchestration |
| simulation workers | 3,0 ms avg | 5 ms burst budgetizzato | async/batch, no starvation |
| render thread/RHI CPU | 4,5 ms | 6 ms | overlap possibile, misurare |
| GPU | 13,5 ms | 16 ms | ≥15% headroom nominale |
| audio thread | 1,0 ms | 2 ms burst | voce/folla/eventi |
| UI | 0,8 ms CPU + 0,8 ms GPU | 1,5 ms ciascuno | menu grandi virtualizzati |

I budget non si sommano ingenuamente per thread paralleli; il frame gate e traces sono autorità.

## Memoria e disco

| Risorsa | Target iniziale | Gate |
|---|---:|---|
| RAM processo | ≤ 10 GiB steady | ≤ 12 GiB peak transitorio |
| VRAM | ≤ 6,5 GiB target preset | ≤ 7,2 GiB peak su 8 GiB class, da validare |
| resident simulation data | ≤ 1,5 GiB | include record/index/cache |
| resident NPC/crowd | ≤ 1,0 GiB | tutte projection e AI loaded |
| install demo | ≤ 30 GiB | cooked, senza debug/source art |
| patch interna ordinaria | ≤ 5 GiB target | dipende da packaging/chunking |
| save slot worst-case | ≤ 256 MiB | target P0 molto inferiore; backup esclusi |
| telemetria/log locale | ≤ 2 GiB rotante | default inferiore, export esplicito |

## Streaming e caricamento

| Metrica | Target |
|---|---:|
| traversal PVS-1 | nessun hitch >50 ms; p99 frame gate |
| cell activation main-thread | ≤2 ms/frame budgetizzata |
| I/O sustained design point | 250 MB/s baseline provvisoria |
| cold boot menu | ≤15 s su target |
| nuova/loaded demo cold | ≤30 s |
| warm load | ≤15 s |
| interno/esterno | senza loading screen quando previsto; preload bounded |
| manual save feedback | ≤3 s target, max 10 s con progress |
| autosave main-thread hitch | ≤8 ms extra singolo frame; preferenza invisibile |

## NPC, animazione, navigazione e folla

| Categoria | Budget iniziale scena stress |
|---|---:|
| NPC N0 ad alta fedeltà | 40 |
| NPC Actor N1 visibili | 120 addizionali |
| Mass/low representation N1–N2 | 800 candidati |
| popolazione individuale città N3 | 10.000 record attivi a intervalli |
| popolazione N4/N5 | 50.000+ statistiche/coorti, non per-frame |
| skeletal meshes full animation | 80 |
| reduced animation/visibility | 200 |
| path requests dettagliate | 32/frame avg, 64 burst |
| avoidance neighbors | max 16 per agente candidato |
| veicoli/animali/traffico N0/N1 | 60 simultanei candidati |
| folla evento grande demo | 500 visibili/proiettati, di cui N0/N1 bounded |

Sono envelope di benchmark, non promesse di contenuto. Ogni NPC P0 può consumare più budget, riducendo count.

## Frequenze simulazione

N0/combat frame/event; N1 5–10 Hz candidate; N2 1 Hz/event; N3 minuti simulati; N4/N5 ore/giorni o eventi. Economia E0 transazionale, E1 secondi/minuti, E2 ore, E3+ giorni/eventi. Militare M0 frame/event, M1 secondi, M2 ore, M3+ giorni. Scheduler ha max work/time slice e back-pressure.

## Scalabilità e degradazione

Ordine: ridurre distanza/densità projection → animation update/LOD → audio voices → crowd detail/avoidance → HLOD/visual quality. Non degradare causalità, ID, save, conoscenza, contratti o accessibilità. Quality profiles separano visuale e simulazione; riduzione simulazione conserva invarianti e tempi.

## Benchmark scenes

PVS traversal; Foro/mercato peak; Via dell'Abbondanza; terme interno/esterno; anfiteatro/folla; incendio/panico; combattimento gruppo; save/load worst-case; time-skip 30/90 giorni; Mass promotion storm; editor/PIE non è misura shipping.

## Misurazione e gate

Build Development/Test/Shipping-like controllate, hardware fixed, warm/cold separati, mediana/p95/p99, captures versionate. Regressione >5% su metrica owner o superamento budget blocca merge salvo waiver ADR. CI smoke; nightly benchmark; milestone soak.

## Dipendenze

- [CPU](cpu-budget.md)
- [GPU](gpu-budget.md)
- [Memoria](memory-budget.md)
- [Streaming](streaming-budget.md)
- [NPC/crowd](npc-crowd-budget.md)
- [Save/load](save-load-budget.md)

## Collegamenti agli altri documenti

- [Benchmark scenes](benchmark-scenes.md)
- [Scalabilità](scalability.md)
- [World Partition](../unreal-engine-5/world-partition.md)
- [Mass](../unreal-engine-5/mass-entity.md)

## Test e Definition of Done

Ogni budget ha hardware/build/scene/percentile/owner; captures riproducibili e trend. S4 dopo Q-229 e benchmark reali; fino ad allora i numeri sono target D iniziali.

## Decisioni ancora aperte

- Hardware/preset/risoluzione e supporto 30 fps.
- Count finali dopo contenuto P0 e spike Mass/nav/animation.

## TODO

- Chiudere Q-243–Q-247 e aggiornare sottodocumenti.
- Definire performance waiver e dashboard.
