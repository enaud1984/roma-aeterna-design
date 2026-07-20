# Moneta, pagamenti e unità di conto

## Scopo

Definire denominazioni, mezzi di pagamento, resto, qualità e aggregazione senza inventare prezzi storici.

## Descrizione

La moneta è bene e mezzo di pagamento; il valore contabile può essere espresso in un'unità di riferimento configurata. Credito, baratto e pagamento in natura restano possibili.

## Ambito

Pompei flavia come primo profilo; future epoche/province hanno cataloghi versionati.

## Modello

CoinDefinition: autorità/zecca, denominazione, metallo, finestra, massa/tolleranza, corso/accettazione. CoinLot: quantità, qualità, provenienza, custode. Payment: parti, obbligo, componenti monetarie/in natura/credito, resto e prova.

## Regole

- Nessun wallet astratto vicino al player: quantità e custodia contano.
- A livelli lontani i lotti monetari diventano saldo per denominazione/qualità.
- Resto insufficiente può generare credito, sostituzione, rifiuto o arrotondamento contestuale.
- Monete fuori periodo non compaiono; qualità/accettazione possono variare.
- Unità di conto UI è licenza D e non implica moneta fisica corrispondente.

## Stati pagamento

Proposed → Tendered → Validated → Settled oppure Rejected/PartiallySettled/ConvertedToDebt.

## Casi limite

Falso, moneta danneggiata, denominazione non accettata, resto, pagamento misto, furto durante scambio, cambio data/zecca, saldo aggregato raffinato.

## Test e persistenza

Conservazione per denominazione, resto, pagamento misto, E0↔E3, eredità, furto, save. Persistono holdings e transazioni salienti.

## Dipendenze

- [Modello economico](economic-model.md)
- [Inventario](../../05-player/items/inventory.md)
- [Credito](credit-and-debt.md)

## Collegamenti agli altri documenti

- [Prezzi](prices.md)
- [Compravendite](trade.md)
- [Fonti economiche](../../02-historical-foundation/sources/bibliography.md)

## Criteri di completamento

Catalogo per data, unità UI, pagamenti misti, resto, aggregazione e test approvati.

## Definition of Done

Dossier numismatico e parametri demo revisionati; nessuna denominazione anacronistica.

## Decisioni ancora aperte

- Unità contabile UI e granularità fisica delle monete.

## TODO

- Creare catalogo flavio con fonti puntuali.
