# Scripts

Script riproducibili per generazione dei file Rider, compilazione Editor, costruzione/validazione headless della mappa tecnica e test automatici.

| Script | Scopo |
|---|---|
| `GenerateProjectFiles.ps1` | rigenera il modello di progetto Rider |
| `BuildEditor.ps1` | compila `RomaAeternaEditor Win64 Development` |
| `BuildTechnicalSandbox.ps1` | genera e valida il Technical Roman Street Prototype |
| `RunPlayableFoundationTests.ps1` | esegue la suite `RomaAeterna.PlayableFoundation` e valida il report JSON |

Gli script non contengono percorsi personali; il default UE è `C:\Program Files\Epic Games\UE_5.8` e può essere sostituito tramite parametro o `UE_5_8_ROOT`.
