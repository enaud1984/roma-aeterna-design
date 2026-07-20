# Visione creativa

**ID:** VIS-001
**Stato:** Approved — Baseline 1.0
**Owner:** Game Director
**Dipendenti principali:** tutti i documenti di design e produzione

## Scopo

Definire l'identità creativa di *Roma Aeterna* in termini sufficientemente precisi da orientare decisioni interdisciplinari senza prescrivere soluzioni di dettaglio.

## Descrizione

Documento canonico per high concept, fantasia centrale, tono, differenziatori e relazione tra persona e mondo.

## Ambito

Governa l'intero prodotto e la vertical slice; non specifica valori di bilanciamento, contenuti storici puntuali o soluzioni software.

## Obiettivo

Realizzare un RPG open world sandbox storico in cui il giocatore costruisce una vita possibile nell'Impero Romano come persona comune, dentro un mondo autonomo che non lo considera il proprio centro causale.

## High concept

Il giocatore entra in una società romana simulata attraverso origine, status, household, competenze, bisogni e obblighi concreti. Lavora, commercia, apprende, forma legami, pratica culti, affronta il diritto, partecipa alla politica o alla violenza e tenta di cambiare la propria condizione. NPC, famiglie, attività, istituzioni e flussi continuano a evolvere anche quando il giocatore non li osserva.

## Fantasia centrale

> Vivere una vita romana possibile; comprendere il mondo attraverso le conseguenze; conquistare margini di scelta senza ricevere privilegi da protagonista.

La fantasia è **agency situata**: poter formulare progetti e trasformare condizioni entro vincoli materiali, sociali, giuridici, geografici e temporali. Il gioco non promette uguale accesso a tutto, ma promette che vincoli e opportunità abbiano cause comprensibili e percorsi plausibili di negoziazione o cambiamento.

## Visione del mondo

Il mondo è composto da persone e istituzioni con continuità. Beni, informazioni, autorità e reputazioni hanno una provenienza. La simulazione usa risoluzioni diverse, ma non cancella fatti osservati, proprietà, legami o obblighi significativi.

~~~mermaid
flowchart LR
    O["Origine e status"] --> A["Possibilità percepite"]
    W["Mondo autonomo"] --> A
    A --> C["Scelta situata"]
    C --> X["Azione con costo"]
    X --> E["Conseguenze sistemiche"]
    E --> K["Conoscenza e memoria"]
    K --> A
    E --> W
~~~

## Identità dell'esperienza

| Asse | Roma Aeterna è | Roma Aeterna non è |
|---|---|---|
| Protagonista | una persona situata | un prescelto o sovrano implicito |
| Storia | sistema e contesto vissuto | scenografia intercambiabile |
| Open world | rete densa di cause e attività | superficie riempita di marker |
| Progressione | capacità, accesso, relazioni e status | crescita numerica sovrumana |
| NPC | individui o popolazioni persistenti | distributori statici di quest |
| Economia | produzione, logistica, scambio e consumo | negozi con scorte infinite |
| Religione | pratica, comunità e interpretazione | magia oggettiva o buff machine |
| Violenza | rischiosa e socialmente situata | soluzione universale |
| Narrazione | autoriale ed emergente | sequenza immutabile centrata sul player |
| Accuratezza | trasparente sul grado di certezza | pretesa di ricostruzione assoluta |

## Tono e prospettiva

Il tono è umano, materiale, intimo e stratificato. Monumentalità e quotidianità convivono; splendore, coercizione, devozione, umorismo, ambizione, noia, solidarietà e paura sono rappresentati senza nostalgia acritica né giudizio semplicistico.

La camera e la prospettiva di gioco restano decisioni tecniche aperte, ma la prospettiva narrativa è sempre limitata: il giocatore conosce ciò che il personaggio percepisce, apprende o inferisce.

## Struttura temporale dell'esperienza

- **Minuti:** osservare, conversare, muoversi, usare, negoziare, lavorare, reagire.
- **Giorni:** mantenere bisogni, routine, incarichi, debiti e relazioni.
- **Mesi:** apprendere, accumulare o perdere capitale, cambiare lavoro, sostenere reti.
- **Anni:** modificare status, household, proprietà, carriera e influenza.
- **Generazioni:** direzione coerente con la visione, ma promessa subordinata a decisione e validazione tecnica.

## Differenziatori

1. Simulazione sociale vincolata da istituzioni storiche, non sandbox contemporaneo in costume.
2. Autonomia del mondo dimostrabile durante assenza del giocatore.
3. Informazione locale: fatti, credenze e reputazioni rimangono separati.
4. Economia materiale collegata a lavoro, proprietà, trasporti e consumo.
5. Narrazione emergente resa leggibile da contenuti autoriali modulari.
6. Espansione da una Pompei densa a un Impero differenziato, non omogeneizzato.

## Gameplay

La visione richiede verbi non violenti robusti quanto quelli fisici: osservare, chiedere, promettere, contrattare, produrre, insegnare, curare, testimoniare, celebrare, organizzare e rifiutare. Il combattimento esiste, ma conserva rischio corporeo, giuridico e reputazionale.

## Accuratezza storica

La visione non decide singoli fatti storici. Impone però che evidenza, ricostruzione, sintesi e controfattuale siano distinguibili; le regole siano circoscritte per periodo e luogo; le istituzioni sensibili siano strutturali e non decorative; l'incertezza non venga colmata con stereotipi silenziosi.

## Interazioni con altri sistemi

La visione governa [mondo](../03-world/world-model.md), [simulazione](../04-simulation/simulation-architecture.md), [gameplay](../05-player/gameplay/README.md), [contenuti](../06-content/README.md), [UX](../08-ux/README.md), [tecnologia](../10-technical/README.md) e [produzione](../11-production/README.md).

## Esempio pratico

Una persona impiegata in un panificio perde una giornata di paga perché manca farina. Può cercare credito, lavorare altrove, chiedere aiuto a un patrono, partecipare a una protesta o sfruttare il mercato nero. Nessun percorso è etichettato come “soluzione corretta”; ciascuno usa risorse e produce conseguenze. La crisi sarebbe avvenuta anche senza il giocatore.

## Casi limite

- Se il giocatore ottiene grande potere, le regole non cessano di applicarsi.
- Se una simulazione non è osservabile, lascia esiti e spiegazioni coerenti.
- Se l'accuratezza rende un percorso inaccessibile, il design offre altre vite significative, non un'eccezione anacronistica.
- Se l'espansione geografica riduce densità o varietà, viene rinviata.

## Rischi

Scope imperiale prematuro; falsa profondità tramite statistiche; opacità sistemica; progressione grind-based; riduzione delle persone oppresse a risorse; tono uniformemente cupo o celebrativo.

## Dipendenze

- [Mandato della Game Bible](game-design-bible/game-bible-charter.md)
- [Pilastri](design-pillars.md)
- [Promessa al giocatore](game-design-bible/player-promise.md)
- [Framework storico](../02-historical-foundation/historical-framework.md)

## Collegamenti agli altri documenti

- [Obiettivi di esperienza](game-design-bible/experience-goals.md)
- [Principi operativi](game-design-bible/design-principles.md)
- [Scope](scope-and-non-goals.md)
- [Tracciabilità](../00-governance/traceability-matrix.md)

## Decisioni ancora aperte

Data e orizzonte della demo; prospettiva/camera; piattaforme; rating; lingue; modello commerciale; successione generazionale. Sono gestite nel [registro aperto](../00-governance/open-questions.md).

## Possibili estensioni future

Nuove città e province, viaggio interregionale, carriere militari e politiche complete, successione generazionale. Multiplayer, VR e live operations non fanno parte della promessa e restano [analisi future](../12-future-analysis/README.md).

## Criteri di completamento

- High concept, fantasia e tono non si contraddicono.
- Ogni differenziatore ha una prova prevista nella vertical slice.
- Ogni feature core rafforza almeno un pilastro e non ne viola alcuno.
- Team creativo, storico, tecnico e produttivo possono usare il documento come gate.

## TODO

- Riesaminare dopo le decisioni Q-001–Q-005.
- Validare la comprensione della promessa tramite ricerca con giocatori.
