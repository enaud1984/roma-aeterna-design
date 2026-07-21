#include "World/Modular/RARomanProceduralBuildingActor.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMesh.h"

namespace
{
FRARomanGenerationMessage MakeRuntimeMessage(FName Code, const FString& Message, bool bIsError)
{
	FRARomanGenerationMessage Result;
	Result.Code = Code;
	Result.Message = Message;
	Result.bIsError = bIsError;
	return Result;
}

TSoftObjectPtr<UStaticMesh> MakeEngineMeshReference(const TCHAR* Path)
{
	return TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(Path));
}

FName MakeRuntimeComponentKey(ERARomanModuleCategory Category, const UStaticMesh* Mesh)
{
	return FName(*FString::Printf(TEXT("%d_%s"), static_cast<int32>(Category), Mesh ? *Mesh->GetPathName() : TEXT("MissingMesh"))));
}

bool IsPlacementTransformFinite(const FRARomanModulePlacement& Placement)
{
	const FVector Location = Placement.Transform.GetLocation();
	const FVector Scale = Placement.Transform.GetScale3D();
	const FRotator Rotation = Placement.Transform.Rotator();
	return FMath::IsFinite(Location.X) && FMath::IsFinite(Location.Y) && FMath::IsFinite(Location.Z) &&
		FMath::IsFinite(Scale.X) && FMath::IsFinite(Scale.Y) && FMath::IsFinite(Scale.Z) &&
		FMath::IsFinite(Rotation.Pitch) && FMath::IsFinite(Rotation.Yaw) && FMath::IsFinite(Rotation.Roll) &&
		Scale.X > 0.0 && Scale.Y > 0.0 && Scale.Z > 0.0;
}
} // namespace

ARARomanProceduralBuildingActor::ARARomanProceduralBuildingActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RomanModularRoot"));
	RootComponent = SceneRoot;
	InitializeDefaultPlaceholderVisuals();
}

void ARARomanProceduralBuildingActor::BeginPlay()
{
	Super::BeginPlay();
	if (bGenerateOnBeginPlay)
	{
		GenerateBuilding();
	}
}

bool ARARomanProceduralBuildingActor::GenerateBuilding()
{
	FRARomanBuildingParameters NormalizedParameters = URARomanBuildingRuleLibrary::NormalizeBuildingParameters(BuildingParameters);
	BuildingParameters = NormalizedParameters;

	TArray<FRARomanGenerationMessage> ParameterWarnings;
	TArray<FRARomanGenerationMessage> ParameterErrors;
	URARomanConstructionValidator::ValidateParameters(BuildingParameters, ParameterWarnings, ParameterErrors);

	FRARomanGenerationResult NewResult = BuildLayoutFromCurrentParameters();
	NewResult.Warnings.Append(ParameterWarnings);
	NewResult.Errors.Append(ParameterErrors);

	TArray<FRARomanGenerationMessage> PlacementWarnings;
	TArray<FRARomanGenerationMessage> PlacementErrors;
	URARomanConstructionValidator::ValidatePlacements(NewResult.GeneratedPlacements, BuildingParameters.MaximumModuleCount, PlacementWarnings, PlacementErrors);
	NewResult.Warnings.Append(PlacementWarnings);
	NewResult.Errors.Append(PlacementErrors);

	if (NewResult.EstimatedModuleCount > BuildingParameters.MaximumModuleCount || NewResult.GeneratedPlacements.Num() > BuildingParameters.MaximumModuleCount)
	{
		AppendGenerationMessage(NewResult, "ModuleLimitExceeded", TEXT("Il layout supera MaximumModuleCount e non verrà istanziato completamente."), true);
	}

	ClearVisualInstances();
	LastGenerationResult = NewResult;
	if (LastGenerationResult.Errors.Num() > 0 || LastGenerationResult.GeneratedPlacements.Num() == 0)
	{
		if (LastGenerationResult.GeneratedPlacements.Num() == 0)
		{
			AppendGenerationMessage(LastGenerationResult, "EmptyGenerationResult", TEXT("Il layout non contiene placement da visualizzare."), true);
		}
		LastGenerationResult.bSuccess = false;
		return false;
	}

	const bool bVisualsBuilt = BuildVisualInstances();
	LastGenerationResult.bSuccess = LastGenerationResult.Errors.Num() == 0 && bVisualsBuilt;
	DrawRuntimeDebug();
	return LastGenerationResult.bSuccess;
}

bool ARARomanProceduralBuildingActor::GenerateFromParameters(const FRARomanBuildingParameters& Parameters)
{
	BuildingParameters = Parameters;
	return GenerateBuilding();
}

bool ARARomanProceduralBuildingActor::RebuildBuilding()
{
	ClearVisualInstances();
	return GenerateBuilding();
}

void ARARomanProceduralBuildingActor::ClearGeneratedBuilding()
{
	ClearVisualInstances();
	LastGenerationResult = FRARomanGenerationResult();
}

bool ARARomanProceduralBuildingActor::BuildVisualInstances()
{
	ClearVisualInstances();
	if (!bUseDebugPlaceholders)
	{
		AppendGenerationMessage(LastGenerationResult, "PlaceholdersDisabled", TEXT("Placeholder runtime disattivati: layout astratto generato senza istanze visuali."), false);
		return true;
	}
	if (!GetWorld())
	{
		AppendGenerationMessage(LastGenerationResult, "MissingWorld", TEXT("World nullo: impossibile creare componenti runtime."), true);
		return false;
	}

	for (const FRARomanModulePlacement& Placement : LastGenerationResult.GeneratedPlacements)
	{
		if (!IsPlacementTransformFinite(Placement))
		{
			AppendGenerationMessage(LastGenerationResult, "InvalidPlacementTransform", FString::Printf(TEXT("Placement non valido per %s."), *Placement.ModuleId.ToString()), true);
			continue;
		}

		const FRARomanPlaceholderVisualDefinition Visual = ResolveVisualDefinition(Placement.Category);
		UStaticMesh* Mesh = ResolvePlaceholderMesh(Visual, LastGenerationResult);
		if (!Mesh)
		{
			continue;
		}

		UInstancedStaticMeshComponent* Component = FindOrCreateInstanceComponent(Visual, Mesh);
		if (!Component)
		{
			AppendGenerationMessage(LastGenerationResult, "InstanceComponentFailed", TEXT("Creazione componente instanced fallita."), true);
			continue;
		}

		Component->AddInstance(CalculateVisualTransform(Placement, Visual));
		++GeneratedInstanceCount;
		InstanceCountByCategory.FindOrAdd(Placement.Category)++;
	}

	return LastGenerationResult.Errors.Num() == 0;
}

void ARARomanProceduralBuildingActor::ClearVisualInstances()
{
	for (UInstancedStaticMeshComponent* Component : InstanceComponents)
	{
		if (Component)
		{
			Component->ClearInstances();
			Component->DestroyComponent();
		}
	}
	InstanceComponents.Empty();
	RuntimeInstanceComponentByKey.Empty();
	InstanceCountByCategory.Empty();
	GeneratedInstanceCount = 0;
}

int32 ARARomanProceduralBuildingActor::GetInstanceCountByCategory(ERARomanModuleCategory Category) const
{
	if (const int32* Count = InstanceCountByCategory.Find(Category))
	{
		return *Count;
	}
	return 0;
}

FRARomanGenerationResult ARARomanProceduralBuildingActor::GenerateLayout()
{
	LastGenerationResult = BuildLayoutFromCurrentParameters();
	return LastGenerationResult;
}

bool ARARomanProceduralBuildingActor::ValidateConfiguration(TArray<FRARomanGenerationMessage>& OutWarnings, TArray<FRARomanGenerationMessage>& OutErrors) const
{
	URARomanConstructionValidator::ValidateParameters(BuildingParameters, OutWarnings, OutErrors);
	if (ModuleCatalog.IsNull())
	{
		OutWarnings.Add(MakeRuntimeMessage("NullCatalog", TEXT("Catalogo non impostato: saranno usati placement astratti o placeholder."), false));
	}
	return OutErrors.Num() == 0;
}

void ARARomanProceduralBuildingActor::RebuildInstances()
{
	BuildVisualInstances();
}

void ARARomanProceduralBuildingActor::ClearGeneratedLayout()
{
	ClearGeneratedBuilding();
}

FString ARARomanProceduralBuildingActor::GetGenerationSummary() const
{
	return FString::Printf(
		TEXT("Successo=%s, Placement=%d, Istanze=%d, Warning=%d, Errori=%d, Seed=%d"),
		LastGenerationResult.bSuccess ? TEXT("true") : TEXT("false"),
		LastGenerationResult.GeneratedPlacements.Num(),
		GeneratedInstanceCount,
		LastGenerationResult.Warnings.Num(),
		LastGenerationResult.Errors.Num(),
		BuildingParameters.RandomSeed);
}

void ARARomanProceduralBuildingActor::InitializeDefaultPlaceholderVisuals()
{
	PlaceholderVisuals.Reset();
	PlaceholderVisuals.Reserve(static_cast<int32>(ERARomanModuleCategory::Decoration) + 1);
	for (int32 CategoryIndex = 0; CategoryIndex <= static_cast<int32>(ERARomanModuleCategory::Decoration); ++CategoryIndex)
	{
		PlaceholderVisuals.Add(MakeDefaultVisualDefinition(static_cast<ERARomanModuleCategory>(CategoryIndex)));
	}
}

FRARomanPlaceholderVisualDefinition ARARomanProceduralBuildingActor::MakeDefaultVisualDefinition(ERARomanModuleCategory Category) const
{
	FRARomanPlaceholderVisualDefinition Visual;
	Visual.Category = Category;
	Visual.Mesh = MakeEngineMeshReference(TEXT("/Engine/BasicShapes/Cube.Cube"));
	Visual.SizeCm = FVector(120.0f, 40.0f, 120.0f);
	Visual.DebugColor = FLinearColor::White;

	switch (Category)
	{
	case ERARomanModuleCategory::Door:
		Visual.SizeCm = FVector(120.0f, 16.0f, 220.0f);
		Visual.DebugColor = FLinearColor(0.1f, 0.25f, 1.0f);
		break;
	case ERARomanModuleCategory::Window:
		Visual.SizeCm = FVector(90.0f, 12.0f, 90.0f);
		Visual.DebugColor = FLinearColor(0.1f, 0.8f, 1.0f);
		break;
	case ERARomanModuleCategory::Corner:
		Visual.SizeCm = FVector(70.0f, 70.0f, 260.0f);
		Visual.DebugColor = FLinearColor::Yellow;
		break;
	case ERARomanModuleCategory::Column:
		Visual.Mesh = MakeEngineMeshReference(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
		Visual.SizeCm = FVector(60.0f, 60.0f, 300.0f);
		Visual.DebugColor = FLinearColor(0.9f, 0.9f, 0.75f);
		break;
	case ERARomanModuleCategory::Capital:
		Visual.SizeCm = FVector(80.0f, 80.0f, 35.0f);
		Visual.DebugColor = FLinearColor(0.9f, 0.85f, 0.55f);
		break;
	case ERARomanModuleCategory::Base:
		Visual.SizeCm = FVector(90.0f, 90.0f, 30.0f);
		Visual.DebugColor = FLinearColor(0.55f, 0.55f, 0.55f);
		break;
	case ERARomanModuleCategory::Arch:
		Visual.Mesh = MakeEngineMeshReference(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
		Visual.SizeCm = FVector(180.0f, 35.0f, 180.0f);
		Visual.LocalRotation = FRotator(90.0f, 0.0f, 0.0f);
		Visual.DebugColor = FLinearColor(0.8f, 0.65f, 0.35f);
		break;
	case ERARomanModuleCategory::Beam:
		Visual.SizeCm = FVector(200.0f, 35.0f, 35.0f);
		Visual.DebugColor = FLinearColor(0.75f, 0.55f, 0.25f);
		break;
	case ERARomanModuleCategory::Floor:
		Visual.SizeCm = FVector(800.0f, 600.0f, 12.0f);
		Visual.DebugColor = FLinearColor(0.35f, 0.35f, 0.35f);
		break;
	case ERARomanModuleCategory::Roof:
		Visual.SizeCm = FVector(820.0f, 620.0f, 45.0f);
		Visual.LocalRotation = FRotator(4.0f, 0.0f, 0.0f);
		Visual.DebugColor = FLinearColor(0.65f, 0.18f, 0.08f);
		break;
	case ERARomanModuleCategory::Stair:
		Visual.SizeCm = FVector(180.0f, 220.0f, 45.0f);
		Visual.LocalRotation = FRotator(-6.0f, 0.0f, 0.0f);
		Visual.DebugColor = FLinearColor(0.45f, 0.45f, 0.45f);
		break;
	case ERARomanModuleCategory::Podium:
		Visual.SizeCm = FVector(850.0f, 650.0f, 80.0f);
		Visual.DebugColor = FLinearColor(0.55f, 0.50f, 0.42f);
		break;
	case ERARomanModuleCategory::Portico:
		Visual.Mesh = MakeEngineMeshReference(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
		Visual.SizeCm = FVector(55.0f, 55.0f, 280.0f);
		Visual.DebugColor = FLinearColor(0.8f, 0.8f, 0.65f);
		break;
	case ERARomanModuleCategory::Prop:
		Visual.SizeCm = FVector(60.0f, 60.0f, 70.0f);
		Visual.DebugColor = FLinearColor(0.45f, 0.25f, 0.12f);
		break;
	case ERARomanModuleCategory::Vegetation:
		Visual.Mesh = MakeEngineMeshReference(TEXT("/Engine/BasicShapes/Cone.Cone"));
		Visual.SizeCm = FVector(90.0f, 90.0f, 160.0f);
		Visual.DebugColor = FLinearColor::Green;
		break;
	case ERARomanModuleCategory::Decoration:
		Visual.Mesh = MakeEngineMeshReference(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
		Visual.SizeCm = FVector(45.0f, 45.0f, 45.0f);
		Visual.DebugColor = FLinearColor(1.0f, 0.6f, 0.15f);
		break;
	case ERARomanModuleCategory::Wall:
	default:
		Visual.SizeCm = FVector(URARomanBuildingRuleLibrary::CalculateBayWidth(BuildingParameters), BuildingParameters.WallThicknessCm, BuildingParameters.FloorHeightCm);
		Visual.DebugColor = FLinearColor(0.68f, 0.62f, 0.52f);
		break;
	}

	return Visual;
}

FRARomanPlaceholderVisualDefinition ARARomanProceduralBuildingActor::ResolveVisualDefinition(ERARomanModuleCategory Category) const
{
	for (const FRARomanPlaceholderVisualDefinition& Visual : PlaceholderVisuals)
	{
		if (Visual.Category == Category)
		{
			return Visual;
		}
	}
	return MakeDefaultVisualDefinition(Category);
}

FVector ARARomanProceduralBuildingActor::CalculatePlaceholderSizeCm(const FRARomanModulePlacement& Placement, const FRARomanPlaceholderVisualDefinition& Visual) const
{
	const float BayWidth = FMath::Max(URARomanBuildingRuleLibrary::CalculateBayWidth(BuildingParameters), 10.0f);
	const float WallThickness = FMath::Max(BuildingParameters.WallThicknessCm, 10.0f);
	const float FloorHeight = FMath::Max(BuildingParameters.FloorHeightCm, 220.0f);
	FVector Size = Visual.SizeCm;

	switch (Placement.Category)
	{
	case ERARomanModuleCategory::Wall:
		Size = FVector(BayWidth, WallThickness, FloorHeight);
		break;
	case ERARomanModuleCategory::Door:
		Size = FVector(BayWidth * 0.55f, WallThickness * 0.65f, FloorHeight * 0.68f);
		break;
	case ERARomanModuleCategory::Window:
		Size = FVector(BayWidth * 0.42f, WallThickness * 0.55f, FloorHeight * 0.28f);
		break;
	case ERARomanModuleCategory::Column:
	case ERARomanModuleCategory::Portico:
		Size = FVector(WallThickness * 1.35f, WallThickness * 1.35f, FloorHeight * 0.95f);
		break;
	case ERARomanModuleCategory::Beam:
		Size = FVector(BayWidth, WallThickness * 0.8f, WallThickness * 0.8f);
		break;
	case ERARomanModuleCategory::Floor:
		Size = FVector(FMath::Max(BuildingParameters.WidthCm, 100.0f), FMath::Max(BuildingParameters.DepthCm, 100.0f), 12.0f);
		break;
	case ERARomanModuleCategory::Roof:
		Size = FVector(FMath::Max(BuildingParameters.WidthCm + 60.0f, 100.0f), FMath::Max(BuildingParameters.DepthCm + 60.0f, 100.0f), 45.0f);
		break;
	case ERARomanModuleCategory::Podium:
		Size = FVector(FMath::Max(BuildingParameters.WidthCm + 80.0f, 100.0f), FMath::Max(BuildingParameters.DepthCm + 80.0f, 100.0f), 80.0f);
		break;
	default:
		break;
	}

	return FVector(FMath::Max(Size.X, 1.0f), FMath::Max(Size.Y, 1.0f), FMath::Max(Size.Z, 1.0f));
}

FTransform ARARomanProceduralBuildingActor::CalculateVisualTransform(const FRARomanModulePlacement& Placement, const FRARomanPlaceholderVisualDefinition& Visual) const
{
	const FVector SizeCm = CalculatePlaceholderSizeCm(Placement, Visual);
	FTransform VisualTransform = Placement.Transform;
	VisualTransform.ConcatenateRotation(Visual.LocalRotation.Quaternion());
	VisualTransform.AddToTranslation(Visual.LocalOffsetCm);
	VisualTransform.SetScale3D(SizeCm / BasicShapeUnitCm);
	return VisualTransform;
}

UStaticMesh* ARARomanProceduralBuildingActor::ResolvePlaceholderMesh(const FRARomanPlaceholderVisualDefinition& Visual, FRARomanGenerationResult& InOutResult) const
{
	if (Visual.Mesh.IsNull())
	{
		AppendGenerationMessage(InOutResult, "MissingPlaceholderSoftReference", TEXT("Soft reference placeholder non configurata."), true);
		return nullptr;
	}

	UStaticMesh* Mesh = Visual.Mesh.LoadSynchronous();
	if (!Mesh)
	{
		AppendGenerationMessage(InOutResult, "PlaceholderMeshNotFound", FString::Printf(TEXT("Mesh placeholder non trovata: %s"), *Visual.Mesh.ToSoftObjectPath().ToString()), true);
	}
	return Mesh;
}

UInstancedStaticMeshComponent* ARARomanProceduralBuildingActor::FindOrCreateInstanceComponent(const FRARomanPlaceholderVisualDefinition& Visual, UStaticMesh* Mesh)
{
	const FName Key = MakeRuntimeComponentKey(Visual.Category, Mesh);
	if (TWeakObjectPtr<UInstancedStaticMeshComponent>* Existing = RuntimeInstanceComponentByKey.Find(Key))
	{
		if (Existing->IsValid())
		{
			return Existing->Get();
		}
	}

	UInstancedStaticMeshComponent* Component = NewObject<UInstancedStaticMeshComponent>(this, NAME_None, RF_Transient);
	if (!Component)
	{
		return nullptr;
	}
	Component->SetMobility(EComponentMobility::Movable);
	Component->SetupAttachment(RootComponent);
	Component->SetStaticMesh(Mesh);
	Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Component->NumCustomDataFloats = 4;
	Component->RegisterComponent();
	InstanceComponents.Add(Component);
	RuntimeInstanceComponentByKey.Add(Key, Component);
	return Component;
}

FRARomanGenerationResult ARARomanProceduralBuildingActor::BuildLayoutFromCurrentParameters() const
{
	switch (BuildingParameters.BuildingType)
	{
	case ERARomanBuildingType::Taberna:
		return URARomanBuildingRuleLibrary::BuildTabernaLayout(BuildingParameters);
	case ERARomanBuildingType::Temple:
		return URARomanBuildingRuleLibrary::BuildTempleLayout(BuildingParameters);
	case ERARomanBuildingType::StreetSection:
		return URARomanBuildingRuleLibrary::BuildStreetSectionLayout(BuildingParameters);
	case ERARomanBuildingType::SimpleHouse:
	default:
		return URARomanBuildingRuleLibrary::BuildSimpleHouseLayout(BuildingParameters);
	}
}

void ARARomanProceduralBuildingActor::AppendGenerationMessage(FRARomanGenerationResult& InOutResult, FName Code, const FString& Message, bool bIsError) const
{
	FRARomanGenerationMessage RuntimeMessage = MakeRuntimeMessage(Code, Message, bIsError);
	if (bIsError)
	{
		InOutResult.Errors.Add(RuntimeMessage);
	}
	else
	{
		InOutResult.Warnings.Add(RuntimeMessage);
	}
}

void ARARomanProceduralBuildingActor::DrawRuntimeDebug() const
{
	if (!GetWorld())
	{
		return;
	}
	if (bShowDebugBounds && LastGenerationResult.Bounds.IsValid)
	{
		DrawDebugBox(GetWorld(), LastGenerationResult.Bounds.GetCenter(), LastGenerationResult.Bounds.GetExtent(), FColor::Orange, false, 10.0f, 0, 4.0f);
	}
	if (bShowDebugLabels)
	{
		DrawDebugString(GetWorld(), GetActorLocation() + FVector(0.0f, 0.0f, 120.0f), GetGenerationSummary(), nullptr, FColor::White, 10.0f, true);
	}
}
