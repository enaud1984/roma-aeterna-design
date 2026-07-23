# Sistema di generazione degli interni romani

Il Prompt 29 aggiunge un guscio interno runtime agli archetipi `PopularHouse`, `DomusMedia`, `Taberna`, `Thermopolium`, `BathComplex` e `MetalWorkshop`.

Ogni guscio usa coordinate locali coerenti con il fronte stradale: ingresso aperto, architrave, pavimento continuo, pareti perimetrali, divisorio con passaggio, uscita libera e due coperture occultabili. Le collisioni dei vecchi volumi `Wall` vengono disattivate soltanto per questi archetipi e sostituite dalle collisioni del guscio. Porte e `ShopOpening` restano non bloccanti.

Le luci interne sono componenti dinamici creati una sola volta durante la generazione. Non esiste `Tick`. Il sistema è tecnico e usa `HISTORICAL_APPROXIMATION`.

## API

`GetAccessibleRoomCount`, `SetRoofVisibility`, `GenerateRoomDecoration`, `ClearRoomDecoration` e `RebuildRoomDecoration` sono disponibili in C++ e Blueprint.

## Limiti

Le porte sono aperture permanenti; non esistono ancora serrature, navigazione NPC o geometrie artistiche definitive. La prova fisica con tastiera e mouse resta manuale.
