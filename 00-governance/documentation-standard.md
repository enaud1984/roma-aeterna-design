# Standard documentale

**ID:** GOV-DOC-001
**Stato:** Draft
**Owner:** Technical Writing / Game Direction

## Obiettivo

Rendere ogni scelta rintracciabile dalla promessa creativa fino al test che la verifica. Lo standard riduce contraddizioni, numeri “magici”, dipendenze nascoste e interpretazioni divergenti tra discipline.

## Front matter minimo

Ogni specifica dovrà dichiarare: ID stabile, stato, owner, reviewer, versione, ultima revisione, documenti genitori, documenti dipendenti e decisioni correlate. In questa baseline gli owner sono ruoli, non persone.

## Struttura normativa

Una specifica di sistema include almeno:

1. intenzione e risultato per il giocatore;
2. confini e non-obiettivi;
3. termini di dominio;
4. entità, stati, input, output e invarianti;
5. loop e transizioni;
6. interazioni con altri sistemi;
7. livelli di simulazione e politiche di degradazione;
8. telemetria e strumenti di osservazione;
9. rischi storici, etici, tecnici e produttivi;
10. criteri di accettazione e scenari di test;
11. domande aperte e riferimenti.

## Linguaggio

- **DEVE** indica un requisito vincolante.
- **DOVREBBE** indica la soluzione preferita, derogabile con decisione registrata.
- **PUÒ** indica un'opzione.
- **IPOTESI** indica un'affermazione da validare.
- **TBD** indica una lacuna nota con owner e criterio di chiusura.
- **ESEMPIO** non crea un requisito.

Evitare “realistico”, “dinamico”, “intelligente” o “immersivo” senza una condizione osservabile. Scrivere invece il comportamento, il contesto e la misura: per esempio, “un panettiere senza grano riduce la produzione entro un ciclo economico e cerca almeno una fonte alternativa”.

## Collegamenti e granularità

Ogni documento deve collegare il proprio genitore concettuale e le specifiche direttamente influenzate. Un argomento appartiene a un solo documento canonico; gli altri lo sintetizzano e lo linkano. I nomi file sono in inglese, minuscoli e con trattini; il contenuto editoriale iniziale è in italiano.

## Accuratezza storica

Le affermazioni sono etichettabili come:

| Classe | Definizione | Trattamento |
|---|---|---|
| H1 — attestato | sostenuto direttamente da evidenza primaria o forte consenso | citazione puntuale |
| H2 — ricostruito | inferenza accademica plausibile | nota di incertezza e fonti |
| H3 — sintetizzato | composito necessario alla giocabilità | motivazione di design |
| H4 — controfattuale | deviazione emergente dal gioco | regole di plausibilità |

Il metodo completo è in [framework storico](../02-historical-foundation/historical-framework.md).

## Definition of Ready documentale

Una funzionalità può entrare in pianificazione solo quando ha: valore per un pilastro, confini, owner, dipendenze, rischio, costo qualitativo, criterio di accettazione e strategia di fallimento/degradazione.

## Definition of Done documentale

Una specifica è approvabile quando non contiene contraddizioni note, tutte le decisioni bloccanti sono risolte, i collegamenti sono validi, un reviewer esterno alla disciplina l'ha letta e almeno uno scenario end-to-end dimostra l'integrazione.

## Manutenzione

Ogni milestone esegue un audit dei link, un audit terminologico, un audit storico e un audit dei requisiti orfani. Vedere [matrice di tracciabilità](traceability-matrix.md) e [strategia QA](../11-production/qa-strategy.md).

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
