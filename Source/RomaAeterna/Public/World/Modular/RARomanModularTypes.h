#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "RARomanModularTypes.generated.h"

UENUM(BlueprintType)
enum class ERARomanBuildingType : uint8 { SimpleHouse, Domus, AtriumDomus, PeristyleDomus, RichDomus, UrbanVilla, SuburbanVilla, Insula, UpperFloorApartment, Taberna, Thermopolium, Popina, Caupona, BakeryShop, MarketStall, Bookshop, ArtisanShop, Warehouse, Horrea, Macellum, Market, Fullonica, Pistrinum, Winery, OilWorkshop, DyeWorkshop, PotteryWorkshop, MetalWorkshop, TextileWorkshop, MillingWorkshop, BakeryProduction, PressingWorkshop, Forum, Basilica, Curia, Comitium, AdministrativeBuilding, PublicLatrine, PublicFountain, BathComplex, Palaestra, Theatre, Odeon, Amphitheatre, Portico, PublicGarden, SmallTemple, Temple, Sanctuary, Shrine, Lararium, Sacellum, ImperialCultBuilding, Brothel, Tavern, Inn, Stable, MedicalShop, BarberShop, School, Library, MonumentalArch, CityGate, CityWall, WatchTower, AqueductSection, StreetSection, Plaza, StatueBase, Monument, FountainMonument, ForumSection };
UENUM(BlueprintType)
enum class ERARomanWallType : uint8 { Plaster UMETA(DisplayName="Intonaco"), Stone UMETA(DisplayName="Pietra"), Brick UMETA(DisplayName="Mattone"), OpusReticulatum UMETA(DisplayName="Opus reticulatum"), OpusIncertum UMETA(DisplayName="Opus incertum"), OpusLatericium UMETA(DisplayName="Opus latericium"), OpusMixtum UMETA(DisplayName="Opus mixtum") };
UENUM(BlueprintType)
enum class ERARomanRoofType : uint8 { Flat UMETA(DisplayName="Piano"), SingleSlope UMETA(DisplayName="Faldata singola"), DoubleSlope UMETA(DisplayName="Doppia falda"), Portico UMETA(DisplayName="Portico"), Compluvium UMETA(DisplayName="Compluvium"), Monumental UMETA(DisplayName="Monumentale") };
UENUM(BlueprintType)
enum class ERARomanArchitecturalOrder : uint8 { None UMETA(DisplayName="Nessuno"), Tuscan UMETA(DisplayName="Toscano"), Doric UMETA(DisplayName="Dorico"), Ionic UMETA(DisplayName="Ionico"), Corinthian UMETA(DisplayName="Corinzio"), Composite UMETA(DisplayName="Composito") };
UENUM(BlueprintType)
enum class ERARomanBuildingFunction : uint8 { Residential, Commercial, Productive, Religious, Civic, Entertainment, Hospitality, Sanitary, Hydraulic, Monumental, MixedUse };
UENUM(BlueprintType)
enum class ERARomanBuildingScale : uint8 { Small, Medium, Large, Monumental };
UENUM(BlueprintType)
enum class ERARomanAccessType : uint8 { StreetAccess, SecondaryAccess, ServiceAccess, CourtyardAccess, MonumentalAccess, ShopfrontAccess, InternalAccess };
UENUM(BlueprintType)
enum class ERARomanZoneFunction : uint8 { Public, Private, Service, Commercial, Productive, Religious, Sanitary, Hydraulic, Circulation, Storage, AnimalWork, OpenSpace };
UENUM(BlueprintType)
enum class ERARomanRoomType : uint8 { Fauces, Vestibulum, Atrium, Impluvium, Ala, Cubiculum, Tablinum, Triclinium, Oecus, Exedra, Culina, DomesticLatrine, Corridor, Stair, Peristyle, Hortus, ServiceRoom, Storage, UpperRoom, Shopfront, CounterArea, DiningArea, KitchenArea, CustomerArea, BackRoom, StreetPortico, CommercialStorage, WorkshopArea, MillingArea, OvenArea, PressArea, WashingArea, DryingArea, DyeingArea, AnimalDriveArea, FurnaceArea, RawMaterialStorage, FinishedGoodsStorage, PreparationArea, Nave, Aisle, Tribunal, CouncilHall, AssemblyArea, BathHall, Apodyterium, Frigidarium, Tepidarium, Calidarium, Laconicum, PalaestraRoom, Auditorium, Cavea, Orchestra, Scaena, Arena, Vomitorium, PublicLatrineHall, Cella, Pronaos, PodiumRoom, AltarArea, SacredCourt, ProcessionalArea, ForumPlaza, MarketCourt, PorticoRoom, FountainCourt, MonumentCourt, Garden, Street, Alley, ServiceYard };
UENUM(BlueprintType)
enum class ERARomanInteractionPointType : uint8 { Entrance, Exit, WorkerPosition, CustomerPosition, QueuePosition, VendorPosition, ServicePosition, StoragePosition, WorshipPosition, SeatingPosition, AnimalPathPoint, RestrictedPosition, InteractionPosition };
UENUM(BlueprintType)
enum class ERARomanModuleCategory : uint8 { Wall, Door, Window, Corner, Column, Capital, Base, Arch, Beam, Floor, Roof, Stair, Podium, Portico, Prop, Vegetation, Decoration, Counter, Dolium, Basin, WaterChannel, Millstone, Oven, Furnace, Workbench, Seat, LatrineSeat, Drain, Altar, Shrine, StatueMarker, AnimalPath, ShopSign, Shelf, StorageContainer, GardenFeature, Fountain, MosaicZone, FrescoZone, DryingRack, WorkPlatform, RotationArm, ServiceBasin, InteractionMarker };
UENUM(BlueprintType)
enum class ERARomanWealthLevel : uint8 { Poor, Modest, Comfortable, Wealthy, Elite, Monumental };
UENUM(BlueprintType)
enum class ERARomanDegradationLevel : uint8 { New, Maintained, Weathered, Damaged, Ruined };

USTRUCT(BlueprintType)
struct ROMAETERNA_API FRARomanModuleDimensions { GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") float WidthCm = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") float DepthCm = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") float HeightCm = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") float GridSizeCm = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FVector PivotOffset = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") float RotationStepDegrees = 90.f;
};
USTRUCT(BlueprintType)
struct ROMAETERNA_API FRARomanModuleDefinition { GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FName ModuleId = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanModuleCategory Category = ERARomanModuleCategory::Wall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FRARomanModuleDimensions Dimensions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TSoftObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TArray<TSoftObjectPtr<UMaterialInterface>> OptionalMaterialOverrides;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TArray<FName> Tags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bSupportsNanite = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bRequiresCollision = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 EstimatedTriangleCost = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FString HistoricalNotes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FName SourceAssetId = NAME_None;
};
USTRUCT(BlueprintType)
struct ROMAETERNA_API FRARomanBuildingParameters { GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanBuildingType BuildingType = ERARomanBuildingType::SimpleHouse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") float WidthCm = 800.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") float DepthCm = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 FloorCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 BayCount = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") float FloorHeightCm = 320.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") float WallThicknessCm = 40.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 DoorCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 WindowCount = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanRoofType RoofType = ERARomanRoofType::DoubleSlope;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanWallType WallType = ERARomanWallType::Plaster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanArchitecturalOrder ArchitecturalOrder = ERARomanArchitecturalOrder::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanWealthLevel WealthLevel = ERARomanWealthLevel::Modest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanDegradationLevel DegradationLevel = ERARomanDegradationLevel::Maintained;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bHasPortico = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bHasCourtyard = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bHasAtrium = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bHasPeristyle = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bGenerateInterior = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 RandomSeed = 1337;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 MaximumModuleCount = 256;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") ERARomanBuildingScale BuildingScale = ERARomanBuildingScale::Medium;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") int32 SocialStatusRank = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") int32 DecorationLevel = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") int32 UrbanDensityLevel = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") bool bHasUpperFloor = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") bool bHasWater = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") bool bHasDrainage = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") bool bHasFireArea = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") bool bHasServiceAccess = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") bool bHasCustomerArea = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") bool bHasProductionArea = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") bool bHasStorage = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular|Archetypes") int32 MaximumRoomCount = 64;
};
USTRUCT(BlueprintType)
struct ROMAETERNA_API FRARomanModulePlacement { GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FName ModuleId = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FTransform Transform = FTransform::Identity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanModuleCategory Category = ERARomanModuleCategory::Wall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 FloorIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 BayIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bMirrored = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TArray<FName> PlacementTags;
};
USTRUCT(BlueprintType)
struct ROMAETERNA_API FRARomanBuildingInteractionPoint { GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FName PointId = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanInteractionPointType Type = ERARomanInteractionPointType::InteractionPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FVector Position = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FRotator Orientation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 FloorIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 Capacity = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TArray<FName> Tags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FName ZoneId = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bAccessible = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FString Role;
};
USTRUCT(BlueprintType)
struct ROMAETERNA_API FRARomanGenerationMessage { GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FName Code = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FString Message;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bIsError = false;
};
USTRUCT(BlueprintType)
struct ROMAETERNA_API FRARomanGenerationResult { GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bSuccess = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TArray<FRARomanModulePlacement> GeneratedPlacements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TArray<FRARomanGenerationMessage> Warnings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TArray<FRARomanGenerationMessage> Errors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 EstimatedModuleCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 EstimatedTriangleBudget = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FBox Bounds = FBox(EForceInit::ForceInit);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 GeneratedRoomCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 GeneratedZoneCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 GeneratedInteractionPointCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 ProductionDeviceCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") int32 WaterFeatureCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TArray<FRARomanBuildingInteractionPoint> InteractionPoints;
};
