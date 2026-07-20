# Tempo e persistenza

**ID:** WRL-002
**Stato:** Draft

## Scale temporali

| Scala | Fenomeni | Requisito |
|---|---|---|
| secondi/minuti | movimento, dialogo, azione fisica | risposta immediata |
| ore | lavoro, pasti, viaggio urbano, rituali | schedule e sostituzioni |
| giorni | mercati, salari, consegne, ferite | continuità durante riposo |
| mesi | stagioni, debiti, cariche, raccolti | aggregazione stabile |
| anni | età, status, proprietà, politica | da validare per demo |

## Calendario

Il calendario combina giorno/notte, stagioni, giorni di mercato, scadenze legali, feste e disponibilità lavorative. La conversione fra data storica e rappresentazione al giocatore deve essere coerente ma leggibile. Le eccezioni locali sono dati storici versionati.

## Accelerazione

Il tempo può accelerare solo se non esiste una decisione urgente che il personaggio ragionevolmente percepirebbe. Interruzioni: pericolo, arrivo, scadenza, bisogno critico, perdita rilevante o richiesta esplicitamente monitorata. L'accelerazione non annulla costi o simulazione.

## Persistenza selettiva

Persistono sempre identità, status, legami, proprietà rilevanti, obblighi, eventi irreversibili e fatti già comunicati. Dettagli effimeri possono essere riassunti. La politica di memoria è definita in [NPC life](../04-simulation/npc-life-simulation.md) e [data model](../10-technical/data-model.md).

## Assenza e ritorno

Al ritorno, il giocatore riceve un recap basato su ciò che il personaggio può sapere: cambiamenti visibili, messaggi ricevuti, voci e contatti. Il sistema non rivela causalità segrete. Deve tuttavia offrire spiegazioni progressive per evitare la sensazione di casualità.

## Salvataggio

Requisiti: determinismo sufficiente alla diagnosi; versionamento; consistenza transazionale degli eventi importanti; recovery da salvataggi parziali; nessuna duplicazione di risorse. Specifica tecnica futura collegata a [technical architecture](../10-technical/technical-architecture.md).

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
