# Data Assets, Data Tables e registri

## Scopo

Assegnare il formato UE corretto a definizioni, dataset, riferimenti e configurazioni senza confonderli con stato di partita.

## Descrizione

Schema in C++; contenuto read-only in asset validati; stato runtime in record persistenti. Soft reference e Asset Manager controllano caricamento.

## Ambito

Data Asset, Primary Data Asset, Data Table, Curve Table, Data Registry candidato, String Table, config e asset bundle.

## Policy

| Strumento | Uso | Divieto |
|---|---|---|
| Data Asset | definizione ricca singola con riferimenti | stato mutevole/save |
| Primary Data Asset | identità, bundle e load/unload Asset Manager | singleton globale arbitrario |
| Data Table | righe omogenee, import/export e bilanciamento | gerarchie complesse/UObject state |
| Curve Table | curve di tuning con unità/versione | logica nascosta |
| Data Registry | accesso read-only/caching multi-source, se approvato | dipendenza P0 senza spike |
| String Table | testo localizzabile stabile | dialogo hard-coded |
| Config | environment/build/default tecnici | contenuto storico massivo |

Ogni schema include stable ID, schema version, provenance, validità data/area, owner, tags e validation status. Row name non è l'unico ID persistente. Nessun hard reference da core a contenuti Pompei.

## Caricamento e fallback

Catalogo bootstrap minimo → resolve ID → richiesta asincrona bundle → validate → cache bounded → release. Asset mancante produce placeholder diagnostico o feature unavailable, mai crash/salvataggio corrotto. Save conserva ID/versione, non serializza l'asset.

## Test e performance

Validation editor/commandlet futura, duplicate ID, riferimenti, unità, provenance, tag, import/export round-trip, async load, memory residency e packaging. Cambi schema richiedono migration e compatibility test.

## Dipendenze

- [Data architecture](../data/data-architecture.md)
- [Content data](../data/content-data.md)
- [Asset management](../pipelines/asset-management.md)
- [Gameplay Tags](gameplay-tags.md)

## Collegamenti agli altri documenti

- [Fonti UE5](official-sources.md)
- [Schema versioning](../data/schema-versioning.md)
- [Configurazione](../architecture/configuration.md)

## Definition of Done

Ogni dataset P0 ha formato, schema, ID, provenance, bundle, validation, fallback, memory budget e migration impact.

## Decisioni ancora aperte

- Adozione Data Registry e divisione Data Asset/Table per cataloghi P0.
- Strategia patch/DLC futura, esclusa dalla demo.

## TODO

- Creare matrice dataset→formato→owner.
- Definire future validation rules, senza asset.
