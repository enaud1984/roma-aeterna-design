# Modello demografico e individualizzazione

## Scopo

Rappresentare popolazioni numerose tramite individui, coorti e statistiche compatibili, senza inventare precisione storica.

## Descrizione

La popolazione conserva persone e distribuzioni attraverso luogo, età, sesso, status, origine, household, professione, salute e mobilità. I totali storici restano scenari C/E finché la ricerca non li chiude.

## Ambito

Popolazione residente, presente temporanea, viaggiatori e bacino regionale N3–N5.

## Assi minimi

Età/range, sesso, status giuridico, cittadinanza/origine, lingua, household, attività, luogo, salute/capacità e mobilità. Le correlazioni sono esplicite: campionare ogni asse indipendentemente produrrebbe persone impossibili.

## Stock e flussi

Stock per zona/coorte; flussi di nascita, morte, arrivo, partenza, cambio status, household e attività. Ogni flusso conserva massa e genera milestone quando individualizzato.

## Individualizzazione

Coorte → selezione condizionata → sottrazione atomica → Person ID → household/lavoro/luogo coerenti → storia sintetica C/D → persistenza. Non creare parenti, case o lavori senza capacità disponibile.

## De-individualizzazione

Solo per NPC eleggibili secondo N3→N4. Restituisce attributi alla coorte e conserva ledger biografico/tombstone. Vietata per persone salienti.

## Demografia dinamica

Nascite e morti derivano da modelli storici revisionati, salute e contesto, non da tassi moderni. Migrazione risponde a lavoro, rischio, reti e autorità. La demo breve può usare tassi bassi ma deve supportare gli eventi reali.

## Casi limite

Coorte senza capacità abitativa, household senza adulti, saldo negativo, individualizzazione ripetuta, migrazione durante evento, catastrofe, popolazione fluttuante da giochi.

## Persistenza e performance

Persistono stock, distribuzioni con versione, flussi in corso, individui e seed. Aggiornamenti vettoriali N4/N5; riconciliazione periodica con capacità urbane ed economia.

## Test

Conservazione massa, correlazioni, 100 anni accelerati, catastrofe, migrazione, N4→N3→N4, household capacity, confronto scenari demografici.

## Dipendenze

- [Livelli](simulation-levels.md)
- [Lifecycle](npc-lifecycle.md)
- [Mondo](../../03-world/settlements/settlement-framework.md)
- [Ricerca Pompei](../../02-historical-foundation/pompeii-research-plan.md)

## Collegamenti agli altri documenti

- [Demo population](../../07-pompeii-demo/demo-population.md)
- [Generazione](npc-generation.md)
- [Economia](../economy.md)

## Criteri di accettazione

Massa conservata, correlazioni documentate, capacità rispettate, individualizzazione atomica e nessun totale storico presentato come A senza fonte.

## Definition of Done

Scenari demografici, distribuzioni, tassi, test longitudinali e budget approvati.

## Decisioni ancora aperte

- Q-102 e HV-003: popolazione e livelli della demo.

## TODO

- Commissionare dossier demografico e definire tre scenari.
