# Registro degli elementi da verificare

## Scopo

Raccogliere tutte le affermazioni E e le decisioni che non possono entrare nel canone senza ulteriore evidenza.

## Descrizione

Ogni voce identifica l'evidenza mancante, l'impatto e il criterio di chiusura. “Da verificare” non significa falso: significa non sufficientemente delimitato o sostenuto.

## Ambito

Claim storici e quantitativi della Game Bible, con priorità alla vertical slice.

| ID | Elemento | Problema | Evidenza necessaria | Impatto | Owner | Gate |
|---|---|---|---|---|---|---|
| HV-001 | data iniziale della demo | anno, mese e stagione aperti | confronto storico/design + ADR | tutto il canone Pompei | Direction/History | prima dello scope finale |
| HV-002 | giorno e mese dell'eruzione | tradizione manoscritta e indizi divergenti | edizione critica + sintesi archeologica aggiornata | timeline/eruzione | History | prima di includere eruzione |
| HV-003 | popolazione di Pompei | stime dipendono da metodo e area | review demografica con intervalli | densità NPC | History/Simulation | prima del budget popolazione |
| HV-004 | insulae giocabili | selezione non approvata | atlante per fase e accessibilità | mappa demo | World/History | scope map |
| HV-005 | funzione/proprietà edifici | nomi moderni e attribuzioni variabili | scheda per edificio e fase | interazioni/economia | Archaeology | authoring edificio |
| HV-006 | prezzi e salari | dati discontinui per luogo/data/qualità | dossier monetario comparabile | economia | Economic History | bilanciamento |
| HV-007 | composizione household | dati individuali incompleti | scenari da epigrafia/material culture | popolazione/famiglia | Social History | casting |
| HV-008 | cristiani a Pompei | letture di graffiti controverse | review epigrafica specialistica | religione | Religion/Epigraphy | prima di contenuti cristiani |
| HV-009 | calendario festivo locale | calendario romano ≠ pratica locale completa | iscrizioni, fasti, culti attestati | eventi/religione | Religion | calendario demo |
| HV-010 | competenze delle autorità locali | rischio di importare procedure di Roma | dossier epigrafico/giuridico municipale | politica/diritto | Legal History | sistema istituzionale |
| HV-011 | procedura criminale locale | fonti normative tarde/frammentarie | casi e competenze per il I secolo | crimine/processi | Legal History | gameplay crimine |
| HV-012 | reclutamento accessibile a ciascuno status | varia per periodo/corpo/origine | diplomi, epigrafia, sintesi militare | carriera militare | Military History | post-slice |
| HV-013 | rete fognaria e gestione rifiuti per area | infrastruttura diseguale | rilievi per strada/edificio | salute/città | Archaeology | map authoring |
| HV-014 | malattie e prevalenze | diagnosi retrospettiva rischiosa | bioarcheologia + paleopatologia | salute | Bioarchaeology | sistema malattie |
| HV-015 | lingua e registri sociali | corpus non equivale a parlato completo | epigrafia, sociolinguistica, policy adattamento | dialoghi/audio | Linguistics | script/audio |
| HV-016 | collegamenti portuali di Pompei | ruolo di approdi e paleo-linea costiera | geoarcheologia e studi logistici | commercio/mappa | Geoarchaeology | world nodes |
| HV-017 | cave/miniere collegate alle filiere locali | provenienze da dimostrare | petrografia e studi di supply | produzione | Archaeometry | catene materiali |
| HV-018 | equipaggiamento “standard” militare | variabilità cronologica e individuale | corpus per decennio/corpo | arte/combattimento | Military/Material | asset brief |

## Flusso di chiusura

Ricerca → dossier → review → aggiornamento claim A–D → eventuale controversia/licenza → aggiornamento consumer. Una voce chiusa resta archiviata con esito e data.

## Criteri di accettazione

Ogni elemento E ha owner, impatto, evidenza richiesta e gate; nessun consumer lo presenta come fatto.

## Definition of Done

Nessun elemento E bloccante resta aperto per la milestone approvata.

## Dipendenze

- [Registro claim](historical-claims-register.md)
- [Metodologia](research-methodology.md)

## Collegamenti agli altri documenti

- [Questioni aperte](../../00-governance/open-questions.md)
- [Controversie](controversies-register.md)
- [Roadmap documentale](../../11-production/roadmap-backlog/documentation-roadmap.md)

## Decisioni ancora aperte

- Owner nominativi e date di review.

## TODO

- Collegare ogni HV ai documenti consumer specifici.
- Registrare esiti e fonti man mano che le voci vengono chiuse.

