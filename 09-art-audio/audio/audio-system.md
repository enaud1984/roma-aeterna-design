# Sistema audio, voce e paesaggio sonoro

## Scopo

Definire un audio informativo, storico, accessibile e non ripetitivo che renda leggibili spazio, attività, persone ed eventi.

## Descrizione

L'audio è una proiezione causale del mondo: sorgenti, ambienti, attività, densità e conoscenza generano suono. Italiano e latino hanno funzioni deliberate; variazioni sociali/regionali sono guidate da ricerca e performance, non caricature.

## Ambito

Voci, italiano, latino, sottotitoli italiani, variazione sociale/regionale, ambienti urbani/rurali, mercati, botteghe, templi, terme, anfiteatri, campagne, esercito, folle, eventi, musica, mix, spazializzazione, accessibilità e anti-ripetizione.

## Architettura concettuale

| Layer | Contenuto | Autorità |
|---|---|---|
| sorgente | voce, utensile, animale, fuoco, acqua, arma | entità/evento reale |
| attività | mercato, bottega, rito, terme, arena, marcia | sistema/luogo |
| ambiente | occlusione, riverbero, interno/esterno, ora/meteo | mondo |
| folla | individui P0 + texture aggregate | crowd/NPC |
| musica | diegetica e score raro/contestuale | evento/direzione audio |
| UX | feedback e accessibilità | UI, mai informazione segreta |

## Lingue e voce

- **Italiano:** lingua principale comprensibile per dialoghi e UI.
- **Latino:** formule, saluti, grida, iscrizioni lette, rituali o modalità estesa solo con consulenza; traduzione/sottotitolo configurabile.
- **Variazioni sociali/regionali:** lessico, ritmo, registro e pronuncia definiti da bible linguistica; niente accenti italiani moderni usati come stereotipo automatico.
- Ogni battuta possiede speaker, destinatario, intento, lingua/registro, fonte, emozione, ambiente e varianti.
- Sottotitoli italiani includono speaker, contenuto non verbale rilevante, direzione opzionale, dimensione/contrasto e timing regolabile.

## Soundscape per luogo

| Luogo | Sorgenti/ritmo | Variazioni |
|---|---|---|
| strada urbana | passi, ruote, animali, voci, porte, acqua/lavoro | ora, fondo, densità, evento |
| mercato | contrattazione, merci, contenitori, animali | prezzo/scarsità, apertura, folla |
| bottega | utensili e cicli produttivi reali | mestiere, input, attività, guasto |
| tempio | officianti, offerte, musica/formule se attestate | rito, calendario, accesso |
| terme | acqua, riverbero, conversazioni, servizi | stanza, ora, densità |
| anfiteatro | folla, annunci, musica, combattimento | programma, esito, sicurezza |
| campagna | vento, animali, lavoro, insetti/acqua | stagione, ora, meteo |
| esercito | marcia, ordini, equipaggiamento, campo | unità, disciplina, terreno |

## Eventi e mixing

Eventi modificano layer: incendio, panico, festa, gioco, epidemia, battaglia remota e catastrofe hanno attacco, propagazione, durata e aftermath. Priorità: sicurezza/feedback critico → voce focalizzata → sorgenti vicine → attività → ambiente → musica. Ducking è graduale e accessibile; niente muro sonoro continuo.

## Anti-ripetizione

Pool per semantica, non solo pitch casuale; cooldown per clip/intento/speaker/area; varianti di frase e performance; granularità procedurale per folla/ambiente; memoria delle ultime selezioni; silenzio e distanza come opzioni valide. Vietati bark identici consecutivi, coro sincronizzato, loop con periodo evidente e pitch-shift caricaturale.

## Informazione e anacronismi

NPC pronuncia solo fatti conosciuti. Niente sirene, segnali moderni, orchestration cinematografica continua o lessico anacronistico. Strumenti, musiche, pronunce e soundmark richiedono fonte A–E/licenza D. Audio UX non imita oggetti moderni fuori contesto.

## Casi limite, performance e persistenza

Molte voci, cambio lingua, speaker fuori schermo, occlusione errata, evento interrotto, time-skip e save durante rito usano priorità/virtualizzazione e ripresa coerente. Budget per voci reali/virtuali, memoria, streaming e riverberi; folle lontane aggregate. Persistono preferenze e stato di eventi/audio diegetico rilevante, non posizione di ogni one-shot.

## Dipendenze

- [Voce](voice.md)
- [Soundscape](soundscape.md)
- [Folle](crowd-audio.md)
- [Musica](music.md)
- [Accessibilità audio](audio-accessibility.md)

## Collegamenti agli altri documenti

- [Dialoghi e lingue](../../06-content/dialogue-and-language.md)
- [Eventi](../../06-content/events/dynamic-event-framework.md)
- [UI](../../08-ux/ui/ui-architecture.md)
- [Mondo](../../03-world/living-city.md)

## Test e Definition of Done

Test linguistico/storico, intelligibilità, sottotitoli, occlusione, ogni luogo P0, storm di eventi, anti-ripetizione 30–60 minuti, accessibilità e budget. S4 con bible linguistica, catalogo sorgenti, mix target e scenari Pompei approvati.

## Decisioni ancora aperte

- Proporzione italiano/latino e profilo di pronuncia.
- Budget voce, densità folla e musica diegetica/score.

## TODO

- Creare matrice luogo-ora-attività-evento-sorgenti.
- Definire corpus voce P0 e protocollo consulenza.
