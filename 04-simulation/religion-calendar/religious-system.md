# Sistema religioso vivo

## Scopo

Simulare pratiche, comunità, calendari, autorità e interpretazioni religiose intrecciate alla vita domestica, civica, economica e politica.

## Descrizione

La religione non è una barra di fede né magia. Il sistema registra ciò che persone e comunità credono, praticano, osservano e interpretano; non certifica causalità soprannaturale. Appartenenze e pratiche possono sovrapporsi senza classi religiose esclusive.

## Ambito

Religione domestica e pubblica, templi, sacerdoti, sacrifici, voti, feste, auspici/divinazione, collegia, culto imperiale, misteri e culti d'origine orientale quando attestati, ebraismo, prime comunità cristiane solo se coerenti, superstizioni, sincretismo, conflitti e funerali.

## Modello dati

| Entità | Dati minimi |
|---|---|
| `Tradition/Community` | nome contestuale, area, periodo, pratiche, autorità, appartenenze |
| `SacredPlace` | titolarità/custodia, accessi, culti, calendario e risorse |
| `RitualDefinition/Occurrence` | occasione, officiante, partecipanti, sequenza, offerte, regole e prove |
| `Vow/Dedication` | soggetto, promessa, condizione creduta, adempimento, memoria |
| `SignInterpretation` | fenomeno osservato, conoscenza, interprete, lettura e destinatari |
| `ReligiousStanding` | valutazioni locali di pietas, correttezza o trasgressione; non verità divina |

## Domini

- **Domestico:** pratiche dell'household, antenati/Lares e riti di passaggio secondo fonti; varia per casa e status.
- **Pubblico:** calendario civico, processioni, sacrifici, feste, giochi, spesa e legittimazione.
- **Templi/sacerdoti:** luoghi, personale, incarichi, risorse e accessi con competenze specifiche.
- **Collegia:** associazioni con dimensioni cultuali/sociali/professionali quando attestate; non chiese moderne.
- **Pluralità:** misteri, Iside e altri culti, culto imperiale, comunità ebraiche/cristiane solo con dossier locale-temporale; niente checklist imperiale universale.
- **Pratiche informali:** amuleti, maledizioni, guarigione, divinazione e “superstizione” rappresentate con terminologia prospettica, non giudizio neutro moderno.

## Ciclo rituale

```mermaid
flowchart LR
    A[Calendario, voto, crisi o bisogno] --> B[Conoscenza e autorità]
    B --> C[Preparazione: luogo, beni, partecipanti]
    C --> D[Pratica osservabile]
    D --> E[Testimoni e memoria]
    E --> F[Interpretazioni divergenti]
    F --> G[Effetti sociali, politici, economici e personali]
```

## Regole e conseguenze

- Un rito consuma tempo/risorse e coordina persone; non concede buff soprannaturali certificati.
- Correttezza dipende da tradizione, officiante, osservatori e informazione.
- Auspicio/segno conserva fenomeno materiale e interpretazioni separate.
- Feste modificano lavoro, domanda, mobilità, folla, politica e sicurezza con frequenza da calendario.
- Conflitto religioso nasce da interessi, autorità, spazio, reputazione e decisioni; non da “odio” casuale.
- Sincretismo è relazione storica tra pratiche/interpretazioni, non fusione automatica di alberi abilità.

## Frequenza ed eventi

Pratiche domestiche possono essere frequenti; feste civiche seguono calendario; grandi prodigi, repressioni o conflitti sono rari e condizionati. Produce `RitualScheduled/Performed`, `VowMade/Fulfilled`, `SignInterpreted`, `FestivalStarted`, `ReligiousDisputeOpened`; ascolta tempo, morte, nascita, carica, crisi, guerra, malattia, mercato e direttiva.

## Casi limite, aggregazione e persistenza

Officiante assente, risorse mancanti, rito interrotto, calendari sovrapposti, luogo chiuso, interpretazioni opposte, persona multi-appartenente e comunità non attestata richiedono fallback o esclusione. Riti P0 sono individuali; lontano si aggregano partecipazione e domanda preservando voti, cariche, controversie e memorie. Save/load conserva occorrenze, promesse, interpretazioni e conseguenze.

## Accuratezza e rischi

Ogni culto/comunità ha periodo, area, fonti e livello A–E. Evitare “religione romana” uniforme, monoteismo/politeismo come UI esaustiva, sacerdoti equivalenti a clero moderno, cristiani onnipresenti e culti “orientali” esotizzati. Review storica, religiosa, linguistica ed etica obbligatoria.

## Dipendenze

- [Calendario](calendar.md)
- [Religione domestica](domestic-religion.md)
- [Religione pubblica](public-religion.md)
- [Culti](cults.md)
- [Diversità religiosa](religious-diversity.md)

## Collegamenti agli altri documenti

- [Templi](temples.md)
- [Sacerdoti](priests.md)
- [Rituali e sacrifici](rituals-sacrifices.md)
- [Politica](../politics-law/political-system.md)
- [Economia](../economy-production/economic-model.md)

## Test e Definition of Done

Testare rito domestico/pubblico, voto, festa, auspicio divergente, multi-appartenenza, conflitto, aggregazione e save/load. S4 quando calendario e culti P0 di Pompei sono validati, effetti cross-system spiegabili e nessuna causalità divina viene certificata.

## Decisioni ancora aperte

- Culti, comunità, sacerdozi e feste P0 per data e area demo.
- Limiti di rappresentazione per ebraismo e prime comunità cristiane sulla base delle evidenze locali.

## TODO

- Creare matrice culto-luogo-calendario-autorità-fonte.
- Allineare tutti i sottodocumenti e scenari P0.
