# Mappa Game Bible → sistemi UE5

## Scopo

Mappare ogni sistema di gameplay a dati, autorità runtime, tecnologia UE candidata, livello di simulazione, presentazione e persistenza.

## Descrizione

La mappa impedisce che la tecnologia diventi il dominio. Actor, Component, StateTree, Mass e widget sono adapter/rappresentazioni; i record persistenti e le regole restano autoritativi nei moduli.

## Ambito

Mondo, NPC, economia, istituzioni, interazione, inventario, quest, dialogo, AI, tempo/eventi, combattimento, save, localizzazione, audio e UI.

## Matrice di implementazione

| Sistema | Autorità/dati | UE5 candidato | Simulazione lontana | Presentazione/caricamento |
|---|---|---|---|---|
| Identità/world state | record C++ versionati | subsystem + repositories | sempre persistente | proxy Actor/Mass on demand |
| Tempo/calendario | world clock + scheduler | `UWorldSubsystem` | interval-driven | UI/audio subscribers |
| Eventi | journal/event bus tipizzato | C++ service/subsystem | code/milestone | projection on demand |
| Mondo/edifici | place/building records | World Partition bridge, Data Layers | semplificata/intervalli | celle/HLOD/load on demand |
| NPC/persona | person record, needs, commitments | C++ domain + StateTree/Mass adapters | N2–N5 interval/statistical | Actor high LOD, Mass lower LOD |
| Routine/AI | goals/commitments/knowledge | StateTree candidate; BT tactical | interval/reconstruction | wake by signals/proximity |
| Crowd/nav | flow/agent projections | MassGameplay/Nav/avoidance candidate | density/flows | ISM/low actor/no representation |
| Economia | ledger, market, enterprise | pure C++ domains/subsystems | E2–E5 interval/statistical | UI/views on demand |
| Inventario/proprietà | containers/lots/rights | C++ + Actor components as adapter | persistent records | component only loaded objects |
| Interazione | affordance/intent/command | Actor components/interfaces + subsystem | frozen without actor | prompts/view model on demand |
| Quest/situazioni | bindings, leads, commitments | content subsystem + Data Assets | event-driven | journal/UI on demand |
| Dialogo | conversation state/knowledge | dialogue subsystem + assets | frozen/summary | localized UI/voice on demand |
| Politica/religione/diritto | domain records/processes | C++ domain services | intervals/events | content/UI/audio projections |
| Combattimento | engagement/trauma | Actor components + C++ resolver | M1/M2 aggregate | animation/audio/camera |
| Guerra | formations/campaigns | simulation domain | M3–M5 interval/statistical | loaded only relevant scenes |
| Save | snapshot/journal/migration | GameInstance service + SaveGame adapter | n/a | async UI feedback |
| Localizzazione | text keys/culture/variant | UE Localization Dashboard/String Tables candidate | n/a | loaded packages on demand |
| Audio | semantic emitters/mix state | Audio components/MetaSounds candidate | aggregate soundscape | virtualized/on demand |
| UI | epistemic view models/preferences | UMG/CommonUI candidate + MVVM evaluation | n/a | local-player lifetime |
| Animazione | movement/action state | Anim BP/Control Rig/Motion Warping candidates | representation-free | high LOD only |

## Politica dei livelli

| Categoria | Definizione | Esempi |
|---|---|---|
| completamente simulata | invarianti individuali e aggiornamenti puntuali | player, NPC P0, combattimento vicino, contratti attivi |
| semplificata | stessi saldi, meno dettagli | NPC città, imprese E1/E2, unità M2 |
| intervalli | milestone/scadenze anziché tick | bisogni lontani, mercati, eventi, campagne |
| congelata | stato fermo perché irrilevante e senza scadenze | dialogo non avviato, presentation proxy |
| ricostruita statisticamente | distribuzioni con invarianti e seed/journal | popolazione N4/N5, guerra M5, corridoi E5 |
| caricata su richiesta | definizioni/asset/presentation | voice, UI, map cells, HLOD/Actor proxy |

Il congelamento non sospende orologi o obblighi: un record con scadenza viene aggiornato a intervalli. Ricostruzione non può cancellare ID P0, debiti, proprietà, morti, casi o memoria critica.

## State machine, StateTree e Behavior Tree

- State machine C++ per lifecycle/invarianti deterministici (contratto, ferita, save, evento).
- StateTree per selezione gerarchica di attività e transizioni data-driven, inclusa integrazione Mass se validata.
- Behavior Tree per tattiche Actor-centric con Blackboard locale; nessun fatto non conosciuto.
- Nessuno dei tre possiede il record persona o scrive domini senza comandi.

## Componenti e subsystem

Componenti solo per capability di Actor caricati (`Interactable`, `InventoryProxy`, `CombatantPresentation`, `AudioEmitter`); non come database persistente. Subsystem per servizi con lifetime naturale e API bounded; evitare “God Subsystem”. World teardown, PIE multiplo e load/save definiscono lifecycle.

## Dati e configurazione

Data Asset per definizioni ricche/riferimenti soft; Primary Data Asset per bundle/load; Data Table/Registry per righe omogenee read-only; Gameplay Tags per tassonomie governate; config per comportamento ambiente/build. Stato partita mai in Data Asset/Table/Tag.

## Eventi, errori e test

Event bus separa domain event affidabile da presentation signal best-effort. Eventi versionati con entity ID, correlation/causation, world time e payload. Test per ogni mapping: headless domain, adapter UE, LOD reconciliation, load/unload, save, knowledge leak e benchmark.

## Dipendenze

- [Architettura tecnica](../technical-architecture.md)
- [Moduli](modules.md)
- [Data Asset e Table](data-assets-tables.md)
- [StateTree/BT](state-tree-behavior-tree.md)
- [Mass](mass-entity.md)

## Collegamenti agli altri documenti

- [World Partition](world-partition.md)
- [Navigazione](navigation-crowds.md)
- [Save](../save-system/save-architecture.md)
- [Performance](../performance/performance-strategy.md)

## Test e Definition of Done

Ogni riga ha owner, dati, tecnologia, livello, adapter, persistenza, failure e test; nessun sistema P0 dipende esclusivamente da feature sperimentale; reconciliation e streaming non cambiano stato canonico.

## Decisioni ancora aperte

- Risultati spike Mass/StateTree/CommonUI/MVVM/MetaSounds.
- Intervalli e budget quantitativi per N/E/M e streaming.

## TODO

- Collegare API/event contract puntuali per sistema.
- Convertire la matrice in checklist di readiness, senza implementazione.
