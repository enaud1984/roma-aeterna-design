# Pilastri di design

**ID:** VIS-002
**Stato:** Approved — Baseline 1.0
**Owner:** Game Director / Lead Game Designer

## Scopo

Fornire i criteri non negoziabili con cui accettare, modificare o respingere feature, contenuti e soluzioni tecniche.

## Descrizione

Set di sette gate decisionali, ciascuno corredato da requisiti, divieti e prova attesa nella demo di Pompei.

## Ambito

I pilastri si applicano all'intero prodotto. I [principi operativi](game-design-bible/design-principles.md) ne specificano l'uso quotidiano; non costituiscono un elenco di feature.

## P1 — Una vita, non una leggenda

Il personaggio è una persona situata. Origine, corpo, status, famiglia, competenze, ricchezza, reputazione e luogo definiscono opportunità reali.

**Richiede:** molte definizioni di successo; progressione con provenienza; autorità guadagnata o concessa da istituzioni; fallimenti biografici.
**Vieta:** predestinazione, immunità narrativa, accesso universale, level scaling che rende il mondo funzione del player.
**Prova Pompei:** tre origini affrontano uno stesso bisogno con accessi, rischi e reti differenti.

## P2 — Il mondo non aspetta

Persone, attività e istituzioni agiscono durante assenza, viaggio, sonno e disinteresse del giocatore.

**Richiede:** calendari, deadline, sostituzioni, successioni, simulazione multi-risoluzione e recap.
**Vieta:** crisi sospese, NPC congelati, missioni che attendono indefinitamente senza causa.
**Prova Pompei:** trenta giorni simulati senza input producono cambiamenti coerenti e recuperabili tramite fonti locali.

## P3 — Provenienza e conseguenza

Beni, denaro, informazioni, ordini, diritti e reputazioni hanno origine e percorso; le azioni significative si propagano oltre il premio immediato.

**Richiede:** ownership, ledger causali, conservazione, memoria e conseguenze cross-system.
**Vieta:** risorse infinite al livello dettagliato, reputazione globale, effetti privi di causa interrogabile.
**Prova Pompei:** una consegna mancata modifica produzione, consumo, credito, relazioni e agenda politica.

## P4 — Autenticità leggibile

Il mondo segue regole storicamente fondate, ma il giocatore può comprenderne cause, vincoli e alternative senza studio obbligatorio esterno.

**Richiede:** informazione a strati, tutoraggio sociale, feedback contestuale, distinzione tra fatto e voce.
**Vieta:** oscurità scambiata per realismo, numeri onniscienti, modernizzazione silenziosa delle istituzioni.
**Prova Pompei:** un'azione negata comunica il vincolo e almeno un percorso plausibile per affrontarlo.

## P5 — Densità sistemica prima della scala

Ogni luogo sostiene attività, relazioni e cambiamenti nel tempo. L'espansione avviene soltanto dopo aver provato profondità e sostenibilità.

**Richiede:** pacchetti regionali, strumenti riusabili, livelli di dettaglio e metriche di costo.
**Vieta:** mappe vaste ma uniformi, riuso che cancella differenze locali.
**Prova Pompei:** lo stesso quartiere produce esperienze diverse su scala oraria, giornaliera e mensile.

## P6 — Potere con attrito

Ricchezza, competenza, libertà, carica e forza ampliano possibilità ma generano costi, obblighi, opposizione ed esposizione.

**Richiede:** trade-off, manutenzione, responsabilità, conflitti di interesse e rischio di perdita.
**Vieta:** progressione cumulativa senza costi, organizzazioni che obbediscono personalmente al player.
**Prova Pompei:** gestire una bottega crea reddito ma anche scorte, salari, debiti, clienti e responsabilità.

## P7 — Persone, non funzioni

Gli NPC possiedono continuità e interessi indipendenti dal ruolo svolto per il giocatore.

**Richiede:** household, lavoro, bisogni, memoria, relazioni, obiettivi e sostituzione plausibile.
**Vieta:** quest giver immobili, gruppi definiti soltanto da stereotipi o servizio al player.
**Prova Pompei:** la perdita di casa o lavoro cambia routine e relazioni senza distruggere l'agente.

## Matrice di valutazione

Ogni proposta riceve 0–2 per pilastro: 0 contraddice, 1 è neutra o indiretta, 2 rafforza. Un solo zero blocca la proposta salvo ADR esplicito. Una feature core deve ottenere almeno 10/14; una supporting almeno 7/14.

| Domanda | Evidenza |
|---|---|
| Rafforza una vita comune significativa? | scenario con origine/status |
| Funziona senza il player? | scenario autonomo o degradazione |
| Ha cause e conseguenze? | catena causale |
| È storicamente leggibile? | fonte/classe H e feedback |
| Giustifica il costo di scala? | metrica e riuso |
| Il potere introduce attrito? | costo/obbligo/rischio |
| Gli NPC restano soggetti? | impatto su vita e obiettivi |

## Flusso decisionale

~~~mermaid
flowchart TD
    F["Proposta"] --> Z{"Contiene uno zero?"}
    Z -- Sì --> R["Riprogettare o aprire ADR"]
    Z -- No --> C{"Punteggio sufficiente?"}
    C -- No --> B["Supporting, Future o Reject"]
    C -- Sì --> E["Definire prova e costo totale"]
    E --> S["Classificare nello scope"]
~~~

## Casi limite

Una feature può rafforzare un pilastro e danneggiarne un altro: il punteggio non compensa uno zero. Un requisito di accessibilità non può essere respinto perché non diegetico. Una semplificazione tecnica è accettabile se conserva l'esito osservabile e gli invarianti.

## Dipendenze

- [Visione creativa](creative-vision.md)
- [Promessa](game-design-bible/player-promise.md)
- [Tassonomia feature](game-design-bible/feature-taxonomy.md)

## Collegamenti agli altri documenti

- [Scope](scope-and-non-goals.md)
- [Tracciabilità](../00-governance/traceability-matrix.md)
- [Rischi](../11-production/risk-register.md)

## Decisioni ancora aperte

Le soglie potranno essere ricalibrate dopo il primo ciclo di feature review, ma non durante la valutazione di una singola proposta.

## Rischi

Uso rituale del punteggio; valutazioni senza evidenza; eccezioni ripetute; interpretazione di accuratezza come massima complessità.

## Criteri di completamento

- Ogni pilastro contiene requisito, divieto e prova.
- La matrice produce decisioni ripetibili.
- Nessuna promessa fondamentale resta senza pilastro.
- Almeno una review interdisciplinare usa il processo senza ambiguità.

## TODO

- Eseguire la prima review sullo scope della demo.
- Registrare esempi di feature accettate e respinte.
