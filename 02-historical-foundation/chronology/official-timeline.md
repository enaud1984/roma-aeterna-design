# Cronologia ufficiale del progetto

## Scopo

Definire le finestre temporali canoniche e impedire la sovrapposizione inconsapevole di istituzioni, oggetti e personaggi appartenenti a epoche diverse.

## Descrizione

La cronologia distingue contesto storico, finestra della demo e futuro simulato. La baseline di pianificazione inizia il 1 luglio 77 d.C.; il giorno è licenza D e richiede review dello snapshot P0.

## Ambito

Pompei e Campania con il minimo contesto romano necessario; l'espansione imperiale richiederà timeline regionali.

## Timeline verificata e condizionale

| Data/finestra | Evento | Area | Classe | Fonti/base | Uso progettuale |
|---|---|---|---:|---|---|
| 80 a.C. | deduzione della colonia sillana a Pompei | Pompei | A/B | epigrafia e sintesi Cooley/Zanker | stratificazione civica; non identità uniforme |
| 27 a.C.–14 d.C. | principato di Augusto | Impero/Italia | A | fonti storiche, epigrafia, numismatica | contesto istituzionale, non data demo |
| 14–37 | Tiberio | Impero | A | fonti storiche/numismatiche | cronologia imperiale |
| 37–41 | Caligola | Impero | A | fonti storiche/numismatiche | cronologia imperiale |
| 41–54 | Claudio | Impero | A | fonti storiche/numismatiche | cittadinanza/amministrazione da contestualizzare |
| 54–68 | Nerone | Impero | A | fonti storiche/numismatiche | periodo del terremoto campano |
| 62/63 | terremoto campano con gravi danni a Pompei | Campania | A evento / E anno esatto | Tacito; Seneca; archeologia | edifici in riparazione per scheda, non globalmente |
| 68–69 | guerra civile e quattro imperatori | Impero | A | fonti storiche/numismatiche | effetti locali da dimostrare, non assumere |
| 69–79 | principato di Vespasiano | Impero | A | fonti storiche/numismatiche | finestra candidata per la demo |
| 1 luglio 77 | inizio della demo | Pompei | D | ADR-0022; convenzione progettuale | ancora temporale di sistemi e contenuti |
| 23 giugno 79 | morte di Vespasiano; successione di Tito | Impero | A/B | fonti letterarie/numismatiche | dipende dalla data iniziale scelta |
| dopo 17 ottobre 79 | *terminus post quem* suggerito dal graffito a carboncino per l'eruzione | Pompei | A per iscrizione / B per inferenza | scavo Regio V | non equivale da solo al 24 ottobre |
| autunno 79, giorno aperto | eruzione distruttiva del Vesuvio | area vesuviana | A anno/evento; E giorno | Plinio, depositi, studi moderni | fuori scope demo; controversia preservata per futuro |
| 81 | morte di Tito e successione di Domiziano | Impero | A | fonti storiche/numismatiche | fuori dall'orizzonte salvo sopravvivenza controfattuale |
| 212 | Constitutio Antoniniana | ampie parti dell'Impero | A, dettagli discussi | P. Giss. 40; Cassio Dione | barriera: non retrodatare cittadinanza generalizzata |
| VI sec. | compilazione giustinianea | Impero orientale | A | Corpus Iuris Civilis | barriera: fonte tarda, non prassi diretta del 79 |

## Canone della demo

- **Data iniziale:** 1 luglio 77 d.C., D, ADR-0022.
- **Stagione:** estate, derivata dalla convenzione; condizioni locali da dossier.
- **Eruzione nell'orizzonte giocabile:** esclusa per la demo.
- **Imperatore:** coerente con il principato di Vespasiano; funzionari locali nominati restano da dossier.
- **Stato degli edifici:** deve essere una fotografia per data e fase, non il palinsesto complessivo degli scavi.

## Regole controfattuali

Dopo l'inizio della simulazione, eventi generati possono divergere solo dove il progetto lo autorizza. Un controfattuale non riscrive retroattivamente fonti, tecnologie o istituzioni; conserva un ledger di divergenza.

## Criteri di accettazione

Ogni evento ha area e classe; nessun documento assume una data demo diversa; le fonti tarde sono etichettate; gli asset dipendenti dalla fase hanno snapshot.

## Definition of Done

ADR della data approvata, timeline locale dettagliata, sincronizzazione con calendario, personaggi, edifici e fonti completata.

## Dipendenze

- [Timeline Pompei](pompeii-timeline.md)
- [Timeline imperiale](imperial-timeline.md)
- [Registro claim](../sources/historical-claims-register.md)

## Collegamenti agli altri documenti

- [Controversie](../sources/controversies-register.md)
- [Data della demo](../../07-pompeii-demo/design/historical-date.md)
- [Tempo](../../03-world/time-and-persistence.md)

## Decisioni ancora aperte

- Snapshot di istituzioni, calendario, edifici e persone al 1 luglio 77.
- Edizione critica adottata per la data pliniana.

## TODO

- Registrare HV-001/002 come risolti per la milestone demo, preservando la controversia storica dell'eruzione.
- Aggiungere timeline edilizie degli spazi selezionati.
