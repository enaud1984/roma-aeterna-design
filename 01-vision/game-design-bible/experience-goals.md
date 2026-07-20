# Obiettivi di esperienza

**ID:** VIS-GDB-003
**Stato:** Approved — Baseline 1.0
**Owner:** Game Director / UX Director

## Scopo

Definire ciò che il giocatore deve percepire, comprendere e raccontare a diverse scale temporali.

## Descrizione

Dieci obiettivi osservabili collegano intenzione creativa, ritmo, ricerca utente e segnali di fallimento.

## Ambito

Copre risultati esperienziali trasversali; metriche e protocolli definitivi saranno specificati in UX e testing.

## Obiettivi

| ID | Obiettivo | Segnale positivo | Anti-segnale |
|---|---|---|---|
| EG-01 | Appartenenza situata | parla di casa, lavoro e persone | si sente turista onnipotente |
| EG-02 | Curiosità materiale | osserva processi e flussi | vede ambienti come fondali |
| EG-03 | Agency sotto vincolo | formula piani e compromessi | cerca la soluzione “del designer” |
| EG-04 | Conseguenza leggibile | collega eventi e decisioni | attribuisce esiti al caso |
| EG-05 | Mondo autonomo | racconta cambiamenti non causati da sé | crede che tutto lo aspetti |
| EG-06 | Relazioni significative | ricorda obblighi e fiducia contestuale | considera NPC menu |
| EG-07 | Ambizione non lineare | definisce il proprio successo | cerca soltanto livelli |
| EG-08 | Comprensione storica vissuta | comprende istituzioni tramite esperienza | memorizza trivia senza contesto |
| EG-09 | Tensione senza attrito gratuito | valuta rischio e tempo | percepisce punizione arbitraria |
| EG-10 | Riflessione etica non prescrittiva | riconosce costi e prospettive | riceve punteggio morale universale |

## Ritmo

~~~mermaid
flowchart LR
    O["Osservare"] --> P["Formare un progetto"]
    P --> A["Agire"]
    A --> F["Ricevere feedback"]
    F --> R["Riflettere e adattare"]
    R --> O
~~~

Il ritmo alterna routine, progetto, perturbazione e recovery. L'intensità non deve crescere continuamente; periodi ordinari rendono significativi feste, crisi e svolte biografiche.

## Flussi principali

- **Primo incontro:** orientamento attraverso casa, relazione e obbligo.
- **Prima settimana:** apprendimento di ritmi, accessi e bisogni.
- **Medio periodo:** progetto professionale/sociale con rischi.
- **Ritorno dopo assenza:** ricostruzione dei cambiamenti tramite fonti.
- **Fallimento:** comprensione della perdita e individuazione di nuove possibilità.

## Flussi alternativi

Giocatori orientati all'esplorazione, economia, relazioni, politica, religione o rischio fisico devono convergere sugli stessi obiettivi di causalità e appartenenza, non sullo stesso contenuto.

## Considerazioni progettuali

Friction e convenienza sono strumenti, non valori assoluti. Una routine può essere automatizzata dopo che il giocatore l'ha compresa. Il recap riduce carico cognitivo senza rivelare informazioni segrete.

## Dati necessari

Tempo per comprendere un vincolo; fonti consultate; cause correttamente identificate; diversità dei percorsi; eventi ricordati; tasso di recupero dal fallimento; percezione di agency e autonomia.

## Esempio

Dopo dieci giorni, un tester dovrebbe descrivere “ho chiesto credito al vicino perché il panificio non pagava” invece di “ho completato la quest 12”.

## Casi limite

- L'accuratezza non giustifica noia obbligatoria.
- La comodità non può annullare tempo, costo e logistica.
- Un evento raro perde valore se orchestrato per ogni player.
- Il mistero è accettabile; l'assenza di segnali causali no.

## Dipendenze

- [Promessa](player-promise.md)
- [Gameplay](../../05-player/gameplay/README.md)
- [UX](../../08-ux/user-experience/README.md)

## Collegamenti agli altri documenti

- [Narrazione emergente](../../06-content/narrative/emergent-narrative.md)
- [Onboarding](../../08-ux/user-experience/onboarding.md)
- [User research](../../08-ux/user-experience/user-research.md)

## Decisioni ancora aperte

Durata target della demo; profilo del pubblico; intensità e frequenza delle crisi; strumenti finali di ricerca utente.

## Rischi

Routine percepita come lavoro ripetitivo; causalità troppo profonda; tutorial intrusivo; eventi che sovraccaricano l'attenzione.

## Criteri di completamento

Ogni obiettivo ha segnale, anti-segnale e metodo di osservazione; la demo copre tutti gli EG almeno una volta.

## TODO

- Definire questionario e protocollo osservativo.
- Collegare EG a milestone e scenari.
