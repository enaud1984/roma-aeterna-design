# Registro delle decisioni

**ID:** GOV-ADR-INDEX
**Stato:** Draft

Questo registro conserva non solo cosa è stato deciso, ma quali alternative sono state escluse e quali segnali possono riaprire la decisione. Usare il [template ADR](../appendices/templates/decision-record-template.md).

## Decisioni iniziali

| ID | Decisione | Stato | Conseguenze principali |
|---|---|---|---|
| ADR-0001 | Pompei è il primo vertical slice | Accepted | densità prima della scala; set di ricerca circoscritto |
| ADR-0002 | Il protagonista non è un eroe predestinato | Accepted | progressione sociale sistemica; nessuna eccezione narrativa gratuita |
| ADR-0003 | Il mondo avanza senza il giocatore | Accepted | persistenza, simulazione multi-risoluzione, test offline |
| ADR-0004 | La documentazione precede il codice | Accepted | gate di pre-produzione e tracciabilità obbligatoria |
| ADR-0005 | Accuratezza dichiarata per livello di certezza | Proposed | provenienza dati e revisione storica |
| ADR-0006 | Data esatta della demo | Open | influenza eruzione, politica, personaggi, asset e tono |
| ADR-0007 | Lingue e rappresentazione linguistica | Open | dialoghi, UI, accessibilità, costi audio |
| ADR-0008 | Piattaforme e target prestazionale | Open | densità NPC e strategia di simulazione |
| ADR-0009 | Separazione delle autorità nella macroarea Visione | Accepted | elimina duplicazioni tra visione, promessa, principi e scope |
| ADR-0010 | Panoramiche mature restano canoniche finché gli scheletri specializzati non sono promossi | Accepted | impedisce che file brevi o duplicati acquisiscano autorità implicita |
| ADR-0011 | Contratto AAA comune e autorità unica per dati/eventi | Accepted | readiness misurabile, mutazioni inter-sistema controllate |
| ADR-0012 | Classificazione storica A–E e claim atomici | Accepted | separa attestazione, probabilità, ricostruzione, design e verifica |
| ADR-0013 | Livelli geografici W0–W5 e G0–G5 | Accepted | scala produzione e simulazione senza uniformare gli insediamenti |
| ADR-0014 | Spina urbana PVS-1 per Pompei | Proposed | Foro–Via dell'Abbondanza–Anfiteatro con profondità selettiva |
| ADR-0015 | Persona persistente separata da agente, conoscenza e coorti | Accepted | evita oggetti onniscienti e consente N0–N5 |

## ADR-0001 — Pompei come vertical slice

**Contesto.** Il progetto finale copre un territorio e una varietà culturale enormi. Occorre dimostrare che la fantasia centrale funziona in una città concreta e documentata.

**Decisione.** La prima demo giocabile è ambientata a Pompei e deve mostrare vita urbana, lavoro, commercio, famiglia, culto, diritto locale e conseguenze persistenti. Non è una miniatura superficiale dell'intero Impero.

**Alternative escluse.** Roma avrebbe maggiore riconoscibilità ma scala e complessità istituzionale inadatte al primo slice; una frontiera militare sovrarappresenterebbe guerra e carriera armata.

**Conseguenze.** La demo privilegia densità, interni e routine; il modello dati deve però distinguere regole locali da regole imperiali per evitare una futura generalizzazione impropria. Vedere [scope Pompei](../07-pompeii-demo/pompeii-vertical-slice.md).

## ADR-0002 — Persona comune

**Decisione.** Nessuna origine garantisce unicità cosmica, immunità legale o accesso universale. Opportunità e ostacoli derivano da status, relazioni, competenze, ricchezza, reputazione, luogo e momento storico.

**Guardrail.** “Può diventare qualsiasi cosa” significa ampia mobilità emergente entro percorsi storicamente plausibili; non significa che ogni personaggio possa ottenere ogni ruolo senza costo o vincolo. Vedere [progressione](../05-player/progression-and-identity.md).

## ADR-0003 — Autonomia del mondo

**Decisione.** Gli agenti e le istituzioni mantengono continuità causale senza osservazione diretta. La fedeltà può diminuire con distanza e rilevanza, ma i risultati devono rispettare invarianti e lasciare una catena causale interrogabile.

**Rischio.** Costo computazionale e instabilità emergente. Mitigazioni in [architettura della simulazione](../04-simulation/simulation-architecture.md) e [budget prestazionali](../10-technical/performance-budgets.md).

## ADR-0009 — Autorità documentali della Visione

**Contesto.** La struttura iniziale distribuiva concetti simili tra visione creativa, pilastri e scheletri della Game Design Bible, creando il rischio di requisiti duplicati o divergenti.

**Decisione.** [Visione creativa](../01-vision/creative-vision.md) governa identità e tono; [promessa](../01-vision/game-design-bible/player-promise.md) governa aspettative verificabili; [obiettivi di esperienza](../01-vision/game-design-bible/experience-goals.md) governano risultati percettivi; [pilastri](../01-vision/design-pillars.md) sono gate non negoziabili; [principi operativi](../01-vision/game-design-bible/design-principles.md) regolano il comportamento delle feature; [scope](../01-vision/scope-and-non-goals.md) e [tassonomia](../01-vision/game-design-bible/feature-taxonomy.md) governano classificazione e promozione.

**Alternative escluse.** Un singolo documento monolitico è meno manutenibile; documenti paralleli senza gerarchia rendono ambigua l'autorità.

**Conseguenze.** Le specifiche inferiori linkano il documento pertinente e non ricopiano promesse o principi. La macroarea è approvabile anche con decisioni di prodotto aperte, purché queste restino registrate.

**Segnali di revisione.** Impossibilità di collocare un nuovo requisito, conflitti ricorrenti o necessità di più di due link per individuare l'autorità.

## ADR-0010 — Promozione controllata delle specifiche

**Contesto.** L'architettura contiene 470 scheletri specializzati e alcune panoramiche precedenti già più mature. Trattare ogni file come equivalente renderebbe ambigua la fonte di verità.

**Decisione.** Le autorità sono dichiarate nel [registro canonico](canonical-document-register.md). Una panoramica matura rimane canonica finché la specifica specializzata non assorbe i requisiti, supera Review e viene promossa tramite ADR. I README non creano requisiti.

**Alternative escluse.** Cancellare gli scheletri perderebbe la roadmap architetturale; promuoverli automaticamente confonderebbe struttura e completezza.

**Conseguenze.** Gli scheletri sono documenti Planned/Draft, non specifiche pronte per implementazione. Le duplicazioni intenzionali vengono ridotte a sintesi e riferimenti durante la promozione.

**Segnali di revisione.** Eccessivo overhead degli ADR di promozione o introduzione di metadata e tooling che garantiscano automaticamente autorità e copertura.

## ADR-0011 — Contratto AAA e autorità dei sistemi

**Contesto.** Sezioni generiche non rendono implementabile un sistema né chiariscono chi possa modificare dati condivisi.

**Decisione.** Ogni sistema usa lo [standard di specifica](system-specification-standard.md), un ID canonico e i livelli S0–S5. Ogni famiglia dati ha un solo proprietario; modifiche esterne passano per comandi validati o transazioni, mentre gli eventi descrivono fatti già accettati. Un sistema è Ready soltanto a S4 e dopo il gate formale.

**Alternative escluse.** Checklist indipendenti per cartella e ownership condivisa, perché produrrebbero criteri e recovery ambigui.

**Conseguenze.** Le specifiche vengono promosse progressivamente. Cambiare ownership o contratto richiede rivalidare consumer, dati, eventi, test e readiness.

**Segnali di revisione.** Costi transazionali sproporzionati o impossibilità dimostrata di assegnare un proprietario unico.

## ADR-0012 — Classificazione storica A–E

**Contesto.** Il precedente schema H1–H4 mescolava attendibilità e natura controfattuale, senza distinguere forte probabilità da evidenza diretta o claim ancora non verificati.

**Decisione.** Ogni proposizione storica rilevante usa A attestato, B altamente probabile, C ricostruzione plausibile, D scelta di design o E da verificare. Periodo e area sono obbligatori; il controfattuale è proprietà dell'evento simulato, non classe della fonte.

**Conseguenze.** I claim E non sono canonici; A/B richiedono evidenze pertinenti; C/D espongono inferenza o licenza. I documenti attivi e i template sono migrati, mentre i vecchi audit restano testimonianze della baseline precedente.

**Segnali di revisione.** Ambiguità ricorrenti tra A e B o necessità di sottoclassi per provenienza, senza perdere la semantica pubblica A–E.

## ADR-0013 — Livelli geografici e di insediamento

**Decisione.** Regioni e luoghi usano scale G0–G5 e livelli di produzione W0–W5. Il livello dichiara risoluzione e costo, non valore storico. Ogni sito conserva identità, capacità, connessioni e memoria anche quando aggregato.

**Conseguenze.** Pompei è W0; città future entrano in portfolio prima di diventare W1/W2. Ville, cave, porti e campagne possono essere nodi vivi senza mappa completa.

## ADR-0014 — Proposta PVS-1

**Stato: Proposed.** La demo candidata usa una spina 1:1 continua dal Foro all'Anfiteatro lungo Via dell'Abbondanza, con cluster Stabian Baths, teatri/Iside e profondità domestico-produttiva selettiva. Mura, necropoli e hinterland restano nodi o mappe locali. Approvazione subordinata a GIS, budget e Q-101.

## ADR-0015 — Separazione delle autorità sociali

**Decisione.** SYS-PER possiede identità e lifecycle; SYS-NPC decisione e attività; SYS-KNOW credenze e memoria; SYS-REL legami; SYS-POP/coorti conservano distribuzioni. Una vista NPC compone i dati senza duplicarne l'autorità. Sei livelli N0–N5 riducono dettaglio mantenendo invarianti.

**Conseguenze.** Promuovere un NPC non gli concede conoscenza; aggregare non può perdere debiti, parentela, casi o proprietà; la morte conserva tombstone e apre successione. Il costo è maggiore disciplina contrattuale e tooling di diagnostica.

## ADR-0016 — Conservazione economica e livelli E0–E5

**Decisione.** Beni, moneta, diritti e obbligazioni hanno autorità distinte; ogni mutazione economica ha causale e controparti. La simulazione usa livelli E0 transazione osservata, E1 impresa, E2 mercato cittadino, E3 città remota, E4 regione/rotta ed E5 condizioni imperiali. Aggregazione e disaggregazione conservano saldi e identità rilevanti.

**Conseguenze.** Prezzi non creano merci; contratti non creano capitale; il raccolto del giocatore pesa soltanto quanto la sua quota reale. Proprietà, custodia, debiti, persone, casi e lotti P0 non vengono cancellati dall'aggregazione. La schiavitù è modellata come regime coercitivo su NPC persistenti, mai come inventario.

## ADR-0017 — Capacità situata e causalità istituzionale

**Decisione.** Libertà, cittadinanza, famiglia, rango, patrimonio e reputazione sono dimensioni separate. Ogni atto istituzionale verifica capacità, autorità, luogo, periodo, conoscenza e prove. Religione conserva fenomeni materiali e interpretazioni senza certificare causalità soprannaturale.

**Conseguenze.** Denaro o fama non comprano automaticamente status o cariche; famiglia non implica proprietà; crimine non genera una risposta onnisciente; carriera pubblica resta fallibile. La schiavitù opera come relazione coercitiva su persone persistenti e la manomissione non cancella biografia o dipendenze.

## ADR-0018 — Conseguenze corporee e livelli militari M0–M5

**Decisione.** Il combattimento risolve spazio, intenzione, contatto, protezione e trauma senza hit point autoritativi. Dolore, sangue, fatica, paura e morale sono assi distinti. Esercito e guerre scalano da M0 individui a M5 teatro, conservando persone P0, scorte, perdite, ordini e causalità.

**Conseguenze.** Player e NPC usano le stesse regole; resa, cattura, fuga e morte sono esiti persistenti. Grandi battaglie e trionfi sono rari e condizionati; il raccolto di eventi non sostituisce requisiti politici, religiosi, logistici o storici.

## ADR-0019 — Esperienza epistemica e contenuti come viste

**Decisione.** Missioni e narrazione non possiedono lo stato dei domini: bindano fatti, conoscenze, impegni e conseguenze. UI e audio presentano soltanto ciò che è percepibile o conosciuto, con fonte e incertezza. Eventi dinamici usano classi D0–D5, gate causali, aftermath e memoria.

**Conseguenze.** Niente marker, reputazioni, diagnosi o posizioni onniscienti; fallimento e scadenza trasformano il mondo invece di resettarlo. Notifiche, thread, eventi e audio condividono budget anti-overload/anti-ripetizione. Grandi eventi restano rari.

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
