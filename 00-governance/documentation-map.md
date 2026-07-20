# Mappa completa della documentazione

## Scopo

Offrire una vista navigabile e definitiva dell'architettura della Game Bible.

## Descrizione

La mappa collega tutte le macroaree. Ogni README di area elenca i documenti figli, permettendo di raggiungere ogni specifica con due passaggi dall'indice principale.

## Ambito

Include documentazione creativa, storica, sistemica, tecnica, produttiva e futura; non include codice o asset.

## Macroaree

- [Visione del Progetto](../01-vision/README.md) — Visione, principi, promessa, scope e Game Design Bible.
- [Ambientazione Storica](../02-historical-foundation/README.md) — Metodo storico, cronologie, fonti, controversie e rappresentazione.
- [Mondo di Gioco](../03-world/README.md) — Geografia, regioni, città, edifici, infrastrutture e siti rurali.
- [Sistemi di Simulazione](../04-simulation/README.md) — Architettura del mondo vivo e domini sociali, economici, istituzionali e fisici.
- [Giocatore e Gameplay](../05-player/README.md) — Esperienza, personaggio, progressione, attività, oggetti e inventario.
- [Contenuti e Narrazione](../06-content/README.md) — Missioni, situazioni, dialoghi, narrazione emergente ed eventi.
- [Pompei e Vertical Slice](../07-pompeii-demo/README.md) — Ricerca, popolazione, economia, area e criteri della demo.
- [UI, UX e Accessibilità](../08-ux/README.md) — Interfacce, flussi, informazione, controlli e accessibilità.
- [Arte, Audio e Animazione](../09-art-audio/README.md) — Direzione visiva e sonora, musica, voce e animazioni.
- [Technical Design](../10-technical/README.md) — Architettura, UE5, dati, salvataggi, performance, strumenti, pipeline e sicurezza.
- [Produzione e QA](../11-production/README.md) — Roadmap, backlog, testing, Git, CI, organizzazione e release.
- [Analisi Future](../12-future-analysis/README.md) — Multiplayer e altre possibilità future esplicitamente fuori dallo scope della demo.
- [Appendici](../appendices/README.md) — Glossario, template e materiali di supporto.

## Percorsi trasversali

- **Dalla promessa al test:** [Visione](../01-vision/README.md) → [Game Design Bible](../01-vision/game-design-bible/README.md) → [Gameplay](../05-player/gameplay/README.md) → [Testing](../11-production/testing/README.md).
- **Dalla fonte al contenuto:** [Fonti](../02-historical-foundation/sources/README.md) → [Mondo](../03-world/README.md) → [Contenuti](../06-content/README.md) → [Historical QA](../11-production/testing/historical-qa.md).
- **Dal sistema ai dati:** [Simulazione](../04-simulation/README.md) → [Architettura tecnica](../10-technical/architecture/README.md) → [Modello dati](../10-technical/data/README.md) → [Salvataggi](../10-technical/save-system/README.md).
- **Dalla demo alla produzione:** [Pompei](../07-pompeii-demo/README.md) → [Scope demo](../07-pompeii-demo/design/README.md) → [Backlog](../11-production/roadmap-backlog/README.md) → [Release readiness](../11-production/testing/release-readiness.md).
- **Dall'audit alla correzione:** [Audit documentali](../11-production/audits/README.md) → [Registro canonico](canonical-document-register.md) → [Decisioni](decision-log.md) → [Roadmap](../11-production/roadmap-backlog/documentation-roadmap.md).

## Dipendenze

- [Standard documentale](documentation-standard.md)
- [Registro decisioni](decision-log.md)

## Collegamenti agli altri documenti

- [Indice generale](../README.md)
- [Matrice delle dipendenze](system-dependency-matrix.md)
- [Roadmap documentale](../11-production/roadmap-backlog/documentation-roadmap.md)

## Decisioni ancora aperte

- Eventuali split ulteriori emersi durante l'approfondimento.
- Owner e reviewer nominali di ogni macroarea.

## TODO

- Generare in futuro un inventario automatizzato dei documenti.
- Aggiungere stato e versione aggregati per macroarea.
- Auditare la mappa a ogni milestone.
