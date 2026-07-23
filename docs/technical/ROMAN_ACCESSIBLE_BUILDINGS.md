# Edifici accessibili della vertical slice

Sono predisposti per l’attraversamento:

| Archetipo | Stanze tecniche | Decorazione |
|---|---:|---|
| PopularHouse | 2 | intonaco semplice, terra/laterizio |
| DomusMedia | 2 | terzo/quarto stile tecnico, opus signinum/mosaico |
| Taberna | 2 | vendita e retrobottega |
| Thermopolium | 2 | pareti sobrie e pavimento commerciale |
| BathComplex | 3 | palette termale e pavimento termale |
| MetalWorkshop | 2 | intonaco di servizio e pavimento produttivo |

Gli ingressi sono rivolti verso la strada in coordinate locali. `E` segnala l’accesso tecnico vicino e nasconde la copertura; non è necessaria un’interazione per entrare.

La mappa non contiene hard reference a `Content/LocalAssets`. Gli interni vengono generati a runtime dagli attori già presenti.

## Correzione Prompt 29-BIS

Il runtime omette i moduli astratti di parete, pavimento, tetto e apertura quando costruisce un archetipo accessibile. Questo elimina i volumi pieni che bloccavano ingresso e vista degli interni. I jamb in legno, la zoccolatura in laterizio, i pavimenti decorativi e le falde inclinate rendono distinguibili gli edifici senza introdurre asset finali.
