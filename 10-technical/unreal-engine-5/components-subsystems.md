# Componenti, interfacce e subsystem UE5

## Scopo

Assegnare lifetime e responsabilità evitando God Object, singleton nascosti e Actor come database.

## Descrizione

Un component rappresenta capability di un Actor caricato; un subsystem offre un servizio coerente con lifetime Engine/GameInstance/World/LocalPlayer. Le interfacce espongono contratti piccoli; i record dominio restano indipendenti.

## Ambito

Actor/Scene Component, UObject service, UE Subsystem, interface, view model, bootstrap e teardown.

## Regole di scelta

- Component: ha bisogno del lifecycle/spazio dell'Actor e può essere ricreato dal record.
- World subsystem: stato/servizio per mondo, inclusi clock/scheduler/stream bridge.
- GameInstance subsystem: sessione, cataloghi e save coordinator; niente stato di singolo world senza ID.
- LocalPlayer subsystem: input, accessibilità e view state locale.
- Plain C++/UObject: logica testabile senza lifetime globale.
- Interface: capability richiesta, non contenitore di utility.

Componenti candidati: interaction target, presentation inventory, combat presentation, audio emitter, streaming source adapter. Subsystem candidati: time, simulation scheduler, event dispatcher, identity repository, content, save, UI coordination. Nessun subsystem accede direttamente ai privati di tutti i domini.

## Lifecycle e errori

Bootstrap ordinato per dependency graph; readiness esplicita; world creation/PIE multiple, travel, teardown e hot reload considerati. Accesso prima di ready restituisce errore retryable; shutdown idempotente; weak/soft reference per Actor streamabili.

## Test e performance

Unit test servizi senza world, automation con test world, PIE multi-world, travel, unload/reload Actor, dependency injection/fake adapters e leak test. Tick off by default; aggregazione work queue nei subsystem con budget.

## Dipendenze

- [Architettura](../technical-architecture.md)
- [Moduli](modules.md)
- [Policy C++/BP](cpp-blueprint-policy.md)

## Collegamenti agli altri documenti

- [Mappa sistemi](system-implementation-map.md)
- [Eventi](../architecture/event-architecture.md)
- [Logging](../architecture/logging-errors.md)

## Definition of Done

Ogni servizio P0 ha lifetime, owner, bootstrap/teardown, API, errori, thread/tick policy e test; nessun Actor/component è unica copia dello stato persistente.

## Decisioni ancora aperte

- Dependency injection/composition pattern concreto UE.
- Granularità dei subsystem P0.

## TODO

- Creare future lifecycle matrix e sequence diagrams per bootstrap/save/travel.
