#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "World/Modular/RARomanModularTypes.h"
#include "RARomanVisualCatalog.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local", meta=(ClampMin="0.0"))
	float VariationWeight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FVector ScaleCorrection = FVector::OneVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FRotator RotationCorrection = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	FName CollisionProfile = TEXT("BlockAll");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	bool bPreferNanite = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local")
	TArray<TSoftObjectPtr<UMaterialInterface>> MaterialOverrides;

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
	static FSoftObjectPath GetFallbackMeshPath(ERARomanModuleCategory Category);
	static FSoftObjectPath GetTechnicalMaterialPath(ERARomanModuleCategory Category);
	static FSoftObjectPath GetLocalCatalogPath();
	static URARomanVisualCatalog* LoadLocalCatalog(bool bWriteLog = true);
	static bool IsLocalCatalogAvailable();
	static bool AreLocalAssetsEnabled();
	static void SetLocalAssetsEnabled(bool bEnabled);
};
