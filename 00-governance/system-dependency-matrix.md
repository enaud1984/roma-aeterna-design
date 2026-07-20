# Matrice delle dipendenze tra sistemi

## Scopo

Rendere visibili le dipendenze principali tra domini prima dell'approfondimento e dell'implementazione.

## Descrizione

La matrice iniziale indica relazioni dirette. Le specifiche future definiranno direzione, contratto, dati, frequenza e failure mode.

## Ambito

Copre i macro-sistemi; le dipendenze di dettaglio restano nei documenti canonici.

| Sistema | Dipende principalmente da | Produce effetti su |
|---|---|---|
| Tempo ed eventi | calendario, mondo, persistenza | tutti i sistemi temporali |
| NPC e AI | popolazione, luoghi, bisogni, conoscenza | economia, relazioni, contenuti |
| Famiglia e status | diritto, NPC, proprietà | progressione, eredità, reputazione |
| Economia | popolazione, produzione, trasporti, proprietà | città, politica, salute, crimine |
| Politica | status, reputazione, economia, informazione | amministrazione, diritto, eventi |
| Religione | calendario, comunità, economia, luoghi | reputazione, politica, contenuti |
| Militare | politica, economia, popolazione, logistica | guerre, prezzi, veterani, trionfi |
| Salute | corpo, ambiente, alimenti, cura | routine, lavoro, famiglia, eventi |
| Missioni | stato canonico, NPC, eventi, conoscenza | relazioni, economia, memoria |
| UI/UX | conoscenza del personaggio, sistemi | leggibilità e decisioni del giocatore |
| Persistenza | tutti gli stati canonici | continuità, recovery e test |
| Pompei | tutti i domini core selezionati | validazione della visione |

## Dipendenze

- [Architettura della simulazione](../04-simulation/simulation-architecture.md)
- [Modello dati](../10-technical/data/README.md)

## Collegamenti agli altri documenti

- [Mappa documentale](documentation-map.md)
- [Matrice di tracciabilità](traceability-matrix.md)
- [Registro rischi](../11-production/risk-register.md)

## Decisioni ancora aperte

- Direzione e criticità di ogni contratto.
- Dipendenze vietate e ownership dello stato.

## TODO

- Espandere a livello di sottosistema.
- Aggiungere classificazione hard/soft, sync/async e criticità.
- Collegare ogni relazione a requisiti, ADR e test.
