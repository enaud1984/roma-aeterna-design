# Registro delle licenze creative

## Scopo

Documentare ogni compressione, composito o deviazione deliberata necessaria al gameplay, distinguendola dalla ricostruzione storica.

## Descrizione

Una licenza non aumenta la classe di attendibilità: resta D e deve preservare i vincoli storici che non sono oggetto della modifica.

## Ambito

Licenze già implicate dalla vertical slice e policy per quelle future.

| ID | Licenza | Necessità | Differenza storica | Guardrail | Consumer | Stato |
|---|---|---|---|---|---|---|
| CL-001 | mappa selettiva/compressa | costo e densità | omissione o compressione di distanze/accessi | nessun landmark spostato senza scheda; UI dichiara scala | Pompei/mappe | Proposed |
| CL-002 | NPC compositi | fonti non danno biografie complete | combina tratti plausibili | non attribuire azioni private a persone storiche reali | popolazione/narrazione | Accepted baseline |
| CL-003 | routine giornaliere sintetiche | rendere leggibile la città | orari precisi spesso non attestati | stagionalità/status; variazione; classe C/D | NPC/AI | Accepted baseline |
| CL-004 | prezzi normalizzati | leggibilità e bilanciamento | unità e serie antiche frammentarie | ratio e volatilità locali; nessun prezzo “imperiale” | economia/UI | Proposed |
| CL-005 | calendario leggibile | UX | conversioni e pratiche locali incomplete | conservare termini romani e segnare equivalenze | tempo/religione | Proposed |
| CL-006 | latino rappresentato tramite italiano | accessibilità | sostituzione linguistica | evitare idiomi moderni e registri sociali piatti | dialoghi/audio | Open |
| CL-007 | propagazione aggregata fuori mappa | performance | simula reti non agenti completi | ritardi, fonti e incertezza; nessuna onniscienza | mondo/economia/guerra | Accepted baseline |
| CL-008 | tre origini iniziali | onboarding | archetipi non esaustivi | status non è classe rigida; conseguenze storiche | player/demo | Proposed |
| CL-009 | procedure giuridiche sintetizzate | durata di gioco | comprime tempi/atti | autorità, prove, status e costi restano visibili | diritto/crimine | Open |
| CL-010 | combattimento leggibile | controllo e feedback | semplifica fisiologia e caos | ferite e resa plausibili; niente “spugne di danno” | combattimento | Open |

## Processo

Proposta → claim e vincoli → alternative → ethics/history/design review → approvazione ADR → comunicazione a consumer e test. Una licenza non approvata resta fuori dal canone.

## Criteri di accettazione

Motivazione, differenza, guardrail, consumer e stato sono espliciti; il giocatore non riceve l'adattamento come fatto storico.

## Definition of Done

Ogni elemento D della milestone ha una licenza approvata o una motivazione che dimostri che il registro non è applicabile.

## Dipendenze

- [Claim](historical-claims-register.md)
- [Etica](../ethics-and-representation.md)

## Collegamenti agli altri documenti

- [Controversie](controversies-register.md)
- [Anacronismi](anachronisms-register.md)
- [Decision log](../../00-governance/decision-log.md)

## Decisioni ancora aperte

- CL-001, 004–006, 009 e 010 richiedono prototipi documentali o ADR.

## TODO

- Collegare ogni licenza ai criteri di accettazione del sistema consumer.
