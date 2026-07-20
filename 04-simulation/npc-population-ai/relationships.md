# Relazioni e reti sociali

**System ID:** SYS-REL-001

**Stato:** S3 — Contracted

## Scopo

Modellare parentela, patronato, clientela, amicizia, inimicizia, fiducia, affetto, autorità, debito e dipendenza senza ridurli a una barra unica.

## Descrizione

Una relazione è direzionale, multidimensionale, fondata su eventi e vincoli. A può fidarsi commercialmente di B senza amarlo; B può dipendere da A senza ricambiare lealtà.

## Ambito

Legami tra persone e, dove necessario, persona–household/istituzione. Status e proprietà restano sistemi separati.

## Dimensioni

| Dimensione | Range concettuale | Evidenze |
|---|---|---|
| conoscenza/familiarità | sconosciuto→intimo | incontri e memoria |
| fiducia per dominio | inaffidabile→affidabile | promesse/esiti |
| affetto | avversione→attaccamento | interazioni e storia |
| rispetto/status percepito | disprezzo→deferenza | norme, cariche, reputazione |
| obbligo | credito/debito sociale | favori, parentela, patronato |
| paura | sicurezza→timore | minacce, potere, trauma |
| conflitto | latente→aperto | competizione, danno, cause |
| autorità | nessuna→coercitiva/legale | status, household, contratto |

## Tipi strutturali

Parentela, matrimonio/unione, patronus–libertus, patronus–cliens, datore–lavoratore, dominus–persona schiavizzata, creditore–debitore, maestro–apprendista, collega, vicino, amico e nemico. Il tipo applica regole ma non predetermina emozioni.

## Aggiornamento

Evento percepito → attribuzione → valutazione per dominio → modifica limitata → memoria/evidenza → eventuale soglia (rottura, riconciliazione, obbligo). Eventi non conosciuti non aggiornano il legame.

## Stati

Latente, Attivo, Teso, Rotto, Ostile, In lutto, Storico. Relazioni giuridiche e affettive possono avere stati diversi.

## Reputazione

SYS-REL governa legami individuali; SYS-REP governa credenze di comunità. Una reputazione può influenzare la prior iniziale ma non sovrascrive esperienze dirette.

## Scalabilità

Persistono edge strutturali e salienti. Conoscenze deboli possono essere aggregate per gruppo/luogo. Cap per edge ordinari con eviction motivata; nessuna perdita di parentela, obbligo, inimicizia attiva o caso legale.

## Casi limite

Relazione reciproca asimmetrica; patrono morto; due patroni incompatibili; parente sconosciuto; adozione; manomissione; debito saldato ma rancore; falsa accusa; identità confusa; coorte individualizzata con legame preesistente.

## Test

Asimmetria, dominio fiducia, evento non percepito, morte, successione, aggregazione, rete densa, conflitto di obblighi, reputazione opposta all'esperienza.

## Dipendenze

- [Memoria](memory.md)
- [Household](../family-social/household.md)
- [Patronato](../family-social/patronage.md)
- [Status](../social-status-and-law.md)

## Collegamenti agli altri documenti

- [Reputazione](../family-social/reputation.md)
- [Comunicazione](communication-gossip.md)
- [AI](ai-architecture.md)

## Criteri di accettazione

Relazioni direzionali e multidominio; ogni variazione importante ha evidenza; legami strutturali persistono; aggregazione non crea amicizie/ostilità individuali arbitrarie.

## Definition of Done

Tassonomia, soglie, retention, UI, test di rete e dati storici approvati.

## Decisioni ancora aperte

- Limite edge individuali e dimensioni visibili al player.
- Tassonomia finale delle relazioni coercitive e sensibili.

## TODO

- Costruire reti campione di dieci household pompeiani.
