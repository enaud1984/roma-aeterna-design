# Gameplay Tags e vocabolario runtime

## Scopo

Governare etichette gerarchiche condivise senza usarle come database, ID entità o sostituto di tipi forti.

## Descrizione

I tag classificano capacità, stato, evento e requisito per query componibili. Le sorgenti sono separate per dominio e sottoposte a owner/review.

## Ambito

Namespace, sorgenti config/C++, redirect, query, versionamento, localizzazione display e validazione.

## Namespace iniziali

`RA.State.*`, `RA.Capability.*`, `RA.Action.*`, `RA.Event.*`, `RA.Item.*`, `RA.Status.*`, `RA.Place.*`, `RA.Content.*`, `RA.UI.*`, `RA.Audio.*`. Il prefisso definitivo è soggetto a naming ADR. Tag di evento non sostituisce payload/event contract.

## Regole

- Definizione centralizzata per sorgente dominio con commento, owner e semantica.
- Tag stabile nei save/eventi; rename tramite redirect e migration test.
- Nessun dato numerico, persona, città concreta o testo localizzato nel path.
- Native tag per contratti core/hot path; config/table solo con governance.
- Query complesse nominate e testate; niente string comparison.
- Display name/localizzazione separati dal tag tecnico.

## Errori e test

Tag sconosciuto, deprecato, orfano, duplicato semanticamente o usato fuori namespace fallisce validation. Test redirect/save, packaging, query, hot reload limitations e asset reference scan.

## Dipendenze

- [Dati UE5](data-assets-tables.md)
- [Event contracts](../architecture/event-contracts.md)
- [Naming asset](../pipelines/asset-naming.md)

## Collegamenti agli altri documenti

- [Fonti UE5](official-sources.md)
- [Configurazione](../architecture/configuration.md)
- [Data validation](../data/data-validation.md)

## Definition of Done

Dizionario P0 approvato, namespace/owner/redirect policy e test stabiliti; nessun tag usato come ID o stato autoritativo senza owner.

## Decisioni ancora aperte

- Prefisso e sorgenti definitive.
- Tag nativi vs config per ciascun dominio.

## TODO

- Produrre futuro registry dei tag con change impact.
- Collegare lint CI.
