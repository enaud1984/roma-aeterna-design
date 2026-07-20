# Audit combattimento e sistemi militari — 2026-07-20

## Scopo

Registrare copertura, coerenza, rischi e lacune di combattimento, trauma, esercito, criminalità connessa e trionfi.

## Descrizione

L'audit promuove le autorità canoniche a S3: risoluzione fisica, lesioni persistenti, gruppi/folle, contesti di violenza, istituzione militare, livelli M0–M5 e grandi cerimonie.

## Ambito

Documenti `military-combat`, dipendenze con salute, crimine, economia, politica, religione, audio e UX. Non certifica ancora numeri, asset, controlli o performance runtime.

## Risultati

| Area | Esito | Bloccante S4 |
|---|---|---|
| Combattimento | S3 | controllo/camera, arsenale P0, test leggibilità |
| Ferite | S3 | granularità, valori e policy morte |
| Gruppi/arena | S3 | budget, luoghi e profilo storico |
| Esercito | S3 | dossier data-provincia e carriera P0/P1 |
| Livelli M0–M5 | S3 | benchmark e tolleranze |
| Criminalità | S3 collegata | illeciti/procedure P0 |
| Trionfi | S3 | decisione scope remoto e dossier Roma |

## Correzioni applicate

Rimossi hit point autoritativi, invulnerabilità player e morale unico; introdotti telegraph, trauma causale, resa/cattura, folla individuale, logistica conservativa, carriera fallibile e gate di rarità. Prigionieri restano persone persistenti.

## Verifiche e rischi

R-050–R-056 governano leggibilità, costo, anacronismo, frequenza e rappresentazione. Gate: link, README, sezioni minime, `git diff --check`, Q-217–Q-222 e scenari interdisciplinari.

## Dipendenze

- [Combattimento](../../04-simulation/military-combat/combat-vision.md)
- [Ferite](../../04-simulation/military-combat/injuries.md)
- [Esercito](../../04-simulation/military-combat/army.md)
- [Trionfi](../../04-simulation/military-combat/triumphs.md)

## Collegamenti agli altri documenti

- [Readiness](../roadmap-backlog/implementation-readiness-matrix.md)
- [Rischi](../risk-register.md)
- [Questioni aperte](../../00-governance/open-questions.md)

## Decisioni ancora aperte

- Q-217–Q-222.
- Owner/reviewer nominali Combat, Military History, Health e Safety.

## TODO

- Ripetere audit dopo profili storici e budget P0.
- Allineare tutti i moduli specialistici ancora S0–S2.
