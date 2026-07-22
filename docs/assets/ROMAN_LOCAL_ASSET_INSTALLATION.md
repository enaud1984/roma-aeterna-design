# Registro di installazione locale degli asset romani

## Strategia obbligatoria

Gli asset Fab, Megascans, Marketplace e di altre librerie restano esclusivamente sulla macchina di sviluppo. Non si configura Git LFS e non si versionano mesh, texture, audio, animazioni, pacchetti, cache, `.uasset` o mappe create soltanto per prove di asset esterni.

Stati operativi:

- `LOCAL_ASSET_ONLY_STRATEGY`
- `GIT_LFS_NOT_USED`
- `EXTERNAL_ASSETS_NOT_VERSIONED`

Le cartelle locali ammesse e ignorate da Git sono:

- `Content/ThirdParty/Fab/`
- `Content/ThirdParty/Megascans/`
- `Content/ThirdParty/Marketplace/`
- `Content/ThirdParty/External/`
- `Content/LocalAssets/`
- `Content/ImportedAssets/`

`Content/Technical/` e `Content/Maps/RomaAeternaVerticalSlice.umap` non sono esclusi: contengono asset tecnici del progetto già versionati e necessari.

## Registro delle installazioni

Nessun pacchetto è installato alla data di creazione del registro.

| Pacchetto | Fonte | Versione | Cartella locale di importazione | Data acquisizione | Licenza | Asset effettivamente utilizzati | Passaggi manuali | Dipendenze | Controlli post-importazione |
|---|---|---|---|---|---|---|---|---|---|
| `NOT_INSTALLED` | `NOT_VERIFIED` | `NOT_VERIFIED` | `NOT_ASSIGNED` | `NOT_ACQUIRED` | `MANUAL_REVIEW_REQUIRED` | Nessuno | Nessuna acquisizione eseguita | `NOT_VERIFIED` | Nessuno |

## Procedura manuale per ogni pacchetto

1. L'utente verifica prezzo, account, licenza e versione del pacchetto.
2. Importa dall'Unreal Editor nella cartella locale ignorata corrispondente, mai in una cartella versionata.
3. Compila una nuova riga del registro senza dati personali o credenziali.
4. Elenca soltanto gli asset effettivamente selezionati, le dipendenze e gli eventuali plugin.
5. Verifica UE 5.8, scala, pivot, snap, collisioni, LOD/Nanite, materiali, memoria e accuratezza storica.
6. Collega gli asset mediante mapping/configurazione testuale o soft path locale; conserva i fallback tecnici versionati.
7. Esegue `AuditRomanAssets.py`, build editor e Automation Test appropriati.
8. Prima di ogni commit controlla `git status --ignored` e `git ls-files Content` per escludere file esterni.

## Ricostruzione dell'ambiente

Una nuova macchina ricostruisce il progetto clonando il repository, installando manualmente gli stessi pacchetti e versioni nelle cartelle indicate e applicando i passaggi registrati. Il repository deve restare compilabile e testabile con i fallback tecnici quando gli asset locali non sono presenti.
