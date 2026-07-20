# Struttura del progetto Unreal Engine 5

## Scopo

Definire layout logico, ownership e regole di collocazione future senza creare il progetto UE.

## Descrizione

Codice e contenuti sono separati per responsabilità. Il progetto game funge da composition root; sistemi riutilizzabili sono plugin first-party. Pompei è contenuto, non dipendenza dei domini core.

## Ambito

Directory future `Source`, `Plugins`, `Content`, `Config`, `Tests`, `Build` e documentazione; ownership, naming e dipendenze. Nessuna directory Unreal viene creata in questa fase.

## Layout approvato concettualmente

```text
RomaAeterna/
  Config/                 # configurazione runtime/editor, tag per sorgente
  Content/
    RA/Core/              # composition/presentation comuni
    RA/Pompeii/           # mappe, Data Layers, contenuto vertical slice
    RA/UI/ Audio/ Art/    # asset per disciplina e feature
    RA/Dev/               # test maps e placeholder, esclusi shipping
  Source/
    RomaAeterna/          # bootstrap/composition root minimale
    RomaAeternaEditor/    # integrazioni editor progetto
  Plugins/RA/
    Foundation/ Simulation/ World/ Population/ Economy/
    Institutions/ Content/ Interaction/ Combat/ Presentation/
    Persistence/ Developer/
  Tests/                  # dataset e piani esterni, se necessari
  Build/                  # configurazione packaging/CI approvata
```

## Regole di collocazione

- Un asset appartiene al plugin/feature che lo possiede; riferimenti inversi vietati.
- `Content/RA/Pompeii` può dipendere da core, mai il contrario.
- Nessun contenuto gameplay in `/Game/Developers` per release; `/Dev` è placeholder tracciabile.
- Mappe World Partition usano One File Per Actor, Data Layers nominate e HLOD policy.
- Configurazione per plugin/tag separata; segreti e credenziali mai nel repository.
- Redirector, reference cycles e asset senza owner falliscono validazione.

## Naming obbligatorio

| Elemento | Regola | Esempio concettuale |
|---|---|---|
| modulo/plugin | `RomaAeterna<Domain>` / `RA<Domain>` | `RomaAeternaEconomy` |
| C++ UObject/Actor | prefisso UE + `RA` | `URAEconomySubsystem` |
| struct/enum/interface | `FRA`, `ERA`, `IRA` | `FRAEntityId` |
| Blueprint | `BP_RA_<Role>` | presentazione bounded |
| Data Asset/Table | `DA_RA_`, `DT_RA_` | definizione/versione |
| map/Data Layer | `MAP_RA_`, `DL_RA_` | luogo/funzione/stato |
| widget/animation/audio | `WBP_RA_`, `ABP_RA_`, prefissi pipeline | funzione, non persona autore |
| test | dominio + comportamento + esito | leggibile e stabile |

I prefissi definitivi sono centralizzati in asset naming; niente abbreviazioni locali non registrate.

## Ownership e dipendenze

Ogni cartella/plugin ha `README`, owner, reviewer, API pubblica, test e matrice asset. Dipendenze runtime dichiarate separatamente da editor/developer. Circular dependency e reference hard cross-feature sono errori di build/validation.

## Configurazione e varianti

Default versionati → piattaforma → build configuration → profilo qualità → override sviluppo. Parametri gameplay/bilanciamento restano dati validati, non CVars nascosti; CVars solo diagnostica/performance con owner.

## Casi limite e migrazione

Asset spostato, plugin rinominato, map reference, redirector, tag eliminato e split/merge modulo richiedono piano di migrazione e compatibilità save. Nessun bulk move senza reference audit.

## Dipendenze

- [Moduli](modules.md)
- [Plugin](plugins.md)
- [Asset naming](../pipelines/asset-naming.md)
- [Asset management](../pipelines/asset-management.md)

## Collegamenti agli altri documenti

- [Policy C++/Blueprint](cpp-blueprint-policy.md)
- [World Partition](world-partition.md)
- [Configurazione](../architecture/configuration.md)
- [Build pipeline](../pipelines/build-pipeline.md)

## Test e Definition of Done

Lint path/naming, dependency graph, redirector/reference audit, packaging test e ownership coverage. DoD quando layout, prefissi, plugin P0 e regole CI sono approvati senza creare file UE.

## Decisioni ancora aperte

- Granularità plugin vs moduli e prefissi definitivi.
- Policy contenuti condivisi e localizzazione asset culturali.

## TODO

- Collegare matrice owner/team quando noto.
- Preparare validatori, senza implementarli ora.
