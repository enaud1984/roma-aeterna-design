# Registro dei rischi

**ID:** PRD-RISK-001
**Stato:** Draft

| ID | Rischio | Prob. | Impatto | Segnale precoce | Mitigazione |
|---|---|---:|---:|---|---|
| R-001 | Esplosione combinatoria simulazione | Alta | Critico | bug cross-system crescono più dei sistemi | contratti, invarianti, slice verticali |
| R-002 | Scala imperiale prematura | Alta | Critico | superficie cresce, densità cala | gate Pompei e criteri espansione |
| R-003 | NPC costosi ma poco credibili | Alta | Alto | routine ripetitive/stalli | modello a livelli, inspector, test longitudinali |
| R-004 | Economia instabile | Alta | Alto | inflazione/collasso senza shock | sorgenti/pozzi, time-lapse, limiti |
| R-005 | Accuratezza incoerente | Media | Critico | scelta D presentata come fatto A | provenance ledger e review |
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
| R-021 | Fonte primaria trattata come testimonianza neutrale | Alta | Alto | claim A basati su un testo senza critica di genere/data | triangolazione e review |
| R-022 | Trasferimento improprio Roma/province/epoche | Alta | Critico | regola “romana” senza area o periodo | area e finestra obbligatorie, analogie C |
| R-023 | Falsa precisione demografica/economica | Alta | Alto | numeri singoli senza intervallo o corpus | scenari, sensitività e registro E |
| R-024 | Scavi o studi recenti rendono obsoleta la baseline | Media | Alto | nuove datazioni/funzioni divergenti | audit periodico e data ultima review |
| R-025 | Full-city creep a Pompei | Alta | Critico | interni e isolati crescono senza loop | PVS-1, tier P0–P5 e gate GIS |
| R-026 | Portfolio imperiale uniforme | Alta | Critico | città riusano identici sistemi/asset | slot di contrasto, moduli regionali e review |
| R-027 | Spina urbana lunga ma poco densa | Media | Alto | attraversamento senza decisioni | profondità selettiva e metriche per tratto |
| R-028 | Paleo-geografia errata | Media | Alto | costa/fiume moderni usati nel 79 | dossier geoarcheologico e precision class |
| R-029 | Costo di folle ed edifici P0 | Alta | Critico | budget superato durante eventi | livelli W/G, access tier e benchmark |
| R-030 | NPC onniscienti | Alta | Critico | agenti reagiscono a fatti non percepiti | SYS-KNOW, provenance e leak test |
| R-031 | Routine artificiali o sincronizzate | Alta | Alto | flussi identici ogni giorno | finestre, impegni, fallback e varianza controllata |
| R-032 | Perdita cross-level | Alta | Critico | beni, persone o eventi duplicati/spariti | invarianti N0–N5 e reconciliation |
| R-033 | Memoria ingestibile | Alta | Alto | save e RAM crescono senza limite | retention, sintesi, top-K e ledger critico |
| R-034 | Folla come mente unica | Media | Alto | panico/fuga uniformi | individui, gruppi, conoscenza e uscite differenziati |
| R-035 | Demografia falsa o instabile | Media | Critico | coorti negative o correlazioni impossibili | conservazione massa e dossier storico |
| R-036 | Planner in stallo/ciclo | Alta | Alto | NPC idle o replan continui | backoff, isteresi, fallback finiti e inspector |

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
