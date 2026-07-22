# Strategia Git e Git LFS per gli asset

## Stato osservato

Al 22 luglio 2026 `Content` contiene 20 file per circa 397 KiB: due mappe autorizzate e sedici materiali tecnici, senza asset esterni. `.gitignore` esclude correttamente `Binaries`, `DerivedDataCache`, `Intermediate` e `Saved`. Git LFS 3.5.1 è disponibile sulla macchina, ma il repository non ha `.gitattributes`: LFS non è configurato.

## Strategia obbligatoria sostitutiva

`LOCAL_ASSET_ONLY_STRATEGY`, `GIT_LFS_NOT_USED`, `EXTERNAL_ASSETS_NOT_VERSIONED`.

Git LFS non viene configurato perché gli asset esterni non entrano nel repository. Fab, Megascans, Marketplace e altre librerie sono importati soltanto nelle cartelle locali elencate in `.gitignore`. Restano versionabili codice, configurazione, script, documentazione, cataloghi, registri, mapping testuali e `.uproject`; gli asset tecnici preesistenti rimangono tracciati.

Sono esclusi da qualsiasi commit: `.uasset` esterni, mappe di prova esterne non autorizzate, texture, mesh, audio, animazioni, cache e pacchetti importati. Prima di un commit si eseguono audit, `git status --ignored` e controllo dell'indice. Il registro `ROMAN_LOCAL_ASSET_INSTALLATION.md` rende riproducibile manualmente l'ambiente senza distribuire i pacchetti.
