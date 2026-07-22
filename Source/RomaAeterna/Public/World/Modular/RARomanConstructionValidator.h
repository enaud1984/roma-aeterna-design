#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "World/Modular/RARomanBuildingRuleLibrary.h"
#include "RARomanConstructionValidator.generated.h"
UCLASS()
class ROMAAETERNA_API URARomanConstructionValidator : public UBlueprintFunctionLibrary { GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") static bool ValidateParameters(const FRARomanBuildingParameters& Parameters,TArray<FRARomanGenerationMessage>& OutWarnings,TArray<FRARomanGenerationMessage>& OutErrors);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") static bool ValidateCatalog(const URARomanModuleCatalog* Catalog,TArray<FRARomanGenerationMessage>& OutWarnings,TArray<FRARomanGenerationMessage>& OutErrors);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") static bool ValidatePlacements(const TArray<FRARomanModulePlacement>& Placements,int32 MaximumModuleCount,TArray<FRARomanGenerationMessage>& OutWarnings,TArray<FRARomanGenerationMessage>& OutErrors);
};
