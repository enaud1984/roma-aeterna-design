# Budget prestazionali e di scala

**ID:** TEC-PERF-001
**Stato:** Draft

## Principio

Nessun numero di NPC o dimensione geografica viene promesso prima di target hardware e misure. I budget sono contratti tra design, simulazione, rendering, audio, memoria, streaming e salvataggio.

## Budget da stabilire

Frame time CPU/GPU; memoria residente e streaming; agenti L0–L4; pathfinding; eventi per ciclo; latenza UI; salvataggio/caricamento; dimensione save; audio voices; storage; tempo di build e validazione contenuti.

## Scenari benchmark

Folla massima nel foro; quartiere notturno; festa con mercato; shock economico e molte decisioni; transizione rapida tra zone; 180 giorni accelerati; salvataggio durante alto volume di eventi; raffinamento di coorte in NPC persistenti.

## Politica di degradazione

Ridurre frequenza e dettaglio lontano, non correttezza essenziale. Non cancellare agenti persistenti, duplicare inventari, arrestare deadline o alterare esiti già osservati. Ogni degradazione ha una metrica di errore accettabile.

## Gate

I numeri entrano in [scope Pompei](../07-pompeii-demo/pompeii-vertical-slice.md) solo dopo benchmark rappresentativi e margine concordato. Piattaforme restano Q-003 nel [registro](../00-governance/open-questions.md).

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
