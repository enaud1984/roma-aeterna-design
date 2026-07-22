# Punti di interazione NPC

`BuildingInteractionPoint` descrive identificativo, tipo, posizione, orientamento, piano, capacità, tag, zona associata, accessibilità e ruolo previsto.

Tipi minimi: `Entrance`, `Exit`, `WorkerPosition`, `CustomerPosition`, `QueuePosition`, `VendorPosition`, `ServicePosition`, `StoragePosition`, `WorshipPosition`, `SeatingPosition`, `AnimalPathPoint`, `RestrictedPosition`, `InteractionPosition`.

Tag supportati includono `npc_workstation`, `npc_customer_position`, `npc_queue_position`, `npc_service_route` e `npc_animal_route`.


## Prompt 23 — Tessuto residenziale, commerciale e misto

Aggiunti sedici archetipi ordinari (DomusMedia, PeristyleDomus, RichDomus, PopularHouse, Insula, Cenaculum, MixedUseHouse, Taberna, Popina, Caupona, Bookshop, Brothel, MedicalShop, BarberShop, MensaArgentaria, Stabulum), profili RomanBuildingUrbanProfile, pesi GetRecommendedUrbanComposition e stati CORE_CPP_DEBUG_TESTS_PASSED, CORE_CPP_RELEASE_TESTS_PASSED, CORE_CPP_SANITIZERS_PASSED, RESIDENTIAL_COMMERCIAL_STATIC_CHECKS_PASSED, UNREAL_BUILD_REQUIRED, UNREAL_AUTOMATION_REQUIRED, MANUAL_VERIFICATION_REQUIRED, FAB_ASSET_IMPORT_NOT_STARTED. Le ricostruzioni ordinarie sono HISTORICAL_APPROXIMATION e usano placeholder, senza .uasset/.umap.
