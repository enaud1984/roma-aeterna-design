# Strategia Git e Git LFS per gli asset

## Stato osservato

Al 22 luglio 2026 `Content` contiene 20 file per circa 397 KiB: due mappe autorizzate e sedici materiali tecnici, senza asset esterni. `.gitignore` esclude correttamente `Binaries`, `DerivedDataCache`, `Intermediate` e `Saved`. Git LFS 3.5.1 è disponibile sulla macchina, ma il repository non ha `.gitattributes`: LFS non è configurato.

## Raccomandazione

`GIT_LFS_RECOMMENDED` **prima** del primo import Fab. `.uasset` e `.umap` sono binari non diffabili e i pacchetti candidati possono crescere rapidamente. Questo task non installa né configura LFS.

Soglie operative proposte:

- tracciare con LFS `.uasset` e `.umap` prima del batch 1, dopo approvazione;
- revisione esplicita per singolo file oltre 50 MiB;
- blocco preventivo a 95 MiB nel Git ordinario, sotto il limite GitHub di 100 MiB;
- budget e report dimensionale per batch; repository sotto 10 GiB;
- non versionare cache, sorgenti scaricati non necessari o duplicati vendor;
- conservare asset vendor solo se la licenza consente la distribuzione nel progetto.

La documentazione GitHub consultata raccomanda LFS per file grandi, indica 100 MiB come limite del Git ordinario e raccomanda repository sotto 10 GiB. Queste soglie possono cambiare e vanno ricontrollate al Prompt 27.
