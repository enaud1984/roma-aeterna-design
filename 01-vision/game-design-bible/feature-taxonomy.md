# Tassonomia delle feature

**ID:** VIS-GDB-005
**Stato:** Approved — Baseline 1.0
**Owner:** Lead Game Designer / Executive Producer

## Scopo

Fornire un linguaggio unico per classificare capability, sistemi, contenuti e qualità, impedendo che “documentato” significhi automaticamente “in scope”.

## Descrizione

La tassonomia combina classe di valore, tipo, orizzonte e maturità per governare backlog e change control.

## Ambito

Si applica a tutte le voci di prodotto e produzione; non sostituisce stime, dipendenze o criteri di accettazione.

## Unità classificata

Una feature è un risultato percepibile o una capability necessaria a produrlo. Epic, sistema, contenuto, strumento e requisito di qualità restano tipi differenti anche quando condividono una classe di scope.

## Dimensioni

### Classe di valore

- **Core:** necessaria a dimostrare una promessa.
- **Supporting:** aumenta forza, varietà o leggibilità del core.
- **Optional:** valore positivo, rimozione non danneggia la tesi.
- **Future:** coerente, non pianificata nell'orizzonte corrente.
- **Research:** classificazione sospesa fino a evidenza.
- **Out:** incompatibile o priva di giustificazione.

### Tipo

System; Gameplay; Content; World; UX; Accessibility; Tool; Technical Foundation; Pipeline; Compliance; Research.

### Orizzonte

D0 Bible; D1 Pompei; D2 Campania; D3 Impero; Future Analysis.

### Maturità

Idea → Framed → Specified → Ready → In Progress → Verified → Shipped → Retired.

## Scheda minima

| Campo | Obbligatorio |
|---|---|
| ID, nome, owner | sempre |
| promessa/pilastro | sempre |
| classe, tipo, orizzonte | sempre |
| risultato per il giocatore | Core/Supporting |
| dipendenze e costo totale | prima di Ready |
| accuratezza/etica | quando applicabile |
| criteri di accettazione | prima di Ready |
| metriche e rischi | Core |
| ADR | per eccezioni o promozioni |

## Flusso

~~~mermaid
stateDiagram-v2
    [*] --> Idea
    Idea --> Framed
    Framed --> Research: evidenza mancante
    Research --> Framed
    Framed --> Specified
    Specified --> Ready: gate superati
    Ready --> Verified: lavoro e test
    Verified --> Shipped
    Framed --> Rejected
    Specified --> Deferred
~~~

## Regole di promozione

- Future → Supporting/Core richiede ADR, capacità e trade-off.
- Optional → Core richiede prova che una promessa altrimenti fallisca.
- Research non riceve stima di produzione definitiva.
- Accessibility e Compliance non possono essere declassificate per preservare contenuti.
- Tooling necessario a produrre o verificare il core eredita la priorità del core.
- Una feature non può avere due owner canonici.

## Punteggio di priorità

Il punteggio orienta, non decide: valore promessa (0–3), copertura pilastri (0–3), riduzione rischio (0–3), riuso (0–2), evidenza (0–2), meno costo totale (1–5), meno rischio residuo (0–3). Dipendenze e gate possono prevalere.

## Esempi

| Feature | Classe D1 | Motivazione |
|---|---|---|
| tempo e calendario | Core | autonomia, routine, eventi |
| filiera grano-pane | Core | prova economia materiale |
| recap dell'assenza | Core | rende leggibile mondo autonomo |
| combattimento campale | Future | non necessario alla tesi di Pompei |
| trionfo completo a Roma | Future | fuori luogo e alto costo |
| notizie da una guerra | Supporting | collega scala locale e imperiale |
| multiplayer | Future Analysis | non requisito del prodotto corrente |
| validatore storico | Core Tool | protegge promessa di accuratezza |

## Interazioni

La tassonomia alimenta [scope](../scope-and-non-goals.md), backlog, roadmap, risk register, budget, test plan e comunicazione. Il backlog non ridefinisce le classi.

## Casi limite

Una feature tecnica invisibile può essere Core. Un contenuto “hero” può essere Optional. Una feature economica completa ma non usata dalla demo resta Future. Un requisito di sicurezza può essere Core senza contribuire direttamente a un pilastro.

## Dipendenze

- [Pilastri](../design-pillars.md)
- [Scope](../scope-and-non-goals.md)
- [Vincoli](product-constraints.md)

## Collegamenti agli altri documenti

- [Backlog demo](../../11-production/roadmap-backlog/demo-backlog.md)
- [Definition of Ready](../../11-production/roadmap-backlog/definition-of-ready.md)
- [Rischi](../../11-production/risk-register.md)

## Decisioni ancora aperte

Formula quantitativa definitiva di priorità; tool di catalogo; authority per eccezioni sotto una soglia economica.

## Rischi

Inflazione del Core; classificazioni politiche; punteggi usati senza analisi; feature spezzate artificialmente per nascondere costo.

## Criteri di completamento

Tutto il backlog è classificabile; promozioni sono auditabili; classi e maturità non vengono confuse.

## TODO

- Classificare lo scope D1 al completamento dei domini.
- Collegare feature ID alla matrice di tracciabilità.
