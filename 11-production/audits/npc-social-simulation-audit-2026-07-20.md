# Audit NPC e simulazione sociale — 2026-07-20

## Scopo

Verificare che persone persistenti e popolazioni numerose possano coesistere senza onniscienza, duplicazioni o costo incontrollato.

## Descrizione

L'audit copre dati, autorità, lifecycle, AI, conoscenza, relazioni, coorti, eventi, persistenza, performance e test. Non certifica budget numerici ancora bloccati.

## Ambito

SYS-PER, SYS-NPC, SYS-KNOW, SYS-REL, bisogni, demografia, folle e risposte sociali; nessun codice.

## Copertura

| Area | Evidenza | Stato |
|---|---|---|
| individuo | schema e ownership completi | S3 |
| livelli | N0–N5, transizioni e invarianti | S3 |
| lifecycle | nascita→morte→successione | S3 |
| bisogni/routine | driver, finestre, fallback | S3 |
| decisione | guardie, score, commitment, errori | S3 |
| conoscenza | osservazioni, credenze, retention | S3 |
| relazioni | multidominio e asimmetriche | S3 |
| comunicazione | canali, voci, provenance | S3 |
| folla/eventi | panico, fuga e matrice eventi | S3 |
| performance | metriche e stress profile | S3, budget aperti |

## Invarianti verificate documentalmente

Un solo ID; nessuna conoscenza da promozione; nessuna duplicazione individuo/coorte; risorse conservate; deadline hard non saltate; morte non cancella storia; erede non eredita memoria; folla non possiede le decisioni individuali.

## Lacune

Q-003, Q-007, Q-102 e Q-110–113; distribuzioni storiche; target hardware; catalogo azioni demo; budget memoria/edge; scala grandi eventi.

## Strategie di test

30 giorni senza player; generazioni accelerate; N0↔N5; crimine non osservato; falsa voce; morte/successione; folla in crisi; promotion storm; save/reload; conservazione massa/beni; leak e soak.

## Criteri di accettazione

Autorità uniche, contratti collegati, eventi e casi limite presenti, link verdi, maturity non sovrastimata e rischi registrati.

## Definition of Done

Baseline S3 pronta per review interdisciplinare; S4 richiede budget, dati demo, cataloghi e test plan quantitativi.

## Dipendenze

- [Modello NPC](../../04-simulation/npc-population-ai/npc-model.md)
- [Livelli](../../04-simulation/npc-population-ai/simulation-levels.md)
- [AI](../../04-simulation/npc-population-ai/ai-architecture.md)

## Collegamenti agli altri documenti

- [Lifecycle](../../04-simulation/npc-population-ai/npc-lifecycle.md)
- [Memoria](../../04-simulation/npc-population-ai/memory.md)
- [Folle](../../04-simulation/npc-population-ai/crowds.md)
- [Readiness](../roadmap-backlog/implementation-readiness-matrix.md)

## Decisioni ancora aperte

- Q-110–113 e owner nominativi.

## TODO

- Dimensionare Pompei e costruire scenari di accettazione quantitativi.
- Far revisionare lifecycle/status da storia e rappresentazione.
