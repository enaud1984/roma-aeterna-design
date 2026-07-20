# Modello del mondo

**ID:** WRL-001
**Stato:** Draft

## Premessa

Il mondo è una rete gerarchica di luoghi, agenti, istituzioni, risorse e relazioni nel tempo. La stessa entità può essere simulata a diversa risoluzione, ma conserva identità, proprietà e obblighi essenziali.

## Gerarchia spaziale

Impero → provincia → territorio/civitas → città/insediamento → regio/quartiere → insula → proprietà → spazio → punto funzionale. Ogni livello espone capacità e vincoli: fiscalità provinciale, mercato cittadino, accessibilità stradale, capacità di un laboratorio.

## Strati

- **Fisico:** terreno, edifici, porte, acqua, oggetti, trasporto.
- **Amministrativo:** confini, giurisdizioni, proprietà, tassazione.
- **Economico:** mercati, capacità, scorte, rotte, credito.
- **Sociale:** famiglie, patronato, collegia, reputazioni.
- **Rituale:** santuari, calendari, autorità e comunità.
- **Informativo:** visibilità, messaggi, voci, archivi, conoscenza.

## Invarianti

Un agente ha una sola posizione logica alla volta; un bene non può essere consumato due volte; un diritto di accesso ha origine; i trasferimenti di proprietà lasciano traccia al livello richiesto; il tempo non retrocede; l'aggregazione non crea esiti impossibili rispetto ai vincoli locali.

## Confini della simulazione

“Fuori mappa” non significa inesistente. Regioni non esplorabili producono flussi aggregati, notizie, persone e shock. Quando una regione diventa giocabile, lo stato aggregato deve poter essere raffinato senza riscrivere la storia già osservata.

## Espansione

Pompei è una specializzazione del modello, non il suo schema universale. Regole locali, provinciali e temporali sono pacchetti dichiarativi concettualmente separati dai sistemi comuni. Vedere [living city](living-city.md), [tempo](time-and-persistence.md), [architettura simulazione](../04-simulation/simulation-architecture.md).

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
