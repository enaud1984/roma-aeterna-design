# Matrice di tracciabilità

Questa matrice collega promessa, sistema, dimostrazione nella demo e verifica. Sarà estesa fino a collegare ogni requisito a test, telemetria e milestone.

| Promessa | Specifica canonica | Prova in Pompei | Verifica iniziale |
|---|---|---|---|
| Persona comune, molte vite possibili | [Esperienza](../05-player/player-experience.md) | almeno tre origini sociali e quattro loop economici | percorsi senza missione principale obbligatoria |
| NPC con vita completa | [Ciclo di vita NPC](../04-simulation/npc-life-simulation.md) | famiglie, case, lavoro, bisogni e memoria | osservazione accelerata per 30 giorni simulati |
| Economia simulata | [Economia](../04-simulation/economy.md) | grano→mulino→pane→consumo | shock di offerta produce effetti spiegabili |
| Politica simulata | [Politica](../04-simulation/politics-and-governance.md) | magistrature e influenza locale | esito cambia con coalizioni senza player |
| Religione simulata | [Religione](../04-simulation/religion.md) | culti domestici e pubblici | calendario, risorse e reputazione interagiscono |
| Guerre simulate | [Guerra](../04-simulation/war-and-military.md) | impatto remoto su prezzi/notizie/veterani | conflitto fuori mappa influenza la città |
| Trionfi simulati | [Trionfi](../04-simulation/triumphs.md) | notizia/preparativi/effetti politici | requisiti e conseguenze non dipendono dal player |
| Città viva | [Modello urbano](../03-world/living-city.md) | ritmi giornalieri, logistica, manutenzione | time-lapse senza collasso o immobilità |
| Mondo autonomo | [Architettura simulazione](../04-simulation/simulation-architecture.md) | assenza/ritorno del player | causalità persistente e riassunto comprensibile |
| Accuratezza storica | [Framework storico](../02-historical-foundation/historical-framework.md) | provenance ledger per elementi chiave | audit H1–H4 e revisione esperta |

## Regola di copertura

Una promessa è “coperta” solo se esistono: documento canonico, responsabile, scenario dimostrabile, fallimento definito e metodo di verifica. Il semplice elenco di una feature non costituisce copertura.

## Scopo

Conservare e sviluppare la responsabilità canonica descritta da questo documento all'interno della Game Bible.

## Descrizione

Il contenuto preesistente costituisce la baseline del dominio. Questa sezione normalizza il documento secondo il contratto minimo della nuova architettura senza sostituirne le informazioni.

## Ambito

Il perimetro è quello definito nelle sezioni precedenti; implementazione e asset restano esclusi finché non saranno autorizzati da milestone e decisioni formali.

## Dipendenze

- [Standard documentale](../00-governance/documentation-standard.md)
- [Visione creativa](../01-vision/creative-vision.md)

## Collegamenti agli altri documenti

- [Indice generale](../README.md)
- [Mappa documentale](../00-governance/documentation-map.md)
- [Registro decisioni](../00-governance/decision-log.md)
- [Questioni aperte](../00-governance/open-questions.md)

## Decisioni ancora aperte

- Owner e reviewer nominali.
- Stato di approvazione e profondità richiesta dalla roadmap documentale.
- Eventuali confini da riallineare con i nuovi sottodomini canonici.

## TODO

- Collegare il contenuto ai nuovi documenti specializzati pertinenti.
- Assegnare ownership, versione e milestone.
- Aggiungere requisiti, fonti, rischi, test e Definition of Done durante l'approfondimento.
