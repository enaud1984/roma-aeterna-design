# Piano di test della vertical slice

## Controlli automatici

Eseguire:

```powershell
python .\Scripts\ValidateRomanModularFoundation.py
powershell -ExecutionPolicy Bypass -File .\Scripts\TestRomaAeternaVerticalSlice.ps1 -EngineRoot "<percorso UE 5.8>"
```

Lo script compila `RomaAeternaEditor` e avvia `RomaAeterna.Prompt24Bis.VerticalSlice`. Il test verifica package e caricamento mappa, GameMode, PlayerStart, creazione di `ARACharacter`, camera, SpringArm, CharacterMovement, sei ruoli edilizi, moduli positivi, collisione Pawn, clear/rebuild e determinismo del conteggio con seed invariato. I log separati sono salvati in `Saved/Logs/Prompt24Bis_Build.log`, `Prompt24Bis_Automation.log` e `Prompt24Bis_Automation_Editor.log`.

Il core indipendente da Unreal deve inoltre superare CMake/CTest Debug e Release, preservando i test Prompt 22–24.

## Checklist PIE manuale residua

Stato: `MANUAL_PIE_VERIFICATION_REQUIRED`.

1. Aprire `RomaAeternaVerticalSlice` e premere Play.
2. Verificare il possesso del Character e la camera in terza persona.
3. Percorrere la strada con `WASD` e mouse; verificare uno spostamento reale.
4. Saltare con `Space`, correre con `Shift` e provare la collisione contro muro e edificio.
5. Verificare che la camera accorci il braccio vicino alle collisioni.
6. Percorrere la strada fino ai sei archetipi e verificare che nessuno blocchi l’intero asse.
7. Terminare Play senza crash o processi Editor residui.

Solo una prova PIE realmente osservata autorizza a dichiararne il superamento.

Il Prompt 25 aggiunge `RomaAeterna.Prompt25.VisualConsolidation`; la procedura estesa è in `ROMA_AETERNA_VISUAL_CONSOLIDATION_TEST_PLAN.md`.
