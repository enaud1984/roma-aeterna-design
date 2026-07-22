#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "World/Modular/RARomanModularTypes.h"
#include "RARomanModuleCatalog.generated.h"
UCLASS(BlueprintType)
class ROMAAETERNA_API URARomanModuleCatalog : public UPrimaryDataAsset { GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TArray<FRARomanModuleDefinition> Modules;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") bool FindModuleById(FName ModuleId, FRARomanModuleDefinition& OutModule) const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") TArray<FRARomanModuleDefinition> GetModulesByCategory(ERARomanModuleCategory Category) const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") TArray<FRARomanModuleDefinition> GetModulesByTag(FName Tag) const;
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") void ValidateCatalog(TArray<FRARomanGenerationMessage>& OutWarnings, TArray<FRARomanGenerationMessage>& OutErrors) const;
};
