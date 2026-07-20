# Principi operativi di design

**ID:** VIS-GDB-004
**Stato:** Approved — Baseline 1.0
**Owner:** Lead Game Designer

## Scopo

Tradurre i [pilastri](../design-pillars.md) in regole applicabili alla progettazione quotidiana di sistemi, contenuti e UX.

## Descrizione

Dodici principi operativi descrivono causalità, informazione, costi, degradazione, accuratezza, accessibilità e rarità.

## Ambito

Si applica a ogni feature di design e ai contratti tecnici che ne preservano il significato.

## Principi

### DP-01 — Stato prima della scena

Il mondo canonico genera le condizioni; contenuti e presentazione le esprimono. Una scena non può imporre uno stato incompatibile.

### DP-02 — Stessa causalità, controllo diverso

Player e NPC rispettano le stesse regole di accesso, risorse, conoscenza e conseguenza. Il player ha controllo diretto, non immunità.

### DP-03 — Informazione situata

Ogni decisione usa ciò che l'agente sa. Fatto, osservazione, testimonianza, voce e credenza sono distinti.

### DP-04 — Risoluzione proporzionata

Simulare in dettaglio solo ciò che cambia un esito osservabile. L'aggregazione conserva quantità, identità rilevanti e fatti comunicati.

### DP-05 — Fallimento produttivo

Il fallimento modifica stato, costi e opportunità. Il game over è riservato agli stati in cui nessuna continuità coerente è possibile.

### DP-06 — Costi multidimensionali

Azioni importanti consumano almeno una combinazione di tempo, beni, denaro, salute, reputazione, relazione, accesso o rischio.

### DP-07 — Reputazione contestuale

Nessuna reputazione globale. Ogni giudizio appartiene a una comunità, un dominio, evidenze e un periodo.

### DP-08 — Nessun sistema isolato

Una feature core produce o riceve effetti da almeno due domini, salvo infrastruttura puramente tecnica.

### DP-09 — Spiegazione progressiva

Feedback immediato, spiegazione contestuale e approfondimento opzionale. La precisione rispetta le conoscenze del personaggio.

### DP-10 — Accuratezza esplicita

Ogni elemento storico significativo dichiara grado di certezza, periodo, luogo e adattamento.

### DP-11 — Accessibilità non punitiva

Le opzioni di accessibilità non riducono ricompense o contenuti. Possono cambiare input e presentazione preservando il significato sistemico.

### DP-12 — Rarità protetta

Eventi eccezionali non vengono moltiplicati per intrattenere costantemente. Frequenza e scala sono governate da calendario e condizioni.

## Flusso di applicazione

~~~mermaid
flowchart TD
    I["Intento"] --> S["Stato canonico"]
    S --> K["Conoscenza disponibile"]
    K --> O["Opzioni valide"]
    O --> C["Costo e rischio"]
    C --> R["Risoluzione"]
    R --> E["Eventi e conseguenze"]
    E --> F["Feedback progressivo"]
~~~

## Tabella di review

| Controllo | Domanda |
|---|---|
| Causalità | quale stato abilita e quale evento produce? |
| Equità sistemica | l'NPC equivalente rispetta la stessa regola? |
| Informazione | chi sa cosa, come e con quale certezza? |
| Costo | cosa impedisce ripetizione infinita? |
| Degradazione | cosa conserva l'aggregazione? |
| Storia | periodo, luogo e classe di certezza? |
| UX | come comprende causa e alternativa? |
| Accessibilità | quali modalità non dipendono da precisione o canale unico? |

## Esempio pratico

Un furto non attiva un livello di ricercato globale. Produce perdita di proprietà, possibili osservazioni, testimonianze, voci, denuncia, interesse di soggetti e conseguenze contestuali. L'assenza di testimoni non cancella tracce materiali o sospetti preesistenti.

## Casi limite

Un sistema tecnico può avere una sola dipendenza visibile, ma deve dichiararne gli effetti. Una semplificazione storica può essere necessaria, ma diventa licenza creativa registrata. Un contenuto autoriale può rendere probabile un incontro, non congelare indefinitamente gli agenti.

## Dipendenze

- [Pilastri](../design-pillars.md)
- [Framework storico](../../02-historical-foundation/historical-framework.md)
- [Architettura simulazione](../../04-simulation/simulation-architecture.md)

## Collegamenti agli altri documenti

- [Feature taxonomy](feature-taxonomy.md)
- [Standard documentale](../../00-governance/documentation-standard.md)
- [QA](../../11-production/qa-strategy.md)

## Decisioni ancora aperte

Tolleranze di errore per aggregazione; soglie di costo minimo; regole di game over e successione.

## Rischi

Applicazione selettiva; regole troppo astratte; costi cumulativi che bloccano recovery; accessibilità trattata tardi.

## Possibili estensioni future

Checklist automatizzate nei tool di authoring e lint sui metadata.

## Criteri di completamento

Ogni principio ha almeno uno scenario di test; ogni specifica core dichiara conformità o ADR.

## TODO

- Integrare la checklist nel template di sistema.
- Validare DP-01–DP-12 sulle feature core di Pompei.
