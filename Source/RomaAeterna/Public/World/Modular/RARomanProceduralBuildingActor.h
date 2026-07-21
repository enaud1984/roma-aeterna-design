#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "World/Modular/RARomanConstructionValidator.h"
#include "RARomanProceduralBuildingActor.generated.h"

USTRUCT(BlueprintType)
struct ROMAETERNA_API FRARomanPlaceholderVisualRule
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanModuleCategory Category = ERARomanModuleCategory::Wall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TSoftObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FVector SizeCm = FVector(100.f, 40.f, 300.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FVector OffsetCm = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FRotator ExtraRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FLinearColor DebugColor = FLinearColor::White;
};

UCLASS(Blueprintable)
class ROMAETERNA_API ARARomanProceduralBuildingActor : public AActor
{
	GENERATED_BODY()
public:
	ARARomanProceduralBuildingActor();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TSoftObjectPtr<URARomanModuleCatalog> ModuleCatalog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FRARomanBuildingParameters BuildingParameters;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") FRARomanGenerationResult LastGenerationResult;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bUseDebugPlaceholders = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bGenerateOnBeginPlay = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bAutoRebuildInEditor = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bShowDebugBounds = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bShowDebugLabels = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") int32 GeneratedInstanceCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TArray<TObjectPtr<UInstancedStaticMeshComponent>> InstanceComponents;

	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") bool GenerateBuilding();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") void ClearGeneratedBuilding();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") bool RebuildBuilding();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") bool GenerateFromParameters(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") FRARomanGenerationResult GenerateLayout();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") bool ValidateConfiguration(TArray<FRARomanGenerationMessage>& OutWarnings,TArray<FRARomanGenerationMessage>& OutErrors) const;
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") void RebuildInstances();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") void ClearGeneratedLayout();
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") FString GetGenerationSummary() const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") int32 GetGeneratedInstanceCount() const { return GeneratedInstanceCount; }
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateBuildingByType(ERARomanBuildingType Type);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateAtriumDomus();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateThermopolium();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateFullonica();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GeneratePistrinum();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GeneratePublicLatrine();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateSmallTemple();
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetGeneratedRoomCount() const { return LastGenerationResult.GeneratedRoomCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetGeneratedZoneCount() const { return LastGenerationResult.GeneratedZoneCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetGeneratedInteractionPointCount() const { return LastGenerationResult.GeneratedInteractionPointCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetProductionDeviceCount() const { return LastGenerationResult.ProductionDeviceCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetWaterFeatureCount() const { return LastGenerationResult.WaterFeatureCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") FString GetBuildingPlanSummary() const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") TArray<ERARomanBuildingType> GetImplementedArchetypes() const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") bool IsArchetypeImplemented(ERARomanBuildingType Type) const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") int32 GetInstanceCountByCategory(ERARomanModuleCategory Category) const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") bool HasGeneratedBuilding() const { return GeneratedInstanceCount > 0 && LastGenerationResult.bSuccess; }

private:
	UPROPERTY(Transient) TMap<ERARomanModuleCategory, TObjectPtr<UInstancedStaticMeshComponent>> CategoryInstanceComponents;
	TArray<FRARomanPlaceholderVisualRule> CreateDefaultVisualRules() const;
	FRARomanPlaceholderVisualRule GetVisualRule(ERARomanModuleCategory Category, const FRARomanBuildingParameters& Parameters) const;
	bool BuildVisualInstances(const FRARomanGenerationResult& Result);
	void ClearVisualInstances();
	void DrawRuntimeDebug() const;
};
