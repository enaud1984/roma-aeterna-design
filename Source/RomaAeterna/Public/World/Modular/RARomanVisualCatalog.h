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
};
