# Matrice di readiness per l'implementazione

## Scopo

Rendere verificabile quando un sistema è sufficientemente progettato per entrare in implementazione, senza confondere la presenza di un file con la maturità del suo contenuto.

## Descrizione

La matrice usa i livelli S0–S5 dello [standard di specifica](../../00-governance/system-specification-standard.md). Nessun sistema può entrare in sviluppo prima di S4 e del superamento della Definition of Ready; S5 richiede validazione interdisciplinare.

## Ambito

Tutti i sistemi del catalogo canonico, inclusi servizi trasversali. La matrice misura readiness documentale, non avanzamento del codice.

## Criteri di valutazione

| Dimensione | Evidenza richiesta per S4 |
|---|---|
| identità e confini | owner, responsabilità, esclusioni, glossario |
| requisiti | FR/NFR/vincoli storici identificati e verificabili |
| contratti | input, output, dati, comandi, query ed eventi versionabili |
| comportamento | stati, transizioni, flussi e invarianti |
| integrazione | dipendenze dirette, inverse e documenti impattati |
| qualità | errori, persistenza, performance, scalabilità e configurazione |
| delivery | priorità, complessità, rischi, test, accettazione e DoD |
| decisioni | nessun blocco incompatibile con la milestone |

## Stato iniziale dei sistemi

| ID | Sistema | Livello | Lacuna principale | Milestone documentale |
|---|---|---:|---|---|
| SYS-TIME | tempo e calendario | S3 | budget e contratti puntuali | Fondazioni AAA |
| SYS-EVT | eventi | S4 | tecnologia differita non bloccante | Fondazioni AAA |
| SYS-ID | identità | S2 | lifecycle di alias/tombstone | Fondazioni AAA |
| SYS-WORLD | mondo e spazio | S3 | budget GIS/streaming e autorità delle trasformazioni | Vertical slice Pompei |
| SYS-SIM | orchestrazione simulazione | S3 | budget quantitativi e recovery | Fondazioni AAA |
| SYS-PER | persona/ciclo di vita | S3 | regole storiche e UX successione | Simulazione sociale |
| SYS-SAVE | persistenza | S1 | snapshot, migrazione e recovery | Fondazioni AAA |
| SYS-KNOW | conoscenza | S3 | budget memoria e policy di sintesi | Simulazione sociale |
| SYS-NPC | decisione NPC | S3 | budget e catalogo azioni demo | Simulazione sociale |
| SYS-REL | relazioni | S3 | budget edge e review dati sensibili | Simulazione sociale |
| SYS-HH | famiglia/successione | S2 | casi giuridici e atomizzazione | Simulazione sociale |
| SYS-STAT | status | S2 | matrice epoca/luogo/diritto | Istituzioni |
| SYS-ECO | economia | S2 | formule, aggregazione e budget | Economia Pompei |
| SYS-PROP | proprietà | S2 | transazioni e titoli | Economia Pompei |
| SYS-INV | inventario | S2 | lotti, custodia, decadimento | Economia Pompei |
| SYS-WORK | professioni/produzione | S2 | contratti output e scheduling | Economia Pompei |
| SYS-INT | interazione | S2 | stati di contesa/interruzione | Gameplay slice |
| SYS-CONT | contratti | S2 | modello obbligazioni | Istituzioni |
| SYS-REP | reputazione | S2 | separazione da conoscenza | Simulazione sociale |
| SYS-NEED | bisogni | S2 | curve e soglie | Gameplay slice |
| SYS-UI | interfaccia | S1 | flussi e accessibilità misurabile | Esperienza slice |
| SYS-RELIG | religione | S2 | autorità rituali e calendario | Istituzioni |
| SYS-POL | politica | S2 | competenze per epoca/luogo | Istituzioni |
| SYS-CRIME | criminalità | S2 | prova, denuncia e processo | Istituzioni |
| SYS-COMBAT | combattimento | S2 | modello lesioni e leggibilità | Gameplay slice |
| SYS-WAR | guerra | S1 | confini demo/futuro | Post-slice |
| SYS-AUTH | autorizzazioni/transazioni | S3 | modello di rollback | Fondazioni AAA |
| SYS-HIST | provenienza storica | S1 | schema claim e gate di revisione | Fondazioni AAA |
| SYS-DBG | diagnostica | S2 | SLO e retention | Fondazioni AAA |

## Gate di avanzamento

```mermaid
flowchart LR
    S0["S0 Registrato"] --> S1["S1 Inquadrato"]
    S1 --> S2["S2 Progettato"]
    S2 --> S3["S3 Contrattualizzato"]
    S3 --> S4["S4 Ready"]
    S4 --> G{"DoR superata?"}
    G -->|sì| I["Implementabile"]
    G -->|no| B["Bloccato con owner"]
    I --> S5["S5 Validato"]
```

## Regole operative

- Il livello è il minimo delle dimensioni, non una media.
- Un TODO critico impedisce S4; un'estensione P3/P4 può essere differita.
- Ogni promozione cita evidenze e revisori.
- Una modifica a un contratto può retrocedere i sistemi dipendenti.
- La matrice viene aggiornata nella stessa modifica dei documenti sorgente.

## Strategie di test

- audit automatico delle sezioni obbligatorie;
- controllo dei riferimenti agli ID canonici;
- review incrociata design/engineering/QA/storia;
- walkthrough di almeno un flusso nominale, alternativo e di errore;
- tracciabilità tra requisiti e criteri di accettazione.

## Criteri di accettazione

- Tutti i sistemi del catalogo sono presenti una sola volta.
- Ogni livello ha lacuna, owner previsto e milestone.
- Nessun sistema marcato S4 conserva decisioni bloccanti per la milestone.
- Le dipendenze P0 sono almeno S3 prima che un consumer raggiunga S4.

## Definition of Done

La matrice è verificata durante ogni gate documentale, allineata a roadmap, rischi e questioni aperte, e approvata dai responsabili delle discipline coinvolte.

## Dipendenze

- [Catalogo dei sistemi](../../00-governance/system-catalog.md)
- [Standard di specifica](../../00-governance/system-specification-standard.md)
- [Definition of Ready](definition-of-ready.md)
- [Roadmap di prodotto](product-roadmap.md)

## Collegamenti agli altri documenti

- [Matrice delle dipendenze](../../00-governance/system-dependency-matrix.md)
- [Registro dei rischi](../risk-register.md)
- [Questioni aperte](../../00-governance/open-questions.md)

## Decisioni ancora aperte

- Assegnare owner nominativi quando saranno definite composizione e responsabilità del team.
- Approvare i budget quantitativi che separano S3 da S4 per simulazione e performance.

## TODO

- Collegare ogni riga alla checklist di review della relativa milestone.
- Rieseguire la valutazione dopo ogni macroarea completata.
