# Registro dei rischi

**ID:** PRD-RISK-001
**Stato:** Draft

| ID | Rischio | Prob. | Impatto | Segnale precoce | Mitigazione |
|---|---|---:|---:|---|---|
| R-001 | Esplosione combinatoria simulazione | Alta | Critico | bug cross-system crescono più dei sistemi | contratti, invarianti, slice verticali |
| R-002 | Scala imperiale prematura | Alta | Critico | superficie cresce, densità cala | gate Pompei e criteri espansione |
| R-003 | NPC costosi ma poco credibili | Alta | Alto | routine ripetitive/stalli | modello a livelli, inspector, test longitudinali |
| R-004 | Economia instabile | Alta | Alto | inflazione/collasso senza shock | sorgenti/pozzi, time-lapse, limiti |
| R-005 | Accuratezza incoerente | Media | Critico | asset H3 presentati H1 | provenance ledger e review |
| R-006 | Rappresentazione dannosa | Media | Critico | coercizione trattata come premio | sensitivity workflow e guardrail |
| R-007 | Simulazione illeggibile | Alta | Alto | tester percepiscono casualità | causal chain e UX a livelli |
| R-008 | Tooling tardivo | Alta | Critico | authoring richiede engineering | strumenti come milestone core |
| R-009 | Performance forza redesign tardivo | Alta | Critico | target NPC non misurato | benchmark e budget prima dello scope |
| R-010 | Save incompatibile | Media | Alto | cambi schema rompono campagne | versionamento/migrazioni precoci |
| R-011 | Contenuti ripetitivi | Alta | Alto | storylet riconoscibili | condizioni ricche, budget e review |
| R-012 | Decisioni fondative aperte troppo a lungo | Alta | Alto | documenti assumono date diverse | owner e deadline per Q-001–005 |
| R-013 | Frammentazione documentale | Alta | Alto | molti file brevi senza autorità chiara | registro canonico, promozione controllata, merge quando utile |
| R-014 | Scheletri interpretati come specifiche complete | Alta | Critico | pianificazione basata su TODO generici | stato esplicito, roadmap e gate di readiness |
| R-015 | Deriva terminologica | Media | Alto | titoli duplicati e sinonimi non governati | glossario, lint e audit per milestone |
| R-016 | Hub con eccessivo fan-in | Media | Medio | quasi tutti i file linkano gli stessi registri | indici locali e link semantici durante l'espansione |
| R-017 | Falsa readiness documentale | Alta | Critico | file completi formalmente ma privi di contratti verificabili | livelli S0–S5, DoR ed evidenze collegate |
| R-018 | Conflitti di ownership dei dati | Media | Critico | due sistemi modificano lo stesso aggregato | proprietario unico, comandi e transazioni |
| R-019 | Tempeste o cicli di eventi | Alta | Alto | backlog crescente e reazioni ricorsive | causalità, back-pressure, coalescenza autorizzata e soak test |
| R-020 | Deriva dei contratti tra documenti | Alta | Alto | payload, errori o ID divergenti | cataloghi canonici, contract review e matrice impatti |

Ogni rischio maturo avrà esposizione numerica, contingency, trigger, owner nominale e revisione per milestone. Collegamenti: [architettura](../10-technical/technical-architecture.md), [etica](../02-historical-foundation/ethics-and-representation.md).

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
