# Scope e non-obiettivi

**ID:** VIS-003
**Stato:** Approved — Baseline 1.0
**Owner:** Game Director / Executive Producer

## Scopo

Definire confini progressivi del prodotto, impedire che la visione imperiale destabilizzi la vertical slice e rendere ogni ampliamento una decisione verificabile.

## Descrizione

Documento canonico per orizzonti di sviluppo, classi di scope, non-obiettivi e change control.

## Ambito

Copre D0–D3 e le regole di promozione; quantità finali, date e backlog dipendono dalle decisioni ancora aperte.

## Visione dello scope

Lo scope è gestito per orizzonti di prova, non come lista cumulativa di desideri. Ogni orizzonte dimostra una tesi prima di autorizzare il successivo.

~~~mermaid
flowchart LR
    D["D0: Game Bible"] -->|gate documentale| P["D1: Pompei"]
    P -->|densità, stabilità, leggibilità| R["D2: Regione campana"]
    R -->|strumenti e differenziazione| I["D3: Impero modulare"]
~~~

## Orizzonte D0 — Game Bible

**Obiettivo:** definire visione, storia, sistemi, dati, contenuti, rischi, test e gate.
**Include:** documentazione e ricerca.
**Exit:** decisioni bloccanti della demo risolte e checklist di readiness approvata.
**Stato:** in corso.

## Orizzonte D1 — Vertical slice di Pompei

**Obiettivo:** dimostrare una vita urbana densa e autonoma.
**Core candidato:** tre origini/status; tempo; bisogni; NPC persistenti; household e relazioni; lavoro; filiera alimentare; scambio/credito; status e diritto locale essenziale; culto selezionato; reputazione; illecito/testimoni; situazioni emergenti; persistenza e recap.
**Semplificato:** mondo esterno, guerra, politica imperiale, demografia di lungo periodo.
**Escluso finché non approvato:** eruzione giocabile, campagna militare, trionfo a Roma, generazioni complete.

## Orizzonte D2 — Ecosistema campano

**Obiettivo:** provare mobilità e interdipendenza tra città, territorio rurale, porto e rotte.
**Gate:** costi misurati; transizioni stabili; contenuti locali differenziati; strumenti usabili dai designer.

## Orizzonte D3 — Impero modulare

**Obiettivo:** espandere regioni collegate attraverso commercio, amministrazione, guerra, religione e informazione.
**Regola:** nessuna regione è un reskin; ogni pacchetto dichiara periodo, istituzioni, economie, lingue, culture materiali, rischi e fonti.

## Non-obiettivi globali

- Replica continua 1:1 dell'intero Impero.
- Protagonista predestinato o onnipotente.
- Combattimento come soluzione universale.
- Simulazione microscopica senza valore osservabile.
- Economia controllabile da una sola attività del player.
- Accuratezza assoluta dove l'evidenza è insufficiente.
- Religione soprannaturale confermata oggettivamente.
- Istituzioni moderne retroproiettate.
- Multiplayer, live service, VR o modding come requisito della demo.
- Quantità usata come sostituto della profondità.

## Classi di scope

| Classe | Significato | Autorità |
|---|---|---|
| Core | necessaria per dimostrare la promessa | Direction + Production |
| Supporting | rafforza il core con costo sostenibile | Area leads |
| Optional | rimovibile senza danneggiare la tesi | Product owner |
| Future | coerente, non pianificata ora | ADR prima della promozione |
| Research | necessita evidenza | Owner ricerca |
| Out | contraddice visione o vincoli | Game Director per riapertura |

## Change control

Ogni ampliamento dichiara pilastri, promessa, orizzonte, costo totale, dipendenze, contenuti, impatto storico/etico, test e feature da rimuovere o ritardare. L'aggiunta senza trade-off è incompleta.

## Esempio

“Battaglie campali nella demo” è Future/Out per D1: richiede nuovi domini e sovrarappresenta la carriera militare. “Notizie e shock economici da una guerra remota” è Supporting perché dimostra il collegamento locale-imperiale con costo controllato.

## Casi limite

- Una feature documentata non è automaticamente in scope.
- Un prototipo non costituisce commitment.
- Un contenuto iconico può restare escluso se non serve la tesi.
- L'accessibilità è qualità core, non optional.
- Tooling e debito tecnico fanno parte del costo totale.

## Dipendenze

- [Visione](creative-vision.md)
- [Pilastri](design-pillars.md)
- [Tassonomia](game-design-bible/feature-taxonomy.md)
- [Vincoli](game-design-bible/product-constraints.md)

## Collegamenti agli altri documenti

- [Pompei](../07-pompeii-demo/README.md)
- [Roadmap](../11-production/roadmap-backlog/product-roadmap.md)
- [Rischi](../11-production/risk-register.md)
- [Analisi future](../12-future-analysis/README.md)

## Decisioni ancora aperte

Data e durata della demo; area esatta; piattaforme; rating; modello commerciale; successione; presenza dell'eruzione.

## Rischi

Scope creep; dipendenze nascoste; promesse premature; future-proofing costoso; taglio di strumenti o accessibilità per preservare contenuti.

## Criteri di completamento

- Ogni feature è classificata e collegata a un orizzonte.
- Ogni ampliamento possiede un trade-off.
- D1 ha tesi, core ed esclusioni.
- Nessun documento inferiore contraddice lo scope senza ADR.

## TODO

- Classificare il backlog di Pompei dopo il completamento dei domini.
- Chiudere Q-001–Q-005 prima del greenlight.
