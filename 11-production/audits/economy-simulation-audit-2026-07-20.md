# Audit della progettazione economica — 2026-07-20

## Scopo

Registrare copertura, coerenza, lacune e prove della macroarea economia simulata.

## Descrizione

Audit documentale della baseline successiva all'introduzione del modello conservativo, livelli E0–E5, moneta e prezzi, diritti, contratti, credito, 21 filiere, carriere e slice economica di Pompei.

## Ambito

Documenti canonici in `04-simulation/economy-production`, framework delle carriere, demo economia e registri di governance. Non certifica valori storici quantitativi né prestazioni runtime.

## Risultati

| Area | Esito | Evidenza |
|---|---|---|
| Autorità dati | conforme S3 | beni, custodia, proprietà, moneta e obbligazioni separati |
| Conservazione | conforme S3 | invarianti e transazioni atomiche definite |
| Scala | conforme S3 | livelli E0–E5 e riconciliazione |
| Filiere | copertura strutturale completa | 21 dossier con template obbligatorio |
| Professioni | copertura sistemica S3 | famiglie di carriera e ciclo completo |
| Demo | definita S3 | spina grano-pane, tre status, shock e metriche |
| Storia quantitativa | incompleta | Q-208–Q-211; nessun valore inventato |
| Sistemi specialistici | incompleti | lavoro, salari, tasse, logistica e crisi richiedono passaggio S3 dedicato |

## Correzioni applicate

- Imposta contabilità conservativa e causalità delle mutazioni.
- Separati contratto, debito, proprietà, possesso e custodia.
- Reso proporzionale l'impatto del giocatore dal mercato locale all'Impero.
- Trattate persone schiavizzate come NPC persistenti in un regime coercitivo, non come oggetti.
- Trasformate professioni da livelli lineari a ruoli, opportunità e rischi reversibili.
- Aggiunti scenari di baseline, shock, fallimento, exploit e save/load.

## Lacune e rischi residui

Valori storici e budget tecnici sono bloccanti; professioni e filiere P0 devono essere selezionate; regole giuridiche per status richiedono review specialistica; i sottodocumenti economici non ancora approfonditi restano S0–S2. R-037–R-043 governano i principali rischi.

## Verifiche

Il gate editoriale richiede link Markdown validi, README per cartella, sezioni minime, `git diff --check` pulito e nessun file sorgente/asset. I risultati sono registrati nel commit di questa attività.

## Dipendenze

- [Modello economico](../../04-simulation/economy-production/economic-model.md)
- [Filiere](../../04-simulation/economy-production/supply-chains.md)
- [Carriere](../../04-simulation/professions-education/career-framework.md)
- [Demo](../../07-pompeii-demo/demo-economy.md)

## Collegamenti agli altri documenti

- [Rischi](../risk-register.md)
- [Questioni aperte](../../00-governance/open-questions.md)
- [Readiness](../roadmap-backlog/implementation-readiness-matrix.md)

## Decisioni ancora aperte

- Q-207–Q-211.
- Owner/reviewer nominali per economia e storia economica.

## TODO

- Ripetere audit dopo dossier quantitativo e approfondimento dei sottosistemi.
- Allegare benchmark E0–E5 quando l'implementazione sarà autorizzata.
