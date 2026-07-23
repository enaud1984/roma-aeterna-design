# Risoluzione runtime dei materiali romani

Il runtime risolve materiali tramite soft object path del catalogo locale e conserva il fallback tecnico quando una superficie non ha una controparte coerente. La cache include categoria, archetipo, ricchezza, usura, distretto e seed; viene invalidata al caricamento del catalogo, con F5 e a ogni cambio F7.

La causa delle superfici grigie osservate dopo il Prompt 29 non era un path errato: i parent material locali e decorativi non dichiaravano l’uso `InstancedStaticMeshes`. In PIE Unreal sostituiva quindi Material Instance valide con `WorldGridMaterial`. Gli script di generazione impostano ora `used_with_instanced_static_meshes`, ricompilano e salvano i parent; il runtime verifica inoltre `MATUSAGE_InstancedStaticMeshes` prima dell’assegnazione.

Le statistiche distinguono cache hit/miss, risoluzioni locali, invalidazioni, path irrisolti e binding locali/fallback effettivi. Il criterio visuale è almeno 25 binding locali. I fallback delle categorie utility senza materiale Batch 1 restano ammessi e non vengono mascherati con materiali storicamente incompatibili.

F7 ricostruisce tutti gli ISMC e aggiorna anche strada, marciapiedi, terreno e vegetazione tecnica. I messaggi temporanei sono `F7 LOCAL MATERIALS ACTIVE` e `F7 FALLBACK MATERIALS ACTIVE`.
