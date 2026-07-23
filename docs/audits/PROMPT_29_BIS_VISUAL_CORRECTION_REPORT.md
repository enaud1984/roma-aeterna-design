# Report di correzione visuale Prompt 29-BIS

## Diagnosi

La riproduzione reale in PIE ha isolato quattro cause:

1. i parent material non avevano il flag ISMC e Unreal applicava il materiale di default;
2. le coordinate 0…dimensione del core non erano ricentrate sul pivot dell’attore;
3. i blocchi astratti coprivano il guscio accessibile e le decorazioni;
4. F10 controllava soltanto le falde accessibili, mentre F7 non aggiornava strada e terreno.

L’eccesso di fallback derivava inoltre dai tier di ricchezza predefiniti non coerenti con DomusMedia e BathComplex. F5 era deterministico ma privo di feedback, quindi appariva inattivo. Il warning Lumen nasceva dalla mancata configurazione esplicita di distance fields/software ray tracing.

## Correzioni

Sono stati aggiunti flag ISMC negli script, ricentratura sui bounds, filtri dei duplicati astratti, mapping di ricchezza, validazioni core/runtime, tetti registrati in un solo toggle, refresh dell’ambiente, statistiche cache/binding, messaggi F5/F7/F10, HUD compatto, camera più vicina e configurazione Lumen software.

`HISTORICAL_APPROXIMATION` continua ad applicarsi a proporzioni, colori e pendenze. Non sono stati acquisiti nuovi asset; Roman Temple Ruins e Rome Empire Character Pack non sono stati importati.

## Esito finale

Il gate completo è stato eseguito realmente con Unreal Engine 5.8: 18 test Python, CTest Debug/Release/sanitizer, UHT/UBT, sette Automation Test, Map Check 0 errori/0 avvisi e PIE renderizzato sono passati. F5, F7, F9, F10 e F11 sono stati esercitati nella sessione reale; dopo il ripristino F11 l’HUD torna a 146 binding locali e 36 fallback senza accumulo.

Le immagini locali confermano intonaco, laterizio, tegole, legno, strada, terreno, decorazioni interne e pavimento distinto. Gli stati finali sono registrati in `IMPLEMENTATION_STATUS.md`. Gli asset esterni, i log e gli screenshot restano locali: `EXTERNAL_ASSETS_NOT_VERSIONED`, `GIT_LFS_NOT_USED`.
