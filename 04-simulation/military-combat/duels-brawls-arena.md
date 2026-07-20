# Risse, duelli e arena

## Scopo

Definire contesti di violenza con regole sociali, giuridiche, rituali e spettatoriali differenti.

## Descrizione

Il motore corporeo è condiviso, ma intenzione, equipaggiamento, autorità, resa, intervento e conseguenze cambiano per contesto. “Duello” non assume automaticamente un istituto legale moderno; l'arena non è combattimento casuale senza organizzazione.

## Ambito

Rissa spontanea, conflitto concordato o ritualizzato solo se attestato, allenamento, combattimento non letale, spettacoli d'arena, organizzatori, partecipanti, pubblico e conseguenze.

## Matrice

| Contesto | Ingresso | Limiti | Uscite | Conseguenze |
|---|---|---|---|---|
| Rissa | escalation sociale | armi/spazio/intervento contestuali | separazione, fuga, resa, incapacità | danni, vendetta, denuncia, reputazione |
| Non letale | ordine, gioco, allenamento, cattura | tecniche/forza obiettivo, mai sicurezza garantita | immobilizzazione, tap/responsa, separazione | trauma, abuso, responsabilità |
| Duello | sfida/accordo attestato e testimoni | luogo, armi, condizioni e autorità | concessione, interruzione, ferita, morte | validità e sanzioni contestuali |
| Arena | contratto/status, programma e organizzatore | abbinamento, equipaggiamento, officianti e regole | decisione, resa se prevista, soccorso, morte | paga, fama, trauma, politica e pubblico |

## Flusso arena

Preparazione programma → selezione/contratti → sicurezza e folla → ingresso/rito → combattimento → decisione e soccorso → paga, memoria e conseguenze. Giochi seguono calendario e finanziamento; non sono continui. Grandi spettacoli competono con lavoro, risorse e altri eventi.

## Dati, eventi e casi limite

`ConflictRuleset`, accordi/contratti, partecipanti/status, arbitro/officiante, equipaggiamento, pubblico, esito e violazioni. Produce `ChallengeIssued`, `BrawlEscalated`, `ArenaBoutScheduled/Resolved`, `RulesViolated`; ascolta calendario, ferite, folla, ordine pubblico, patronato e finanze. Partecipante assente, arma vietata, resa ambigua, pubblico invade, organizzatore insolvente e morte durante non letale aprono conseguenze esplicite.

## Accuratezza, bilanciamento e performance

Ruoli, categorie, contratti e decisioni dell'arena richiedono profilo storico locale/temporale A–E; evitare miti cinematografici. Ricompense non compensano artificialmente letalità. Pubblico usa LOD di folla e osservazioni campionate, mantenendo NPC rilevanti.

## Dipendenze

- [Combattimento](combat-vision.md)
- [Gruppi e folla](group-combat.md)
- [Criminalità](../politics-law/criminality.md)
- [Giochi pubblici](../religion-calendar/public-games.md)

## Collegamenti agli altri documenti

- [Non letale](non-lethal-combat.md)
- [Ferite](injuries.md)
- [Calendario](../religion-calendar/calendar.md)

## Test e Definition of Done

Testare de-escalation/rissa, violazione, cattura non letale, duello interrotto, arena completa, folla, ferite e save/load. S4 dopo dossier storico, policy contenuti e scenari P0 approvati.

## Decisioni ancora aperte

- Quali forme entrano nella demo e con quale frequenza.
- Regole di resa/decisione dell'arena per il profilo scelto.

## TODO

- Collegare luoghi e calendario di Pompei.
- Definire contratti e ruoli del player non combattente.
