# Architettura della simulazione

**ID:** SIM-001
**Stato:** Draft

## Obiettivo

Coordinare sistemi autonomi senza pretendere la massima fedeltà ovunque. La simulazione deve essere coerente, osservabile, degradabile e scalabile dalla singola bottega alle relazioni imperiali.

## Principi

- Autorità unica per ogni tipo di stato: niente copie concorrenti di proprietà o relazione.
- Eventi significativi registrano causa, attori, luogo e tempo.
- I sistemi comunicano tramite contratti di dominio, non conoscenza interna reciproca.
- La frequenza di aggiornamento dipende dalla dinamica, non dall'importanza narrativa.
- L'aggregazione conserva quantità, vincoli e fatti già osservati.
- Il caso usa distribuzioni motivate e semi riproducibili per diagnosi.

## Livelli di simulazione

| Livello | Ambito | Esempio |
|---|---|---|
| L0 immediato | percezione e azione vicina | individuo naviga e usa un oggetto |
| L1 locale | luogo attivo | laboratorio produce per lotto |
| L2 urbano | distretto/città | mercato risolve domanda e offerta |
| L3 regionale | rotte e insediamenti remoti | flussi aggregati e rischi |
| L4 imperiale | macroeventi | guerra, fiscalità, nomine, trionfi |

La promozione a un livello più dettagliato ricostruisce uno stato compatibile; la retrocessione sintetizza senza perdere identità rilevanti.

## Ciclo concettuale

Osservare stato → generare intenzioni → risolvere conflitti e capacità → applicare transazioni → emettere eventi → aggiornare conoscenza → valutare conseguenze differite. L'ordine deve essere documentato per impedire vantaggi accidentali o duplicazioni.

## Stabilità

Ogni sistema dichiara sorgenti, pozzi, feedback e limiti. Test “mondo vuoto”, “mondo senza player”, “shock estremo”, “tempo accelerato” e “raffinamento da aggregato” sono obbligatori. Vedere [QA](../11-production/qa-strategy.md).

## Spiegabilità

Gli strumenti interni devono rispondere: perché un NPC ha agito, perché un prezzo è cambiato, da dove proviene un bene, perché una relazione è variata e quale regola ha risolto un conflitto. La UI giocatore filtra queste risposte secondo conoscenza e [UX](../08-ux/ux-principles.md).

## Dipendenze di dominio

[NPC](npc-life-simulation.md), [economia](economy.md), [status e diritto](social-status-and-law.md), [politica](politics-and-governance.md), [religione](religion.md), [guerra](war-and-military.md), [dati](../10-technical/data-model.md).

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
