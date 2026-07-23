# Strada urbana pompeiana compatta

## Obiettivo

Il Prompt 30 trasforma `/Game/Maps/RomaAeternaVerticalSlice` da esposizione di archetipi isolati a tratto urbano ordinario. La composizione è una `HISTORICAL_APPROXIMATION`: due fronti edilizi addossati, strada basolata stretta, marciapiedi, canalette, vicolo e piccolo slargo.

## Tessuto e facciate

I fronti nord e sud alternano `PopularHouse`, `DomusMedia`, `Taberna`, `Thermopolium`, `Pistrinum`, terme e attività produttive. Gli actor usano seed espliciti, larghezze coordinate e tag `RA_CONTINUOUS_FACADE`. Uno e due piani si alternano; le facciate hanno aperture commerciali più ampie, porte residenziali, finestre alte, fasce dipinte, zoccoli, tetti a falda e balconi o sporti lignei tecnici.

La fontana occupa lo slargo e il vicolo interrompe intenzionalmente il fronte. `UrbanGarden` e `ServiceYard` chiudono il tratto con funzioni di servizio.

## Interni leggibili

Il guscio runtime conserva accessi senza collisione davanti all’ingresso e genera:

- banco e scaffale per la taberna;
- bancone con dolia tecnici per il thermopolium;
- forno e area di lavorazione per il pistrinum;
- impluvium e sedute tecniche per la domus media.

I tag `RA_SHOP_INTERIOR`, `RA_THERMOPOLIUM_COUNTER`, `RA_PISTRINUM_OVEN` e `RA_DOMUS_ATRIUM` rendono verificabile la funzione senza asset artistici finali.

## Diagnostica e limiti

L’HUD mostra categorie edilizie, edifici a uno/due piani, interni, pannelli decorativi e binding local/fallback. F5, F7, F9, F10 e F11 restano disponibili. Tutte le superfici esterne provengono dal catalogo locale ignorato o dai fallback tecnici; nessun asset esterno è versionato.

`PLACEHOLDER_VISUALS_ONLY`: proporzioni, colore e dettagli non sono una ricostruzione definitiva. Non sono presenti personaggi, arredi o decorazioni figurative finali.
