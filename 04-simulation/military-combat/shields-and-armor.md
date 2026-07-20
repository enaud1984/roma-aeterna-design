# Scudi, armature e protezione

## Scopo

Definire protezione geometrica e materiale con costi di mobilità, calore, percezione e manutenzione.

## Descrizione

Lo scudo intercetta traiettorie mediante posizione e angolo; l'armatura copre zone e modifica il trauma. Nessuno dei due aggiunge punti vita o invulnerabilità.

## Ambito

Scudi, elmi, protezione del torso e arti P0/P1; strati, vestibilità, integrità, presa, copertura, penetrazione/trasmissione astratta, equipaggiamento e manutenzione.

## Modello e regole

`ShieldState`: forma, copertura, impugnatura, orientamento, integrità, mano e ingombro. `ArmorLayer`: zona, materiale, spessore/classe storica, vestibilità, integrità e isolamento. Risoluzione: traiettoria → scudo/ostacolo → strati per zona → energia residua/tipo → trauma.

- Copertura dipende da postura e angolo, non probabilità globale.
- Colpi assorbiti trasferiscono carico e possono sbilanciare.
- Armatura mal adattata penalizza movimento e fatica.
- Giunture e zone scoperte emergono dalla copertura, non da critico casuale.
- Calore, peso, rumore e tempo di vestizione influenzano contesto.

## Eventi, casi limite e performance

Produce `ShieldBlocked`, `ArmorLayerHit`, `ProtectionDamaged`, `EquipmentRemoved`; ascolta contatto, presa ferita, caduta, fuoco e manutenzione. Due strati incompatibili, scudo attraversato, zona senza mapping e cambio equipaggiamento durante contatto bloccano o usano fallback tracciato. Collisione dettagliata solo M0; M1+ usa profili di copertura conservativi.

## Accuratezza e bilanciamento

Materiali, costruzione, distribuzione e portatori sono data/area A–E. Ogni protezione scambia copertura con costo, accesso e manutenzione; equipaggiamento raro non diventa tier fantasy.

## Dipendenze

- [Combattimento](combat-vision.md)
- [Armi](weapons.md)
- [Ferite](injuries.md)
- [Fatica](fatigue-fear-morale.md)

## Collegamenti agli altri documenti

- [Produzione](../economy-production/supply-chains.md)
- [Inventario](../../05-player/items/inventory.md)
- [Esercito](army.md)

## Test e Definition of Done

Testare copertura/angolo, strati, giunture, sbilanciamento, integrità, vestibilità, calore e M0↔M2. S4 con catalogo P0, materiali e animazioni approvati.

## Decisioni ancora aperte

- Set P0 e risoluzione delle zone.
- Quanto esporre di copertura/integrità nella UI.

## TODO

- Creare mappe di copertura e compatibilità.
- Collegare fonti archeologiche e manutenzione.
