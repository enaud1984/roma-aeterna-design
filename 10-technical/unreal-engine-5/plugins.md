# Governance dei plugin

## Scopo

Definire plugin first-party, engine e terzi, con approvazione, versioning, sicurezza e fallback.

## Descrizione

Un plugin è un confine di capability/deployment, non una cartella per ogni classe. Dipendenze engine/terze parti sono liabilities gestite.

## Ambito

Plugin runtime/editor/developer, built-in UE, first-party RA, marketplace/source, licenze, upgrade e rimozione.

## Classi e gate

| Classe | Gate |
|---|---|
| first-party runtime | owner, API, grafo aciclico, tests, packaging |
| first-party editor | separazione shipping, tooling/validation |
| built-in Stable | versione baseline, benchmark, piattaforme |
| Beta/Experimental | adapter, flag, spike, fallback, ADR; mai core implicito |
| third-party | necessità, licenza, security, source access, support, exit plan |

Registro obbligatorio: nome/versione, stato Epic/vendor, moduli, owner, dipendenti, piattaforme, licenza, CVE/update, performance, save impact, fallback e data review. Plugin disabilitato non deve corrompere contenuti/save.

## Strategia iniziale

Valutare GameplayTags, Enhanced Input, StateTree, MassEntity/MassGameplay, SmartObjects, CommonUI/MVVM, MetaSounds, DataRegistry e World Partition features. “Built-in” non significa approvato. World Partition baseline; navmesh partizionata resta condizionale se sperimentale.

## Test e Definition of Done

Clean checkout/build/package, plugin on/off, platform matrix, upgrade smoke, asset reference, save compatibility e security/license review. DoD: registro e ADR P0 approvati, nessuna dipendenza senza exit plan.

## Dipendenze

- [Moduli](modules.md)
- [Fonti UE](official-sources.md)
- [Dependency security](../security/dependency-security.md)

## Collegamenti agli altri documenti

- [Engine upgrades](engine-upgrades.md)
- [Build pipeline](../pipelines/build-pipeline.md)
- [Rischi](../../11-production/risk-register.md)

## Decisioni ancora aperte

- Lista plugin P0 e baseline UE.
- Ammissibilità marketplace/closed-source.

## TODO

- Creare registro plugin e checklist ADR.
- Definire cadenza aggiornamenti/security review.
