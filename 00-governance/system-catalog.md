# Catalogo dei sistemi

**ID:** GOV-SYSCAT-001
**Stato:** Approved — Baseline 1.0
**Owner:** Technical Design / Game Design

## Scopo

Fornire l'inventario canonico dei sistemi, assegnare responsabilità, priorità, maturità e documenti autoritativi.

## Descrizione

Il catalogo è la porta d'ingresso per l'architettura sistemica. Non sostituisce le specifiche; impedisce sistemi senza owner, responsabilità sovrapposte e dipendenze invisibili.

## Ambito

Include sistemi runtime concettuali, servizi tecnici, tooling core e orchestrazione dei contenuti. Analisi future non sono sistemi attivi.

## Catalogo core

| ID | Sistema | Responsabilità | Priorità | Maturità | Documento |
|---|---|---|---|---|---|
| SYS-TIME-001 | Tempo e calendario | clock, date, scadenze, accelerazione | P0 | S2 | [Tempo](../03-world/time-and-persistence.md) |
| SYS-EVT-001 | Eventi | contratti, ordinamento, dispatch, causalità | P0 | S4 | [Eventi](../10-technical/architecture/event-architecture.md) |
| SYS-ID-001 | Identità | ID persistenti e lifecycle | P0 | S1 | [Modello dati](../10-technical/data-model.md) |
| SYS-WORLD-001 | Mondo/spazio | luoghi, gerarchie, accessi, livelli | P0 | S3 | [Framework](../03-world/settlements/settlement-framework.md) |
| SYS-SIM-001 | Orchestratore simulazione | clock di dominio, risoluzione, budget | P0 | S2 | [Simulazione](../04-simulation/simulation-architecture.md) |
| SYS-PER-001 | Persona e ciclo di vita | identità biografica, corpo, nascita, invecchiamento, morte | P0 | S3 | [Modello persona](../04-simulation/npc-population-ai/npc-model.md) |
| SYS-SAVE-001 | Persistenza | snapshot, migrazione, recovery | P0 | S1 | [Save](../10-technical/save-system/save-architecture.md) |
| SYS-KNOW-001 | Conoscenza | fatti, osservazioni, credenze, diffusione | P1 | S3 | [Memoria](../04-simulation/npc-population-ai/memory.md) |
| SYS-NPC-001 | Agenti | stato, bisogni, intenti, impegni | P1 | S3 | [AI](../04-simulation/npc-population-ai/ai-architecture.md) |
| SYS-REL-001 | Relazioni | legami multidimensionali ed evidenze | P1 | S3 | [Relazioni](../04-simulation/npc-population-ai/relationships.md) |
| SYS-HH-001 | Household/famiglia | membri, autorità, risorse, successione | P1 | S0 | [Household](../04-simulation/family-social/household.md) |
| SYS-STAT-001 | Status e diritto | capacità, diritti, obblighi, procedure | P1 | S1 | [Status](../04-simulation/social-status-and-law.md) |
| SYS-ECO-001 | Economia | beni, attività, transazioni, prezzi | P1 | S1 | [Economia](../04-simulation/economy.md) |
| SYS-PROP-001 | Proprietà | titolarità, possesso, uso, trasferimenti | P1 | S0 | [Proprietà](../04-simulation/economy-production/property.md) |
| SYS-INV-001 | Inventario | contenitori e custodia fisica | P1 | S0 | [Inventario](../05-player/items/inventory.md) |
| SYS-WORK-001 | Lavoro/produzione | capacità, processi, turni, output | P1 | S0 | [Produzione](../04-simulation/economy-production/production.md) |
| SYS-INT-001 | Interazione | affordance, comandi, risoluzione | P1 | S0 | [Interazione](../05-player/gameplay/interaction-model.md) |
| SYS-CONT-001 | Situazioni/missioni | condizioni, stati, binding, conseguenze | P1 | S1 | [Contenuti](../06-content/content-framework.md) |
| SYS-REP-001 | Reputazione | credenze contestuali delle comunità | P1 | S1 | [Informazione](../04-simulation/information-and-reputation.md) |
| SYS-NEED-001 | Bisogni/salute | bisogni, capacità, malattia, recovery | P1 | S0 | [Salute](../04-simulation/health-medicine/health-system.md) |
| SYS-UI-001 | UI/feedback | presentazione epistemica e input | P1 | S1 | [UX](../08-ux/ux-principles.md) |
| SYS-RELIG-001 | Religione | pratiche, calendari, comunità, autorità | P2 | S1 | [Religione](../04-simulation/religion.md) |
| SYS-POL-001 | Politica | agenda, coalizioni, decisioni, cariche | P2 | S1 | [Politica](../04-simulation/politics-and-governance.md) |
| SYS-CRIME-001 | Illeciti/risposta | atti, prove, denuncia, procedura | P2 | S0 | [Criminalità](../04-simulation/politics-law/criminality.md) |
| SYS-COMBAT-001 | Combattimento | conflitto fisico, ferite, resa | P2 | S0 | [Combattimento](../04-simulation/military-combat/combat-vision.md) |
| SYS-WAR-001 | Guerra | campagne e impatti aggregati | P3 | S1 | [Guerra](../04-simulation/war-and-military.md) |
| SYS-AUTH-001 | Autorità e transazioni | autorizzazioni, commit, rollback, audit delle mutazioni | P0 | S3 | [Architettura tecnica](../10-technical/technical-architecture.md) |
| SYS-HIST-001 | Provenienza storica | fonti, claim, certezza, licenze | P0 Tool | S1 | [Framework storico](../02-historical-foundation/historical-framework.md) |
| SYS-DBG-001 | Osservabilità | inspector, causal trace, replay | P0 Tool | S1 | [Strumenti](../10-technical/tools-and-observability.md) |

## Confini critici

- Tempo possiede avanzamento; i domini possiedono le proprie scadenze.
- Eventi trasportano fatti; non possiedono lo stato di dominio.
- Inventario possiede custodia fisica; proprietà possiede diritti.
- Conoscenza possiede credenze individuali; reputazione possiede aggregati comunitari derivati.
- NPC possiede stato dell'agente; household possiede struttura domestica condivisa.
- Contenuti coordinano condizioni; non scrivono direttamente stato altrui.

## Sistemi che non esistono come autorità unica

“Gameplay”, “città viva”, “realismo” e “narrazione emergente” sono risultati integrati, non servizi proprietari di tutto lo stato correlato.

## Diagramma

~~~mermaid
flowchart TD
    T["TIME"] --> SIM["SIM"]
    ID["IDENTITY"] --> SIM
    SIM --> NPC["NPC"]
    SIM --> ECO["ECONOMY"]
    SIM --> CONT["CONTENT"]
    WORLD["WORLD"] --> NPC
    KNOW["KNOWLEDGE"] --> NPC
    NPC --> REL["RELATIONSHIPS"]
    NPC --> ECO
    PROP["PROPERTY"] --> ECO
    INV["INVENTORY"] --> ECO
    LAW["STATUS/LAW"] --> CONT
    ECO --> CONT
    EVT["EVENTS"] --> KNOW
    NPC --> EVT
    ECO --> EVT
    CONT --> EVT
    EVT --> SAVE["PERSISTENCE"]
    KNOW --> UI["UI"]
~~~

## Dipendenze

- [Standard specifiche](system-specification-standard.md)
- [Matrice dipendenze](system-dependency-matrix.md)
- [Registro canonico](canonical-document-register.md)

## Collegamenti agli altri documenti

- [Ownership dati](../10-technical/data/data-ownership-matrix.md)
- [Contratti eventi](../10-technical/architecture/event-contracts.md)
- [Readiness](../11-production/roadmap-backlog/implementation-readiness-matrix.md)

## Decisioni ancora aperte

Confine bisogno/salute; separazione reputazione/conoscenza; authority delle transazioni; granularità dell'orchestratore; engine mapping.

## Rischi

God system; ownership duplicata; eventi usati come database; servizi tecnici che incorporano regole storiche; maturità sovrastimata.

## Criteri di accettazione

Ogni sistema ha ID unico, responsabilità singola, documento, owner di ruolo, priorità e maturità.

## Definition of Done

Catalogo copre tutti i sistemi fondazionali e viene aggiornato in ogni ADR architetturale.

## TODO

- Espandere sistemi P2/P3 durante le rispettive macroaree.
- Aggiungere owner nominali.
