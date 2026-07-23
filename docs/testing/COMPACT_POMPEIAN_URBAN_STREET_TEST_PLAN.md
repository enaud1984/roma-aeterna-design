# Piano di test della strada pompeiana compatta

## Gate automatici

`Scripts/TestCompactPompeianStreet.ps1 -EngineRoot <UE_5.8>` esegue:

1. audit `--compact-urban-audit`, validatore statico e test Python;
2. CMake/CTest Debug, Release e sanitizer;
3. UHT/UBT e build `RomaAeternaEditor`;
4. rigenerazione della mappa con `CreateRomaAeternaVerticalSlice.py`;
5. tre Automation Test `RomaAeterna.Prompt30`;
6. Map Check;
7. PIE reale con movimento, F5/F7/F9/F10/F11 e otto screenshot.

## Automation Test

- `CompactPompeianComposition`: due fronti, archetipi minimi, piani alternati e moduli.
- `FacadesAndInteriors`: pannelli, balconi, taberna, thermopolium, pistrinum e atrio.
- `RuntimeStability`: rebuild deterministico e toggle senza accumulo.

## Prove PIE

Gli screenshot sono locali in `Saved/Diagnostics/Prompt30/FinalScreenshots` e mostrano strada, fronti addossati, thermopolium/taberna, pistrinum, domus, fallback F7, tetti nascosti F10 e vista semialta. Il log deve contenere `PROMPT30_REAL_PIE_COMPLETED` e la distanza di movimento.

## Vincoli

Il gate fallisce per asset esterni tracciati, modifica di `TechnicalSandbox.umap`, test mancanti, Map Check sporco, marker PIE assenti o screenshot insufficienti.
