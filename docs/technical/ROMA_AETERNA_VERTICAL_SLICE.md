# Vertical slice giocabile di Roma Aeterna

## Scopo

`/Game/Maps/RomaAeternaVerticalSlice` è la prima demo tecnica giocabile in terza persona. Usa esclusivamente primitive Engine e placeholder generati dal runtime dei Prompt 21–24; non costituisce una ricostruzione artistica o archeologica definitiva.

## Apertura e controlli

Aprire `RomaAeterna.uproject` con Unreal Engine 5.8. La mappa è configurata come Editor Startup Map e Game Default Map. Se necessario, aprire manualmente `Content/Maps/RomaAeternaVerticalSlice.umap`, quindi premere **Play**.

- `W` / `S`: avanti e indietro rispetto alla camera.
- `A` / `D`: movimento laterale.
- Mouse: rotazione della camera.
- `Space`: salto.
- `Shift sinistro`: corsa.
- `F9`: alternanza tecnica fra terza e prima persona.

`ARAVerticalSliceGameMode` crea `ARACharacter` dal `PlayerStart`; il Character usa capsule, `CharacterMovementComponent`, SpringArm con collision test e camera in terza persona. Le azioni `IA_Move`, `IA_Look`, `IA_Jump` e `IA_Sprint` e il contesto `IMC_Player` sono subobject C++: non dipendono da asset Input esterni.

## Scena tecnica

La mappa contiene una strada rettilinea di 200 metri Unreal, piano di sicurezza, marciapiedi, limiti terminali, luce direzionale, skylight, atmosfera e label tecniche. I generatori sono collocati ai lati della strada con seed espliciti:

- `PopularHouse` (`24001`), residenza Prompt 23;
- `Taberna` (`24002`), commercio Prompt 23;
- `BathComplex` (`24003`), terme Prompt 24;
- `PublicFountain` (`24004`), elemento idrico Prompt 24;
- `MetalWorkshop` (`24005`), produzione Prompt 24;
- `AqueductSection` (`24006`), infrastruttura idrica Prompt 24.

Gli actor salvano tipo e seed, generano a `BeginPlay`, supportano clear/rebuild e producono istanze con collisione `QueryAndPhysics` bloccante per il Pawn.

## Limiti

`PLACEHOLDER_VISUALS_ONLY`: geometria, materiali, proporzioni, illuminazione e testo sono tecnici. Non sono presenti asset Fab, Marketplace, Starter Content o contenuti esterni. Il test automatico carica la mappa, crea il Pawn e valida generatori e collisioni; la prova fisica completa di input e percorrenza resta `MANUAL_PIE_VERIFICATION_REQUIRED`.

## Consolidamento Prompt 25

La mappa rappresenta ora un isolato con due fronti, dieci archetipi, basolato, marciapiedi, canalette, attraversamento, vicolo e slargo. L’illuminazione è dinamica con Lumen, le categorie usano una palette procedurale e il Character ha testa, torso, braccia e gambe. F1–F6 controllano HUD e debug; F9 conserva il cambio camera.
