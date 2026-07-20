# Livelli di simulazione militare M0–M5

## Scopo

Scalare da individui visibili a guerre remote preservando persone, risorse, causalità e conseguenze.

## Descrizione

Il livello definisce risoluzione e frequenza, non importanza narrativa. Promozione e degradazione usano snapshot e riconciliazione conservativa.

## Ambito

Combattenti, squadre, unità, armate/campi, campagne e teatri di guerra; trasferimenti, aggiornamenti, budget, eventi e persistenza.

## Livelli

| Livello | Rappresentazione | Aggiornamento | Invarianti |
|---|---|---|---|
| M0 | individui e contatti visibili | frame/evento | ferite, equipaggiamento, posizione, intenzioni |
| M1 | gruppo tattico vicino/non visibile | secondi/eventi | membri, coesione, ordini, munizioni/scorte P0 |
| M2 | centuria/coorte o equivalente | minuti/ore | forza effettiva, ufficiali, morale, perdite, scorte |
| M3 | formazione/campo/armata | ore/giorni | composizione, comando, rotta, logistica, obiettivo |
| M4 | campagna/provincia | giorni/settimane | forze, controllo, flussi, assedi, esiti e prigionieri |
| M5 | guerra/teatro imperiale | settimane/eventi | belligeranti, mobilitazione, costo, corridoi e memoria |

## Promozione e degradazione

```mermaid
flowchart LR
    A[Snapshot livello sorgente] --> B[Conservazione: persone/scorte/perdite]
    B --> C[Trasformazione autorizzata]
    C --> D[Snapshot livello destinazione]
    D --> E[Reconciliation e causal trace]
    E --> F{Valido?}
    F -- sì --> G[Commit]
    F -- no --> H[Rollback/quarantena]
```

Persone del player, ufficiali rilevanti, prigionieri, feriti, contratti/paga e controversie non sono eliminati. Perdite aggregate generano identità/tombstone mediante regole approvate prima di una promozione a dettaglio.

## Risoluzione aggregata

Usa obiettivo, forza/capacità, addestramento, coesione, comando, terreno, informazione, fatica, scorte, fortificazioni, meteo e casualità con seed registrato. Produce intervalli ed eventi causali, non un singolo “power score”. Il player influisce solo attraverso azioni/risorse proporzionate.

## Performance e persistenza

Budget per numero di entità M0/M1, frequenza M2–M5, code eventi e tempo di riconciliazione. Scheduler adattivo con priorità a prossimità, rilevanza e scadenze. Snapshot persistono composizione, ID rilevanti, saldi, ordini, posizione, stato, seed e journal.

## Casi limite e test

Promozione durante battaglia, unità divisa/fusa, comandante morto, perdite eccedenti forza, scorte negative, campagna senza rotta, save durante reconciliation e due città che caricano lo stesso evento devono fallire in modo sicuro. Golden tests confrontano M0↔M2 e M2↔M4 entro tolleranze per perdite/scorte/tempo, mai per identità P0.

## Dipendenze

- [Esercito](army.md)
- [Combattimento](combat-vision.md)
- [Simulazione](../simulation-architecture.md)
- [NPC levels](../npc-population-ai/simulation-levels.md)

## Collegamenti agli altri documenti

- [Guerre](wars.md)
- [Battaglie](battles.md)
- [Logistica](military-logistics.md)
- [Persistenza](../../10-technical/save-system/README.md)

## Definition of Done

Schemi M0–M5, invarianti, trasformazioni, budget e failure policy approvati; scenari di marcia, battaglia, assedio, resa e save/load riconciliati; causal trace disponibile in specifica tecnica.

## Decisioni ancora aperte

- Budget numerici, intervalli e tolleranze.
- Livello massimo attivo nella demo di Pompei.

## TODO

- Definire benchmark documentali e dataset sintetici.
- Collegare ownership dati/eventi alla matrice tecnica.
