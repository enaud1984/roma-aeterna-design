# Lavoro e capacità produttiva

## Scopo

Definire l'allocazione credibile di tempo, competenza e forza lavoro tra household, imprese, servizi, obblighi e riposo.

## Descrizione

Il lavoro non è una risorsa astratta: è un impegno di persone persistenti con status, salute, relazioni, luogo, strumenti e consenso o coercizione documentati. La capacità produttiva deriva dall'incontro tra lavoratori, input, attrezzature e organizzazione.

## Ambito

Lavoro occasionale, salariato, autonomo, familiare, apprendistato, obblighi, lavoro di persone schiavizzate, assunzione, turni, assenza, incidente e fine rapporto.

## Regole e dati

Ogni `WorkCommitment` registra parti/autorità, attività, luogo, finestra, compenso o obbligo, competenza, strumenti, condizioni, prova e stato. Un NPC non può lavorare in luoghi incompatibili nello stesso intervallo. Output = capacità limitante × tempo effettivo × competenza/qualità × disponibilità input; stanchezza, malattia e rischio riducono capacità senza cancellare l'individuo.

| Forma | Accesso | Contropartita/autorità | Rischi |
|---|---|---|---|
| Occasionale/salariata | accordo e domanda | paga, vitto o combinazione | disoccupazione, mora, incidente |
| Autonoma/bottega | strumenti, spazio, clienti | ricavo e rischio propri | scorte, debito, responsabilità |
| Household | appartenenza e autorità domestica | risorse condivise | lavoro invisibile, conflitto |
| Apprendistato | maestro, accordo/rete | istruzione, servizio, eventuale paga | abuso, interruzione, accesso |
| Schiavitù | regime coercitivo/status | autorità imposta; eventuali pratiche economiche solo se attestate | violenza, fuga, trauma, separazione |

## Stati e flussi

`Disponibile → Impegnato → In viaggio → Al lavoro → Completato/Pagato`; alternative: assente, sospeso, infortunato, controverso, terminato. Pianificazione verifica routine e bisogni; check-in riserva capacità; produzione consuma input; verifica produce output/scarti; compenso e reputazione seguono prova di prestazione.

## Eventi, errori e persistenza

Produce `WorkerAssigned`, `ShiftStarted`, `WorkInterrupted`, `OutputCompleted`, `CompensationDue`, `WorkEnded`; ascolta malattia, morte, incendio, ordine, calendario, contratto e status. Doppio turno, luogo chiuso, strumenti mancanti, datore insolvente, persona morta o output duplicato sospendono e riconciliano. Persistono impegni, presenze, output, compensi, incidenti e storico competenze.

## Prestazioni e bilanciamento

N0/N1 risolve azioni; N2 turni; N3/N4 capacità e assenze aggregate; N5 tassi demografici. Player, dipendenti, controversie e incidenti rimangono individuali. Nessun bonus nascosto sostituisce input o tempo; il ritmo evita sia profitto senza attività sia animazioni ripetitive obbligatorie.

## Dipendenze

- [Contratti](contracts.md)
- [Salari](wages.md)
- [Produzione](production.md)
- [Carriere](../professions-education/career-framework.md)

## Collegamenti agli altri documenti

- [NPC](../npc-population-ai/npc-model.md)
- [Salute](../health-medicine/health-system.md)
- [Schiavitù](../family-social/slavery.md)

## Test e criteri di completamento

Testare sovrapposizioni, assenza, infortunio, paga, coercizione, time-skip, morte, aggregazione e save/load. Completato quando ogni output P0 ha lavoro, tempo, input, capacità e responsabilità tracciabili.

## Decisioni ancora aperte

- Calendari, compensi e forme di lavoro valide per professione/status a Pompei.
- Rappresentazione UX di coercizione, negoziazione e rifiuto.

## TODO

- Collegare schede P0 a luoghi, turni e fonti.
- Definire test di carico su impegni cittadini.
