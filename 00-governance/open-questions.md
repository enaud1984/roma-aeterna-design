# Registro delle domande aperte

Le domande sono ordinate per impatto. Chiudere una domanda significa creare o aggiornare un ADR, non cancellarla.

## Bloccanti per la definizione del prodotto

| ID | Domanda | Impatto | Owner | Criterio di chiusura |
|---|---|---|---|---|
| Q-001 | In quale anno e stagione si svolge la demo? | canone, eruzione, personaggi, economia | Game Direction + History | confronto di almeno tre finestre e ADR |
| Q-002 | L'eruzione del 79 d.C. è dentro l'orizzonte giocabile? | struttura temporale e promessa | Game Direction | test di compatibilità coi pilastri |
| Q-003 | Quali piattaforme e prestazioni target? | densità, input, memoria | Tech Direction | target hardware e budget firmati |
| Q-004 | Quale rating e pubblico minimo? | schiavitù, violenza, sessualità, linguaggio | Direction + Legal | policy contenuti approvata |
| Q-005 | Qual è il modello commerciale? | scope, persistenza, live operations | Production | business brief approvato |
| Q-006 | Quale prospettiva e modello di camera adotta il gioco? | controlli, animazione, UX, combattimento | Game + UX Direction | prototipi comparativi e ADR |
| Q-007 | La successione generazionale è una promessa del prodotto o un'estensione? | durata, morte, famiglia, save | Game Direction | scenario, costo e ADR |

## Bloccanti per Pompei

| ID | Domanda | Documento che la assorbirà |
|---|---|---|
| Q-101 | Quali insulae e aree extraurbane sono fisicamente esplorabili? | [Scope Pompei](../07-pompeii-demo/pompeii-vertical-slice.md) |
| Q-102 | Quanti NPC nominati, persistenti e aggregati? | [Popolazione demo](../07-pompeii-demo/demo-population.md) |
| Q-103 | Quali mestieri sono completi nel slice? | [Economia demo](../07-pompeii-demo/demo-economy.md) |
| Q-104 | Quali lingue sono rappresentate e come? | [Dialogo](../06-content/dialogue-and-language.md) |
| Q-105 | Quale granularità per schiavitù, manomissione e patronato? | [Status sociale](../04-simulation/social-status-and-law.md) |
| Q-106 | PVS-1 include fisicamente Foro–Anfiteatro, o uno scope Small/Extended? | [Area giocabile](../07-pompeii-demo/design/playable-area.md) |
| Q-107 | Quali porte, necropoli e villa suburbana diventano mappe locali? | [Rete regionale](../07-pompeii-demo/design/regional-connections.md) |
| Q-108 | Quali edifici economici e case sono P0 utilizzabili? | [Edifici](../07-pompeii-demo/design/accessible-buildings.md) |
| Q-109 | Quale modello geoarcheologico adottare per porto, Sarno e paleo-costa? | [Framework geografico](../03-world/geography/geographic-framework.md) |
| Q-110 | Quali target numerici N0–N5 e quanti NPC persistenti per Pompei? | [Livelli NPC](../04-simulation/npc-population-ai/simulation-levels.md) |
| Q-111 | Quali bisogni e azioni sono P0 nella demo? | [Bisogni](../04-simulation/npc-population-ai/needs-ai.md) |
| Q-112 | Quale budget di ricordi ed edge sociali per individuo? | [Memoria](../04-simulation/npc-population-ai/memory.md) |
| Q-113 | Quali grandi eventi sociali entrano nel vertical slice? | [Risposte eventi](../04-simulation/npc-population-ai/social-event-responses.md) |

## Ricerca e sensibilità

- Come rappresentare la schiavitù come istituzione strutturale senza ridurla a valuta o spettacolo?
- Come distinguere pratiche religiose domestiche, civiche, misteriche e imperiali senza usare categorie moderne improprie?
- Quali gruppi sono scarsamente attestati e richiedono una ricostruzione C o una licenza D più esplicita?
- Quali meccaniche rischiano di premiare comportamenti anacronistici pur presentandoli come storici?

## Governance e mantenibilità

| ID | Domanda | Impatto | Owner | Criterio di chiusura |
|---|---|---|---|---|
| Q-201 | Quali metadata documentali saranno validati automaticamente? | autorità, stato, owner, versioni | Technical Writing + Tools | schema e validatore approvati |
| Q-202 | Qual è la soglia per unire uno scheletro troppo piccolo al documento genitore? | navigabilità e frammentazione | Game Direction | regola basata su responsabilità e lifecycle |
| Q-203 | Con quale frequenza eseguire l'audit globale? | deriva e costo di manutenzione | Production | cadence inserita nella roadmap |
| Q-204 | Quale tecnologia UE5 realizzerà dispatch, storage e schema registry? | implementazione di SYS-EVT senza alterarne la semantica | Technical Direction | ADR comparativa dopo target piattaforma |
| Q-205 | Quali retention e granularità del journal sono sostenibili nella demo? | salvataggi, replay, disco e recovery | Tech + Design | benchmark e budget approvati |
| Q-206 | Qual è il massimo confine transazionale tra sistemi e città? | atomicità, deadlock e recovery | Software Architecture | scenari critici e ADR |

| Q-207 | Quali filiere e professioni sono P0 nella demo oltre alla spina grano-pane? | scope, luoghi, contenuti e test | Game Design + Production | scenario end-to-end e budget approvati |
| Q-208 | Quali unità di conto, denominazioni e regole di arrotondamento usa la data canonica? | prezzi, pagamenti, UI e save | Historical + Economy Design | dossier numismatico locale validato |
| Q-209 | Quali panieri e profili household calibrano accessibilità e inflazione locale? | bilanciamento e crisi | Economy Design + Historical | campioni, intervalli e sensitivity review |
| Q-210 | Quali valori di resa, capacità, salario, interesse, affitto e trasporto sono sostenibili e documentati? | tutte le filiere e carriere | Historical + Economy + QA | dossier tematico e test 90 giorni |
| Q-211 | Quali regole di proprietà, contratto e credito valgono per ciascuno status demo? | percorsi cittadino/liberto/schiavo | Legal History + Design | matrice status-atto-rimedio approvata |

| Q-212 | Quale matrice status-atto-capacità vale nella Pompei canonica? | diritto, economia, famiglia, politica | Legal History + Design | profilo locale validato A–E |
| Q-213 | Quali magistrature, elezioni e procedure locali sono attive alla data iniziale? | carriera e amministrazione | Political History + Design | dossier epigrafico/procedurale approvato |
| Q-214 | Quali culti, sacerdozi, feste e comunità sono P0? | religione, calendario, folla e audio | Religious History + Content | matrice luogo-calendario-fonte approvata |
| Q-215 | Quali forme di manomissione e capacità dei liberti sono P0? | schiavitù, mobilità, famiglia, lavoro | Legal/Social History + Ethics | scenari e review specialistica |
| Q-216 | Quali illeciti, procedure e pene possono essere rappresentati nella demo? | crimine, UX, sicurezza e rating | Legal History + Narrative + Safety | matrice e policy contenuti approvate |

| Q-217 | Quali armi, armature e forme di scontro sono P0 a Pompei? | combat, animazione, audio, legge | Combat + Historical + Production | matrice equipaggiamento/scenario approvata |
| Q-218 | Quali camera, controllo direzionale e assistenze rendono il combattimento leggibile? | UX, accessibilità e animazione | Combat + UX + Accessibility | prototipo documentale e test utenti |
| Q-219 | Quale granularità anatomica e policy di morte usa la demo? | trauma, rating, eredità e save | Health + Narrative + Safety | golden scenarios e policy approvati |
| Q-220 | Quali livelli M0–M5 e budget di combattenti/folle sono attivi nella demo? | performance e scope | Technical + AI + Production | benchmark e soglie approvati |
| Q-221 | Quale profilo militare data/provincia governa organici, paga e carriera? | esercito e storia | Military History + Design | dossier A–E approvato |
| Q-222 | Il trionfo resta evento remoto nell'orizzonte Pompei? | scope, Roma, folla e produzione | Game Direction + Historical | decisione formale di milestone |

| Q-223 | Quale mix di situazioni principali, professionali, sociali e sistemiche è P0? | contenuti e durata demo | Narrative + Quest + Production | catalogo e copertura approvati |
| Q-224 | Quali budget di thread, eventi e notifiche impediscono overload? | narrativa, UX e performance | Narrative + UX + Technical | soak test e soglie approvati |
| Q-225 | Quale assistenza di navigazione e HUD è predefinita? | accessibilità e identità UX | UX + Accessibility + Direction | test utenti e preset approvati |
| Q-226 | Quali target di accessibilità e piattaforme/input governa la demo? | UI, controlli, audio e QA | Accessibility + Platform + UX | matrice requisiti approvata |
| Q-227 | Quale proporzione italiano/latino e quale profilo di pronuncia? | voce, sottotitoli e autenticità | Audio + Linguistic History | bible linguistica e corpus P0 |
| Q-228 | Quali frequenze D0–D5 e quale collocazione temporale dell'eruzione? | eventi, scope e storia | Game Direction + Historical | timeline e matrice hazard approvate |

| Q-229 | Quale versione UE5 e quali piattaforme costituiscono la baseline? | API, plugin, build, performance | Technical Direction + Platform | support matrix e ADR approvati |
| Q-230 | MassEntity/MassGameplay supera il benchmark Pompei rispetto ai fallback? | NPC, folla, memoria e authoring | AI + Performance + Tools | spike, metriche e fallback approvati |
| Q-231 | Qual è lo split StateTree/Behavior Tree/domain state machine P0? | AI, combat e debug | AI + Gameplay Architecture | golden traces e budget approvati |
| Q-232 | Quali grid, HLOD, Data Layer e strategia interni usa PVS-1? | streaming, memoria e workflow | World + Performance + Art | benchmark scenes e ADR |
| Q-233 | Quali plugin UE integrati/terzi sono ammessi P0? | sicurezza, build e maintenance | Technical + Security + Production | plugin registry e exit plan |
| Q-234 | Quale packaging di moduli/plugin bilancia isolamento e build time? | ownership e iterazione | Software Architecture + Build | dependency graph e build benchmark |

| Q-235 | Quali formati fisici, indici e store materializzano gli schemi di dominio? | dati, query, migrazioni e tooling | Data Architecture | spike e ADR comparativo |
| Q-236 | Qual è la finestra di compatibilità di schema e contenuti? | release, save e supporto | Data + Production | policy versioni approvata |
| Q-237 | Come si partizionano e indicizzano città, persone, eventi e lotti? | memoria, streaming e query | Data + Simulation | workload e benchmark |
| Q-238 | Quale granularità distingue istanze oggetto, lotti e aggregati? | inventari, economia e save | Economy + Data | invarianti e scenari P0 |
| Q-239 | Quali formato, compressione e checksum usa il save fisico? | dimensione, prestazioni e recovery | Save + Platform | prototipo e failure injection |
| Q-240 | Quante versioni save sono supportate e come si distribuiscono le migrazioni? | compatibilità giocatore | Save + Release | policy supporto approvata |
| Q-241 | Quanti slot, autosave e checkpoint ruotano e con quali trigger? | UX, disco e recovery | UX + Save | playtest e budget disco |
| Q-242 | Cloud save e conflitti sono fuori scope demo o requisito di piattaforma? | account, privacy e recovery | Product + Platform | scope piattaforme approvato |
| Q-243 | Quali hardware, risoluzione e preset definiscono la baseline? | tutti i budget tecnici | Technical Direction | target matrix approvata |
| Q-244 | Quali margini CPU/GPU restano riservati a contenuti e variabilità? | scope e stabilità frame | Performance + Production | benchmark PVS-1 |
| Q-245 | Quali conteggi NPC, folla e animazione sono accettabili per Pompei? | mondo, AI e presentazione | AI + World + Performance | scene benchmark approvate |
| Q-246 | Quali limiti finali valgono per install, save e caricamenti? | piattaforma e UX | Platform + Performance | test hardware target |
| Q-247 | Quale baseline I/O governa World Partition e streaming? | hitch, celle e install | Platform + World | profilo storage approvato |
| Q-248 | Quali tool P0, owner e workflow entrano nella fondazione tecnica? | authoring e staffing | Tools + Production | roadmap e prototipi UX |
| Q-249 | Quali metriche, retention ed export sono ammessi nella telemetria locale? | privacy, disco e QA | Tools + Security | policy dati approvata |
| Q-250 | Quali runner, licenze e capacità sostengono CI e build? | tempi, costo e supply chain | Build + Production | proof di pipeline |
| Q-251 | Quando creare/proteggere `main` e quale branch alimenta l'implementazione? | governance repository | Production + Technical Direction | decisione amministrativa |
| Q-252 | Quali pattern, quote, locking e recovery valgono per Git LFS e artifact? | asset pesanti e collaborazione | Asset + Build | prova clone/build e ADR |

Vedere [etica e rappresentazione](../02-historical-foundation/ethics-and-representation.md) e [framework storico](../02-historical-foundation/historical-framework.md).

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
