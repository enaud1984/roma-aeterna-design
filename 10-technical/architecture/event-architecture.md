# Architettura degli eventi

**System ID:** SYS-EVT

**Stato:** S4 — Ready documentale

**Priorità / complessità:** P0 / L

## Scopo

Fornire trasporto, ordinamento locale, versionamento, osservabilità e controllo del carico per i fatti prodotti dai sistemi, senza diventare proprietario dello stato di dominio.

## Descrizione

SYS-EVT separa produttori e consumatori. Riceve eventi già autorizzati, ne valida la busta, assegna l'ordine nel relativo stream, li consegna secondo policy e conserva soltanto quelli previsti dal journal. Il catalogo semantico è nei [contratti degli eventi](event-contracts.md).

## Ambito

Inclusi dispatch, subscription, deduplicazione, quarantena, replay selettivo, back-pressure e tracing causale. Esclusi autorizzazione dei comandi, transazioni di dominio, logica di gameplay e notifica UI finale.

## Requisiti funzionali

| ID | Requisito | Priorità | Accettazione |
|---|---|---:|---|
| FR-EVT-001 | Validare busta e versione prima della registrazione | P0 | ACC-EVT-001 |
| FR-EVT-002 | Ordinare gli eventi per stream di aggregato | P0 | ACC-EVT-002 |
| FR-EVT-003 | Supportare consumer idempotenti, retry e quarantena | P0 | ACC-EVT-003 |
| FR-EVT-004 | Applicare retention diversa per classe | P1 | ACC-EVT-004 |
| FR-EVT-005 | Esporre causalità e correlazione alla diagnostica | P1 | ACC-EVT-005 |

## Requisiti non funzionali

- `NFR-EVT-001`: nessuna perdita silenziosa di eventi critici.
- `NFR-EVT-002`: il sistema deve applicare back-pressure prima di superare memoria configurata.
- `NFR-EVT-003`: replay e live dispatch devono conservare l'ordine per aggregato.
- `NFR-EVT-004`: payload e subscription non devono dipendere da oggetti presentazionali.

## Vincoli progettuali e storici

Il bus non crea causalità storica: preserva tempo, luogo, fonte e confidenza dichiarati dal produttore. Una voce appresa da un NPC è diversa dal fatto globale da cui può derivare.

## Dipendenze

Utilizza SYS-ID per identità, SYS-TIME per timestamp di simulazione e SYS-DBG per errori. Tutti i sistemi event-driven dipendono dai suoi contratti; nessuno può usarlo per aggirare SYS-AUTH.

## Input, output e dati

Input: evento proposto, subscription, ack e richiesta di replay. Output: evento consegnato, rifiuto tipizzato, metrica e record di quarantena. Possiede offset, subscription, deduplication key e journal tecnico; legge schemi e tempo; non modifica aggregati di dominio.

## Eventi generati e ricevuti

Genera diagnostica di rifiuto, ritardo e quarantena. Riceve tutti gli eventi registrabili dichiarati nel catalogo, ma li tratta come payload opachi dopo la validazione del contratto.

## Stati e transizioni

Proposto → Validato → Registrato → Consegnato → Confermato/Quarantena → Archiviato. La macchina canonica e le policy fuori ordine sono nei [contratti](event-contracts.md).

## Flussi principali e alternativi

Flusso nominale: validazione, assegnazione offset, append se richiesto, fan-out, ack. Duplicato: deduplicazione senza secondo effetto. Consumer indisponibile: retry limitato. Schema sconosciuto: quarantena. Saturazione: coalescenza solo per classi autorizzate, poi pausa controllata.

## Casi limite e gestione degli errori

Riavvio tra append e consegna, evento tardivo, consumer rimosso, dipendenza ciclica, tempesta dopo time-skip e riferimento tombstoned devono produrre esiti deterministici e osservabili. Un evento registrato non viene cancellato per “correggerlo”: si usa compensazione versionata.

## Persistenza, configurabilità e bilanciamento

Persistono journal selettivo, offset, quarantena e checkpoint di replay. Retention, batch, retry, priorità, coalescenza e soglie sono configurabili per classe; i fatti critici non sono bilanciabili tramite perdita casuale.

## Prestazioni, scalabilità e modularità

Il carico scala per partizione logica e livello di simulazione. I budget assoluti attendono Q-003; fino ad allora sono obbligatori profili di carico, metriche di backlog e prove di degradazione. Dispatch, storage e schema registry restano sostituibili dietro contratti stabili.

## Priorità, complessità e rischi

P0 perché ogni sistema temporale e persistente lo usa. Complessità L per ordinamento, replay e failure recovery. Rischi: event storm, accoppiamento semantico nascosto, journal infinito, duplicati non idempotenti e leakage di conoscenza.

## Strategie di test

Contract test per schema; duplicati/fuori ordine; crash-recovery; replay; back-pressure; soak; quarantena; isolamento della conoscenza; compatibilità di versione.

## Criteri di accettazione

- `ACC-EVT-001`: un payload invalido non viene registrato né consegnato.
- `ACC-EVT-002`: eventi concorrenti dello stesso aggregato hanno ordine stabile.
- `ACC-EVT-003`: una riconsegna non duplica l'effetto del consumer.
- `ACC-EVT-004`: la retention rispetta la classe senza perdere fatti critici.
- `ACC-EVT-005`: un esito è tracciabile fino a causa e correlazione.

## Definition of Done

Requisiti, contratti, ownership, failure mode, retention, test e budget relativi sono approvati; consumer P0 hanno contract test progettati; nessuna decisione tecnica differita altera la semantica.

## Collegamenti agli altri documenti

- [Standard di specifica](../../00-governance/system-specification-standard.md)
- [Matrice delle dipendenze](../../00-governance/system-dependency-matrix.md)
- [Proprietà dei dati](../data/data-ownership-matrix.md)
- [Readiness](../../11-production/roadmap-backlog/implementation-readiness-matrix.md)

## Decisioni ancora aperte

- Tecnologia concreta di dispatch e storage, non bloccante prima dell'architettura UE5 esecutiva.
- Budget numerici e retention della demo, bloccati da piattaforme e durata obiettivo.

## TODO

- Collegare gli eventi P2–P4 quando i relativi sistemi raggiungono S2.
- Definire il test plan quantitativo dopo la chiusura di Q-003.
