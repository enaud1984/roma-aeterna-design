# Vincoli del prodotto

**ID:** VIS-GDB-006
**Stato:** Approved with Open Decisions — Baseline 1.0
**Owner:** Game Director / Executive Producer / Technical Director

## Scopo

Raccogliere i limiti che ogni proposta deve rispettare e distinguere vincoli approvati da decisioni ancora aperte.

## Descrizione

Registro canonico dei vincoli creativi, storici, sistemici, UX, tecnici, produttivi, commerciali e legali.

## Ambito

Copre l'intero progetto; i valori e vincoli dipendenti da decisioni aperte non vengono anticipati.

## Vincoli creativi

- Protagonista non predestinato.
- Mondo autonomo e persistente.
- Storia sistemica, non sola estetica.
- Violenza non universale.
- Potere accompagnato da attrito.
- Tono umano, non propaganda imperiale né condanna monocorde.

## Vincoli storici ed etici

- Periodo e luogo espliciti per regole variabili.
- Provenienza per affermazioni significative.
- Incertezza dichiarata.
- Schiavitù, coercizione e disuguaglianza non decorative.
- Nessun gruppo definito soltanto da stereotipo.
- Religione rappresentata dalla prospettiva dei partecipanti senza conferma soprannaturale.
- Review specialistica per contenuti sensibili.

## Vincoli sistemici

- Stato canonico indipendente dalla presentazione.
- NPC senza accesso onnisciente.
- Conseguenze importanti persistenti.
- Aggregazione priva di duplicazioni e contraddizioni.
- Causalità diagnosticabile internamente.
- Ogni sistema core possiede failure mode e degradazione.

## Vincoli UX e accessibilità

- Feedback su causa prossima e alternative.
- Nessuna informazione essenziale affidata a un solo canale sensoriale.
- Remapping e configurazione previsti dall'architettura.
- Accessibilità senza penalità.
- Precisione dell'interfaccia coerente con conoscenza, salvo strumenti esplicitamente assistivi.

## Vincoli tecnici

Finché Q-003 è aperta non esistono target numerici approvati. Restano vincolanti modularità, testabilità, osservabilità, versionamento dati, migrazione salvataggi, streaming, performance budgetizzata e strumenti di authoring.

## Vincoli produttivi

- Pompei prima dell'espansione imperiale.
- Strumenti e QA fanno parte dello scope.
- Costo totale include contenuti, localizzazione, accessibilità, test e mantenimento.
- Nessun commitment di feature future senza ADR.
- Nessun codice prima del gate documentale richiesto dalla roadmap corrente.

## Vincoli commerciali e legali

Modello commerciale, rating, piattaforme, privacy e licenze sono aperti. Il design non può presumere always-online, microtransazioni, account o telemetria remota.

## Matrice

| Vincolo | Fonte | Bloccante per |
|---|---|---|
| persona comune | ADR-0002 | narrativa, progressione |
| mondo autonomo | ADR-0003 | simulazione, save, UX |
| Pompei first | ADR-0001 | world scope, produzione |
| provenienza storica | ADR-0005 proposto | asset, testi, regole storiche |
| piattaforme TBD | Q-003 | budget finali, input, certification |
| rating TBD | Q-004 | contenuti sensibili, marketing |
| business TBD | Q-005 | online, liveops, analytics |

## Flusso di eccezione

~~~mermaid
flowchart TD
    P["Proposta"] --> C{"Conforme?"}
    C -- Sì --> N["Normale review"]
    C -- No --> H{"Vincolo hard?"}
    H -- Sì --> R["Respinta o modifica della visione"]
    H -- No --> A["ADR con costo e compensazioni"]
    A --> D{"Approvata?"}
    D -- No --> R
    D -- Sì --> U["Aggiornare documenti dipendenti"]
~~~

## Esempi

Always-online è vietato come assunzione perché modello commerciale e connettività non sono decisi. Una simulazione aggregata è consentita se conserva invarianti e fatti osservati. Un'opzione che rallenta il combattimento è compatibile con accessibilità anche se non diegetica.

## Casi limite

Conflitti tra accuratezza e accessibilità vengono risolti separando mondo e interfaccia. Un limite prestazionale non autorizza la cancellazione silenziosa di conseguenze. Un vincolo commerciale futuro non può retroattivamente invalidare una promessa senza change control.

## Dipendenze

- [Visione](../creative-vision.md)
- [Scope](../scope-and-non-goals.md)
- [Etica](../../02-historical-foundation/ethics-and-representation.md)
- [Architettura tecnica](../../10-technical/technical-architecture.md)

## Collegamenti agli altri documenti

- [Questioni aperte](../../00-governance/open-questions.md)
- [Decisioni](../../00-governance/decision-log.md)
- [Rischi](../../11-production/risk-register.md)

## Decisioni ancora aperte

Q-001–Q-005, camera, successione, strategia linguistica e policy sull'eruzione.

## Rischi

Vincoli impliciti; requisiti incompatibili; eccezioni non registrate; target tecnici inventati; business model che altera la promessa.

## Possibili estensioni future

Target di piattaforma, rating e sostenibilità operativa saranno aggiunti dopo ADR.

## Criteri di completamento

Ogni vincolo ha fonte e impatto; le questioni aperte non sono trattate come assunzioni; le eccezioni passano da ADR.

## TODO

- Promuovere ADR-0005 dopo review storica.
- Integrare target numerici dopo Q-003.
