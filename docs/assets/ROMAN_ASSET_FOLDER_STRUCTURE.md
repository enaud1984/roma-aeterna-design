# Struttura cartelle e ownership

Non vengono create cartelle Content vuote in questo task.

```text
Content/RomaAeterna/
  Architecture/ Roads/ Materials/ Props/ Production/
  PublicBuildings/ Religion/ Vegetation/ Characters/
  Animations/ Animals/ FX/ Audio/ Data/ Maps/
Content/ThirdParty/
  Fab/<Vendor>/<Package>/
  Megascans/<Package>/
  Other/<Vendor>/<Package>/
```

`Content/ThirdParty`, `Content/LocalAssets` e `Content/ImportedAssets` sono esclusivamente locali e ignorati da Git; conservano struttura e nomi vendor per ricostruzione e aggiornamenti. `Content/RomaAeterna` può contenere soltanto configurazione o asset di proprietà del progetto esplicitamente autorizzati, non copie di asset esterni. Le mappe non incorporano riferimenti hard obbligatori: il visual catalog usa soft reference e fallback. `Content/Technical` e la vertical slice tecnica esistente restano versionati. Cache, `Binaries`, `DerivedDataCache`, `Intermediate` e `Saved` non sono versionati.
