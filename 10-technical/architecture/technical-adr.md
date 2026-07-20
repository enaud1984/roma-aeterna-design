# ADR Tecnici

## Scopo

Definire la futura specifica canonica di **ADR Tecnici**.

## Descrizione

Definisce processo, formato, ownership e segnali di revisione.

## Ambito

Coprirà requisiti, responsabilità, dati, flussi, vincoli, rischi e validazione. Non contiene codice, asset o decisioni tecniche non approvate.

## Dipendenze

- [Indice del dominio](README.md)
- [Architettura tecnica](../technical-architecture.md)
- [Standard documentale](../../00-governance/documentation-standard.md)

## Collegamenti agli altri documenti

- [Indice generale](../../README.md)
- [Mappa documentale](../../00-governance/documentation-map.md)
- [Registro decisioni](../../00-governance/decision-log.md)
- [Questioni aperte](../../00-governance/open-questions.md)

## Decisioni ancora aperte

- Owner, reviewer, priorità e tecnologia definitiva.
- Requisiti minimi della vertical slice e target di piattaforma.

## TODO

- Definire requisiti, contratti, failure mode e criteri di completamento.
- Mappare dipendenze e budget.
- Collegare ADR, test e rischi.

## ADR-T-0001 — Un Character, due visuali, Enhanced Input event-driven

**Stato:** Accepted for technical prototype — 2026-07-20

**Contesto.** La prima esperienza controllabile deve verificare locomozione e camera senza anticipare parkour, combattimento, animazione o UI di produzione.

**Decisione.** `ARACharacter` è l'unica autorità del pawn giocante. Possiede due `UCameraComponent` e uno stato `ERAViewMode`; `F9` cambia lo stato in modo event-driven. La terza persona usa SpringArm con collision probe, la prima persona condivide capsule e movimento. Enhanced Input è obbligatorio e il Character non introduce Tick personalizzati.

**Alternative escluse.** Due Pawn distinti avrebbero duplicato stato e possesso; polling per frame avrebbe introdotto lavoro e transizioni non necessarie; asset esterni o un framework di animazione definitivo avrebbero ampliato la milestone.

**Conseguenze.** Movimento, velocità e posizione restano continui tra le visuali. Gli Input Action subobject e il Canvas HUD sono debito esplicito, registrato nel [registro del debito tecnico](technical-debt-register.md). La decisione può essere riaperta quando parkour, animazione o accessibilità richiederanno un diverso camera rig, mantenendo il contratto di un solo stato gameplay.

**Evidenza.** [Specifiche Character](../../docs/technical/PLAYER_CHARACTER.md), [camera](../../docs/technical/CAMERA_SYSTEM.md), [input](../../docs/technical/ENHANCED_INPUT.md) e [build report](../../docs/audits/PLAYABLE_FOUNDATION_BUILD_REPORT.md).
