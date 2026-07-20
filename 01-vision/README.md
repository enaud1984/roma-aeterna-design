# Visione del Progetto

**Area:** VIS
**Stato:** Complete — Baseline 1.0
**Owner:** Game Director
**Reviewer:** Lead Game Design, Narrative Director, Historical Director, Technical Director, Executive Producer

## Scopo

Stabilire l'identità vincolante di *Roma Aeterna* e fornire i criteri con cui tutte le discipline valutano sistemi, contenuti, tecnologia e scope.

## Descrizione

Questa macroarea è la fonte gerarchicamente più autorevole dopo la governance documentale. Definisce che gioco viene realizzato, quale esperienza promette, quali compromessi sono accettabili e quali proposte devono essere escluse. Non descrive il dettaglio dei singoli sistemi.

## Ambito

Include visione creativa, pilastri, principi operativi, promessa al giocatore, obiettivi di esperienza, tassonomia delle feature, vincoli e strategia di scope. Non include ricerca storica di dettaglio, numeri di bilanciamento, architettura software o backlog esecutivo.

## Documenti contenuti

| Documento | Autorità | Stato |
|---|---|---|
| [Visione creativa](creative-vision.md) | identità, fantasia, tono, differenziatori | Complete |
| [Pilastri di design](design-pillars.md) | gate decisionali non negoziabili | Complete |
| [Scope e non-obiettivi](scope-and-non-goals.md) | orizzonti, confini e change control | Complete |
| [Mandato della Game Bible](game-design-bible/game-bible-charter.md) | funzione e governo della Bible | Complete |
| [Promessa al giocatore](game-design-bible/player-promise.md) | promesse verificabili e relativi limiti | Complete |
| [Obiettivi di esperienza](game-design-bible/experience-goals.md) | risultati emotivi e cognitivi | Complete |
| [Principi operativi](game-design-bible/design-principles.md) | regole applicabili alle feature | Complete |
| [Tassonomia delle feature](game-design-bible/feature-taxonomy.md) | classificazione e gate dello scope | Complete |
| [Vincoli del prodotto](game-design-bible/product-constraints.md) | limiti creativi, storici, tecnici ed etici | Complete |

## Visione del sistema documentale

~~~mermaid
flowchart TD
    V["Visione creativa"] --> P["Pilastri"]
    V --> PP["Promessa al giocatore"]
    P --> PR["Principi operativi"]
    PP --> EG["Obiettivi di esperienza"]
    PR --> FT["Tassonomia feature"]
    C["Vincoli del prodotto"] --> FT
    S["Scope e non-obiettivi"] --> FT
    FT --> D["Specifiche di dominio"]
    D --> T["Test e criteri di accettazione"]
~~~

## Dipendenze

- [Governance documentale](../00-governance/README.md)
- [Framework storico](../02-historical-foundation/historical-framework.md)
- [Piano di produzione](../11-production/production-plan.md)

## Collegamenti con le altre aree

- [Mappa documentale](../00-governance/documentation-map.md)
- [Matrice di tracciabilità](../00-governance/traceability-matrix.md)
- [Esperienza del giocatore](../05-player/player-experience.md)
- [Vertical slice di Pompei](../07-pompeii-demo/pompeii-vertical-slice.md)

## Decisioni ancora aperte

Le decisioni su data della demo, piattaforme, rating, lingue e modello commerciale restano nel [registro delle domande aperte](../00-governance/open-questions.md). Non impediscono l'approvazione della visione, ma impediscono la chiusura dello scope di produzione.

## Rischi

- Diluire l'identità per includere ogni possibile feature.
- Confondere accuratezza storica con quantità di dettaglio.
- Trasformare autonomia del mondo in opacità per il giocatore.
- Usare “persona comune” come pretesto per un'esperienza priva di agency.

## Criteri di completamento

- Ogni documento dell'area possiede responsabilità non sovrapposta.
- Ogni promessa è collegabile a una prova nella demo.
- Pilastri e vincoli permettono di respingere proposte incompatibili.
- Le questioni realmente aperte sono registrate e non mascherate da assunzioni.

## Stato di avanzamento

**Completato:** contenuti fondativi e collegamenti.
**Prossima revisione:** dopo chiusura di Q-001–Q-005 o modifica della promessa di prodotto.

## TODO

- Assegnare persone nominali ai ruoli di owner e reviewer.
- Riesaminare la baseline al greenlight della vertical slice.
