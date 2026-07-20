# Audit della progettazione del mondo — 2026-07-20

## Scopo

Verificare completezza, coerenza storica e producibilità del modello mondiale e della vertical slice di Pompei.

## Descrizione

L'audit confronta il framework generale con i requisiti CTY-01–25 e con i dossier PVS-1. Distingue decisioni approvate, proposte e claim E.

## Ambito

Regioni, insediamenti W0–W5, geografia G0–G5, portfolio 36 città, Pompei, edifici, flussi, cicli e connessioni regionali. Nessun codice o asset.

## Copertura

| Area | Documento | Stato |
|---|---|---|
| modello regione/insediamento | framework generale | Review |
| matrice città | CTY-01–25 | Review |
| portfolio imperiale | 36 slot | Planning |
| geografia | layer G0–G5 | Review |
| data Pompei | tre opzioni | Open |
| mappa Pompei | PVS-1 | Proposed |
| zone/flussi | Z1–Z8 | Review |
| edifici | tier P0–P5 e candidati | Review |
| cicli/eventi | giornaliero, nundinale, stagionale | Review/Open per calendario |
| hinterland | nodi/edge regionali | Review/Open per paleo-costa |

## Correzioni preventive

- *Regiones* archeologiche non trattate come quartieri antichi attestati.
- Città murata di circa 66 ha distinta dall'area della demo.
- Geometria 1:1 separata da scala demografica e territorio nodale.
- Porto, fiume, cave e miniere non inventati in assenza di dossier.
- Terme Centrali non considerate operative automaticamente nel 79.
- Edifici con nomi moderni non ricevono funzione o proprietà certa per default.
- Settimana moderna e weekend non applicati al ciclo nundinale.
- Costa, idrologia e confini moderni non retrodatati.

## Questioni bloccanti

Q-001/002, Q-101 e Q-106–109: data, eruzione, poligono, porte/ville, edifici P0 e paleo-geografia. SYS-WORLD resta S3, non S4.

## Rischi

R-025–R-029: full-city creep, uniformità imperiale, spina poco densa, paleo-geografia errata, folle/interni oltre budget.

## Strategie di test

GIS overlay per fase; walkthrough Small/Recommended/Extended; heatmap NPC; test accessi P0–P5; 30 giorni simulati; shock infrastrutturale; filiera da villa a mercato; fault test di rotta esterna.

## Criteri di accettazione

CTY-01–25 coperti, link validi, ogni proposta con stato, nessun claim E promosso, dipendenze e rischi registrati.

## Definition of Done

Baseline world design pronta per review; S4 solo dopo ADR PVS-1, GIS, budget, snapshot ed edifici core approvati.

## Dipendenze

- [Framework insediamenti](../../03-world/settlements/settlement-framework.md)
- [Framework geografico](../../03-world/geography/geographic-framework.md)
- [Pompei](../../07-pompeii-demo/design/pompeii-urban-system.md)

## Collegamenti agli altri documenti

- [Matrice città](../../03-world/settlements/imperial-city-matrix.md)
- [Area](../../07-pompeii-demo/design/playable-area.md)
- [Rischi](../risk-register.md)
- [Readiness](../roadmap-backlog/implementation-readiness-matrix.md)

## Decisioni ancora aperte

- Approvazione ADR-0014 e chiusura delle domande bloccanti.

## TODO

- Eseguire audit GIS e budget interdisciplinare.
- Trasformare i candidati P0 in schede edificio complete.
