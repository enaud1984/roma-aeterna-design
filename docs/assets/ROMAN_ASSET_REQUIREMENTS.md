# Requisiti degli asset reali romani

Data dell'audit: 22 luglio 2026. La vertical slice deve passare dai placeholder a un lessico coerente con una città vesuviana del 50–80 d.C., senza presentare i prodotti commerciali come prova archeologica.

## Matrice dei fabbisogni

| Priorità | Ambito | Elementi richiesti | Criterio di accettazione |
|---|---|---|---|
| P0 | Architettura | muri lapidei, intonaco, laterizio, aperture, angoli, colonne, archi, portici, scale, soglie, pavimenti, tetti, tegole, travi, parapetti, cornici, facciate commerciali | modulo scalabile, pivot/snap verificabili, collisione semplice |
| P0 | Strade | basolato, marciapiede, cordolo, canaletta, attraversamenti, scarichi, vicoli, terreno e usura | morfologia compatibile con basoli; continuità e collisione |
| P1 | Interni | letti, tavoli, sedute, casse, scaffali, bracieri, lampade, tende e arredi | scala umana, costo istanze e contesto documentati |
| P0 | Commercio | banchi, anfore, dolia, ceste, contenitori e merci | leggibilità di taberna/mercato senza ostruire gameplay |
| P1 | Produzione | presse, telai, forni, fornaci, incudini, macine, vasche e magazzini | corrispondenza agli archetipi Prompt 24 |
| P1 | Pubblico/religioso | statue, altari, fontane, terme, colonne e templi | ordine, proporzioni e decorazione revisionati |
| P0 | Vegetazione | ulivo, cipresso, pino, vite, fico, arbusti, erbe, fiori e suolo mediterraneo | specie plausibili; esclusione esplicita di agave e anacronismi |
| P0 | Personaggi | corpi, tuniche, toghe, calzature e varianti sociali | skeleton/retarget verificabili; abiti del I secolo da validare |
| P0 | Animazioni | idle, cammino, corsa e salto | locomotion base retargetabile |
| P2 | Animazioni | seduta, trasporto, lavoro, dialogo e strumenti | contatto e root motion verificati |
| P3 | Animazioni | combattimento | rinviato al gameplay avanzato |
| P2 | Animali | cavalli, muli, asini, cani, ovini, caprini, galline e maiali | anatomia, skeleton e budget folla |
| P2 | FX/audio | fuoco, fumo, acqua, polvere, città, mercato, folla, animali, officine e terme | licenza, loop, attenuazione e costo runtime |

## Requisiti trasversali

- UE 5.8 deve essere dichiarata o provata in un progetto di staging; in assenza usare `NOT_VERIFIED`.
- Ogni asset deve avere fonte, autore, licenza e prova locale di acquisizione prima dell'import.
- `URARomanVisualCatalog` riceverà wrapper e soft reference solo dopo approvazione.
- Scala, pivot, snap, collisioni, LOD/Nanite, slot materiali e memoria vanno misurati.
- Accuratezza storica e compatibilità con Pompei richiedono revisione per singolo elemento.

Stato: `ASSET_REQUIREMENTS_COMPLETED`.
