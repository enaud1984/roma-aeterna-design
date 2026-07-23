#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "World/Modular/RARomanModularTypes.h"
#include "RARomanVisualCatalog.generated.h"

UENUM(BlueprintType)
enum class ERARomanSurfaceRole : uint8
{
	ExteriorWall, InteriorWall, StructuralBrick, RoadSurface, SecondaryPaving,
	Sidewalk, Kerb, Roof, Timber, Ground, Courtyard, ProductiveFloor,
	ServiceArea, WaterEdge, UtilitySurface
};

UENUM(BlueprintType)
enum class ERARomanWeatheringLevel : uint8
{
	New, Light, Medium, Heavy, Ruined
};

USTRUCT(BlueprintType)
struct ROMAAETERNA_API FRARomanVisualCatalogEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual")
	ERARomanModuleCategory Category = ERARomanModuleCategory::Wall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual")
	TSoftObjectPtr<UMaterialInterface> Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual")
	FName ReplacementAssetId = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FString HistoricalGrade = TEXT("C");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	TArray<FName> DistrictCompatibility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	TArray<ERARomanWealthLevel> WealthTiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	TArray<ERARomanBuildingType> BuildingArchetypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	ERARomanSurfaceRole SurfaceRole = ERARomanSurfaceRole::ExteriorWall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FName MaterialVariant = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	TArray<ERARomanWeatheringLevel> WeatheringLevels;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local", meta=(ClampMin="0.0"))
	float VariationWeight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FVector ScaleCorrection = FVector::OneVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FRotator RotationCorrection = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FVector2D UVScale = FVector2D::UnitVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	float UVRotation = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FLinearColor ColorTint = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local", meta=(ClampMin="0.0"))
	float RoughnessMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local", meta=(ClampMin="0.0"))
	float NormalStrength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local", meta=(ClampMin="0.0"))
	float AOIntensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FName CollisionProfile = TEXT("BlockAll");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	bool bPreferNanite = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	TArray<TSoftObjectPtr<UMaterialInterface>> MaterialOverrides;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	TSoftObjectPtr<UMaterialInterface> FallbackMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FName SourcePackage = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FName LicenseRegistryId = NAME_None;
};

/** Catalogo centralizzato e sostituibile per i placeholder visuali romani. */
UCLASS(BlueprintType)
class ROMAAETERNA_API URARomanVisualCatalog : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual")
	TArray<FRARomanVisualCatalogEntry> Entries;

	bool FindEntry(ERARomanModuleCategory Category, FRARomanVisualCatalogEntry& OutEntry) const;
	bool ResolveEntry(ERARomanModuleCategory Category, ERARomanBuildingType Archetype,
		ERARomanWealthLevel Wealth, ERARomanWeatheringLevel Weathering, FName District,
		int32 Seed, FRARomanVisualCatalogEntry& OutEntry, int32& OutVariantIndex) const;
	int32 CountResolvedCategories() const;
	int32 CountMaterialVariants() const;
	void ClearResolutionCache() const;
	int32 GetCacheHitCount() const { return CacheHitCount; }
	int32 GetCacheMissCount() const { return CacheMissCount; }
	int32 GetLocalResolvedCount() const { return LocalResolvedCount; }
	int32 GetInvalidationCount() const { return InvalidationCount; }
	int32 GetUnresolvedCount() const { return UnresolvedCount; }
	static ERARomanSurfaceRole GetDefaultSurfaceRole(ERARomanModuleCategory Category);
	static ERARomanWeatheringLevel ConvertDegradationLevel(ERARomanDegradationLevel Level);
	static FSoftObjectPath GetFallbackMeshPath(ERARomanModuleCategory Category);
	static FSoftObjectPath GetTechnicalMaterialPath(ERARomanModuleCategory Category);
	static FSoftObjectPath GetLocalCatalogPath();
	static URARomanVisualCatalog* LoadLocalCatalog(bool bWriteLog = true);
	static bool IsLocalCatalogAvailable();
	static bool AreLocalAssetsEnabled();
	static void SetLocalAssetsEnabled(bool bEnabled);

private:
	mutable TMap<uint32, int32> ResolutionCache;
	mutable int32 CacheHitCount = 0;
	mutable int32 CacheMissCount = 0;
	mutable int32 LocalResolvedCount = 0;
	mutable int32 InvalidationCount = 0;
	mutable int32 UnresolvedCount = 0;
};
