# Comunicazione, voci e pettegolezzi

## Scopo

Simulare diffusione di informazioni vere, incomplete o false attraverso reti e canali situati.

## Descrizione

Un messaggio conserva mittente, destinatario, canale, proposizione, intenzione e confidenza. La trasmissione può comprimere, omettere, reinterpretare o falsificare.

## Ambito

Conversazioni, intermediari, annunci, iscrizioni, lettere, autorità e voci pubbliche.

## Regole

- L'NPC comunica solo credenze accessibili, salvo invenzione consapevole.
- Segreti hanno audience e rischio.
- Interesse, salienza, prossimità, relazione e utilità governano la condivisione.
- Alfabetizzazione/accesso governano canali scritti.
- Ripetizione aumenta diffusione, non verità.
- Ogni hop conserva provenance almeno sintetica.

## Stati della voce

Originata → Condivisa → Locale → Diffusa → Contestata → Stabilizzata/Dissipata. “Stabilizzata” significa creduta, non necessariamente vera.

## Scalabilità

N0/N1 conversazioni esplicite; N2 messaggi tra incontri; N3 propagazione su edge sociali; N4 prevalenza per comunità e portatori; N5 notizie regionali. Individui chiave impediscono diffusione istantanea.

## Eventi pubblici

Feste, giochi, funerali, processi e rivolte aumentano contatti e velocità, ma creano anche versioni concorrenti. Annunci autorevoli hanno reach configurata, non universale.

## Casi limite

Fonte anonima, bugia, messaggero morto, destinatario assente, lingua diversa, omonimia, lettera intercettata, autorità contraddetta, notizia arrivata dopo l'esito.

## Test

Catena di cinque hop, mutazione, segreto, rete disconnessa, evento pubblico, N2↔N4, falsa voce e smentita, tempi regionali.

## Dipendenze

- [Memoria](memory.md)
- [Relazioni](relationships.md)
- [Lingue](../../06-content/dialogue-and-language.md)

## Collegamenti agli altri documenti

- [Reputazione](../information-and-reputation.md)
- [Eventi sociali](social-event-responses.md)
- [Narrazione](../../06-content/emergent-narrative.md)

## Criteri di accettazione

Provenance, ritardo e audience preservati; falsità possibile; nessuna diffusione senza canale; aggregazione coerente.

## Definition of Done

Canali, mutazioni, privacy, propagazione, test e UX di certezza approvati.

## Decisioni ancora aperte

- Modello linguistico e dettaglio dei contenuti sintetizzati.

## TODO

- Definire canali e reti della demo.
