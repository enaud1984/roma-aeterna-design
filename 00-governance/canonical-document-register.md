# Registro dei documenti canonici

**ID:** GOV-CANON-001
**Stato:** Approved — Baseline 1.0
**Owner:** Technical Writing / Game Direction

## Scopo

Indicare quale documento possiede l'autorità per ciascun concetto trasversale e distinguere specifiche canoniche, panoramiche, indici e analisi future.

## Descrizione

Il registro previene duplicazioni semantiche in un corpus molto modulare. Un documento canonico contiene requisiti e decisioni; una panoramica sintetizza e collega; un README naviga; un'analisi futura non crea scope.

## Ambito

Copre le autorità principali. Le autorità di dettaglio sono dichiarate nei README locali e saranno aggiunte quando gli scheletri diventano specifiche.

## Classi documentali

| Classe | Può contenere requisiti normativi? | Funzione |
|---|---:|---|
| Canonical specification | sì | unica fonte di verità del dominio |
| Overview | solo sintesi citata | orientamento e integrazione |
| Index/README | no | navigazione, ownership e stato |
| Register/ADR | sì, per governance | decisioni, rischi, domande e audit |
| Template | no | struttura riutilizzabile |
| Future analysis | no per scope corrente | valutazione senza commitment |

## Autorità trasversali

| Concetto | Documento canonico | Panoramiche o consumatori |
|---|---|---|
| Identità del prodotto | [Visione creativa](../01-vision/creative-vision.md) | README principale |
| Promesse | [Promessa al giocatore](../01-vision/game-design-bible/player-promise.md) | tracciabilità, marketing futuro |
| Pilastri | [Pilastri](../01-vision/design-pillars.md) | principi e feature review |
| Scope | [Scope e non-obiettivi](../01-vision/scope-and-non-goals.md) | roadmap e backlog |
| Metodo storico | [Framework storico](../02-historical-foundation/historical-framework.md) | fonti e Historical QA |
| Mondo | [Modello del mondo](../03-world/world-model.md) | città, geografia e Pompei |
| Simulazione | [Architettura simulazione](../04-simulation/simulation-architecture.md) | specifiche dei sottodomini |
| NPC | [Ciclo di vita NPC](../04-simulation/npc-life-simulation.md) finché non è promosso [NPC model](../04-simulation/npc-population-ai/npc-model.md) | popolazione, AI, contenuti |
| Economia | [Economia](../04-simulation/economy.md) finché non è promosso [modello economico](../04-simulation/economy-production/economic-model.md) | filiere e demo |
| Informazione/reputazione | [Informazione e reputazione](../04-simulation/information-and-reputation.md) | NPC, politica, UX |
| Gameplay | [Esperienza del giocatore](../05-player/player-experience.md) finché non è promosso [core loop](../05-player/gameplay/core-loop.md) | attività e progressione |
| Contenuti | [Framework contenuti](../06-content/content-framework.md) | missioni, narrativa, dialoghi |
| Pompei | [Vertical slice](../07-pompeii-demo/pompeii-vertical-slice.md) | documenti demo |
| UX | [Principi UX](../08-ux/ux-principles.md) | UI e flussi |
| Arte | [Direzione artistica](../09-art-audio/art-direction.md) | asset e pipeline |
| Audio | [Direzione audio](../09-art-audio/audio-direction.md) | sistema e pipeline |
| Architettura tecnica | [Technical architecture](../10-technical/technical-architecture.md) | sottodomini tecnici |
| Dati | [Panoramica dati](../10-technical/data-model.md) finché non è promosso [modello concettuale](../10-technical/data/conceptual-model.md) | save, strumenti e contenuti |
| Produzione | [Piano di produzione](../11-production/production-plan.md) | roadmap e backlog |
| QA | [Strategia QA](../11-production/qa-strategy.md) | piani specializzati |

## Regola di promozione

Uno scheletro specializzato diventa canonico solo quando raggiunge Review, assorbe senza perdita i requisiti della panoramica, aggiorna i link in ingresso e registra la promozione in ADR. Fino ad allora prevale il documento maturo indicato nella tabella.

~~~mermaid
flowchart LR
    O["Overview matura"] --> S["Specifica specializzata Draft"]
    S --> R["Review di copertura"]
    R --> A["ADR di promozione"]
    A --> C["Specifica canonical"]
    C --> O2["Overview ridotta a sintesi e link"]
~~~

## Dipendenze

- [Standard documentale](documentation-standard.md)
- [Decision log](decision-log.md)
- [Mappa documentale](documentation-map.md)

## Collegamenti agli altri documenti

- [Report di audit](../11-production/audits/game-bible-audit-2026-07-20.md)
- [Matrice delle dipendenze](system-dependency-matrix.md)
- [Roadmap documentale](../11-production/roadmap-backlog/documentation-roadmap.md)

## Decisioni ancora aperte

- Sequenza di promozione degli scheletri specializzati.
- Metadata automatizzati per classe e autorità.

## Casi limite

Un ADR può modificare un requisito senza diventare la specifica di dominio; la specifica deve recepirlo. Un README può riportare lo stato ma non creare una promessa. Un template non costituisce evidenza che la sezione sia stata completata.

## Rischi

Link validi verso una fonte non autorevole; promozione parziale; panoramiche che continuano a divergere; uso degli scheletri come requisiti approvati.

## Criteri di completamento

- Ogni concetto trasversale ha un'autorità.
- Le duplicazioni intenzionali sono classificate come sintesi.
- Ogni promozione è registrata e aggiorna i link.

## TODO

- Estendere il registro per macroarea durante il completamento dei contenuti.
- Integrare classe e stato nei metadata documentali.
