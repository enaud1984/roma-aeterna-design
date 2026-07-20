# Fonti ufficiali per GitHub e Git LFS

**ID:** TECH-PIPELINE-SOURCES
**Stato:** Verificato il 2026-07-20

## Scopo

Separare le capacità documentate della piattaforma dalle policy progettuali proposte per *Roma Aeterna*.

## Descrizione

Registro minimo di fonti primarie operative consultate per branch protection, status check e asset pesanti. Non sostituisce la documentazione ufficiale né congela limiti commerciali o funzionalità future.

## Ambito

GitHub repository governance e Git Large File Storage. Le decisioni interne restano nella [pipeline](pipeline-overview.md).

## Fonti verificate

| Tema | Fonte ufficiale | Uso nella specifica |
|---|---|---|
| Gestione file grandi | [Managing large files](https://docs.github.com/en/repositories/working-with-files/managing-large-files) | distinguere Git, release artifact e LFS |
| Modello Git LFS | [About Git Large File Storage](https://docs.github.com/en/repositories/working-with-files/managing-large-files/about-git-large-file-storage) | pointer nel repository e oggetto esterno |
| Configurazione LFS | [Configuring Git Large File Storage](https://docs.github.com/en/repositories/working-with-files/managing-large-files/configuring-git-large-file-storage?platform=windows) | `.gitattributes` e tracking condiviso |
| Collaborazione LFS | [Collaboration with Git Large File Storage](https://docs.github.com/en/repositories/working-with-files/managing-large-files/collaboration-with-git-large-file-storage) | requisiti per contributor e distribuzione |
| Status check | [About status checks](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/collaborating-on-repositories-with-code-quality-features/about-status-checks) | gate automatici delle PR |
| Branch protetti | [About protected branches](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches) | review e check prima del merge |
| Regole di protezione | [Managing a branch protection rule](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/managing-a-branch-protection-rule) | configurazione amministrativa futura |

## Regole d'uso

- Ricontrollare le fonti prima di configurare repository, quote, runner o piani.
- Non copiare limiti numerici senza data, piano e contesto.
- Trattare branch protection e LFS come capacità da configurare, non come garanzie già attive.
- Registrare in ADR ogni deviazione dalla pipeline proposta.

## Dipendenze

- [Pipeline](pipeline-overview.md)
- [Gestione asset](asset-management.md)
- [Sicurezza](../security/README.md)

## Collegamenti agli altri documenti

- [Git e CI](../../11-production/devops/README.md)
- [Registro decisioni](../../00-governance/decision-log.md)

## Decisioni ancora aperte

- Piano GitHub, quote LFS e funzionalità effettivamente disponibili al team.
- Necessità del file locking per categorie non mergeabili.

## TODO

- Riesaminare alla configurazione del repository di produzione.
- Registrare data e responsabile della prossima verifica.
