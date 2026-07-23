# Piano di test della correzione visuale

## Gate automatici

- audit asset con `--visual-slice-audit --material-runtime-audit --transform-audit`;
- validatore statico e suite Python;
- CTest Debug, Release e sanitizer;
- UHT/UBT e build `RomaAeternaEditor`;
- sette test `RomaAeterna.Prompt29Bis.*`;
- Map Check della vertical slice;
- PIE reale pilotato da Python con screenshot locali.

I test Unreal verificano mappa e generazione, oltre cento istanze, trasformazioni finite, undici Material Instance, compatibilità ISMC, assenza di `WorldGridMaterial`, almeno 25 binding locali, Enhanced Input, ground trace, F5 senza accumulo, F7 reversibile, F10 reversibile, contatori F11 senza accumulo e decorazioni di DomusMedia/BathComplex.

## Accettazione visuale

Gli screenshot in `Saved/Diagnostics/Prompt29Bis/FinalScreenshots` mostrano vista generale, materiali locali e fallback, tetti visibili/nascosti, risultato dopo F5, decorazioni F11 attive/fallback e interno della DomusMedia in prima persona tramite F9. Sono output locali ignorati da Git.

Il gate visuale è passato dopo ispezione reale delle immagini e assenza nel log PIE di warning `missing usage flag InstancedStaticMeshes`, WorldGrid involontario o errori permanenti Lumen.
