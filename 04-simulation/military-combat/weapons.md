# Armi e strumenti offensivi

## Scopo

Definire armi come oggetti fisici, culturali e giuridici con uso, manutenzione e provenienza, non come valori di danno lineari.

## Descrizione

Un'arma offre modalità tecniche entro portata, spazio e competenza. Geometria, massa, velocità relativa, zona colpita e protezione determinano il trauma; qualità e abilità migliorano affidabilità e controllo.

## Ambito

Armi da taglio, punta, impatto e improvvisate P0; uso a una/due mani, presa, transizioni, porto, estrazione, integrità, manutenzione, sequestro e produzione. Armi a distanza richiedono un'estensione approvata.

## Dati e regole

| Campo | Funzione |
|---|---|
| geometria/portata | distanza efficace, collisione e spazio |
| massa/baricentro | inerzia, fatica e recovery |
| modalità | punta, taglio, impatto, controllo |
| presa/mano | tecniche, compatibilità scudo e perdita |
| materiale/qualità | integrità, flessione e manutenzione |
| provenienza/custodia | proprietà, legalità, crimine e storia |

Attacco fuori misura o contro parete degrada efficacia; arma lunga soffre spazio stretto; disarmo deriva da presa, leva, sorpresa e stato, non RNG puro. Nessuna arma ignora armatura per rarità. Deterioramento è lento e causale, non tassa per colpo.

## Flussi ed eventi

Acquisizione → equipaggiamento → estrazione → tecnica → contatto/nessun contatto → recovery → manutenzione/riparazione/sequestro. Produce `WeaponDrawn`, `ContactResolved`, `WeaponDropped/Broken`, `WeaponMaintained`; ascolta ordine, disarmo, ferita mano, spazio e legge.

## Casi limite, bilanciamento e persistenza

Doppio contatto, arma incastrata, cambio mano, oggetto improvvisato, rottura durante parata e transizione livello devono conservare causalità. Trade-off di portata, controllo, occultabilità e fatica evitano tier assoluti. Persistono identità P0, qualità, custodia, integrità, modifiche e provenienza.

## Accuratezza storica

Tipi, dimensioni, materiali, distribuzione e contesto d'uso sono profili data/area A–E. Niente arsenale gladiatorio/militare universale per civili pompeiani.

## Dipendenze

- [Combattimento](combat-vision.md)
- [Ferite](injuries.md)
- [Scudi e armature](shields-and-armor.md)
- [Oggetti](../../05-player/items/README.md)

## Collegamenti agli altri documenti

- [Produzione](../economy-production/production.md)
- [Criminalità](../politics-law/criminality.md)
- [Equipaggiamento militare](military-pay-equipment.md)

## Test e Definition of Done

Testare portata, spazio stretto, ogni modalità P0, parata, disarmo, rottura, custodia e save/load. S4 dopo corpus archeologico/iconografico, matrice tecnica-trauma e test leggibilità.

## Decisioni ancora aperte

- Arsenale P0 civile, arena e militare.
- Granularità di integrità e manutenzione.

## TODO

- Creare catalogo P0 con fonti e misure a intervallo.
- Collegare animazioni e audio richiesti.
