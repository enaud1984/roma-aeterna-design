# Mandato della Game Bible

**ID:** VIS-GDB-001
**Stato:** Approved — Baseline 1.0
**Owner:** Game Director / Technical Writer

## Scopo

Definire funzione, autorità, pubblico, lifecycle e criteri di qualità della Game Bible.

## Descrizione

Contratto operativo per creazione, revisione, approvazione, sostituzione e audit della documentazione.

## Obiettivo

Fare della documentazione la fonte condivisa che collega intenzione creativa, evidenza storica, comportamento sistemico, requisiti tecnici, contenuti, produzione e test.

## Ambito

La Bible include documenti approvati e draft tracciati. Non contiene codice, asset sorgente, dati personali, contratti commerciali riservati o discussioni effimere.

## Pubblico

Game/Narrative/World Design; History; Art/Animation/Audio; UX/Accessibility; Engineering/Technical Art; QA; Production; Localization; Legal e consulenti pertinenti.

## Gerarchia di autorità

1. Visione e pilastri.
2. Decision record approvati.
3. Specifiche canoniche di dominio.
4. Scope della milestone.
5. Esempi, backlog e note.

Un documento inferiore non può contraddire uno superiore. Se la contraddizione è intenzionale, serve ADR e aggiornamento della catena.

## Regole

- Un argomento ha un solo documento canonico.
- Le sintesi linkano, non copiano requisiti.
- “Draft” non costituisce commitment.
- Ogni requisito usa linguaggio verificabile.
- Ogni affermazione storica significativa possiede provenienza.
- Ogni sistema dichiara dipendenze, eventi, dati e test.
- Le decisioni superate rimangono auditabili.

## Stati e flusso

~~~mermaid
stateDiagram-v2
    [*] --> Draft
    Draft --> Review
    Review --> Approved
    Review --> Draft: modifiche richieste
    Approved --> Superseded: nuova decisione
    Superseded --> [*]
~~~

| Stato | Autorità | Azione consentita |
|---|---|---|
| Draft | esplorativa | ricerca e discussione |
| Review | candidata | stime preliminari |
| Approved | vincolante | pianificazione e implementazione autorizzata |
| Superseded | storica | audit, non nuovo lavoro |
| Archived | nulla | consultazione |

## Flusso principale

Proposta → owner → analisi impatto → aggiornamento link e registri → review interdisciplinare → approvazione → baseline → audit.

## Flussi alternativi

- **Correzione storica urgente:** marcatura immediata, blocco degli usi, review e ADR se cambia il design.
- **Conflitto tra documenti:** prevale la gerarchia; si apre un issue documentale.
- **Decisione reversibile:** si registra comunque se influenza più discipline.
- **Informazione mancante:** si crea una domanda con owner e criterio di chiusura.

## Dati necessari

ID, titolo, stato, owner, reviewer, versione, data, genitori, dipendenti, ADR, fonti, rischi, TODO e criteri di completamento.

## Interazioni con altri sistemi

La Bible alimenta backlog, pianificazione, authoring, test, onboarding, change control e comunicazione esterna. Il marketing può usare soltanto claim compatibili con promesse e stato dello scope.

## Esempio pratico

Una proposta di “fast travel gratuito” viene valutata contro tempo, logistica e mondo autonomo. Se accettata come assistenza, il documento precisa quali costi simulativi continuano, quale tempo passa e come il personaggio conosce la destinazione.

## Casi limite

- Un README è indice, non fonte canonica di dettaglio.
- Un diagramma non sostituisce regole testuali.
- Un valore numerico di esempio non è target finché non marcato requisito.
- L'assenza di opposizione non equivale ad approvazione.

## Dipendenze

- [Standard](../../00-governance/documentation-standard.md)
- [Decision log](../../00-governance/decision-log.md)
- [Mappa](../../00-governance/documentation-map.md)

## Collegamenti agli altri documenti

- [Visione](../creative-vision.md)
- [Feature taxonomy](feature-taxonomy.md)
- [Roadmap documentale](../../11-production/roadmap-backlog/documentation-roadmap.md)

## Decisioni ancora aperte

Strumento futuro per metadata e validazione automatica; cadence formale delle review; persone nominali.

## Rischi

Documentazione obsoleta; owner assenti; sovraspecificazione prematura; review solo disciplinare; link validi ma semantica incoerente.

## Criteri di completamento

- Gerarchia e workflow sono applicati.
- Ogni documento ha owner e stato.
- Contraddizioni e requisiti orfani sono rilevati per milestone.
- Un nuovo membro individua la fonte canonica senza assistenza.

## TODO

- Assegnare owner nominali.
- Definire calendario degli audit.
