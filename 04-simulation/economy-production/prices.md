# Prezzi, domanda, offerta e inflazione locale

## Scopo

Definire formazione e comunicazione dei prezzi senza listino globale o oscillazioni ingestibili.

## Descrizione

Il prezzo è proprietà di una transazione o osservazione: bene, qualità, quantità, luogo, tempo, parti e termini. Il mercato conserva distribuzioni e memoria, non “il vero prezzo”.

## Ambito

Negoziazione E0, mercati E1/E2 e indici E3–E5.

## Formazione

Prezzo di riserva del venditore: costo atteso + scarsità + rischio + margine/obblighi. Disponibilità acquirente: utilità + urgenza + sostituti + liquidità/credito. Relazione, informazione, status e autorità influenzano il range; la transazione avviene se compatibile.

## Stabilità

Memoria a finestra, smoothing, quantità minime, cooldown e limiti di reazione evitano ping-pong. Lo shock reale può superare i limiti. Nessun rubber-banding occulto contro il player.

## Inflazione locale

Indice di paniere per mercato/household, ponderato e versionato. Distinguere rincaro relativo, inflazione monetaria, svalutazione qualitativa e scarsità. In assenza di serie storica il paniere è D per bilanciamento, non fatto A.

## Informazione e speculazione

Prezzi conosciuti derivano da osservazione, contatti e voci con ritardo. Arbitraggio richiede trasporto, capitale, rischio e accesso. La speculazione trattiene o anticipa stock e lascia esposizione al rischio.

## Casi limite

Nessuna vendita, bene unico, prezzo outlier, qualità sconosciuta, mercato chiuso, domanda senza denaro, razionamento, tetto imposto, valuta mista, indice con bene assente.

## Test

Shock domanda/offerta, sostituti, arbitraggio, monopolio locale, relazione, festival, 180 giorni, outlier, E0↔E4 e confronto con range target.

## Dipendenze

- [Modello](economic-model.md)
- [Scorte](warehousing.md)
- [Trasporto](transport.md)

## Collegamenti agli altri documenti

- [Moneta](currency.md)
- [Crisi](economic-crises.md)
- [Bilanciamento](economic-balancing.md)

## Criteri di completamento

Prezzi contestuali, indici locali, smoothing, informazione, sostituti e test di stabilità approvati.

## Definition of Done

Range demo e UX di prezzo revisionati, nessun prezzo universale o fonte storica inventata.

## Decisioni ancora aperte

- Paniere e volatilità target.

## TODO

- Costruire dataset di calibrazione sintetico dichiarato D.
