# Report implementazione Prompt 22

Audit: Prompt 21, core C++ standard, adapter Blueprint, actor runtime placeholder, batching con `UInstancedStaticMeshComponent`, validatore statico, test CMake/CTest e documentazione risultano presenti. Rischio principale: duplicare algoritmi core negli adapter Unreal; mitigazione: gli adapter chiamano il core.

Implementati sei archetipi: `AtriumDomus`, `Thermopolium`, `Fullonica`, `Pistrinum`, `PublicLatrine`, `SmallTemple`. Gli altri archetipi richiesti sono registrati come `ARCHETYPE_PLANNED`.

Non sono stati creati `.uasset`, `.umap`, asset Fab o materiali persistenti. Stati richiesti: `BUILDING_ARCHETYPE_STATIC_CHECKS_PASSED`, `UNREAL_BUILD_REQUIRED`, `UNREAL_AUTOMATION_REQUIRED`, `MANUAL_VERIFICATION_REQUIRED`, `FAB_ASSET_IMPORT_NOT_STARTED`.
