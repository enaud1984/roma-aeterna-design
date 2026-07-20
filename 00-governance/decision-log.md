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
