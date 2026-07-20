# Bilanciamento e validazione economica

## Scopo

Mantenere un'economia leggibile, resistente agli exploit e capace di crisi senza imporre stabilità artificiale o grind.

## Descrizione

Il bilanciamento calibra relazioni, non prezzi fissi: accessibilità, margini, scorte, capacità, mobilità, rischio, concentrazione e velocità di recupero. Le correzioni avvengono su dati e cause verificabili, mai con sottrazioni invisibili al giocatore.

## Ambito

Fonti e pozzi, elasticità, volatilità, progressione economica, fallimento, shock, mercato nero, aggregazione E0–E5, telemetria locale e suite di scenario.

## Obiettivi misurabili

| Obiettivo | Indicatore | Segnale d'allarme |
|---|---|---|
| Conservazione | bilancio beni/moneta/diritti per evento | creazione o perdita senza causale |
| Accessibilità | giorni-lavoro per paniere/status | fame sistemica fuori scenario |
| Attività | quota imprese operative e transazioni | mercato congelato o churn totale |
| Volatilità | variazione per paniere e mercato | oscillazioni alternate senza shock |
| Mobilità | tempo/opportunità per apprendistato e impresa | percorso garantito o impossibile |
| Resilienza | tempo di recupero dopo shock | ritorno istantaneo o collasso permanente |
| Scala player | quota di mercato locale/regionale | singolo raccolto muove E4/E5 |

## Regole

- Le fonti monetarie devono essere attori espliciti; i pozzi sono pagamenti verso un attore o ritiro documentato.
- Consumo, deterioramento, manutenzione, tasse, salari e investimenti hanno causali visibili.
- Prezzi reagiscono con ritardo e limiti configurabili; l'offerta risponde solo se esistono input, capacità e lavoro.
- La difficoltà modifica informazione, rischio e margini di errore, non falsifica inventari.
- Nessuna carriera garantisce profitto; nessun fallimento elimina tutte le vie di recupero.
- Antidumping e antimonopolio sono conseguenze sociali/istituzionali plausibili, non pareti invisibili.

## Exploit da prevenire

Doppia vendita, save/load arbitrage, loop di ricetta positivo, prestiti circolari, salario senza lavoro, rinnovo infinito di ordini, teletrasporto merci, manipolazione di mercato con quantità irrilevanti, furto senza cambio di custodia, eredità duplicata, prezzi negativi e conversioni di unità incoerenti.

## Suite di scenari

1. Baseline Pompei: 90 giorni simulati senza player.
2. Ritardo del grano: scorte, sostituzioni, prezzi, debiti e folla.
3. Incendio di forno/magazzino: capacità distrutta e recupero.
4. Epidemia: lavoro, domanda, mortalità, trasporto e credito.
5. Guerra/rotta interrotta: importazioni, mercato nero e requisizioni.
6. Player bottega: avvio, assunzione, perdita, credito, fallimento e ripresa.
7. Whale test: grande raccolto personale confinato alla quota E1/E2.
8. Time-skip/save-load: risultati identici a parità di seed e input.

## Persistenza, prestazioni e configurabilità

Metriche aggregate per mercato e intervallo, campionamento dettagliato solo per attori P0. Snapshot conservano prezzi, scorte, capacità, ordini, debiti e shock. Tabelle configurabili: unità, ricette, rese, deterioramento, capacità, priorità, intervalli E0–E5 e limiti di stabilizzazione; ogni modifica è versionata.

## Dipendenze

- [Modello economico](economic-model.md)
- [Prezzi](prices.md)
- [Filiere](supply-chains.md)
- [Crisi](economic-crises.md)

## Collegamenti agli altri documenti

- [Testing](../../11-production/testing/README.md)
- [Prestazioni](../../10-technical/performance/README.md)
- [Economia demo](../../07-pompeii-demo/demo-economy.md)

## Criteri di accettazione e Definition of Done

Bilanci di conservazione chiusi; scenario baseline stabile ma non statico; shock spiegabili e recuperabili; nessun exploit P0; risultati E0/E2 coerenti entro tolleranza approvata; player incapace di influenzare livelli superiori senza capacità corrispondente; metriche riproducibili.

## Decisioni ancora aperte

- Soglie numeriche di volatilità, accessibilità e quota di mercato per la demo.
- Durata e severità degli scenari di stress accettabili.

## TODO

- Approvare paniere e profili household di Pompei.
- Definire dashboard e report automatici in fase tecnica, senza implementarli ora.
