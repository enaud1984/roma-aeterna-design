# Standard delle specifiche di sistema

**ID:** GOV-SYS-001
**Stato:** Approved — Baseline 1.0
**Owner:** Technical Design / Lead Game Design
**Reviewer:** Architecture, QA, Production, Technical Writing

## Scopo

Definire il contratto minimo affinché un documento di sistema sia utilizzabile per pianificazione, implementazione futura, test e manutenzione senza richiedere una riprogettazione fondamentale.

## Descrizione

Lo standard separa comportamento normativo, contratto di integrazione, qualità e pianificazione. Le sezioni non applicabili devono indicare “N/A” con motivazione; non possono essere omesse silenziosamente.

## Ambito

Si applica ai documenti classificati System, Technical Foundation, Tool o Pipeline. I documenti di visione, ricerca, contenuto e indice usano strutture specifiche ma devono linkare i sistemi consumati.

## Livelli di maturità

| Livello | Evidenza | Uso consentito |
|---|---|---|
| S0 Placeholder | titolo, scopo, TODO | architettura documentale |
| S1 Framed | ambito, owner, dipendenze, rischi | ricerca e stime di ordine |
| S2 Contracted | dati, eventi, stati, flussi, errori | prototipi pianificati |
| S3 Specified | requisiti, NFR, casi limite, test, accettazione | backlog Ready |
| S4 Approved | decisioni bloccanti chiuse, review firmata | implementazione |
| S5 Verified | test e telemetria dimostrano requisiti | release candidate |

Nessun documento S0/S1 è implementation-ready.

## Struttura obbligatoria

### Identità e responsabilità

ID; stato S0–S5; owner; reviewer; versione; autorità; promesse/pilastri; parent; consumatori.

### Obiettivo e ambito

Risultato per giocatore/team; inclusioni; esclusioni; livelli geografici e temporali; scope demo/futuro.

### Requisiti

- **FR-xxx:** comportamento funzionale osservabile.
- **NFR-xxx:** qualità misurabile: prestazioni, affidabilità, sicurezza, accessibilità, manutenibilità.
- **HIS-xxx:** vincolo storico con periodo, luogo e provenienza.
- **CON-xxx:** vincolo progettuale/tecnico.
- **ACC-xxx:** criterio di accettazione collegato.

Ogni requisito usa DEVE/DOVREBBE/PUÒ, ha owner, priorità e metodo di verifica.

### Contratto del sistema

| Campo | Contenuto |
|---|---|
| Possiede | stato per cui il sistema è unica autorità |
| Legge | stato altrui senza modificarlo |
| Modifica | solo tramite API/comando del proprietario |
| Input | comandi, query, configurazione, eventi |
| Output | risultati, query, stato derivato, eventi |
| Eventi prodotti | ID evento, payload, ordine, persistenza |
| Eventi ascoltati | ID evento, reazione, idempotenza |
| Consumatori | sistemi che dipendono dal contratto |
| Documenti impattati | aggiornamenti obbligatori al cambio |

### Comportamento

Entità; invarianti; stati; transizioni; flusso principale; flussi alternativi; errori; recovery; casi limite.

### Dati e persistenza

Schema concettuale; identità; lifecycle; retention; snapshot/eventi; migrazione; ricostruzione; privacy.

### Qualità operativa

Configurabilità; bilanciamento; prestazioni; scalabilità L0–L4; determinismo; osservabilità; modularità; sicurezza; accessibilità.

### Delivery

Priorità; complessità T-shirt con driver; dipendenze bloccanti; rischi; strategia test; criteri di accettazione; Definition of Done.

## Convenzioni di identità

- Sistema: SYS-[DOM]-NNN.
- Requisito: [SYS]-FR-001, NFR-001, HIS-001, CON-001.
- Evento: EVT.[Dominio].[Nome].vMajor.
- Comando: CMD.[Dominio].[Verbo].vMajor.
- Query: QRY.[Dominio].[Nome].vMajor.
- Stato: ST.[Dominio].[Nome].
- Configurazione: CFG.[Dominio].[Nome].

Gli identificatori restano stabili quando cambia il testo; una rottura del contratto incrementa la major dell'evento/comando.

## Priorità

P0 Foundation; P1 Vertical Slice Core; P2 Supporting; P3 Expansion; P4 Future Analysis. La priorità non esprime l'ordine esatto nel backlog, ma la conseguenza della mancata consegna.

## Complessità

| Classe | Driver |
|---|---|
| XS | locale, nessuna persistenza, pochi consumatori |
| S | un dominio, persistenza semplice |
| M | più stati/consumer, tooling e test integrati |
| L | cross-system, migrazione, performance o contenuti elevati |
| XL | rischio architetturale, ricerca/prototipo necessario |

XL deve essere scomposto o preceduto da discovery.

## Gestione errori

Ogni sistema classifica: input invalido; precondizione fallita; conflitto; risorsa mancante; timeout/budget; dato corrotto; versione incompatibile; dipendenza indisponibile. Deve dichiarare fail-safe/fail-soft, retry, compensazione, logging e feedback al giocatore quando pertinente.

## Strategia di test minima

Unità/regole; contratti; integrazione; proprietà/invarianti; determinismo; persistenza; performance; soak; contenuti/dati; accessibilità; scenari end-to-end; migrazione.

## Definition of Done documentale S3

- Tutte le sezioni applicabili sono sostanziali.
- Nessun requisito senza verifica.
- Ownership di dati ed eventi non confligge con le matrici.
- Errori e casi limite coprono failure mode principali.
- Budget o metodo per ottenerli sono definiti.
- Decisioni bloccanti sono risolte o impediscono esplicitamente S4.
- Link, ADR, rischi e documenti impattati sono aggiornati.

## Flusso di promozione

~~~mermaid
flowchart LR
    S0["S0 Placeholder"] --> S1["S1 Framed"]
    S1 --> S2["S2 Contracted"]
    S2 --> S3["S3 Specified"]
    S3 --> G{"Decisioni chiuse?"}
    G -- No --> B["Blocked at S3"]
    G -- Sì --> S4["S4 Approved"]
    S4 --> S5["S5 Verified"]
~~~

## Dipendenze

- [Standard documentale](documentation-standard.md)
- [Catalogo sistemi](system-catalog.md)
- [Matrice dipendenze](system-dependency-matrix.md)

## Collegamenti agli altri documenti

- [Ownership dati](../10-technical/data/data-ownership-matrix.md)
- [Contratti evento](../10-technical/architecture/event-contracts.md)
- [Readiness](../11-production/roadmap-backlog/implementation-readiness-matrix.md)
- [Template](../appendices/templates/system-spec-template.md)

## Decisioni ancora aperte

Tool di validazione; schema machine-readable; soglie numeriche di coverage; authority finale per S4.

## Rischi

Compilazione burocratica; requisiti non misurabili; identità duplicate; contratti troppo precoci; false stime di complessità.

## Criteri di accettazione

Una feature review può individuare senza interpretazione owner, stato, input/output, failure mode, requisiti e test.

## Definition of Done

Standard approvato, template aggiornato e usato dai sistemi fondazionali.

## TODO

- Automatizzare lint e metadata quando saranno autorizzati strumenti.
- Riesaminare dopo tre promozioni S3.
