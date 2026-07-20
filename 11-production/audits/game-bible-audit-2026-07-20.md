# Audit completo della Game Bible — 2026-07-20

**ID:** AUD-GB-2026-07-20
**Baseline:** commit 8754c31
**Stato:** Complete with follow-up actions
**Owner:** Technical Writing / Game Direction

## Scopo

Valutare qualità, coerenza, navigabilità e mantenibilità dell'intero corpus documentale senza introdurre nuove funzionalità di gameplay.

## Descrizione

L'audit combina controlli automatici sull'intero repository e review editoriale delle fonti canoniche mature. Distingue tre concetti che non devono essere confusi:

1. **validità strutturale:** file, sezioni e link corretti;
2. **maturità editoriale:** contenuto sufficiente per una review professionale;
3. **readiness implementativa:** requisiti approvati, decisioni chiuse e test definiti.

La baseline supera il primo livello, ha completato la macroarea Visione e non soddisfa ancora il terzo.

## Ambito

Sono stati inclusi tutti i 528 file Markdown e le 58 cartelle indicizzate, esclusi metadati Git. Sono stati verificati struttura, collegamenti, titoli, sezioni, dimensioni, terminologia, autorità, duplicazioni, dipendenze e stato dichiarato.

## Metodo

### Controlli automatici

- conteggio di file, cartelle, parole e link;
- presenza di README in ogni cartella;
- presenza delle sette sezioni strutturali obbligatorie;
- risoluzione di tutti i link Markdown relativi;
- rilevamento di file orfani;
- titoli H1 duplicati;
- intestazioni H2 duplicate nello stesso file;
- fence Markdown/Mermaid non bilanciate;
- trailing whitespace tramite controllo Git;
- identificazione di scheletri e documenti molto brevi.

### Review editoriale

- gerarchia della Visione e della Game Design Bible;
- separazione tra panoramiche, specifiche e indici;
- consistenza di “giocatore/player”, “NPC/agente”, “status”, “household”, “feature”, “scope” e “vertical slice”;
- qualità degli esempi e dei casi limite nei documenti maturi;
- coerenza tra roadmap, decisioni, rischi e questioni aperte.

### Limiti dell'audit

L'accuratezza storica sostanziale non può essere certificata per i 470 scheletri, perché non contengono ancora affermazioni verificabili. I documenti storici maturi richiedono la macroarea di audit delle fonti prevista dalla roadmap. La validità di un link non garantisce che la destinazione sia già completa.

## Metriche della baseline

| Metrica | Risultato iniziale | Risultato dopo correzione |
|---|---:|---:|
| File Markdown | 528 | 531 |
| Cartelle documentali | 56 | 57 |
| Parole approssimative | 84.703 | aumentate da registri e report |
| Scheletri rilevati | 470 | 470, ora esplicitamente non canonici |
| File sotto 150 parole | 448 | invariato sostanzialmente; follow-up |
| File oltre 2.500 parole | 0 | 0 |
| Link interni interrotti | 0 | 0 |
| File senza link | 0 | 0 |
| File orfani | 3 | 0 |
| Titoli H1 duplicati | 6 coppie | 0 |
| File con H2 duplicati | 4 | 0 |
| Fence non bilanciate | 0 | 0 |
| Cartelle senza README | 0 | 0 |
| Documenti senza sezioni obbligatorie | 0 | 0 |

## Problemi trovati e correzioni

### A-01 — Maturità sovrastimata

**Severità:** critica.
**Problema:** 470 file usano testo da scheletro; 448 hanno meno di 150 parole. La struttura completa poteva essere interpretata come Game Bible completa.
**Correzione:** ADR-0010 distingue architettura e specifica; il [registro canonico](../../00-governance/canonical-document-register.md) identifica le autorità mature; roadmap e README dichiarano lo stato.
**Residuo:** gli scheletri devono essere sviluppati macroarea per macroarea.

### A-02 — Autorità ambigua tra panoramiche e sottodocumenti

**Severità:** alta.
**Problema:** documenti come economia, NPC, dati e gameplay possiedono una panoramica matura e uno scheletro specializzato dal titolo simile.
**Correzione:** introdotta classe documentale e regola di promozione; nessuno scheletro acquisisce autorità per posizione o nome.
**Residuo:** ogni promozione richiede assorbimento, review, ADR e aggiornamento dei link.

### A-03 — Titoli duplicati

**Severità:** media.
**Problema:** sei coppie con H1 uguale rendevano ricerca e breadcrumb ambigui.
**Correzione:** distinti requisiti UX/accessibilità, pipeline audio creativa/tecnica, panoramica/modello dati, sistema/attività per lavoro e commercio, panoramica/sistema narrativo.

### A-04 — Intestazioni duplicate

**Severità:** bassa.
**Problema:** quattro file contenevano due sezioni “Scopo” o “Dipendenze” dopo la normalizzazione iniziale.
**Correzione:** rinominate in “Responsabilità documentale” o “Dipendenze di dominio”.

### A-05 — Documenti orfani

**Severità:** media.
**Problema:** strumenti e osservabilità, template storico e indice audit non avevano link in ingresso.
**Correzione:** aggiunti ai README canonici di Technical Design, Template e Produzione.

### A-06 — Fan-in artificiale sugli hub

**Severità:** media.
**Problema:** 470 scheletri rimandano genericamente agli stessi registri; il README principale riceve oltre 500 link. I link sono validi ma poco semantici.
**Correzione:** registrato R-016; gli indici locali rimangono la navigazione primaria.
**Residuo:** durante l'espansione, sostituire link generici con dipendenze reali e ridurre i riferimenti non pertinenti.

### A-07 — Terminologia mista

**Severità:** media.
**Problema:** italiano e termini tecnici inglesi sono usati senza una policy completamente formalizzata.
**Correzione:** mantenuti termini già canonici quando semanticamente utili; eliminata l'ambiguità nei titoli duplicati.
**Residuo:** il glossario deve definire forme preferite e forme ammesse durante la macroarea storica/editoriale.

### A-08 — Dipendenze valide ma generiche

**Severità:** alta.
**Problema:** molti scheletri dichiarano dipendenze di governance, non i veri contratti di sistema.
**Correzione:** la [matrice](../../00-governance/system-dependency-matrix.md) resta la fonte macro; ADR-0010 impedisce di considerare completi i contratti.
**Residuo:** sostituire ogni dipendenza generica durante lo sviluppo del documento.

### A-09 — Accuratezza non ancora auditabile globalmente

**Severità:** alta.
**Problema:** i documenti storici e sistemici non possiedono ancora tutti periodo, area, fonte e classe di certezza.
**Correzione:** nessuna affermazione è stata promossa artificialmente; la lacuna rimane esplicita nella roadmap.
**Residuo:** completare fonti, cronologia, controversie, licenze creative e ledger delle affermazioni.

## Analisi di modularità

Nessun documento supera 2.500 parole; non esistono monoliti che richiedano split immediato. Il rischio prevalente è opposto: frammentazione prematura. Gli scheletri non vengono uniti in massa perché rappresentano responsabilità future richieste dall'architettura, ma saranno valutati con questa regola:

- unire quando due documenti hanno stesso owner, lifecycle, fonti, consumatori e criteri di completamento;
- separare quando cambiano autorità, frequenza di aggiornamento, livello di rischio o discipline reviewer;
- conservare un overview quando integra più specifiche senza duplicarne requisiti.

## Analisi della terminologia

| Concetto | Forma preferita | Uso ammesso |
|---|---|---|
| persona controllata | giocatore per la persona reale; personaggio giocante per l'entità | player solo in formule tecniche consolidate |
| persone simulate | NPC nel linguaggio di produzione; agente nel modello decisionale | evitare “mob” |
| condizione giuridico-sociale | status | non ridurre a classe economica |
| unità domestica | household quando famiglia e convivenza non coincidono | definizione nel glossario |
| elemento pianificabile | feature | funzionalità in testo divulgativo |
| porzione rappresentativa | vertical slice | non “demo” quando si parla del gate produttivo |
| fonte di verità | documento canonico | overview solo per sintesi |

## Coerenza delle dipendenze

La direzione macro è coerente: Visione → Storia → Mondo/Simulazione → Gameplay/Contenuti → UX/Arte → Tecnologia → Produzione/QA. La matrice non descrive ancora cardinalità, sincronizzazione, ownership ed error handling: questi attributi sono follow-up obbligatori.

~~~mermaid
flowchart TD
    V["Visione — Complete"] --> H["Storia — Planned/In progress"]
    H --> W["Mondo e Pompei — Planned"]
    H --> S["Simulazioni — Planned"]
    W --> G["Gameplay e contenuti — Planned"]
    S --> G
    G --> U["UX, arte e audio — Planned"]
    S --> T["Technical Design — Planned"]
    U --> T
    T --> P["Produzione e QA — Planned"]
~~~

## Lacune ancora presenti

1. 470 specifiche restano scheletri.
2. Fondazione storica e bibliografia non sono ancora complete.
3. Data, stagione ed eruzione della demo non sono decise.
4. Piattaforme, rating, lingue e modello commerciale sono aperti.
5. I contratti evento/dati/dipendenze dei sistemi non sono specificati.
6. I budget tecnici non hanno target hardware.
7. La Definition of Ready implementativa non è approvata.
8. Glossario storico e policy terminologica richiedono espansione.
9. Ownership nominale non è assegnata.
10. Non esiste ancora validazione automatizzata in CI.

## Decisioni registrate

- [ADR-0009](../../00-governance/decision-log.md): separazione delle autorità della Visione.
- [ADR-0010](../../00-governance/decision-log.md): promozione controllata delle specifiche.
- R-013–R-016 nel [risk register](../risk-register.md).
- Q-201–Q-203 nel [registro aperto](../../00-governance/open-questions.md).

## Dipendenze

- [Standard documentale](../../00-governance/documentation-standard.md)
- [Registro canonico](../../00-governance/canonical-document-register.md)
- [Roadmap](../roadmap-backlog/documentation-roadmap.md)

## Collegamenti agli altri documenti

- [Mappa documentale](../../00-governance/documentation-map.md)
- [Matrice delle dipendenze](../../00-governance/system-dependency-matrix.md)
- [Registro rischi](../risk-register.md)
- [QA strategy](../qa-strategy.md)

## Decisioni ancora aperte

Q-201–Q-203; sequenza di promozione delle panoramiche; soglia di merge dei documenti; cadence dell'audit.

## Rischi

Il report può diventare obsoleto mentre il corpus evolve. Le metriche sono una fotografia e non sostituiscono review contenutistica o storica.

## Criteri di completamento

- Tutti i controlli automatici strutturali sono verdi.
- Problemi e correzioni hanno ID e follow-up.
- Le lacune non vengono presentate come contenuti completi.
- Registri e roadmap recepiscono gli esiti.

## TODO

- Rieseguire l'audit dopo ogni macroarea.
- Aggiungere lint di metadata e link in CI quando l'implementazione degli strumenti sarà autorizzata.
- Chiudere A-09 durante la fondazione storica.
