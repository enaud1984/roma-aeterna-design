# Promessa al giocatore

**ID:** VIS-GDB-002
**Stato:** Approved — Baseline 1.0
**Owner:** Game Director

## Scopo

Convertire la visione in promesse osservabili, limiti espliciti e prove necessarie nella vertical slice.

## Descrizione

Dieci promesse formano il contratto esperienziale interno del prodotto e il limite dei claim esterni.

## Ambito

Le promesse valgono per il prodotto; Pompei deve dimostrarle con un perimetro ridotto ma rappresentativo.

## Promesse

| ID | Promessa | Limite | Prova minima |
|---|---|---|---|
| PP-01 | Puoi costruire vite diverse | possibilità storicamente situate, non accesso universale | tre origini con loop distinti |
| PP-02 | Il mondo continua senza di te | dettaglio variabile, continuità invariata | assenza di 30 giorni con recap |
| PP-03 | Gli NPC hanno vite proprie | fedeltà proporzionata alla rilevanza | routine, relazioni e adattamento |
| PP-04 | Le conseguenze hanno cause | non tutte le cause sono subito note | catena interrogabile e feedback locale |
| PP-05 | Il lavoro produce valore reale | nessun mestiere è minigioco isolato | input, output, cliente, paga, rischio |
| PP-06 | Status e relazioni contano | i vincoli possono essere duri | stesso obiettivo, accessi differenti |
| PP-07 | La storia è trattata onestamente | l'incertezza non scompare | provenance e classi di certezza |
| PP-08 | La violenza non è obbligatoria | non ogni conflitto ha esito perfetto | percorsi sociali/economici plausibili |
| PP-09 | Il mondo è comprensibile | non offre onniscienza | fatto, voce e inferenza distinti |
| PP-10 | Il fallimento cambia la vita | alcune perdite possono essere irreversibili | recovery e nuovi stati |

## Visione del sistema

~~~mermaid
flowchart TD
    PR["Promessa"] --> R["Requisiti di dominio"]
    R --> DS["Dimostrazione in Pompei"]
    DS --> Q["Test qualitativo e sistemico"]
    Q -->|fallisce| C["Correzione o riduzione promessa"]
    Q -->|passa| B["Baseline approvata"]
~~~

## Gameplay

Le promesse si manifestano attraverso scelte con costi di opportunità, feedback stratificato, conseguenze persistenti e alternative dipendenti dal contesto. Nessuna promessa richiede una quest principale obbligatoria.

## Regole

- Una promessa non può essere introdotta solo dal marketing.
- Una demo può dimostrare una promessa con perimetro ridotto, ma non falsificarla.
- Il comportamento del player e degli NPC usa gli stessi principi, con differenze dovute a conoscenza e controllo.
- Una promessa non verificabile viene riscritta o rimossa.

## Flussi alternativi

Se una promessa è tecnicamente troppo costosa: preservare l'esito percepito tramite aggregazione, ridurre lo scope o declassificarla. Non sostituirla con un'illusione non dichiarata.

## Dati ed eventi necessari

Promessa ID; requisiti collegati; scenari; metriche; issue; risultato playtest. Eventi di prova: cambi status, transazioni, adattamento NPC, assenza/ritorno, diffusione informazione, fallimento/recovery.

## Esempio

Il player non compra pane perché il prezzo è salito. La UI non mostra “evento economico +20%”: apprende la scarsità dal prezzo, dalle scorte, da conversazioni e dal comportamento di clienti e panettieri.

## Casi limite

Una conseguenza realistica ma incomprensibile viola PP-09. Una carriera formalmente disponibile ma impraticabile per tutte le origini non soddisfa PP-01. Un NPC con schedule completo ma nessun adattamento non soddisfa PP-03.

## Dipendenze

- [Visione](../creative-vision.md)
- [Obiettivi esperienza](experience-goals.md)
- [Tracciabilità](../../00-governance/traceability-matrix.md)

## Collegamenti agli altri documenti

- [Pompei](../../07-pompeii-demo/pompeii-vertical-slice.md)
- [Testing](../../11-production/testing/README.md)
- [UX](../../08-ux/ux-principles.md)

## Decisioni ancora aperte

Soglie quantitative dei test; durata della prova di autonomia; formulazione pubblica finale.

## Rischi

Overpromising; prove troppo sceneggiate; metriche che ignorano comprensione; conflitto tra accuratezza e accessibilità.

## Possibili estensioni future

Promesse specifiche per viaggio interregionale e successione potranno essere aggiunte solo dopo validazione.

## Criteri di completamento

Ogni promessa ha limite, prova, owner e requisiti collegati; nessun claim esterno eccede il documento.

## TODO

- Collegare le promesse ai requisiti di ciascuna macroarea.
- Definire protocolli di playtest per PP-01–PP-10.
