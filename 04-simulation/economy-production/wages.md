# Salari e compensi

## Scopo

Definire compensi monetari, in natura, a risultato o misti coerenti con lavoro, status e mercato locale.

## Descrizione

Il compenso è un'obbligazione prodotta da prestazione, accordo o autorità; non è generato automaticamente dal trascorrere del tempo. Tariffe e potere d'acquisto sono intervalli contestuali da validare storicamente.

## Ambito

Paga per tempo/compito, vitto/alloggio, anticipi, trattenute lecite o contestate, premi, quote, mora e reclami. Non equipara tutte le forme di lavoro al salario moderno.

## Regole

- Base, unità, qualità, scadenza, mezzo e prova sono espliciti.
- Il datore riserva liquidità/beni o assume debito; l'insolvenza non cancella il credito.
- Paga nominale e reale sono distinte tramite paniere locale.
- Competenza, rischio, rarità, stagione, patronato, status e potere negoziale influenzano condizioni.
- Lavoro coercitivo e compensi eventuali restano modellati separatamente dallo status.

## Flusso e dati

Accordo → prestazione verificata/parziale → obbligazione → pagamento totale/parziale/mora → ricevuta o controversia. `CompensationTerm` possiede base, quantità, denaro/beni, calendario, tolleranze e prova; `Payable` possiede saldo e priorità; `Payment` usa il ledger monetario/inventario.

## Casi limite, bilanciamento e test

Datore senza fondi, paga in bene deteriorato, qualità contestata, anticipo superiore, giornata interrotta, morte e cambio di unità aprono rimedio esplicito. Testare conservazione, pagamento misto, parziale, mora, inflazione locale, aggregazione e save/load. Vietato bilanciare sottraendo paga invisibilmente.

## Dipendenze

- [Lavoro](labor.md)
- [Moneta](currency.md)
- [Prezzi](prices.md)
- [Credito](credit-and-debt.md)

## Collegamenti agli altri documenti

- [Carriere](../professions-education/career-framework.md)
- [Contratti](contracts.md)
- [Bilanciamento](economic-balancing.md)

## Prestazioni e persistenza

Paghe P0 individuali; payroll remoto per lotti idempotenti con eccezioni individuali. Persistono termini, prestazioni, saldi, pagamenti, arretrati e controversie.

## Criteri di completamento

Ogni lavoro P0 produce un compenso o una ragione storico-giuridica della sua assenza; potere d'acquisto e insolvenza sono testati su 90 giorni.

## Decisioni ancora aperte

- Panieri, intervalli e frequenze di pagamento della demo.
- Forme di compenso per professione e status.

## TODO

- Collegare dataset e fonti economiche approvate.
- Definire scenari di arretrato e reclamo.
