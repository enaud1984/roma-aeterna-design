# Contratto di decisione e pianificazione

## Scopo

Specificare candidati, guardie, scoring, commitment e fallback usati dall'architettura AI.

## Descrizione

La decisione è deterministica a parità di stato autorevole, credenze, configurazione e seed; la varietà deriva da persone e contesti, non rumore incontrollato.

## Ambito

Goal selection N0–N3 e policy equivalenti N4/N5.

## Contratto candidato

Ogni azione candidata dichiara precondizioni note, requisiti reali da validare, costo, durata, luogo, rischio, effetti attesi, risorse prenotate, alternative e ragioni di fallimento. Le precondizioni “note” possono essere errate; la validazione reale avviene all'esecuzione.

## Guardie

Capacità fisica, status/autorità, accesso, risorsa, tempo, distanza minima, conoscenza, impegno incompatibile e sicurezza. Una guardia hard esclude; un costo soft modifica utilità.

## Tie-break e stabilità

Ordine: priorità hard → utilità oltre isteresi → preferenza stabile → costo cambio → seed deterministico. Un nuovo candidato marginalmente migliore non interrompe automaticamente l'azione corrente.

## Stati

Generated → Filtered → Scored → Selected → Committed → Executing → Completed/Failed/Cancelled. Ogni transizione produce ragione diagnostica.

## Casi limite

Nessun candidato, tutti impossibili, score non finito, due agenti prenotano la stessa risorsa, target morto, piano ciclico, fallback ricorsivo, conoscenza cambiata dopo commit.

## Performance e persistenza

Candidate generation indicizzata e limitata; ricalcolo su trigger; score cache versionato. Persistono commitment e prenotazioni, non score temporanei.

## Test

Golden scenarios, proprietà delle guardie, tie-break, isteresi, contesa, conoscenza falsa, fallback finito, equivalenza N0/N3, fuzz di configurazione.

## Dipendenze

- [Architettura AI](ai-architecture.md)
- [Routine](routines.md)
- [Memoria](memory.md)

## Collegamenti agli altri documenti

- [Bisogni](needs-ai.md)
- [Percezione](perception.md)
- [Performance](ai-performance.md)

## Criteri di accettazione

Ogni scelta ha candidati e ragione; nessun NaN/ciclo; prenotazioni atomiche; stabilità e fallback testati.

## Definition of Done

Contratti, guardie, score, tie-break, diagnostica e suite scenari approvati.

## Decisioni ancora aperte

- Formula/configurazione finale e tecnica di planning.

## TODO

- Definire catalogo azioni della demo.
