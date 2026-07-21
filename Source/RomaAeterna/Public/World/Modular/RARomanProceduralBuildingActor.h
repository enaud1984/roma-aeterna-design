#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "World/Modular/RARomanConstructionValidator.h"
#include "RARomanProceduralBuildingActor.generated.h"


USTRUCT(BlueprintType)
struct ROMAETERNA_API FRARomanPlaceholderVisualDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Visual")
	ERARomanModuleCategory Category = ERARomanModuleCategory::Wall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Visual")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Visual")
	FVector SizeCm = FVector(100.0f, 100.0f, 100.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Visual")
	FLinearColor DebugColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Visual")
	FVector LocalOffsetCm = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Visual")
	FRotator LocalRotation = FRotator::ZeroRotator;
};

UCLASS(Blueprintable)
class ROMAETERNA_API ARARomanProceduralBuildingActor : public AActor
{
	GENERATED_BODY()

public:
	ARARomanProceduralBuildingActor();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roma Aeterna|Modular")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roma Aeterna|Modular")
	TSoftObjectPtr<URARomanModuleCatalog> ModuleCatalog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular", meta = (DisplayName = "Parameters"))
	FRARomanBuildingParameters BuildingParameters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roma Aeterna|Modular")
	FRARomanGenerationResult LastGenerationResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Visual")
	bool bUseDebugPlaceholders = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular")
	bool bGenerateOnBeginPlay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Debug")
	bool bShowDebugBounds = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Debug")
	bool bShowDebugLabels = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roma Aeterna|Modular|Visual")
	TArray<FRARomanPlaceholderVisualDefinition> PlaceholderVisuals;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Roma Aeterna|Modular|Visual")
	TArray<TObjectPtr<UInstancedStaticMeshComponent>> InstanceComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Roma Aeterna|Modular|Visual")
	int32 GeneratedInstanceCount = 0;

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular")
	bool GenerateBuilding();

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular")
	bool GenerateFromParameters(const FRARomanBuildingParameters& Parameters);

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular")
	bool RebuildBuilding();

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular")
	void ClearGeneratedBuilding();

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular|Visual")
	bool BuildVisualInstances();

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular|Visual")
	void ClearVisualInstances();

	UFUNCTION(BlueprintPure, Category = "Roma Aeterna|Modular|Visual")
	int32 GetGeneratedInstanceCount() const { return GeneratedInstanceCount; }

	UFUNCTION(BlueprintPure, Category = "Roma Aeterna|Modular|Visual")
	int32 GetInstanceCountByCategory(ERARomanModuleCategory Category) const;

	UFUNCTION(BlueprintPure, Category = "Roma Aeterna|Modular")
	bool HasGeneratedBuilding() const { return LastGenerationResult.GeneratedPlacements.Num() > 0 || GeneratedInstanceCount > 0; }

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular")
	FRARomanGenerationResult GenerateLayout();

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular")
	bool ValidateConfiguration(TArray<FRARomanGenerationMessage>& OutWarnings, TArray<FRARomanGenerationMessage>& OutErrors) const;

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular")
	void RebuildInstances();

	UFUNCTION(BlueprintCallable, Category = "Roma Aeterna|Modular")
	void ClearGeneratedLayout();

	UFUNCTION(BlueprintPure, Category = "Roma Aeterna|Modular")
	FString GetGenerationSummary() const;

private:
	static constexpr float BasicShapeUnitCm = 100.0f;

	TMap<FName, TWeakObjectPtr<UInstancedStaticMeshComponent>> RuntimeInstanceComponentByKey;
	TMap<ERARomanModuleCategory, int32> InstanceCountByCategory;

	void InitializeDefaultPlaceholderVisuals();
	FRARomanPlaceholderVisualDefinition MakeDefaultVisualDefinition(ERARomanModuleCategory Category) const;
	FRARomanPlaceholderVisualDefinition ResolveVisualDefinition(ERARomanModuleCategory Category) const;
	FVector CalculatePlaceholderSizeCm(const FRARomanModulePlacement& Placement, const FRARomanPlaceholderVisualDefinition& Visual) const;
	FTransform CalculateVisualTransform(const FRARomanModulePlacement& Placement, const FRARomanPlaceholderVisualDefinition& Visual) const;
	UStaticMesh* ResolvePlaceholderMesh(const FRARomanPlaceholderVisualDefinition& Visual, FRARomanGenerationResult& InOutResult) const;
	UInstancedStaticMeshComponent* FindOrCreateInstanceComponent(const FRARomanPlaceholderVisualDefinition& Visual, UStaticMesh* Mesh);
	FRARomanGenerationResult BuildLayoutFromCurrentParameters() const;
	void AppendGenerationMessage(FRARomanGenerationResult& InOutResult, FName Code, const FString& Message, bool bIsError) const;
	void DrawRuntimeDebug() const;
};
