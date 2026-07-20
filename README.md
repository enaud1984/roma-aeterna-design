# Roma Aeterna — Project Documentation

> **Stato:** pre-produzione documentale
> **Prodotto:** RPG open world sandbox storico
> **Vertical slice iniziale:** Pompei
> **Regola del repository:** nessuna implementazione di gioco prima dell'approvazione della Game Bible.

La progettazione dei sistemi usa lo [standard AAA](00-governance/system-specification-standard.md), il [catalogo canonico](00-governance/system-catalog.md) e la [matrice di readiness](11-production/roadmap-backlog/implementation-readiness-matrix.md). La presenza di un documento non implica che il sistema sia pronto per l'implementazione.

## Mandato

*Roma Aeterna* vuole simulare la vita nell'Impero Romano dal punto di vista di una persona comune. Il giocatore non riceve uno status eroico: nasce dentro reti familiari, economiche, giuridiche, religiose e politiche che esistono anche senza di lui. Può tentare qualsiasi ascesa consentita dalle condizioni storiche e sistemiche, subirne i limiti o vivere ai margini. Il mondo continua a produrre, consumare, credere, votare, complottare, combattere, invecchiare e morire indipendentemente dalla presenza del giocatore.

Questo repository è la fonte autorevole per le intenzioni di design, i requisiti, le assunzioni storiche e tecniche e le decisioni di produzione. I documenti descrivono prima il **perché**, poi il **cosa**, infine i vincoli del **come**; non contengono codice di gioco.

## Mappa della Game Bible

| Area | Scopo | Punto di ingresso |
|---|---|---|
| Governance | proprietà, stati, decisioni, tracciabilità | [Indice e convenzioni](00-governance/README.md) |
| Visione | promessa, pubblico, principi, confini | [Visione creativa](01-vision/creative-vision.md) |
| Storia | canone, metodo, fonti e gestione dell'incertezza | [Framework storico](02-historical-foundation/historical-framework.md) |
| Mondo | struttura geografica, tempo e persistenza | [Modello del mondo](03-world/world-model.md) |
| Simulazioni | persone, economia, politica, religione, guerra | [Architettura della simulazione](04-simulation/simulation-architecture.md) |
| Giocatore | identità, progressione, attività e conseguenze | [Esperienza del giocatore](05-player/player-experience.md) |
| Contenuti | NPC, missioni emergenti, dialoghi e narrazione | [Framework dei contenuti](06-content/content-framework.md) |
| Pompei | confini e obiettivi della prima demo | [Vertical slice Pompei](07-pompeii-demo/pompeii-vertical-slice.md) |
| UX | informazione, accessibilità e interfaccia diegetica | [Principi UX](08-ux/ux-principles.md) |
| Audio/visual | direzione artistica e sonora | [Direzione artistica](09-art-audio/art-direction.md) |
| Tecnologia | requisiti, dati, prestazioni e strumenti | [Architettura tecnica](10-technical/technical-architecture.md) |
| Produzione | milestone, rischi, QA e criteri di uscita | [Piano di produzione](11-production/production-plan.md) |
| Appendici | glossario, template, registri | [Glossario](appendices/glossary.md) |

## Principi non negoziabili

1. **La storia è un sistema, non una scenografia.** Status, diritto, genere, cittadinanza, schiavitù, parentela e religione modificano possibilità concrete.
2. **Il giocatore non è il centro causale del mondo.** Ogni sistema deve avere comportamenti verificabili in sua assenza.
3. **La simulazione deve essere leggibile.** Una conseguenza inspiegabile equivale a una conseguenza arbitraria.
4. **Accuratezza e onestà epistemica.** Fatti, ricostruzioni plausibili e invenzioni devono essere distinti.
5. **Profondità prima dell'estensione geografica.** Pompei dimostra il modello; l'Impero lo scala solo dopo che il modello funziona.
6. **Nessun sistema isolato.** Ogni specifica dichiara input, output, dipendenze, frequenza di aggiornamento e degradazione.
7. **Nessun contenuto senza provenienza.** Ogni elemento storico rilevante deve poter risalire a una fonte o a una decisione registrata.

## Stato attuale

La documentazione presente costituisce la **Baseline 0.1**: definisce architettura, intenzioni, domande aperte e criteri di validazione. Le sezioni marcate `TBD`, le ipotesi e i valori numerici non sono decisioni definitive. La cronologia precisa della demo, il rating, le piattaforme e il modello commerciale richiedono decisioni formali nel [registro delle decisioni](00-governance/decision-log.md).

### Avanzamento dei contenuti

- **Visione e Game Design Bible:** Complete — Baseline 1.0.
- **Fondazione storica:** prossima macroarea in lavorazione.
- **Mondo, sistemi, contenuti, UX, arte, tecnologia e produzione:** struttura completa, contenuti da sviluppare.

### Qualità documentale

L'[audit completo del 20 luglio 2026](11-production/audits/game-bible-audit-2026-07-20.md) distingue validità strutturale, maturità editoriale e readiness implementativa. Il corpus è strutturalmente valido; 470 documenti restano intenzionalmente marcati come scheletri.

## Regole di contribuzione

- Consultare [standard documentale](00-governance/documentation-standard.md) prima di modificare una specifica.
- Non cancellare decisioni superate: marcarle e collegare la sostituzione.
- Usare link relativi e identificatori stabili.
- Separare requisito, proposta, esempio e domanda aperta.
- Ogni modifica che altera la promessa al giocatore richiede aggiornamento di visione, scope e criteri di validazione.

## Scopo

## Architettura completa della Game Bible

La navigazione canonica parte dalla [mappa completa della documentazione](00-governance/documentation-map.md). Ogni area e sottodominio possiede un proprio `README.md` con l'elenco dei documenti figli.

| Macroarea | Indice | Domini principali |
|---|---|---|
| Governance | [Indice](00-governance/README.md) | decisioni, questioni, rischi, tracciabilità, dipendenze |
| Visione e Game Design Bible | [Indice](01-vision/README.md) | promessa, principi, scope, tassonomia feature |
| Storia | [Indice](02-historical-foundation/README.md) | ambientazione, cronologia, fonti, bibliografia, controversie |
| Mondo | [Indice](03-world/README.md) | geografia, regioni, città, edifici, infrastrutture, siti rurali |
| Simulazione | [Indice](04-simulation/README.md) | NPC, AI, società, economia, politica, diritto, religione, militare, salute, eventi |
| Giocatore | [Indice](05-player/README.md) | gameplay, ciclo principale, personaggio, progressione, attività, oggetti |
| Contenuti | [Indice](06-content/README.md) | missioni, dialoghi, narrazione emergente, eventi e catastrofi |
| Pompei | [Indice](07-pompeii-demo/README.md) | ricerca, area, popolazione, sistemi e criteri della vertical slice |
| UI/UX | [Indice](08-ux/README.md) | interfaccia, flussi, controlli, camera e accessibilità |
| Arte/Audio | [Indice](09-art-audio/README.md) | direzione artistica, audio, musica, voce e animazioni |
| Technical Design | [Indice](10-technical/README.md) | architettura, UE5, dati, save, performance, strumenti, pipeline, sicurezza |
| Produzione | [Indice](11-production/README.md) | roadmap, backlog, testing, Git, CI, team, piattaforme e release |
| Analisi future | [Indice](12-future-analysis/README.md) | multiplayer, modding, live operations, cloud, VR |
| Appendici | [Indice](appendices/README.md) | glossario e template |

Documenti trasversali: [mappa documentale](00-governance/documentation-map.md), [matrice dipendenze](00-governance/system-dependency-matrix.md), [registro decisioni](00-governance/decision-log.md), [questioni aperte](00-governance/open-questions.md), [registro rischi](11-production/risk-register.md) e [roadmap documentale](11-production/roadmap-backlog/documentation-roadmap.md).

Conservare e sviluppare la responsabilità canonica descritta da questo documento all'interno della Game Bible.

## Descrizione

Il contenuto preesistente costituisce la baseline del dominio. Questa sezione normalizza il documento secondo il contratto minimo della nuova architettura senza sostituirne le informazioni.

## Ambito

Il perimetro è quello definito nelle sezioni precedenti; implementazione e asset restano esclusi finché non saranno autorizzati da milestone e decisioni formali.

## Dipendenze

- [Standard documentale](00-governance/documentation-standard.md)
- [Visione creativa](01-vision/creative-vision.md)

## Collegamenti agli altri documenti

- [Indice generale](README.md)
- [Mappa documentale](00-governance/documentation-map.md)
- [Registro decisioni](00-governance/decision-log.md)
- [Questioni aperte](00-governance/open-questions.md)

## Decisioni ancora aperte

- Owner e reviewer nominali.
- Stato di approvazione e profondità richiesta dalla roadmap documentale.
- Eventuali confini da riallineare con i nuovi sottodomini canonici.

## TODO

- Collegare il contenuto ai nuovi documenti specializzati pertinenti.
- Assegnare ownership, versione e milestone.
- Aggiungere requisiti, fonti, rischi, test e Definition of Done durante l'approfondimento.
