# IA dei bisogni e capacità

## Scopo

Trasformare fame, sete, sonno, igiene, salute, dolore, sicurezza e appartenenza in pressioni contestuali senza creare barre che comandano ogni azione.

## Descrizione

Un bisogno ha stato fisiologico/sociale, percezione soggettiva, soglie, capacità compromesse, opzioni note e conseguenze. SYS-NEED possiede il valore; SYS-NPC decide la risposta.

## Ambito

Individui N0–N3 e distribuzioni N4/N5. Riproduzione e malattie specifiche sono in lifecycle/salute.

| Bisogno | Driver | Segnali | Conseguenze | Risposte |
|---|---|---|---|---|
| fame | tempo, lavoro, malattia | sensazione, disponibilità cibo | fatica, salute | pasto, acquisto, richiesta, rinvio |
| sete | clima, sforzo, tempo | accesso acqua | incapacità rapida | fontana, riserva, assistenza |
| sonno | veglia, lavoro, stress | stanchezza | errori, rischio | casa, posto autorizzato, micro-riposo |
| igiene | attività, ambiente, cura | disagio/percezione sociale | relazione/salute contestuale | lavaggio, terme, cambio abiti |
| salute/dolore | ferita/malattia | sintomi conosciuti | capacità, paura | cura, riposo, aiuto, ignorare |
| sicurezza | minaccia percepita | paura/rumore/folla | fuga, difesa, panico | riparo, rete, autorità |
| sociale | isolamento/obbligo | desiderio/pressione | umore/reputazione | visita, patronato, culto |

## Stati

Stable → Rising → Pressing → Critical → Incapacitated; soddisfacimento porta a Recovering e poi Stable. Soglie dipendono da persona, attività e salute.

## Regole

- Il bisogno reale non rivela automaticamente la soluzione migliore.
- Risorse, status e accesso limitano le opzioni.
- Un impegno può giustificare rinvio entro tolleranza.
- Più bisogni critici richiedono triage, non oscillazione.
- L'igiene non diventa moralità o stereotipo di classe.
- Bisogni aggregati consumano risorse reali o contabilizzate.

## Livelli e persistenza

N0 integra con precisione necessaria; N1 intervalli; N2 calcola ai checkpoint; N3 usa esposizione e consumo aggregato; N4/N5 distribuzioni. Persistono valore/soglia solo se non ricostruibili in sicurezza; danni e crisi sono eventi hard.

## Casi limite

Nessun luogo sicuro, caregiver assente, digiuno rituale, coercizione, malattia che altera percezione, sonno interrotto, risorsa prenotata ma rubata, transizione di livello durante bisogno critico.

## Test e performance

Curve temporali, caldo/lavoro, scarsità, multi-bisogno, 30 giorni, N0↔N3, consumo conservato, zero polling globale, distribuzioni N4 coerenti.

## Dipendenze

- [Salute](../health-medicine/health-system.md)
- [AI](ai-architecture.md)
- [Economia](../economy.md)
- [Accessi Pompei](../../07-pompeii-demo/design/accessible-buildings.md)

## Collegamenti agli altri documenti

- [Routine](routines.md)
- [Lifecycle](npc-lifecycle.md)
- [Folle](crowds.md)

## Criteri di accettazione

Ogni bisogno ha driver, soglie, capacità, opzioni, livelli e test; nessun bisogno crea risorse; agenti con contesti diversi reagiscono diversamente.

## Definition of Done

Curve, consumi, UI epistemica, aggregazione e test di scarsità approvati.

## Decisioni ancora aperte

- Bisogni attivi nella demo e granularità igiene/sete.
- Curve per età, salute e stagione.

## TODO

- Collegare parametri ai budget economici e sanitari.
