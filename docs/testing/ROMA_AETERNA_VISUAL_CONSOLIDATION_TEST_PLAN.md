# Piano di test del consolidamento visuale

Eseguire `Scripts/TestRomaAeternaVisualConsolidation.ps1 -EngineRoot "<UE 5.8>"`. Lo script compila `RomaAeternaEditor`, esegue Map Check e `RomaAeterna.Prompt25.VisualConsolidation`, verifica Success e rifiuta “Lighting needs to be rebuilt”. I log sono `Prompt25_Build.log`, `Prompt25_Automation.log` e `Prompt25_Automation_Editor.log`.

Il test verifica dieci generatori, due fronti, basolato, marciapiedi, crossing stones, vicolo, slargo, materiali, collisioni, luci movable, label, Character, catalogo, clear/rebuild e seed deterministico. CMake/CTest Debug e Release coprono le regressioni core Prompt 22–24.

## PIE manuale

Stato: `MANUAL_PIE_VERIFICATION_REQUIRED`.

1. Premere Play e verificare possesso e silhouette.
2. Percorrere carreggiata, marciapiedi, attraversamento e vicolo.
3. Provare salto, sprint e collisione camera.
4. Usare F1 HUD, F2 label, F3 bounds, F4 interaction points, F5 rebuild, F6 utilities e F9 camera.
5. Terminare senza crash o processi residui.

Il superamento PIE non viene dichiarato senza prova fisica osservata.
