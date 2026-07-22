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

`Content/ThirdParty` conserva struttura e nomi originali per aggiornamenti e tracciabilità; ownership del vendor. `Content/RomaAeterna` contiene solo wrapper, istanze materiali, Data Asset e adattamenti creati dal progetto; ownership Roma Aeterna. Le mappe restano separate e non incorporano riferimenti hard obbligatori: il visual catalog usa soft reference e fallback. Migrazioni si fanno dall'Editor, mai con Explorer. Cache, `Binaries`, `DerivedDataCache`, `Intermediate` e `Saved` non sono versionate.
