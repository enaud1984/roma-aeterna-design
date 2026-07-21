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
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateAtriumDomusPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateThermopoliumPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateFullonicaPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GeneratePistrinumPlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GeneratePublicLatrinePlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintCallable, Category="Roma Aeterna|Modular|Archetypes") static FRARomanGenerationResult GenerateSmallTemplePlan(const FRARomanBuildingParameters& Parameters);
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static TArray<ERARomanBuildingType> GetImplementedArchetypes();
	UFUNCTION(BlueprintPure, Category="Roma Aeterna|Modular|Archetypes") static bool IsArchetypeImplemented(ERARomanBuildingType Type);
};
