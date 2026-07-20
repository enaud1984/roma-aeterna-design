# Patronato, clientela e favori

## Scopo

Definire relazioni asimmetriche di protezione, accesso, sostegno e obbligo senza ridurle a fazioni o punti spendibili.

## Descrizione

Patrono e cliente interpretano aspettative contestuali: raccomandazione, assistenza, rappresentanza, lavoro, presenza, sostegno pubblico, credito o informazione. Ogni favore ha memoria, testimoni e costo reputazionale; reciprocità non significa uguaglianza.

## Ambito

Patronato personale, relazioni post-manomissione, clientela, favori, mediazione, conflitti tra obblighi, rottura e trasmissione familiare solo quando attestata.

## Modello e regole

`PatronageLink` possiede parti, origine, ambiti, aspettative, asimmetria, visibilità, stato e validità storica. `Favor` registra richiesta, prestazione, costo, beneficiario, prova e reciprocità attesa. Nessun favore garantisce un esito fuori dall'autorità del patrono; denaro, amicizia, clientela e corruzione restano relazioni distinte.

## Flusso

Bisogno/opportunità → richiesta o offerta → valutazione di capacità, costo e lealtà → accettazione/rifiuto → prestazione → riconoscimento, debito sociale, contestazione o rottura. Obblighi incompatibili producono scelta e conseguenze, non soluzione automatica.

## Eventi e conseguenze

Produce `FavorRequested/Accepted/Fulfilled/Refused`, `PatronageFormed/Strained/Ended`; ascolta manomissione, carica, debito, scandalo, morte, migrazione e decisione. Effetti su accesso, reputazioni locali, politica, lavoro, credito e protezione.

## Casi limite, accuratezza e persistenza

Patrono morto o senza autorità, richieste contraddittorie, favore illecito, cliente multiplo, promessa non pubblica e time-skip mantengono stato contestato. Forme, terminologia e obblighi variano per epoca/status/luogo A–E. Persistono relazione, favori, prove, rifiuti e memoria.

## Dipendenze

- [Clientela](clientela.md)
- [Status](social-status.md)
- [Reputazione](reputation.md)
- [Politica](../politics-law/political-system.md)

## Collegamenti agli altri documenti

- [Corruzione](../politics-law/corruption.md)
- [Credito](../economy-production/credit-and-debt.md)
- [Schiavitù e manomissione](slavery.md)

## Test e Definition of Done

Testare formazione, favore possibile/impossibile, rifiuto, conflitto, abuso, morte, rottura e save/load. S4 quando reti P0 hanno basi storiche e conseguenze end-to-end.

## Decisioni ancora aperte

- Obblighi post-manomissione e pratiche clientelari P0.
- Grado di trasparenza UX delle aspettative.

## TODO

- Creare scenari economico, legale e politico.
- Allineare `clientela.md` alla specifica canonica.
