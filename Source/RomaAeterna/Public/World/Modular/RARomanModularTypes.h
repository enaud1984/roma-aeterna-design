#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "RARomanModularTypes.generated.h"

UENUM(BlueprintType)
enum class ERARomanBuildingType : uint8 { SimpleHouse UMETA(DisplayName="Casa semplice"), Taberna UMETA(DisplayName="Taberna"), Domus UMETA(DisplayName="Domus"), Insula UMETA(DisplayName="Insula"), Temple UMETA(DisplayName="Tempio"), Basilica UMETA(DisplayName="Basilica"), Portico UMETA(DisplayName="Portico"), AdministrativeBuilding UMETA(DisplayName="Edificio amministrativo"), StreetSection UMETA(DisplayName="Tratto di strada"), Plaza UMETA(DisplayName="Piazza"), ForumSection UMETA(DisplayName="Sezione di foro") };
UENUM(BlueprintType)
enum class ERARomanWallType : uint8 { Plaster UMETA(DisplayName="Intonaco"), Stone UMETA(DisplayName="Pietra"), Brick UMETA(DisplayName="Mattone"), OpusReticulatum UMETA(DisplayName="Opus reticulatum"), OpusIncertum UMETA(DisplayName="Opus incertum"), OpusLatericium UMETA(DisplayName="Opus latericium"), OpusMixtum UMETA(DisplayName="Opus mixtum") };
UENUM(BlueprintType)
enum class ERARomanRoofType : uint8 { Flat UMETA(DisplayName="Piano"), SingleSlope UMETA(DisplayName="Faldata singola"), DoubleSlope UMETA(DisplayName="Doppia falda"), Portico UMETA(DisplayName="Portico"), Compluvium UMETA(DisplayName="Compluvium"), Monumental UMETA(DisplayName="Monumentale") };
UENUM(BlueprintType)
enum class ERARomanArchitecturalOrder : uint8 { None UMETA(DisplayName="Nessuno"), Tuscan UMETA(DisplayName="Toscano"), Doric UMETA(DisplayName="Dorico"), Ionic UMETA(DisplayName="Ionico"), Corinthian UMETA(DisplayName="Corinzio"), Composite UMETA(DisplayName="Composito") };
UENUM(BlueprintType)
enum class ERARomanModuleCategory : uint8 { Wall, Door, Window, Corner, Column, Capital, Base, Arch, Beam, Floor, Roof, Stair, Podium, Portico, Prop, Vegetation, Decoration };
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
};
