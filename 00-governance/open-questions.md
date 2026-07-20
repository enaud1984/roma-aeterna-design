# Registro delle domande aperte

Le domande sono ordinate per impatto. Chiudere una domanda significa creare o aggiornare un ADR, non cancellarla.

## Bloccanti per la definizione del prodotto

| ID | Domanda | Impatto | Owner | Criterio di chiusura |
|---|---|---|---|---|
| Q-001 | In quale anno e stagione si svolge la demo? | canone, eruzione, personaggi, economia | Game Direction + History | confronto di almeno tre finestre e ADR |
| Q-002 | L'eruzione del 79 d.C. è dentro l'orizzonte giocabile? | struttura temporale e promessa | Game Direction | test di compatibilità coi pilastri |
| Q-003 | Quali piattaforme e prestazioni target? | densità, input, memoria | Tech Direction | target hardware e budget firmati |
| Q-004 | Quale rating e pubblico minimo? | schiavitù, violenza, sessualità, linguaggio | Direction + Legal | policy contenuti approvata |
| Q-005 | Qual è il modello commerciale? | scope, persistenza, live operations | Production | business brief approvato |
| Q-006 | Quale prospettiva e modello di camera adotta il gioco? | controlli, animazione, UX, combattimento | Game + UX Direction | prototipi comparativi e ADR |
| Q-007 | La successione generazionale è una promessa del prodotto o un'estensione? | durata, morte, famiglia, save | Game Direction | scenario, costo e ADR |

## Bloccanti per Pompei

| ID | Domanda | Documento che la assorbirà |
|---|---|---|
| Q-101 | Quali insulae e aree extraurbane sono fisicamente esplorabili? | [Scope Pompei](../07-pompeii-demo/pompeii-vertical-slice.md) |
| Q-102 | Quanti NPC nominati, persistenti e aggregati? | [Popolazione demo](../07-pompeii-demo/demo-population.md) |
| Q-103 | Quali mestieri sono completi nel slice? | [Economia demo](../07-pompeii-demo/demo-economy.md) |
| Q-104 | Quali lingue sono rappresentate e come? | [Dialogo](../06-content/dialogue-and-language.md) |
| Q-105 | Quale granularità per schiavitù, manomissione e patronato? | [Status sociale](../04-simulation/social-status-and-law.md) |

## Ricerca e sensibilità

- Come rappresentare la schiavitù come istituzione strutturale senza ridurla a valuta o spettacolo?
- Come distinguere pratiche religiose domestiche, civiche, misteriche e imperiali senza usare categorie moderne improprie?
- Quali gruppi sono scarsamente attestati e richiedono una ricostruzione H2/H3 più esplicita?
- Quali meccaniche rischiano di premiare comportamenti anacronistici pur presentandoli come storici?

## Governance e mantenibilità

| ID | Domanda | Impatto | Owner | Criterio di chiusura |
|---|---|---|---|---|
| Q-201 | Quali metadata documentali saranno validati automaticamente? | autorità, stato, owner, versioni | Technical Writing + Tools | schema e validatore approvati |
| Q-202 | Qual è la soglia per unire uno scheletro troppo piccolo al documento genitore? | navigabilità e frammentazione | Game Direction | regola basata su responsabilità e lifecycle |
| Q-203 | Con quale frequenza eseguire l'audit globale? | deriva e costo di manutenzione | Production | cadence inserita nella roadmap |

Vedere [etica e rappresentazione](../02-historical-foundation/ethics-and-representation.md) e [framework storico](../02-historical-foundation/historical-framework.md).

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
