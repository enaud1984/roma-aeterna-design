#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "World/Modular/RARomanConstructionValidator.h"
#include "RARomanProceduralBuildingActor.generated.h"
UCLASS(Blueprintable)
class ROMAETERNA_API ARARomanProceduralBuildingActor : public AActor { GENERATED_BODY()
public:
	ARARomanProceduralBuildingActor();
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TSoftObjectPtr<URARomanModuleCatalog> ModuleCatalog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FRARomanBuildingParameters BuildingParameters;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") FRARomanGenerationResult LastGenerationResult;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bUseDebugPlaceholders = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bGenerateOnBeginPlay = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TArray<TObjectPtr<UInstancedStaticMeshComponent>> InstanceComponents;
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") FRARomanGenerationResult GenerateLayout();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") bool ValidateConfiguration(TArray<FRARomanGenerationMessage>& OutWarnings,TArray<FRARomanGenerationMessage>& OutErrors) const;
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") void RebuildInstances();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") void ClearGeneratedLayout();
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") FString GetGenerationSummary() const;
};
