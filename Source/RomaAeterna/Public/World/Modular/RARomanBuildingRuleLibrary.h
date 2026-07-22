#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "World/Modular/RARomanModuleCatalog.h"
#include "RARomanBuildingRuleLibrary.generated.h"
UCLASS()
class ROMAETERNA_API URARomanBuildingRuleLibrary : public UBlueprintFunctionLibrary { GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") static bool ValidateBuildingParameters(const FRARomanBuildingParameters& Parameters,TArray<FRARomanGenerationMessage>& OutWarnings,TArray<FRARomanGenerationMessage>& OutErrors);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") static FRARomanBuildingParameters NormalizeBuildingParameters(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") static float CalculateBayWidth(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") static float CalculateFloorHeight(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") static FBox CalculateBuildingBounds(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") static int32 EstimateRequiredModules(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") static bool IsModuleCompatible(const FRARomanModuleDefinition& Module,const FRARomanBuildingParameters& Parameters,const TArray<FName>& RequiredTags);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") static TArray<FRARomanModuleDefinition> SelectCompatibleModules(const URARomanModuleCatalog* Catalog,const FRARomanBuildingParameters& Parameters,ERARomanModuleCategory Category,const TArray<FName>& RequiredTags,TArray<FRARomanGenerationMessage>& OutWarnings);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular") static FTransform CalculateGridAlignedTransform(const FVector& Location,const FRotator& Rotation,const FVector& Scale,float GridSizeCm,float RotationStepDegrees);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") static FRARomanGenerationResult BuildSimpleHouseLayout(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") static FRARomanGenerationResult BuildTabernaLayout(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") static FRARomanGenerationResult BuildTempleLayout(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular") static FRARomanGenerationResult BuildStreetSectionLayout(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateBuildingByType(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateDomusMediaPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GeneratePeristyleDomusPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateRichDomusPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GeneratePopularHousePlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateInsulaPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateCenaculumPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateMixedUseHousePlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateTabernaPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GeneratePopinaPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateCauponaPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateBookshopPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateBrothelPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateMedicalShopPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateBarberShopPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateMensaArgentariaPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateStabulumPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateAtriumDomusPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateThermopoliumPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateFullonicaPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GeneratePistrinumPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GeneratePublicLatrinePlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateSmallTemplePlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static TArray<ERARomanBuildingType> GetImplementedArchetypes();
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static int32 GetResidentCapacity(const FRARomanGenerationResult& Result);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static int32 GetWorkerCapacity(const FRARomanGenerationResult& Result);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static int32 GetCustomerCapacity(const FRARomanGenerationResult& Result);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static int32 GetApartmentCount(const FRARomanGenerationResult& Result);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static int32 GetCommercialUnitCount(const FRARomanGenerationResult& Result);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static int32 GetResidentialUnitCount(const FRARomanGenerationResult& Result);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static FString GetUrbanProfileSummary(ERARomanBuildingType Type);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static ERARomanFrequencyClass GetFrequencyClass(ERARomanBuildingType Type);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static TArray<ERARomanUrbanZone> GetCompatibleUrbanZones(ERARomanBuildingType Type);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static bool IsArchetypeImplemented(ERARomanBuildingType Type);
};
