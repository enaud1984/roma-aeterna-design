# Mapping Batch 1 per archetipo

| Archetipo | Superfici locali | Fallback deliberato |
|---|---|---|
| PopularHouse | intonaco ocra, laterizio esposto, tetto, legno | elementi lapidei e acqua |
| DomusMedia | intonaco chiaro, tetto regolare, legno, terreno cortile | decorazione e pietra nobile |
| Taberna | intonaco, pavimento secondario, banco, porta, tetto | soglie lapidee |
| Thermopolium | intonaco, pavimento usurato, banco e scaffali | dolia e vasche |
| BathComplex | intonaco chiaro, laterizio termico, pavimento secondario | vasche, acqua e pietra monumentale |
| PublicFountain | pavimentazione/terreno circostante | vasca e acqua restano tecniche |
| MetalWorkshop | laterizio termico, terreno produttivo, legno usurato | metallo, incudine e pericoli |
| AqueductSection | laterizio selettivo su archi/parti coerenti | canale e pietra principale |
| UrbanGarden | terreno asciutto e legno leggero | acqua e vegetazione tecnica |
| ServiceYard | terreno produttivo, laterizio e legno | attrezzature specialistiche |

## Ricchezza

- `Poor`: laterizio e legno usurato, intonaco incompleto.
- `Modest`: mix intonaco/laterizio e copertura semplice.
- `Comfortable`: intonaco più uniforme e legno scuro.
- `Wealthy`: intonaco chiaro, usura ridotta; nessun affresco.
- `Elite`/`Monumental`: materiali locali solo secondari, lapidei tecnici preservati.

## Strade

`Cobblestone05` è ammesso per `SecondaryPaving`, vicoli, cortili e fronti commerciali. La strada principale conserva geometria e materiale tecnico: il pacchetto non è dichiarato basolato romano.

La vertical slice riceve i materiali esclusivamente a runtime. `RomaAeternaVerticalSlice.umap` non contiene riferimenti hard al catalogo locale e non deve essere salvata dopo l'attivazione.
