#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "World/Modular/RARomanConstructionValidator.h"
#include "World/Modular/RARomanBuildingRuleLibrary.h"
#include "World/Modular/RARomanDecorationTypes.h"
#include "World/Modular/RARomanVisualCatalog.h"
#include "RARomanProceduralBuildingActor.generated.h"

USTRUCT(BlueprintType)
struct ROMAAETERNA_API FRARomanPlaceholderVisualRule
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") ERARomanModuleCategory Category = ERARomanModuleCategory::Wall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TSoftObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FVector SizeCm = FVector(100.f, 40.f, 300.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FVector OffsetCm = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FRotator ExtraRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FLinearColor DebugColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") TSoftObjectPtr<UMaterialInterface> Material;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local") ERARomanSurfaceRole SurfaceRole = ERARomanSurfaceRole::ServiceArea;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local") FName MaterialVariant = NAME_None;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local") int32 VariantIndex = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local") bool bResolvedLocally = false;
};

UCLASS(Blueprintable)
class ROMAAETERNA_API ARARomanProceduralBuildingActor : public AActor
{
	GENERATED_BODY()
public:
	ARARomanProceduralBuildingActor();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TSoftObjectPtr<URARomanModuleCatalog> ModuleCatalog;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TObjectPtr<URARomanVisualCatalog> VisualCatalog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") FRARomanBuildingParameters BuildingParameters;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") FRARomanGenerationResult LastGenerationResult;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bUseDebugPlaceholders = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bGenerateOnBeginPlay = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bAutoRebuildInEditor = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bShowDebugBounds = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bShowDebugLabels = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bShowInteractionPoints = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Modular") bool bShowUtilityNodes = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") int32 GeneratedInstanceCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Modular") TArray<TObjectPtr<UInstancedStaticMeshComponent>> GeneratedInstanceComponents;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local") int32 LocallyResolvedCategoryCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local") int32 FallbackCategoryCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Visual|Local") TArray<FName> ActiveMaterialVariants;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Decoration") bool bDecorationEnabled = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Decoration") bool bForceDecorationFallback = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Roma Aeterna|Decoration") int32 DecorationVariant = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") bool bRoofsVisible = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") bool bRoomLabelsVisible = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") int32 AccessibleRoomCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") int32 DecorationPanelCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") int32 DecorationFallbackCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") ERAPompeianDecorativeStyle CurrentDecorativeStyle = ERAPompeianDecorativeStyle::PlainPlaster;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") ERARomanFloorDecorationType CurrentFloorDecoration = ERARomanFloorDecorationType::PackedEarth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") FName CurrentRoomName = TEXT("Ingresso");
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") TArray<TObjectPtr<UInstancedStaticMeshComponent>> InteriorInstanceComponents;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Roma Aeterna|Decoration") TArray<TObjectPtr<UInstancedStaticMeshComponent>> RoofInstanceComponents;
	UPROPERTY(Transient) TArray<TObjectPtr<UActorComponent>> InteriorAuxiliaryComponents;

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
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateDomusMedia();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GeneratePeristyleDomus();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateRichDomus();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GeneratePopularHouse();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateInsula();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateCenaculum();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateMixedUseHouse();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateTaberna();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GeneratePopina();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateCaupona();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateBookshop();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateBrothel();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateMedicalShop();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateBarberShop();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateMensaArgentaria();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateStabulum();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateBathComplex();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GeneratePalaestra();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateCastellumAquae();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateAqueductSection();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateSewerSection();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GeneratePublicFountain();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateCistern();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateWell();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateTinctoria();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateTannery();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateTextileWorkshop();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateMetalWorkshop();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GeneratePotteryWorkshop();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateOilWorkshop();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateWinery();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GeneratePressingWorkshop();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateStandaloneOven();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateHorrea();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateUrbanGarden();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Utilities") bool GenerateServiceYard();
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Utilities") float GetWaterDemand() const { return LastGenerationResult.WaterDemand; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Utilities") float GetDrainageDemand() const { return LastGenerationResult.DrainageDemand; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Utilities") float GetHeatDemand() const { return LastGenerationResult.HeatDemand; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Utilities") float GetStorageCapacity() const { return LastGenerationResult.StorageCapacity; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Utilities") int32 GetUtilityConnectionCount() const { return LastGenerationResult.UtilityConnectionCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Utilities") int32 GetHazardZoneCount() const { return LastGenerationResult.HazardZoneCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Utilities") int32 GetProductionStageCount() const { return LastGenerationResult.ProductionStageCount; }
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateAtriumDomus();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateThermopolium();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateFullonica();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GeneratePistrinum();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GeneratePublicLatrine();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") bool GenerateSmallTemple();
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetResidentCapacity() const { return URARomanBuildingRuleLibrary::GetResidentCapacity(LastGenerationResult); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetWorkerCapacity() const { return URARomanBuildingRuleLibrary::GetWorkerCapacity(LastGenerationResult); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetCustomerCapacity() const { return URARomanBuildingRuleLibrary::GetCustomerCapacity(LastGenerationResult); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetApartmentCount() const { return URARomanBuildingRuleLibrary::GetApartmentCount(LastGenerationResult); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetCommercialUnitCount() const { return URARomanBuildingRuleLibrary::GetCommercialUnitCount(LastGenerationResult); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetResidentialUnitCount() const { return URARomanBuildingRuleLibrary::GetResidentialUnitCount(LastGenerationResult); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetGeneratedRoomCount() const { return LastGenerationResult.GeneratedRoomCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetGeneratedZoneCount() const { return LastGenerationResult.GeneratedZoneCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetGeneratedInteractionPointCount() const { return LastGenerationResult.GeneratedInteractionPointCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetProductionDeviceCount() const { return LastGenerationResult.ProductionDeviceCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") int32 GetWaterFeatureCount() const { return LastGenerationResult.WaterFeatureCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") FString GetUrbanProfileSummary() const { return URARomanBuildingRuleLibrary::GetUrbanProfileSummary(BuildingParameters.BuildingType); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") ERARomanFrequencyClass GetFrequencyClass() const { return URARomanBuildingRuleLibrary::GetFrequencyClass(BuildingParameters.BuildingType); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") TArray<ERARomanUrbanZone> GetCompatibleUrbanZones() const { return URARomanBuildingRuleLibrary::GetCompatibleUrbanZones(BuildingParameters.BuildingType); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") FString GetBuildingPlanSummary() const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") TArray<ERARomanBuildingType> GetImplementedArchetypes() const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") bool IsArchetypeImplemented(ERARomanBuildingType Type) const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") int32 GetInstanceCountByCategory(ERARomanModuleCategory Category) const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") bool HasGeneratedBuilding() const { return GeneratedInstanceCount > 0 && LastGenerationResult.bSuccess; }
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Visual|Local") void RefreshVisualCatalogFromLocalAssets();
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Visual|Local") bool IsUsingLocalAssetCatalog() const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Visual|Local") int32 GetLocallyResolvedCategoryCount() const { return LocallyResolvedCategoryCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Visual|Local") int32 GetFallbackCategoryCount() const { return FallbackCategoryCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Visual|Local") int32 GetActiveMaterialVariantCount() const { return ActiveMaterialVariants.Num(); }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Visual|Local") FString GetActiveMaterialSummary() const;
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Decoration") bool GenerateRoomDecoration();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Decoration") void ClearRoomDecoration();
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Decoration") bool RebuildRoomDecoration();
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Decoration") ERAPompeianDecorativeStyle GetDecorativeStyle() const { return CurrentDecorativeStyle; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Decoration") int32 GetDecorationPanelCount() const { return DecorationPanelCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Decoration") ERARomanFloorDecorationType GetFloorDecorationType() const { return CurrentFloorDecoration; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Decoration") int32 GetDecorationFallbackCount() const { return DecorationFallbackCount; }
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Decoration") void SetDecorationEnabled(bool bEnabled);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Decoration") void SetDecorationVariant(int32 Variant);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Decoration") void SetDecorationFallbackEnabled(bool bFallback);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Decoration") void SetRoofVisibility(bool bVisible);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Decoration") void SetRoomLabelsVisible(bool bVisible) { bRoomLabelsVisible = bVisible; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Decoration") int32 GetAccessibleRoomCount() const { return AccessibleRoomCount; }
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Decoration") bool IsAccessibleInteriorArchetype() const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Decoration") bool IsUsingLocalDecorationAssets() const;
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Decoration") FString GetDecorationSummary() const;

private:
	UPROPERTY(Transient) TMap<ERARomanModuleCategory, TObjectPtr<UInstancedStaticMeshComponent>> CategoryInstanceComponents;
	TArray<FRARomanPlaceholderVisualRule> CreateDefaultVisualRules() const;
	FRARomanPlaceholderVisualRule GetVisualRule(ERARomanModuleCategory Category, const FRARomanBuildingParameters& Parameters) const;
	bool BuildVisualInstances(const FRARomanGenerationResult& Result);
	bool BuildAccessibleInterior();
	void ClearVisualInstances();
	void DrawRuntimeDebug();
};
