# Principi e convenzioni architetturali obbligatorie

## Scopo

Definire regole verificabili per modularità, testabilità, performance, manutenibilità, estendibilità e separazione delle responsabilità.

## Descrizione

Questi principi sono architecture fitness constraints: una feature che li viola non è pronta anche se funziona visivamente.

## Ambito

Codice futuro, Blueprint, asset, dati, eventi, configurazione, test, logging, documentazione e dipendenze.

## Principi

1. Autorità unica per dato; proiezioni ricostruibili.
2. Dependency inversion sui confini; grafo moduli aciclico.
3. Comandi espliciti, query read-only, eventi immutabili.
4. Stato persistente indipendente da Actor/Widget/Mass handle.
5. LOD conserva invarianti e causalità.
6. Event-driven prima di polling/tick; budget per ogni clock.
7. Fallimento tipizzato, recovery e idempotenza.
8. Configurazione/data-driven con schema e provenance.
9. Test al livello più basso possibile; integrazione per adapter.
10. Feature sperimentale solo dietro adapter, flag, benchmark e fallback.

## Convenzioni obbligatorie

| Area | Regola |
|---|---|
| nomi | inglese tecnico nel software; prefissi UE+RA; niente abbreviazioni non registrate |
| cartelle | per dominio/feature e owner; Runtime/Editor/Tests separati |
| classi | una responsabilità; lifecycle esplicito; API pubblica minima |
| componenti | capability di Actor caricato, mai unica persistenza |
| interfacce | verbi/capacità bounded; niente utility dump |
| eventi | passato, versionati, correlation/causation, producer owner |
| configurazione | default→platform→build→quality→dev; validazione all'avvio |
| errori | result tipizzato; assert per bug, non input utente/contenuto |
| test | naming Given_When_Then concettuale; deterministici e isolabili |
| documentazione | Scopo/owner/API/dati/eventi/failure/performance/test/change impact |

## Architecture fitness tests

Dependency allowlist, forbidden includes/references, naming/path lint, schema/tag/event registry validation, no runtime→Editor, no hard cross-feature content, save compatibility, Blueprint tick/cast/reference scan e documentation coverage.

## Dipendenze

- [Architettura](../technical-architecture.md)
- [Moduli](../unreal-engine-5/modules.md)
- [Standard di sistema](../../00-governance/system-specification-standard.md)

## Collegamenti agli altri documenti

- [Logging](logging-errors.md)
- [Configurazione](configuration.md)
- [Project structure](../unreal-engine-5/project-structure.md)
- [Testing](../../11-production/testing/README.md)

## Definition of Done

Ogni principio ha controllo manuale o automatico pianificato, owner e waiver via ADR; nessuna eccezione silenziosa.

## Decisioni ancora aperte

- Tool concreto per fitness tests e lint Blueprint/asset.
- Prefissi e lingua dei commenti/documentazione API definitivi.

## TODO

- Preparare checklist review e waiver template.
- Collegare CI futura senza implementarla.
