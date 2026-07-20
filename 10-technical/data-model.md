# Modello dati concettuale

**ID:** TEC-DATA-001
**Stato:** Draft

## Scopo

Definire ownership e relazioni concettuali senza vincolare database o linguaggio.

## Aggregati principali

**Persona:** identità, status, corpo, conoscenza, impegni. **Household:** membri, autorità, risorse condivise, residenza. **Luogo:** gerarchia, accessi, capacità. **Proprietà:** bene, titolare, possessore, diritti. **Attività:** trasformazioni, lavoratori, strumenti, scorte. **Relazione:** parti, dimensione, evidenze. **Istituzione:** ruoli, regole, giurisdizione. **Evento:** tipo, tempo, luogo, cause, partecipanti, effetti. **Fonte storica:** affermazione, classe H, citazione, decisione.

## Identità e riferimenti

Ogni entità persistente ha ID stabile; nomi visualizzati non sono chiavi. Relazioni puntano a identità anche quando un'entità è aggregata. Eliminazione logica e successione preservano audit.

## Eventi e stato

Non è ancora deciso se l'architettura sarà event-sourced. Requisito minimo: gli eventi narrativamente o economicamente rilevanti permettono spiegazione e replay diagnostico limitato; snapshot evitano ricostruzioni infinite.

## Conoscenza

Fatto canonico, osservazione e credenza sono strutture separate. Una reputazione deriva da eventi/affermazioni presso una comunità, non modifica il fatto originale.

## Provenienza

Regole, asset e contenuti storici possono collegarsi a schede fonte. La provenienza editoriale non deve gonfiare il salvataggio runtime: strategia di compilazione TBD.

## Validazioni

Unicità ID, riferimenti validi, unità compatibili, quantità non negative dove richiesto, calendari coerenti, accessi non circolari, eventi senza effetti non autorizzati e contenuti privi di fonte/decisione.

## Scopo

Conservare e sviluppare la responsabilità canonica descritta da questo documento all'interno della Game Bible.

## Descrizione

Il contenuto preesistente costituisce la baseline del dominio. Questa sezione normalizza il documento secondo il contratto minimo della nuova architettura senza sostituirne le informazioni.

## Ambito

Il perimetro è quello definito nelle sezioni precedenti; implementazione e asset restano esclusi finché non saranno autorizzati da milestone e decisioni formali.

## Dipendenze

- [Standard documentale](../00-governance/documentation-standard.md)
- [Visione creativa](../01-vision/creative-vision.md)

## Collegamenti agli altri documenti

- [Indice generale](../README.md)
- [Mappa documentale](../00-governance/documentation-map.md)
- [Registro decisioni](../00-governance/decision-log.md)
- [Questioni aperte](../00-governance/open-questions.md)

## Decisioni ancora aperte

- Owner e reviewer nominali.
- Stato di approvazione e profondità richiesta dalla roadmap documentale.
- Eventuali confini da riallineare con i nuovi sottodomini canonici.

## TODO

- Collegare il contenuto ai nuovi documenti specializzati pertinenti.
- Assegnare ownership, versione e milestone.
- Aggiungere requisiti, fonti, rischi, test e Definition of Done durante l'approfondimento.
