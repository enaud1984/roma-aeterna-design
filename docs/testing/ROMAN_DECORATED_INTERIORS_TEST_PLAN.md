# Piano test degli interni decorati

Lo script [TestRomanDecoratedInteriors.ps1](../../Scripts/TestRomanDecoratedInteriors.ps1) esegue:

1. parser PowerShell;
2. core Debug, Release e sanitizer;
3. build `RomaAeternaEditor`;
4. creazione locale delle Material Instance e della preview;
5. audit e validatore Python;
6. tutti i test Python;
7. `RomaAeterna.Prompt29.DecoratedInteriors`;
8. `RomaAeterna.Prompt29.InteriorTraversal`;
9. Map Check della preview;
10. controllo Git e apertura opzionale dell’Editor.

L’Automation verifica cinque archetipi obbligatori, stanze, collisioni, pannelli, pavimenti, stili, fallback, clear/rebuild, determinismo e tetti. Il traversal simula esterno, soglia, interno e ritorno.

La simulazione non sostituisce la prova fisica: `MANUAL_GAMEPLAY_TRAVERSAL_REQUIRED`. La preview tecnica non sostituisce la revisione estetica: `MANUAL_DECORATION_VISUAL_REVIEW_REQUIRED`.
