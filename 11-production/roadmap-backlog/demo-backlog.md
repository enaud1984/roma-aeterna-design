# Backlog eseguibile della demo

**ID:** PRD-DEMO-BACKLOG-001
**Stato:** Prioritizzato; stime e assegnazioni da produrre dopo il gate Ready

## Scopo

Tradurre gli epic in feature e user story verificabili, ordinate per dipendenza e valore della vertical slice.

## Descrizione

`Must` è indispensabile alla promessa; `Should` entra solo se budget e milestone restano verdi; `Could` non può ritardare un Must. Ogni voce deve superare la [Definition of Ready](definition-of-ready.md) prima dell'implementazione.

## Ambito

Backlog iniziale di prodotto e enablement. Non include task di codice, asset list esecutiva o stime in giorni-persona.

## Backlog feature

| ID | Epic | Feature | Pri. | Dipendenze | Milestone | Accettazione sintetica |
|---|---|---|---:|---|---|---|
| F-001 | EP-01 | baseline progetto/moduli/config | Must | READY | PT | build pulita e grafo valido |
| F-002 | EP-01 | logging, errori e test map | Must | F-001 | PT | errore tracciabile e smoke pass |
| F-003 | EP-01 | CI build/test/docs | Must | F-001 | PT | clone pulito produce artifact |
| F-004 | EP-02 | orologio e calendario 77 d.C. | Must | F-001 | PT | ordine, pause e scadenze |
| F-005 | EP-02 | event bus e scheduler | Must | F-004 | PT | causalità/versione/back-pressure |
| F-006 | EP-02 | save manuale/autosave/recovery | Must | F-004–005 | PT | golden save e fault injection |
| F-007 | EP-02 | tier e simulazione lontana | Must | F-005 | PG | conservazione tra livelli |
| F-008 | EP-03 | graybox spina urbana | Must | GIS, F-001 | PG | hub continui e bordi diegetici |
| F-009 | EP-03 | accessi e interazioni edificio | Must | F-008 | PG | orari/status/proprietà |
| F-010 | EP-03 | streaming/navigation baseline | Must | F-008 | PA | budget e nessuna perdita stato |
| F-011 | EP-04 | tre profili iniziali | Must | F-004, schema | PG | dati completi e onboarding |
| F-012 | EP-04 | bisogni/salute/riposo | Must | F-011 | PG | conseguenze leggibili, non grind |
| F-013 | EP-04 | inventario proprietà/custodia | Must | F-011 | PG | zero duplicazione/ownership leak |
| F-014 | EP-05 | NPC visibili e routine | Must | F-007–010 | PA | planner stabile e fallback |
| F-015 | EP-05 | conoscenza/memoria/pettegolezzo | Must | F-014 | PA | provenance e leak test |
| F-016 | EP-05 | relazioni e reputazioni locali | Must | F-015 | PA | effetti per comunità |
| F-017 | EP-05 | folla mercato/rito | Should | F-010, F-014 | VS | budget e comportamento non uniforme |
| F-018 | EP-06 | filiera pane end-to-end | Must | F-013–016 | PA | ledger, qualità e scarti |
| F-019 | EP-06 | loop tessile/fullonica | Must | F-013–016 | PA | lotto, danno, paga e cliente |
| F-020 | EP-06 | servizio/consegna/custodia | Must | F-009, F-013–16 | PA | ordine, ricevuta e conflitto |
| F-021 | EP-06 | prezzi, credito, debiti e affitto | Must | F-018–020 | VS | stabilità e insolvenza recuperabile |
| F-022 | EP-07 | matrice status-capacità | Must | ricerca legale, F-011 | PA | tutti gli atti P0 validati |
| F-023 | EP-07 | household/unione/dipendenti | Must | F-016, F-022 | VS | differenze matrimonio/contubernium |
| F-024 | EP-07 | eredità e continuazione | Must | F-006, F-023 | VS | identità non copiata |
| F-025 | EP-07 | culto domestico e pubblico | Must | calendario, F-009, F-016 | VS | rito, accesso, memoria |
| F-026 | EP-07 | favori e autorità locale | Should | F-016, F-022 | VS | nessuna carriera garantita |
| F-027 | EP-08 | runtime situazioni persistenti | Must | F-005–006 | PA | stati/scadenze/aftermath |
| F-028 | EP-08 | dialogo epistemico | Must | F-015–016, F-027 | PA | fonti, fallback e loc |
| F-029 | EP-08 | situazione grano condivisa | Must | F-018, F-021, F-027 | VS | tre ingressi, sei esiti |
| F-030 | EP-08 | situazioni professionali/sociali | Must | F-019–028 | VS | copertura catalogo P0 |
| F-031 | EP-09 | furto/frode/testimoni/caso | Must | F-015, F-022, F-027 | VS | risposta non onnisciente |
| F-032 | EP-09 | rissa, fuga, resa e trauma | Should | F-012, F-031 | VS | contatto e recovery |
| F-033 | EP-10 | diario/mappa/notifiche | Must | F-015, F-027 | PA | nessun indicatore onnisciente |
| F-034 | EP-10 | inventario/economia/salute UI | Must | F-012–013, F-021 | PA | proprietà e incertezza leggibili |
| F-035 | EP-10 | accessibilità/input | Must | target approvati | VS | matrice P0 completabile |
| F-036 | EP-10 | soundscape e dialoghi audio | Must | F-008, F-028 | VS | zone, varianti e cooldown |
| F-037 | EP-11 | validator dati/storia | Must | schema, fonti | PT | errori blocker impediscono publish |
| F-038 | EP-11 | editor eventi/dialoghi/situazioni | Must | F-005, F-027–028 | PA | change set, preview e undo |
| F-039 | EP-11 | debugger/telemetria/profiler | Must | F-002, F-007 | PT–PA | repro package e budget |
| F-040 | EP-11 | generatore NPC vincolato | Should | F-014–016, F-037 | PA | seed e distribuzioni approvate |
| F-041 | EP-12 | suite golden/soak/performance | Must | feature P0 | DI | gate automatici |
| F-042 | EP-12 | loc, accessibilità e historical QA | Must | contenuti chiusi | DI | zero blocker |
| F-043 | EP-12 | packaging/release/rollback | Must | F-003, F-041–042 | DP | artifact immutabile |
| F-044 | EP-12 | polish basato su playtest | Must | VS completa | DI–DP | metriche acceptance raggiunte |

Legenda milestone: PT prototipo tecnico; PG prototipo gameplay; PA pre-alpha; VS vertical slice; DI demo interna; DP demo pubblicabile.

## User story rappresentative

| ID | Feature | User story | Criteri principali |
|---|---|---|---|
| US-001 | F-011 | Come giocatore scelgo un'origine e comprendo capacità e obbligo iniziali senza schermata enciclopedica. | prima scelta autonoma entro 20 min; nessuna regola falsa |
| US-002 | F-018 | Come lavoratore trasformo input reali in pane e ricevo un compenso contestabile. | input/scarti/output/ledger conservati |
| US-003 | F-015 | Come giocatore posso scoprire chi sa una notizia e perché, senza che tutti reagiscano subito. | provenance interrogabile; ritardo credibile |
| US-004 | F-021 | Come debitore posso negoziare, pagare, fallire o trovare lavoro alternativo. | almeno tre esiti persistenti, nessun soft-lock inevitabile |
| US-005 | F-023 | Come personaggio costruisco un household coerente con il mio status. | capacità e termini distinti; relazioni persistenti |
| US-006 | F-024 | Come erede continuo nel mondo modificato senza ricevere memoria o abilità del defunto. | trasferimenti validi e recap epistemico |
| US-007 | F-025 | Come praticante partecipo a un rito perché ne conosco tempo, luogo e comunità. | accesso/calendario/offerta e conseguenze sociali |
| US-008 | F-031 | Come testimone posso denunciare, tacere o alterare una prova e il caso reagisce alle fonti disponibili. | nessuna autorità onnisciente |
| US-009 | F-032 | Come persona minacciata posso evitare, fuggire, arrendermi o combattere. | alternative leggibili e trauma persistente |
| US-010 | F-033 | Come giocatore consulto impegni e conoscenze senza vedere obiettivi o luoghi sconosciuti. | UIFact leak suite a zero |
| US-011 | F-006 | Come giocatore recupero l'ultimo stato valido dopo un salvataggio interrotto. | slot precedente intatto e report recovery |
| US-012 | F-039 | Come QA riproduco una divergenza con build, seed, save e trace. | repro deterministico sul golden scenario |

Ogni feature sarà scomposta in ulteriori story/task soltanto durante planning della milestone; i task non devono cambiare outcome o scope senza change control.

## Regole di priorità e taglio

Ordine di protezione: persistenza e causalità; differenze di status; loop lavoro/economia; relazioni/conoscenza; accessibilità; contenuti; ampiezza ambientale e polish. In caso di sforamento si tagliano Should, quantità e duplicazioni di edifici prima dei Must.

## Dipendenze

- [Epic](epics.md)
- [Milestone](milestones.md)
- [Scope sistemi](../../07-pompeii-demo/design/demo-systems-scope.md)
- [Scope contenuti](../../07-pompeii-demo/design/demo-content-scope.md)

## Collegamenti agli altri documenti

- [DoR](definition-of-ready.md)
- [DoD](definition-of-done.md)
- [READY](../../READY_FOR_IMPLEMENTATION.md)
- [Rischi](../risk-register.md)

## Decisioni ancora aperte

- Owner, stime, capacità, ordine intra-milestone e feature Should.
- Toolchain, piattaforme e target che possono modificare criteri tecnici.

## Criteri di completamento

Ogni Must ha owner, stima, dipendenze, criterio, test e milestone; nessun Must dipende da un Could o sistema escluso.

## TODO

- Assegnare owner e range di stima dopo greenlight.
- Collegare test case e issue tracker quando scelto.
