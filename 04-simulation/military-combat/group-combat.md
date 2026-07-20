# Combattimento di gruppo, coesione e folla

## Scopo

Definire scontri con più partecipanti senza duelli paralleli artificiali, caos illeggibile o NPC suicidi.

## Descrizione

Gruppi condividono obiettivo, percezione imperfetta, comando, spazio e coesione. Ogni individuo conserva paura, ferite e decisione; formazione e pressione emergono dalle relazioni spaziali.

## Ambito

Risse collettive, scorte, pattuglie, formazione militare, accerchiamento, rotta, resa di gruppo, spettatori, panico e sicurezza degli eventi.

## Dati e regole

`CombatGroup`: membri, leader, obiettivo, regole d'ingaggio, coesione e canali d'ordine. `FormationSlot`: posizione relativa e compatibilità. `ThreatAssignment`: bersaglio, priorità e conoscenza. `CrowdZone`: densità, uscite, pericolo e flusso.

- Nessun bersaglio è assegnato globalmente: percezione e linea d'azione contano.
- Alleati occupano spazio, ostacolano e proteggono; niente compenetrazione.
- Superiorità locale, fianco, retro, formazione e terreno contano più del totale astratto.
- Ordini hanno latenza, raggio, comprensione e possibilità di rifiuto/fallimento.
- Coesione degrada con perdite, isolamento, leader caduto, fatica e panico; può recuperare con spazio e comando.
- Rotta propaga segnali osservati, non un debuff istantaneo universale.

## Flusso

```mermaid
flowchart LR
    A[Obiettivo e schieramento] --> B[Percezione locale]
    B --> C[Ordini/iniziative]
    C --> D[Pressione, contatti e supporto]
    D --> E[Perdite, fatica e coesione]
    E --> F{Tenuta?}
    F -- sì --> B
    F -- no --> G[Disimpegno, rotta, resa o frammentazione]
```

## Folla

Spettatori valutano appartenenza, rischio, uscite e comportamenti vicini. Possono arretrare, creare cerchi, fuggire, cadere, intervenire o chiamare autorità. Sicurezza usa corridoi, capienza e personale; panico non produce traiettorie identiche.

## Bilanciamento, performance e persistenza

Limiti per aggressori simultanei derivano dallo spazio, non da token invisibili; il director può scaglionare intenzioni solo con cause diegetiche. LOD: M0 contatti, M1 gruppi, M2 coesione/forza. Persistono ferite, perdite, rese, catture, ostilità e osservazioni; micro-posizioni remote possono essere ricostruite.

## Dipendenze

- [Combattimento](combat-vision.md)
- [Morale](fatigue-fear-morale.md)
- [Livelli militari](military-simulation-levels.md)
- [Folle](../npc-population-ai/crowds.md)

## Collegamenti agli altri documenti

- [Risse e arena](duels-brawls-arena.md)
- [Ordine pubblico](../politics-law/public-order.md)
- [Battaglie](battles.md)

## Test e Definition of Done

Testare 2v1, linea stretta, formazione, leader caduto, rotta, resa, spettatori, uscita bloccata, M0↔M2 e save/load. DoD: nessun overlap, knowledge leak o deadlock; causalità leggibile e budget rispettato.

## Decisioni ancora aperte

- Budget P0 di combattenti e spettatori.
- Modello di comando accessibile al player.

## TODO

- Definire scenari benchmark urbani e militari.
- Collegare capienze e uscite dei luoghi demo.
