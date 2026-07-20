# Simulazione della vita degli NPC

**ID:** SIM-NPC-001
**Stato:** Draft

## Definizione di “vita completa”

Non significa simulare ogni gesto. Significa che ogni NPC persistente possiede continuità sufficiente per spiegare dove vive, come ottiene sostentamento, quali obblighi mantiene, chi conosce, cosa vuole nel breve periodo e come cambia nel tempo.

## Modello dell'agente

- identità: nome, età, origine, lingua, tratti contestuali;
- status: libertà, cittadinanza, genere giuridicamente rilevante, famiglia, dipendenze;
- corpo: salute, capacità, bisogni e rischio;
- competenze e ruoli: pratica, mestiere, autorità;
- risorse: accesso a denaro, beni, alloggio e strumenti;
- relazioni: parentela, patronato, proprietà, debito, affetto, fiducia, conflitto;
- conoscenza: fatti appresi, fonti, confidenza, memoria;
- impegni: orari, promesse, contratti, riti, scadenze;
- obiettivi: bisogni urgenti, progetti e preferenze.

## Processo decisionale

Gli NPC filtrano azioni legalmente e materialmente possibili, valutano urgenza, costo, rischio, norma sociale, relazione e informazione disponibile, poi assumono un impegno. Non leggono stato globale. Personalità modula priorità, non sostituisce condizioni.

## Routine adattiva

La routine è un piano con alternative: se manca un input, un lavoratore può cercare il responsabile, acquistare altrove, attendere, contrarre debito o cambiare attività. Le alternative dipendono da status e rete. Un fallback generico non deve cancellare differenze sociali.

## Ciclo di vita

Nascita, formazione, lavoro, unioni, dipendenza, malattia, mobilità, cambi status e morte influenzano reti e proprietà. L'estensione temporale effettivamente giocabile è TBD; il modello non deve precluderla.

## Memoria e relazioni

Gli eventi diventano ricordi con soggetto, valenza, intensità, fonte e decadimento. Le relazioni sono multidimensionali: fiducia commerciale non implica affetto o lealtà politica. Voci e testimonianze possono essere false senza alterare il fatto sottostante.

## NPC storici e sintetici

I personaggi attestati hanno una scheda di provenienza; le lacune biografiche non vengono presentate come fatti. Gli NPC sintetici devono rispettare distribuzioni e contesti, evitando nomi o ruoli assemblati casualmente senza vincoli.

## Criteri di accettazione

- Un NPC può essere seguito per più giorni e le sue azioni risultano motivate.
- La rimozione di lavoro, casa o relazione produce adattamento, non stallo silenzioso.
- Due NPC con condizioni diverse reagiscono diversamente allo stesso shock.
- L'assenza del giocatore non arresta progressi e conflitti.
- Il debug espone la catena decisionale.

Collegamenti: [status](social-status-and-law.md), [economia](economy.md), [contenuti](../06-content/content-framework.md), [popolazione demo](../07-pompeii-demo/demo-population.md).

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
