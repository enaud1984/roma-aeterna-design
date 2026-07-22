# Audit tecnico Asset Batch 1

## Risultati pre-importazione

| Pacchetto | Tipo | Mappe operative | Risoluzione | Mesh/collisione/LOD/Nanite | Stato |
|---|---|---|---|---|---|
| Plastered Wall 03 | MATERIAL_ONLY | Color, Normal DX, Roughness, AO | 2K | non applicabile | NEEDS_IMPORT_PIPELINE |
| Bricks 066 | MATERIAL_ONLY | Color, Normal DX, Roughness, AO | 2K | non applicabile | NEEDS_IMPORT_PIPELINE |
| Cobblestone 05 | MATERIAL_ONLY | Color, Normal DX, Roughness, AO | 2K | non applicabile | NEEDS_IMPORT_PIPELINE |
| Roofing Tiles 013 A | MATERIAL_ONLY | Color, Normal DX, Roughness, AO | 2K | non applicabile | NEEDS_IMPORT_PIPELINE |
| Bricks 042 | MATERIAL_ONLY | Color, Normal DX, Roughness, AO | 2K | non applicabile | NEEDS_IMPORT_PIPELINE |
| Wood Planks Grey | MATERIAL_ONLY | Color, Normal DX, Roughness, AO | 2K | non applicabile | NEEDS_IMPORT_PIPELINE |
| Ground 039 | MATERIAL_ONLY | Color, Normal DX, Roughness, AO | 2K | non applicabile | NEEDS_IMPORT_PIPELINE |

I file sono materiali, non moduli geometrici: pivot, scala mesh, collisione, LOD e Nanite restano proprietà delle primitive e dei moduli procedurali Roma Aeterna. Le primitive sono compatibili con ISMC/HISMC e collisione semplice. L’import usa Normal DX, disabilita sRGB sulle mappe dati e non abilita Virtual Texture automaticamente.

## Gate tecnici

- Import scale geometrica: non applicabile ai materiali; tiling configurato per sorgente.
- Material slots: uno per primitive placeholder.
- Shader: quattro texture sample per materiale, senza displacement.
- Plugin: Python Editor Script Plugin già previsto dal progetto per la generazione locale.
- Redirector: da controllare dopo import; lo script ricrea deterministicamente i materiali locali.
- Import UE 5.8: 1,92 secondi, picco processo 1.785 MiB fisici e 1.640 MiB virtuali; 0 errori e 0 warning.
- Output locale: 28 texture, 7 materiali, 1 Data Asset e 1 mappa; 89.535.085 byte complessivi.
- Texture massima: 2048×2048; shader materiali con quattro texture sample, senza displacement.
- Draw call indicative: una componente ISMC per categoria generata; la preview usa 15 primitive statiche di confronto più label e luci. La misura GPU finale resta dipendente dalla scena e dalla piattaforma.
- Tempo apertura Editor/preview: circa 10 secondi di inizializzazione nella sessione verificata; Map Check 0 errori/0 avvisi.
- Collisioni: `BlockAll`, QueryAndPhysics sulle geometrie edilizie; nessuna collisione per-poly introdotta.

Qualsiasi valore non misurato resta `NOT_VERIFIED`; non si deduce la compatibilità da `.blend` o glTF perché questi file non vengono importati.

## Audit Prompt 28

L'importazione aggiornata mantiene 28 texture operative e sette master, aggiungendo undici Material Instance condivise. Nessun displacement, tessellation o POM è attivo. L'audit `--material-replacement-audit --batch 1` verifica normal DirectX, limite 2K, parametri PBR, mapping di dieci archetipi, licenze, assenza di duplicazioni, asset tracciati e Git LFS.

Misura Prompt 28: 48 output locali, 89.732.295 byte; import 2,04 secondi e 1.787 MiB fisici di picco. Sui dieci archetipi il test osserva 164 istanze, 64 componenti ISMC, 27 categorie locali e 37 fallback. La cache shader era già calda; il log non espone un conteggio affidabile di shader compilati, quindi tale valore resta `NOT_VERIFIED`.
