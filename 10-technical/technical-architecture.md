# Architettura tecnica — requisiti e principi

**ID:** TEC-001
**Stato:** Draft
**Nota:** questo documento non seleziona engine e non contiene codice.

## Driver

Persistenza di molti agenti; simulazione multi-risoluzione; streaming urbano; determinismo diagnostico; authoring data-driven; provenienza storica; salvataggi versionabili; strumenti di osservazione; espansione regionale; accessibilità.

## Domini logici

Tempo/eventi; entità e identità; spazio/streaming; agenti; economia; relazioni/conoscenza; istituzioni; contenuti; presentazione; persistenza; strumenti/telemetria. I confini definitivi seguiranno workshop e prototipi tecnici autorizzati dopo la Game Bible.

## Requisiti architetturali

- La simulazione canonica non dipende dalla presenza di rappresentazione grafica.
- Identificatori persistenti sopravvivono a streaming e salvataggio.
- Dati storici e parametri di bilanciamento sono versionati e validabili.
- Eventi importanti hanno causalità interrogabile.
- Sistemi supportano clock diversi e lavoro budgetizzato.
- Contenuti dichiarano prerequisiti e side effect.
- Migrazioni di salvataggio e compatibilità sono progettate prima della produzione di massa.

## Decisioni rinviate

Engine, linguaggi, ECS/OOP, database, networking, piattaforme, toolchain e formati non sono scelti in questa fase. Ogni scelta dovrà confrontare esigenze in [performance](performance-budgets.md), [dati](data-model.md) e produzione.

## Qualità

Testabilità, osservabilità, recovery, sicurezza dei contenuti, riproducibilità e costo di iterazione hanno lo stesso rango delle prestazioni. Una simulazione che raggiunge il frame budget ma non può spiegare un collasso non è production-ready.

## Scopo

Conservare e sviluppare la responsabilità canonica descritta da questo documento all'interno della Game Bible.

## Descrizione

Il contenuto preesistente costituisce la baseline del dominio. Questa sezione normalizza il documento secondo il contratto minimo della nuova architettura senza sostituirne le informazioni.

## Ambito

Il perimetro è quello definito nelle sezioni precedenti; implementazione e asset restano esclusi finché non saranno autorizzati da milestone e decisioni formali.

## Dipendenze

- [Standard documentale](../00-governance/documentation-standard.md)
- [Visione creativa](../01-vision/creative-vision.md)

## Collegamenti agli altri documenti

- [Indice generale](../README.md)
- [Mappa documentale](../00-governance/documentation-map.md)
- [Registro decisioni](../00-governance/decision-log.md)
- [Questioni aperte](../00-governance/open-questions.md)

## Decisioni ancora aperte

- Owner e reviewer nominali.
- Stato di approvazione e profondità richiesta dalla roadmap documentale.
- Eventuali confini da riallineare con i nuovi sottodomini canonici.

## TODO

- Collegare il contenuto ai nuovi documenti specializzati pertinenti.
- Assegnare ownership, versione e milestone.
- Aggiungere requisiti, fonti, rischi, test e Definition of Done durante l'approfondimento.
