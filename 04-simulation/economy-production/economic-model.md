# Modello canonico dell'economia simulata

**System ID:** SYS-ECO-001
**Stato:** S3 — Contracted

## Scopo

Simulare produzione, scambio, consumo, credito e shock con causalità leggibile, conservazione dei valori materiali e costo scalabile.

## Descrizione

L'economia è una rete di agenti, household, attività, mercati e rotte. Non è un'asta globale né un minigioco separato: lavoro, status, proprietà, patronato e informazione determinano accesso e potere contrattuale.

## Ambito

Economia locale dettagliata, mercati urbani, flussi regionali e macroeconomia aggregata. La simulazione non pretende serie storiche complete dove le fonti non esistono.

## Entità e autorità

| Entità | Proprietario | Invarianti |
|---|---|---|
| GoodDefinition | catalogo dati | unità, qualità, durabilità versionate |
| Lot/Stock | SYS-INV | quantità non negativa, luogo/custode |
| OwnershipRight | SYS-PROP | titolare e titolo separati dalla custodia |
| MoneyHolding | SYS-ECO | denominazione/quantità/proprietario |
| Account | SYS-ECO | movimenti bilanciati e auditabili |
| Contract/Claim | SYS-CONT | parti, obbligo, scadenza, prova |
| Enterprise | SYS-WORK | capacità, locali, strumenti, lavoro |
| Market | SYS-ECO | luogo, partecipanti, categorie, memoria prezzi |
| Route | SYS-WORLD | tempo, capacità, costo, rischio |

## Invarianti economiche

- Nessun bene, denaro o diritto nasce senza sorgente autorizzata.
- Produzione consuma input, tempo, capacità e lavoro; scarti e perdite sono contabilizzati.
- Proprietà, possesso, custodia e uso non sono sinonimi.
- Una transazione è atomica per denaro, bene, titolo e obbligo oppure fallisce/compensa.
- I prezzi non trasferiscono fisicamente merci.
- Aggregazione conserva stock, crediti/debiti, capacità e impegni entro tolleranze.
- Il player è un agente locale soggetto alle stesse regole.

## Ciclo economico

```mermaid
flowchart LR
    R["Risorsa / importazione"] --> P["Produzione"]
    P --> S["Stoccaggio"]
    S --> T["Trasporto"]
    T --> M["Mercato / assegnazione"]
    M --> C["Consumo / uso"]
    C --> W["Scarto / usura / recupero"]
    M --> A["Pagamento / credito"]
    A --> I["Investimento, tasse, rendite"]
    I --> P
```

## Domanda e offerta

Domanda effettiva = bisogno/desiderio + accesso + capacità di pagare/credito + informazione + tempo. Offerta effettiva = stock disponibile + diritto di vendere + accesso al mercato + capacità logistica. Bisogno senza potere d'acquisto resta domanda sociale ma non ordine di mercato: influenza fame, politica, patronato e crimine.

## Mercati e formazione dei prezzi

I mercati sono locali e segmentati per luogo, qualità, relazione e tempo. Venditore e acquirente formano aspettative da prezzi osservati, scorte, urgenza e voci. Il clearing aggregato produce range, volumi e transazioni rappresentative; vicino al player si negoziano transazioni reali.

## Lavoro, salari e remunerazioni

Il lavoro può essere salariato, a cottimo, household, obbligato, schiavizzato, apprendistato, favore o quota. `WageOffer` specifica unità temporale/output, vitto/alloggio, anticipo, penalità, scadenza e prova. Non monetizzare automaticamente ogni prestazione.

## Tasse, affitti e rendite

Ogni prelievo ha autorità, base, periodo, luogo, debitore, beneficiario, modalità, esenzioni e conseguenza. Affitto separa uso, durata, manutenzione, deposito/garanzia e sublocazione. Tasse imperiali, municipali e canoni privati non confluiscono in un'unica percentuale universale.

## Collegia e patronato economico

Un *collegium* può offrire rete, rito, mutuo supporto, reputazione e accesso, quando attestato; non è automaticamente gilda moderna che fissa prezzi. Patronato fornisce capitale, garanzia, clienti o protezione in cambio di obblighi; non è prestito gratuito né fazione lineare.

## Scarsità e shock

Scarsità nasce da domanda, perdita, capacità, ritardo o informazione. Crisi, carestia, guerra, epidemia e incendio sono combinazioni di shock su stock, lavoro, trasporto, rischio, credito e autorità. L'inflazione locale è aumento persistente di un paniere contestuale, non ogni rincaro di un bene.

## Mercato nero e speculazione

Il mercato nero emerge quando divieti, tasse, scarsità o status rendono costoso lo scambio legale. Richiede rete, fiducia, nascondiglio, rischio e ricettazione. Speculazione significa detenere/riallocare beni sulla base di aspettative; può stabilizzare o aggravare, senza etichetta morale automatica.

## Livelli E0–E5

| Livello | Scope | Simulazione |
|---:|---|---|
| E0 | transazione osservata | lotti, monete/credito, negoziazione |
| E1 | attività/edificio | ordini, scorte, lavoro, capacità |
| E2 | mercato cittadino | curve a gradini, volumi, range prezzi |
| E3 | città non caricata | settori e bilanci aggregati |
| E4 | regione/rotta | flussi, capacità, shock, prezzi indice |
| E5 | Impero | indici e grandi corridoi, nessun lotto individuale |

Il raccolto del player modifica E0/E1 e, se grande, una quota E2. Non può alterare E4/E5 oltre il peso reale dichiarato.

## Eventi

Produce `TransactionSettled`, `PriceObserved`, `StockShortage`, `EnterpriseOpened/Closed`, `DefaultOccurred`, `MarketDisrupted`, `TaxDue/Paid`, `RentDue/Paid`. Riceve tempo, produzione, consumo, rotta, guerra, salute, incendio, contratto e proprietà.

## Persistenza

Snapshot di stock, conti, mercati, attività, rotte e indici; ledger per transazioni salienti, proprietà, debiti e contratti. I prezzi derivati sono ricostruibili da storia minima/versione.

## Casi limite

Prezzo zero/negativo, bene indivisibile, moneta insufficiente, baratto, pagamento misto, stock rubato, doppia vendita, mercato senza partecipanti, attività senza clienti, eredità durante transazione, rotta interrotta, shock simultanei.

## Performance

Aggiornamenti event-driven; mercati E2 a intervalli; E3–E5 batch; lotti fungibili compressi; eventi hard non coalescibili; indici per bene/luogo; back-pressure e limite ordini.

## Test

Conservazione, doppia entrata concettuale, 180 giorni, shock grano, perdita acquirente, festa, guerra, incendio, epidemia, arbitraggio, player farm, E0↔E4, save/migrazione e fuzz dei parametri.

## Dipendenze

- [Ownership dati](../../10-technical/data/data-ownership-matrix.md)
- [Proprietà](property.md)
- [Contratti](contracts.md)
- [Trasporto](transport.md)
- [NPC](../npc-population-ai/npc-model.md)

## Collegamenti agli altri documenti

- [Moneta](currency.md)
- [Prezzi](prices.md)
- [Credito](credit-and-debt.md)
- [Filiere](supply-chains.md)
- [Bilanciamento](economic-balancing.md)

## Criteri di completamento

Invarianti, E0–E5, transazioni, shock, persistence e test approvati; nessuna fonte/pozzo implicita; demo stabile 180 giorni.

## Definition of Done

Cataloghi, formule, budget, dati storici, scenari e inspector economico pronti per S4.

## Decisioni ancora aperte

- Paniere, unità contabile e parametri quantitativi Pompei.
- Beni e mercati P0 della demo.

## TODO

- Chiudere dossier monetario/prezzi HV-006.
- Dimensionare scenari E0–E5.
