# Governance documentale

Questa area definisce come la Game Bible rimane coerente mentre cresce. La documentazione è un sistema di requisiti vivo, non una collezione di note.

## Gerarchia di autorità

1. [Visione creativa](../01-vision/creative-vision.md) — promessa e identità del prodotto.
2. [Pilastri di design](../01-vision/design-pillars.md) — criteri per accettare o respingere una soluzione.
3. Specifiche di dominio — comportamento atteso dei sistemi.
4. [Decision log](decision-log.md) — risoluzioni contestuali e loro motivazioni.
5. [Registro domande](open-questions.md) — incertezze non ancora risolte.
6. Esempi e scenari — materiale illustrativo, non normativo salvo esplicita promozione.

In caso di conflitto prevale il documento più alto; il conflitto deve comunque diventare una voce del registro decisionale.

## Stati dei documenti

| Stato | Significato | Uso consentito |
|---|---|---|
| Draft | esplorazione incompleta | discussione, non pianificazione vincolante |
| Review | pronto a controllo incrociato | stime preliminari e prototipi documentali |
| Approved | baseline accettata | requisiti di produzione |
| Superseded | sostituito, conservato per audit | consultazione storica |
| Archived | non più applicabile | nessun nuovo lavoro |

## Ownership prevista

Ogni documento maturo avrà un **Owner** responsabile della coerenza e almeno un **Reviewer** di disciplina diversa. Le specifiche storiche richiedono revisione di consulenza storica; quelle simulativo-tecniche richiedono Game Design e Engineering; quelle sensibili richiedono anche narrative/cultural review.

## Flusso di modifica

Proposta → analisi delle dipendenze → scenario di validazione → revisione interdisciplinare → decisione → aggiornamento dei documenti collegati → changelog. Il [template di specifica](../appendices/templates/system-spec-template.md) rende esplicite le dipendenze.

## Indici operativi

- [Standard documentale](documentation-standard.md)
- [Registro decisioni](decision-log.md)
- [Domande aperte](open-questions.md)
- [Matrice di tracciabilità](traceability-matrix.md)
- [Registro dei documenti canonici](canonical-document-register.md)
- [Glossario comune](../appendices/glossary.md)

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
