# Framework giuridico e procedurale

## Scopo

Tradurre status, norme, giurisdizioni, prove e autorità in procedure leggibili ma non anacronisticamente moderne.

## Descrizione

Il diritto non reagisce automaticamente a ogni torto. Un rimedio richiede soggetto capace o rappresentante, autorità competente, conoscenza, iniziativa, prove, tempo e risorse. Regola sostanziale, procedura ed esito sociale rimangono distinti.

## Ambito

Proprietà, contratti, debiti, famiglia, delitti, pene, processi, magistrature e conflitti di giurisdizione. Ogni profilo è datato/localizzato.

## Entità e regole

`LegalRule` possiede periodo, area, fonte A–E, soggetti, condizioni ed effetti; `CapacityFinding` applica status e atto; `Claim/Accusation` registra parti e rimedio; `EvidenceItem/Testimony` conserva provenienza e accesso; `Proceeding` possiede autorità, fasi e decisione; `Sanction` base, destinatario, esecuzione e conseguenze.

- Nessun illecito genera automaticamente un processo.
- Proprietà, possesso, custodia e uso sono distinti.
- Contratto valido, promessa sociale e obbligazione eseguibile non coincidono.
- Status influenza capacità e protezione ma non predetermina ogni esito.
- Le prove sono conosciute da soggetti specifici; niente giudice/guardia onnisciente.
- Pene e rimedi dipendono da atto, status, foro, prova, periodo e autorità.

## Procedura canonica

```mermaid
flowchart LR
    A[Danno o pretesa] --> B[Conoscenza e iniziativa]
    B --> C[Capacità/legittimazione]
    C --> D[Autorità competente]
    D --> E[Domanda o accusa]
    E --> F[Prove, difesa e udienza]
    F --> G[Decisione]
    G --> H[Esecuzione, appello/contestazione o fallimento]
```

## Delitti, processi e pene

La tassonomia P0 include violenza, omicidio, furto/rapina, frode, danneggiamento, contrabbando e corruzione soltanto nelle forme storicamente valide. Esiti: restituzione, compensazione, multa, perdita di diritti/status, coercizione fisica, espulsione, detenzione o pena capitale solo con profilo e review. Il sistema registra anche mancata tutela, accordo, fuga ed esecuzione fallita.

## Eventi, casi limite e persistenza

Produce `ClaimFiled`, `JurisdictionAccepted/Rejected`, `EvidenceAdmitted`, `DecisionIssued`, `SanctionExecuted`; ascolta crimine osservato, morte, status, proprietà, contratto, direttiva e fuga. Autorità morta, parti assenti, prove contraddittorie, norma mutata, doppio foro, prescrizione/tempo e save durante udienza usano stati sospesi e recovery idempotente. Persistono fascicolo, prove, conoscibilità, fasi, decisioni ed esecuzione.

## Accuratezza storica

Niente polizia, pubblico ministero, carcere o diritti processuali moderni come default. Lessico UI distingue traduzione funzionale da termine latino. Ogni procedura P0 richiede review di storia giuridica.

## Dipendenze

- [Status](../family-social/social-status.md)
- [Diritto civile](civil-law.md)
- [Criminalità](criminality.md)
- [Processi](trials.md)
- [Pene](punishments.md)

## Collegamenti agli altri documenti

- [Proprietà](../economy-production/property.md)
- [Contratti](../economy-production/contracts.md)
- [Indagini](investigations.md)
- [Magistrature](magistracies.md)

## Test e Definition of Done

Test a matrice status × atto × foro × prova, mancata denuncia, autorità errata, sentenza/esecuzione, aggregazione e save/load. S4 quando almeno un caso civile e uno criminale P0 sono completi e storicamente approvati.

## Decisioni ancora aperte

- Fori, procedure, rimedi e pene della data canonica.
- Livello di astrazione UX e contenuti esclusi per sicurezza.

## TODO

- Creare matrice illecito/pretesa-procedura-rimedio-fonte.
- Allineare sottodocumenti specialistici.
