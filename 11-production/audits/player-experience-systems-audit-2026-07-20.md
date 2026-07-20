# Audit dei sistemi di esperienza del giocatore — 2026-07-20

## Scopo

Registrare copertura, coerenza, rischi e lacune di missioni, narrazione emergente, eventi, UI/UX e audio.

## Descrizione

La revisione ha imposto un contratto epistemico: simulazione e ledger possiedono i fatti; contenuti, interfaccia e audio li selezionano senza acquisire onniscienza o autorità di dominio.

## Ambito

Documenti canonici in `06-content`, `08-ux`, `09-art-audio` e registri correlati. Non include implementazione, mockup, registrazioni o asset.

## Risultati

| Area | Esito | Bloccante S4 |
|---|---|---|
| Missioni/situazioni | S3 | catalogo e golden situations P0 |
| Narrazione emergente | S3 | corpus storylet, budget e test longitudinali |
| Eventi D0–D5 | S3 | hazard, frequenze, eruzione e benchmark |
| UI/UX | S3 | prototipi, target accessibilità e test utenti |
| Audio/lingue | S3 | bible linguistica, corpus, mix e budget |

## Correzioni applicate

Eliminata autorità dei quest marker; resi persistenti fallimento e aftermath; separate prospettive dai fatti; introdotti budget per eventi, thread e notifiche; definite UI epistemica, equivalenza input, accessibilità nativa e selezione audio anti-ripetizione.

## Verifiche e rischi

R-057–R-063 coprono artificialità, causalità, overload, onniscienza, ripetizione e accessibilità. Gate editoriale: link, README, sezioni minime e `git diff --check`; gate S4: Q-223–Q-228.

## Dipendenze

- [Missioni](../../06-content/quests/quest-framework.md)
- [Narrazione](../../06-content/narrative/emergent-narrative.md)
- [Eventi](../../06-content/events/dynamic-event-framework.md)
- [UI](../../08-ux/ui/ui-architecture.md)
- [Audio](../../09-art-audio/audio/audio-system.md)

## Collegamenti agli altri documenti

- [Readiness](../roadmap-backlog/implementation-readiness-matrix.md)
- [Rischi](../risk-register.md)
- [Questioni aperte](../../00-governance/open-questions.md)

## Decisioni ancora aperte

- Q-223–Q-228.
- Owner e reviewer nominali Narrative, UX, Accessibility, Audio e Linguistic History.

## TODO

- Ripetere audit dopo prototipi documentali e corpus P0.
- Allineare tutti i moduli specialistici ancora S0–S2.
