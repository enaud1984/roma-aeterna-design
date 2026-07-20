# Proprietà, possesso e uso

## Scopo

Definire diritti economici persistenti su immobili, imprese e beni distinguendoli dalla mera detenzione fisica.

## Descrizione

Il sistema registra proprietario, possessore, custode, utilizzatore, quote, vincoli e titolo. Tale separazione permette affitto, deposito, pegno, furto, eredità, comproprietà e gestione per conto altrui.

## Ambito

Beni mobili, terreni, edifici, botteghe, attrezzature, carichi e quote d'impresa. Le persone schiavizzate sono NPC persistenti soggetti a un regime giuridico coercitivo documentato in [Schiavitù](../family-social/slavery.md), non oggetti inventariali.

## Regole e dati

- Ogni diritto ha soggetto, oggetto, tipo, quota, origine, validità, foro e vincoli.
- Un passaggio di proprietà richiede titolo valido, capacità e trasferimento registrato.
- Possesso e proprietà possono divergere; il furto cambia custodia/possesso illecito, non titolo.
- Affitto concede uso temporaneo e obblighi, non proprietà.
- Eredità, confisca e decisione giudiziaria usano transazioni esplicite.
- Un bene vincolato o già venduto non può essere trasferito senza risolvere il conflitto.

| Stato del diritto | Significato |
|---|---|
| Proposto | trasferimento non ancora efficace |
| Attivo | diritto esercitabile |
| Vincolato | pegno, lite, sequestro o condizione |
| Contestato | titoli incompatibili o denuncia |
| Trasferito | chiuso con successore noto |
| Estinto | oggetto distrutto o diritto terminato |

## Flussi

Compravendita: verifica titolo → accordo → pagamento e consegna atomici → nuovo titolo → tasse/eventi. Locazione: verifica disponibilità → contratto → uso e canone → rinnovo, restituzione o lite. Eredità: morte → massa ereditaria → debiti/legati → decisione → trasferimenti tracciati.

## Input, output ed eventi

Legge input da identità/status, contratti, inventario, catasto locale, edifici e successione. Produce `RightCreated`, `PossessionChanged`, `PropertyTransferred`, `LeaseExpired`, `RightDisputed`; ascolta distruzione, morte, furto, pagamento, sentenza ed emancipazione.

## Casi limite, prestazioni e persistenza

Quote che non sommano, proprietario inesistente, doppio titolo, edificio distrutto, carico perduto e time-skip con affitto scaduto generano quarantena dati. Vicino al giocatore i beni materiali restano lotti; lontano si aggregano quantità ma non diritti unici, proprietà del giocatore o controversie. Save/load conserva catena del titolo, quote, vincoli, uso e custodia.

## Dipendenze

- [Contratti](contracts.md)
- [Inventario](../../05-player/items/inventory.md)
- [Edifici](../../03-world/structures/README.md)
- [Eredità](../family-social/inheritance.md)

## Collegamenti agli altri documenti

- [Credito e debiti](credit-and-debt.md)
- [Criminalità](../politics-law/criminality.md)
- [Modello dati](../../10-technical/data-model.md)

## Strategie di test e criteri di completamento

Testare vendita, locazione, quote, pegno, furto, distruzione, successione e doppia transazione. Completato quando ogni bene rilevante ha custodia e diritti coerenti, e nessun flusso duplica valore.

## Decisioni ancora aperte

- Granularità del catasto giocabile di Pompei.
- Diritti e limiti per ciascuno status disponibile nella demo.

## TODO

- Collegare planimetrie e identificativi degli immobili della vertical slice.
- Validare terminologia giuridica con l'audit storico.
