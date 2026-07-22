# Candidati reali verificati

Fonte canonica dei dati: [roman_asset_catalog.json](roman_asset_catalog.json). Verifica effettuata il 22 luglio 2026. Prezzi, sconti, disponibilità e imposte possono cambiare. `NOT_VERIFIED` significa che la scheda pubblica non esponeva il dato: non è una valutazione positiva.

## Metodo e formula

Sono stati aperti i singoli listing, non valutati soltanto i titoli. I dieci criteri tecnici ricevono 0–5. `TechnicalScore` è la media di modularità, qualità, UE 5.8, prestazioni, collisioni e LOD/Nanite. `HistoricalScore`: A=5, B=3,5, C=2, D=0,5. `IntegrationScore` è la media di facilità, variazione e compatibilità col visual catalog. `PriorityScore = 0,35T + 0,25H + 0,25I + 0,15 valore/prezzo`.

## Inventario sintetico

| Gruppo | AssetId | Candidati | Nota dominante |
|---|---|---:|---|
| Architettura | RA-FAB-ARCH-001…006 | 6 | un solo kit dichiara UE 5.8; fantasy/monumentale da filtrare |
| Materiali | RA-FAB-MAT-001…003 | 3 | superfici generiche; shader e memoria da provare |
| Strada | RA-FAB-ROAD-001…002 | 2 diretti, 4 con kit | cobblestone non equivale a basoli pompeiani |
| Tetti | RA-FAB-ROOF-001…002 | 2 diretti, 6 con kit | forme non verificate come tegula/imbrex |
| Props | RA-FAB-PROP-001…003 | 3 | ceramica da fonte tipologica è il candidato storico più forte |
| Vegetazione | RA-FAB-VEG-001…003 | 3 | rimuovere agave; specie da selezionare |
| Personaggi | RA-EPIC/FAB-CHAR-001…004 | 4 | manichini tecnici o abiti/rig non ancora verificati |
| Animazioni | RA-EPIC/FAB-ANIM-001…003 | 3 | locomotion generica, retarget da provare |

I 26 record completi includono URL, prezzi osservati, campi tecnici, rischi, archetipi, categorie e punteggi. Le classi storiche sono: A direttamente pertinente ma ancora da contestualizzare; B adattabile; C utile per elementi selezionati; D inadatto. Nessun candidato è dichiarato “storicamente accurato” sulla base del marketing.

Stati: `FAB_RESEARCH_COMPLETED`, `ASSET_CANDIDATES_VERIFIED` rispetto all'esistenza e ai dati pubblicamente osservati; licenza e integrazione locale restano da verificare.
