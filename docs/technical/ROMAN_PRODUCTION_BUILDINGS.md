# Edifici produttivi romani

`Fullonica` e `Pistrinum` sono i primi archetipi produttivi completi.

## Fullonica

Flusso: ricezione tessuti → lavaggio → trattamento → asciugatura → deposito. Richiede vasche, canale idrico e scarico con tag `water_required`, `drainage_required` e `textile_processing`.

## Pistrinum

Flusso: deposito grano → macina → deposito farina → impastamento → forno → deposito/vendita pane. La macina è composta da `Millstone`, `RotationArm` e punti `AnimalPathPoint` marcati `animal_work_area` e `npc_animal_route`; non viene creato alcun asino 3D.
# Flussi produttivi Prompt 24

I flussi sono sequenze ordinate di ricezione, preparazione, lavorazione e deposito, collegate a acqua, drenaggio o calore quando necessari.
