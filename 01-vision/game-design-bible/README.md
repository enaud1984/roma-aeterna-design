# Game Design Bible

**Area:** VIS-GDB
**Stato:** Complete — Baseline 1.0
**Owner:** Lead Game Designer

## Scopo

Tradurre la visione creativa in un contratto di prodotto verificabile e in regole operative per le specifiche di dominio.

## Descrizione

Questo indice assegna un'autorità distinta a ogni documento, evitando duplicazioni. La visione definisce l'identità; questa cartella definisce come preservarla durante progettazione e produzione.

## Ambito

Comprende mandato, promessa, obiettivi di esperienza, principi operativi, tassonomia feature e vincoli. Non sostituisce le specifiche di gameplay o simulazione.

## Documenti contenuti

| Documento | Domanda a cui risponde | Stato |
|---|---|---|
| [Mandato](game-bible-charter.md) | come governa la Bible? | Complete |
| [Promessa](player-promise.md) | cosa può aspettarsi il giocatore? | Complete |
| [Obiettivi di esperienza](experience-goals.md) | cosa deve percepire e comprendere? | Complete |
| [Principi operativi](design-principles.md) | come devono comportarsi le feature? | Complete |
| [Tassonomia](feature-taxonomy.md) | come classifichiamo le feature? | Complete |
| [Vincoli](product-constraints.md) | quali limiti non possono essere ignorati? | Complete |

## Flusso principale

~~~mermaid
flowchart LR
    P["Promessa"] --> E["Obiettivo esperienza"]
    E --> R["Principio operativo"]
    R --> F["Feature classificata"]
    C["Vincoli"] --> F
    F --> S["Specifica e test"]
~~~

## Dipendenze

- [Visione creativa](../creative-vision.md)
- [Pilastri](../design-pillars.md)
- [Scope](../scope-and-non-goals.md)
- [Governance](../../00-governance/README.md)

## Collegamenti con le altre aree

- [Gameplay](../../05-player/gameplay/README.md)
- [Simulazione](../../04-simulation/README.md)
- [Pompei](../../07-pompeii-demo/README.md)
- [Produzione](../../11-production/README.md)

## Decisioni ancora aperte

Nessuna decisione aperta interna blocca la baseline. Le decisioni di prodotto Q-001–Q-005 limitano gli usi produttivi ma non l'autorità concettuale.

## Rischi

Uso della Bible come enciclopedia passiva; duplicazione; decisioni non registrate; feature promosse senza prove.

## Criteri di completamento

Tutti i documenti sono completi, non sovrapposti, collegati a test e applicabili a una feature review.

## Stato di avanzamento

**Completato:** 6/6 documenti.
**Prossima revisione:** chiusura dello scope di Pompei.

## TODO

- Eseguire un workshop di allineamento interdisciplinare.
- Aggiungere esempi reali dalla prima classificazione del backlog.
