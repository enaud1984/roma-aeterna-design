# Logging, errori e recovery

## Scopo

Rendere ogni anomalia diagnosticabile senza crash evitabili, rumore ingestibile o esposizione di dati.

## Descrizione

Logging descrive fatti tecnici; domain trace spiega causalità di gioco; error result guida recovery. Le tre cose non vengono confuse.

## Ambito

Categorie, severità, contesto, correlation, rate limit, assert, error types, recovery, crash, privacy e test.

## Contratto log

Campi: timestamp monotonic/world time, build/ruleset, category, severity, message ID, entity IDs redatti, world, thread, correlation/causation, result e context bounded. Categorie per modulo (`RA.Sim`, `RA.Economy`, ecc.); testo strutturato localmente, mai stringhe di UI.

## Classi di errore

| Classe | Azione |
|---|---|
| Rejected | input/comando non valido; nessuna mutazione |
| Retryable | risorsa/streaming non pronto; backoff e timeout |
| Degraded | fallback autorizzato con segnale |
| Corrupt | quarantena, rollback/recovery, blocco save sovrascrivente |
| Programmer invariant | ensure/assert in dev, crash policy controllata |
| Fatal bootstrap | stop chiaro prima di stato parziale |

Transazioni atomiche e idempotency key evitano doppi effetti. Errori non vengono inghiottiti; UI riceve codici user-safe. Rate limiting/coalescenza preservano il primo, conteggio e contesto finale.

## Privacy e retention

Niente token, percorsi sensibili, contenuto personale o dump illimitati. Retention per build, rotazione, opt-in telemetria locale e export esplicito. Crash artifact policy separata.

## Test e Definition of Done

Fault injection su streaming, asset, save, evento, config e teardown; verificare rollback, log singolo, correlation e messaggio UI. DoD: catalogo errori P0, owner, recovery, severity, test e runbook.

## Dipendenze

- [Observability](observability.md)
- [Event architecture](event-architecture.md)
- [Recovery save](../save-system/corruption-recovery.md)

## Collegamenti agli altri documenti

- [Configurazione](configuration.md)
- [Privacy](../security/privacy.md)
- [Debugger](../tools/simulation-debugger.md)

## Decisioni ancora aperte

- Backend/file format locale e retention numerica.
- Crash reporting/provider futuro.

## TODO

- Creare catalogo error codes e categorie.
- Definire runbook prima dell'implementazione.
