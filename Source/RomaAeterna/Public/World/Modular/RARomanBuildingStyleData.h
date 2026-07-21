#pragma once
#include "CoreMinimal.h"
#include "Engine/PrimaryDataAsset.h"
#include "World/Modular/RARomanModularTypes.h"
#include "RARomanBuildingStyleData.generated.h"
UCLASS(BlueprintType)
class ROMAETERNA_API URARomanBuildingStyleData : public UPrimaryDataAsset { GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") FName StyleId=NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") FString City;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") FString HistoricalPeriod;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") TArray<ERARomanBuildingType> AllowedBuildingTypes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") TArray<ERARomanWallType> PreferredWallTypes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") TArray<ERARomanRoofType> PreferredRoofTypes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") TArray<ERARomanArchitecturalOrder> PreferredArchitecturalOrders;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") TArray<TSoftObjectPtr<UMaterialInterface>> DefaultMaterials;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") TArray<FName> RequiredTags;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") TArray<FName> ForbiddenTags;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Style") FString Notes;
};
