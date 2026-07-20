# Policy C++ e Blueprint

## Scopo

Stabilire dove vive la logica e come designer ed engineering collaborano senza duplicare autorità o creare dipendenze fragili.

## Descrizione

C++ definisce contratti, invarianti e percorsi critici; Blueprint assembla presentazione e contenuto bounded tramite API intenzionali. La scelta dipende da ownership, testabilità, frequenza e rischio, non da preferenza personale.

## Ambito

Classi, componenti, subsystem, Blueprint/AnimBP/Widget, eventi, dati, test, conversione e review.

## Matrice obbligatoria

| Responsabilità | C++ | Blueprint |
|---|---:|---:|
| ID, schema, serialization, migrazione | sì | no |
| regole dominio, transazioni, scheduler | sì | no |
| Mass processor/hot path | sì | no |
| API e base class stabili | sì | consumo |
| assemblaggio Actor/component | base | sì |
| feedback, VFX, audio, UI, AnimGraph | adapter | sì |
| flusso locale di set-piece | guardrail | sì, bounded |
| valori di tuning | schema/validation | Data Asset/Table, non graph literals |
| logica globale/persistente | sì | vietata |

## Regole

- Blueprint non scrive proprietà private di dominio: invia comando e gestisce risultato.
- Nessun Level Blueprint per logica sistemica; solo glue locale eccezionale con owner.
- Tick Blueprint disabilitato di default; richiede budget e review.
- Niente cast chain, hard reference cross-feature, dispatcher globale o macro library non governata.
- API `BlueprintCallable/Pure/ImplementableEvent` minime, categorizzate, documentate e null-safe.
- Data-only Blueprint solo quando ereditarietà/authoring supera il costo; altrimenti Data Asset.
- Blueprint nativization non è strategia architetturale.

## Conversione e debito

Segnali di migrazione a C++: uso cross-feature, stato persistente, performance, duplicazione, test difficile o graph complexity oltre soglia. Conversione conserva API/versione e richiede test equivalenza. Prototipo Blueprint non entra P0 senza review.

## Logging, errori e test

Blueprint riceve errori tipizzati e messaggi user-safe; log di dominio nasce in C++. Automation/headless per regole; functional tests per integrazione BP; lint per tick, casts, reference e complessità; compile/package su ogni gate.

## Dipendenze

- [Architettura](../technical-architecture.md)
- [Moduli](modules.md)
- [Componenti/subsystem](components-subsystems.md)

## Collegamenti agli altri documenti

- [Animazione](animation-system.md)
- [UI](ui-framework.md)
- [Audio](audio-framework.md)
- [Testing](../../11-production/testing/README.md)

## Definition of Done

Ogni feature P0 assegna logica a C++/BP/dati con motivo, API, test e budget; nessun Blueprint possiede stato canonico o loop globale.

## Decisioni ancora aperte

- Soglie quantitative di complessità/tick Blueprint.
- CommonUI/MVVM e strumenti lint finali.

## TODO

- Definire checklist Blueprint review e API exposure.
- Collegare ownership per disciplina.
