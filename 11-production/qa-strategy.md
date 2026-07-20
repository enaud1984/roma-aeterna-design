# Strategia QA

**ID:** PRD-QA-001
**Stato:** Draft

## Obiettivo

Verificare non solo singole feature, ma stabilità e plausibilità delle interazioni nel tempo.

## Livelli

Validazione dati e fonti; test di regole/invarianti; test di contratti tra sistemi; scenari end-to-end; soak/time-lapse; performance; salvataggi/migrazioni; contenuti/localizzazione; accessibilità; review storica e di rappresentazione.

## Oracoli di simulazione

Quando non esiste un risultato unico, testare invarianti e intervalli: conservazione delle risorse, nessuna posizione impossibile, deadline avanzate, distribuzioni plausibili, causalità presente, assenza di crescita infinita. Semi controllati permettono riproduzione.

## Scenari aurei

Giornata ordinaria senza player; scarsità di grano; festa; perdita di un agente chiave; cambio proprietà; voce falsa; conflitto contrattuale; ritorno dopo lunga assenza; aggregazione/raffinamento; salvataggio durante transazione.

## Historical QA

Campioni per rischio, non soltanto per quantità: elementi iconici, sensibili, controversi e riusati ricevono priorità. Ogni deviazione deve avere ADR o provenance note.

## Exit

Nessun bug critico di duplicazione/perdita; nessun collasso sistemico negli orizzonti concordati; cause disponibili per gli eventi chiave; criteri accessibilità core superati; review storica e sensibilità chiusa per lo scope.

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
