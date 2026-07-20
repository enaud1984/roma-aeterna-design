# Economia della demo di Pompei

**ID:** DEM-ECO-001
**Stato:** Specifica S3 — valori storici e budget da validare

## Scopo

Dimostrare con una catena verticale leggibile che il mondo produce, trasporta, contratta, consuma e reagisce anche senza il giocatore.

## Descrizione

La spina P0 è grano → stoccaggio → molitura → farina → panificazione → distribuzione/credito → consumo/scarto. Attraversa lavoro, proprietà, bisogni, prezzi, relazioni, diritto e folla. Vino, olio, ceramica e tessili sono P1 candidati; le altre filiere restano condizioni aggregate o contenuto futuro.

## Ambito

Un mercato cittadino E2, imprese E1 selezionate, azioni E0 attorno al giocatore e corridoi E3/E4 verso hinterland e porti. E5 fornisce soltanto condizioni esterne. Nessun raccolto del giocatore altera l'Impero.

## Ciclo dimostrativo

```mermaid
flowchart LR
    A[Informazione e lavoro] --> B[Guadagno o credito]
    B --> C[Acquisto input/strumenti]
    C --> D[Produzione o trasporto]
    D --> E[Consegna e vendita]
    E --> F[Consumo, reinvestimento o debito]
    F --> A
```

## Percorsi per status

| Status | Ingresso candidato | Progressione possibile | Vincoli da mostrare |
|---|---|---|---|
| Cittadino | lavoro, investimento o piccola proprietà | specializzazione, contratto, bottega, quota | capitale, reputazione, rischio e obblighi |
| Liberto | mestiere/rete del patronato e lavoro autonomo | clientela, collegium, bottega, investimento | obblighi, stigma/opportunità contestuali, credito |
| Schiavo | mansione assegnata e relazioni coercitive | competenza, responsabilità, peculio solo se storicamente/configurativamente valido, manomissione non garantita | assenza di libertà contrattuale piena, violenza e conseguenze; mai inventario |

## Attori, luoghi e dati

Intermediari, trasportatori, proprietari di scorte, mugnai/panettieri, lavoratori liberi e schiavizzati, venditori, household, creditori e autorità. Luoghi P0: almeno un magazzino, mulino/panificio, mercato, abitazioni clienti e rotta d'ingresso. Persistono lotti rilevanti, scorte E1/E2, contratti, debiti, diritti, capacità, prezzi, shock e storico del player.

## Shock dimostrativo

Un ritardo di approvvigionamento autonomo riduce scorte. Attori usano riserve, sostituiscono, rinegoziano, razionano, importano o chiudono secondo mezzi e conoscenze. Prezzi, credito, pettegolezzi e folla reagiscono; non esiste un'unica quest risolutiva.

## Bilanciamento, performance e test

Metriche: copertura scorte, throughput, prezzo per qualità/luogo, accessibilità per household, insolvenza, tempi, spreco, concentrazione e quota player. Test: baseline 90 giorni, shock, incendio, fallimento, doppia transazione, time-skip, save/load, E0↔E2 e grande raccolto personale. Budget numerici dipendono dal benchmark tecnico.

## Dipendenze

- [Modello economico](../04-simulation/economy-production/economic-model.md)
- [Filiere](../04-simulation/economy-production/supply-chains.md)
- [Carriere](../04-simulation/professions-education/career-framework.md)
- [Pompei](README.md)

## Collegamenti agli altri documenti

- [Prezzi](../04-simulation/economy-production/prices.md)
- [Contratti](../04-simulation/economy-production/contracts.md)
- [Bilanciamento](../04-simulation/economy-production/economic-balancing.md)
- [Readiness](../11-production/roadmap-backlog/implementation-readiness-matrix.md)

## Criteri di completamento

Catena P0 end-to-end, tre percorsi su carta, shock autonomo, conservazione chiusa, aggregazione riconciliata, fallimento recuperabile, fonti collegate e budget approvati.

## Decisioni ancora aperte

- Edifici e imprese P0 dopo verifica archeologica.
- Professioni disponibili, paniere, valori e durata dello shock.

## TODO

- Collegare imprese a coordinate e dossier edilizi.
- Preparare scenari di accettazione interdisciplinari.
