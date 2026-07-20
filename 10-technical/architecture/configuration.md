# Configurazione, feature flag e tuning

## Scopo

Definire gerarchia, ownership, validazione e versionamento delle impostazioni.

## Descrizione

Configurazione tecnica, tuning gameplay, definizioni storiche e preferenze utente sono categorie distinte. Ogni valore ha unità, range, default, owner e change impact.

## Ambito

`.ini`/Developer Settings futuri, Data Asset/Table, CVars, platform/build profiles, feature flag, accessibilità e migrazione.

## Gerarchia

Default versionato → piattaforma → configurazione build → profilo qualità/scalabilità → preferenza utente → override sviluppo consentito. Server/networking futuro escluso dalla demo. Gameplay storico/bilanciamento usa asset versionati; CVars solo diagnostica/performance e non alterano save senza versioning.

## Regole

- Nessun magic number fuori schema/config autorizzata.
- Range, unità e compatibilità validati al bootstrap.
- Feature sperimentali off di default in shipping e dietro adapter/fallback.
- Config che cambia semantica persistente incrementa schema/ruleset version.
- Segreti mai in Config/repository/log.
- Preferenze accessibilità sono locali, migrabili e ripristinabili.

## Errori e test

Missing/invalid usa default sicuro se semanticamente valido, altrimenti fail-fast di bootstrap con messaggio. Test precedence, range, piattaforme, packaging, flag on/off, migration e determinismo ruleset.

## Dipendenze

- [Dati UE5](../unreal-engine-5/data-assets-tables.md)
- [Schema versioning](../data/schema-versioning.md)
- [Scalabilità](../performance/scalability.md)

## Collegamenti agli altri documenti

- [Logging](logging-errors.md)
- [Gameplay Tags](../unreal-engine-5/gameplay-tags.md)
- [Save](../save-system/save-architecture.md)

## Definition of Done

Registro P0 di chiavi/asset con tipo, unità, range, owner, default, layer, restart/hot reload, save impact e test.

## Decisioni ancora aperte

- Formato del ruleset manifest e policy hot reload.
- Feature flag service locale.

## TODO

- Creare template del registro configurazioni.
- Collegare budget e profili hardware quando approvati.
