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
| R-037 | Duplicazione o perdita di valore | Media | Critico | bilanci non chiudono dopo transazione/save | invarianti, ledger e test property-based |
| R-038 | Oscillazione dei mercati | Alta | Alto | prezzi alternano senza shock | smoothing, isteresi, capacità e soak test |
| R-039 | Dominio economico prematuro del player | Media | Alto | un raccolto muove regione/Impero | quota reale e confini E0–E5 |
| R-040 | Spirale di debito senza uscita | Media | Alto | insolvenza diventa game over differito | rinegoziazione, conseguenze plurali e test longitudinali |
| R-041 | Falsa precisione di prezzi e salari | Alta | Alto | numero singolo privo di corpus | intervalli, provenance e sensitivity analysis |
| R-042 | Persone schiavizzate trattate come inventario | Media | Critico | aggregazione cancella identità o trauma | NPC persistenti, guardrail e review etico-storica |
| R-043 | Esplosione di lotti e ordini | Alta | Alto | RAM/save/tick crescono con transazioni | livelli E0–E5, coalescenza conservativa e budget |
| R-044 | Status ridotto a bonus lineare | Alta | Alto | ricchezza sblocca ogni accesso | assi separati e matrice capacità |
| R-045 | Istituzioni anacronistiche | Alta | Critico | polizia/partiti/clero moderni impliciti | profili data-luogo e review specialistica |
| R-046 | Carriera politica deterministica | Media | Alto | grind garantisce elezione | opposizione, procedure, fallimento e memoria |
| R-047 | Religione come magia o fazione unica | Media | Critico | rito produce buff/divinità certificata | interpretazioni separate e pluralità attestata |
| R-048 | Schiavitù romanticizzata o decorativa | Media | Critico | coercizione senza danni/agency | invarianti etici, conseguenze e sensitivity review |
| R-049 | Giustizia onnisciente | Alta | Alto | reato genera pena senza conoscenza | prove, denuncia, autorità e knowledge graph |
| R-050 | Combattimento illeggibile o arbitrario | Alta | Critico | morte senza telegraph/causalità | segnali, trace e test utenti |
| R-051 | Realismo punitivo e grind medico | Media | Alto | ogni ferita interrompe il gioco senza alternative | resa, fuga, recupero e tuning conseguenze |
| R-052 | Desincronizzazione animazione-contatto | Alta | Critico | hit senza geometria o doppio danno | autorità contatto e test property-based |
| R-053 | Esplosione CPU di gruppi/folle | Alta | Critico | M0 scala con tutti i partecipanti | livelli M0–M5 e budget |
| R-054 | Esercito anacronistico uniforme | Alta | Critico | organici/equipaggiamento universali | profili data-provincia A–E |
| R-055 | Grandi eventi troppo frequenti | Media | Alto | battaglie/trionfi diventano routine | gate storici, risorse e calendario |
| R-056 | Prigionieri ridotti a props | Media | Critico | identità cancellate in battaglia/trionfo | NPC persistenti e review etica |
| R-057 | Missioni come checklist artificiale | Alta | Alto | marker sostituiscono scoperta e relazioni | situazioni, fonti e impegni diegetici |
| R-058 | Narrazione inventa causalità | Media | Critico | storylet contraddice ledger | binding read-only e causal trace |
| R-059 | Eventi e catastrofi continui | Alta | Alto | nessun aftermath/cooldown | classi D0–D5, gate e budget |
| R-060 | UI onnisciente | Alta | Critico | mostra segreti, GPS o reputazione globale | UIFactView e leak tests |
| R-061 | Sovraccarico di notifiche | Alta | Alto | messaggi/minuto e dismiss crescono | priorità, deduplica, recap e silenzioso |
| R-062 | Audio ripetitivo o stereotipato | Alta | Alto | bark/loop riconoscibili e accenti caricaturali | pool semantici, cooldown e review linguistica |
| R-063 | Accessibilità aggiunta tardi | Alta | Critico | flussi P0 dipendono da un solo canale/input | contratti nativi e gate utenti |
| R-064 | Actor/Blueprint diventano database | Alta | Critico | stato perso allo streaming | domain record e adapter ricostruibili |
| R-065 | God Subsystem e dipendenze circolari | Alta | Critico | ogni modulo include ogni altro | allowlist, API strette e fitness tests |
| R-066 | Mass adottato senza fallback | Media | Critico | design dipende da plugin prima del benchmark | spike, adapter e coorti/Actor fallback |
| R-067 | Streaming modifica stato canonico | Media | Critico | unload congela obblighi o duplica NPC | bridge e reconciliation |
| R-068 | Blueprint hot path/logic sprawl | Alta | Alto | tick/cast chain e test impossibili | C++ policy, lint e conversion gate |
| R-069 | Plugin/upgrade UE rompe progetto | Media | Critico | API/stato feature cambia | baseline, registry, ADR e exit plan |
| R-070 | Asset/data hard references esplodono memoria | Alta | Alto | residency e cook crescono | Asset Manager, soft refs e bundle budget |
| R-071 | Save serializza oggetti engine fragili | Media | Critico | streaming/upgrade rompe campagne | schema record, ID/versione e migration |
| R-072 | Schemi proliferano o duplicano ownership | Alta | Critico | record equivalenti divergono | registry, owner unico e contract review |
| R-073 | Migrazione corrompe storia persistente | Media | Critico | checksum o invarianti cambiano | migrazione in copia, backup e golden saves |
| R-074 | Save e tempi di load crescono senza limite | Alta | Alto | slot supera budget a ogni milestone | segmenti, retention, compact e benchmark |
| R-075 | Autosave causa hitch o perdita dati | Media | Critico | frame spike o slot incompleto | consistency barrier, staging e failure injection |
| R-076 | Budget provvisori diventano promesse non validate | Alta | Alto | scope usa numeri senza hardware | marcatura D, owner e benchmark gate |
| R-077 | Tooling tardivo blocca authoring e QA | Alta | Critico | designer dipendono da engineering | tool P0 nella fondazione e metriche UX |
| R-078 | Generazione NPC crea incoerenza o stereotipi | Media | Critico | distribuzioni e biografie implausibili | vincoli, seed, review storica/etica e report |
| R-079 | Telemetria locale espone dati o satura disco | Media | Alto | log non redatti o crescita continua | allowlist, ring buffer, retention e scrub |
| R-080 | Binary/LFS rende repository fragile o costoso | Alta | Alto | clone lento, quota o pointer mancanti | pattern, quota, locking e recovery test |
| R-081 | CI lenta o flaky perde autorità | Alta | Alto | retry/skip diventano norma | stage rapidi, owner flaky e SLO |
| R-082 | Default branch documentale confonde integrazione futura | Media | Alto | codice e docs confluiscono senza gate | decisione Q-251 e protezione `main` |
| R-083 | Vertical slice diventa miniatura dell'intero gioco | Alta | Critico | sistemi esclusi rientrano come “placeholder” | content lock, Must/Should/Could e change control |
| R-084 | PVS-1 supera budget prima del GIS | Alta | Critico | spina lunga, interni e streaming non stimati | varianti, gate GIS e taglio profondità duplicata |
| R-085 | Tre origini triplicano contenuti e QA | Alta | Alto | scene separate senza riuso sistemico | situazione condivisa, contratti comuni e golden paths |
| R-086 | Percorso schiavo produce sfruttamento o agency falsa | Media | Critico | coercizione come difficoltà/ricompensa | Historical/Sensitivity review e conseguenze persistenti |
| R-087 | Successione appare artificiale in 30 giorni | Alta | Alto | gravidanza/figlio accelerati | erede iniziale ed epilogo/scenario accelerato dichiarato |
| R-088 | Data 77 mescola evidenza del 79 | Alta | Critico | edificio/contenuto retrodatato senza prova | snapshot edificio e classe A–E |
| R-089 | Conteggi contenuti diventano quota e riempitivo | Media | Alto | authoring cresce senza copertura | cap, valore per contenuto e taglio quantitativo |
| R-090 | Milestone chiuse per calendario, non qualità | Media | Critico | blocker trascinati o test disabilitati | entry/exit binari e regressione esplicita |
| R-091 | READY firmata senza evidenza | Media | Critico | checkbox senza link/owner | audit, firme interdisciplinari e autorizzazione utente |
| R-092 | Demo pubblica promette scala imperiale prematura | Media | Alto | marketing mostra esclusioni come roadmap certa | promise review e go/no-go post-demo |

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
