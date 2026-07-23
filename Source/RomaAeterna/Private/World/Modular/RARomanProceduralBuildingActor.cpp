#include "World/Modular/RARomanProceduralBuildingActor.h"

#include "Components/SceneComponent.h"
#include "Components/PointLightComponent.h"
#include "DrawDebugHelpers.h"
#include "Materials/MaterialInterface.h"

namespace
{
const TCHAR* CubePath = TEXT("/Engine/BasicShapes/Cube.Cube");
const TCHAR* CylinderPath = TEXT("/Engine/BasicShapes/Cylinder.Cylinder");
const TCHAR* SpherePath = TEXT("/Engine/BasicShapes/Sphere.Sphere");
const TCHAR* ConePath = TEXT("/Engine/BasicShapes/Cone.Cone");
constexpr float EngineBasicShapeSizeCm = 100.f;

FRARomanGenerationMessage MakeMessage(const FName Code, const FString& Message, const bool bIsError)
{
	FRARomanGenerationMessage Result; Result.Code = Code; Result.Message = Message; Result.bIsError = bIsError; return Result;
}

FName GetDistrictForArchetype(const ERARomanBuildingType Type)
{
	switch (Type)
	{
	case ERARomanBuildingType::PopularHouse: return TEXT("PopularResidential");
	case ERARomanBuildingType::DomusMedia: return TEXT("MediumResidential");
	case ERARomanBuildingType::Taberna:
	case ERARomanBuildingType::Thermopolium: return TEXT("CommercialAxis");
	case ERARomanBuildingType::BathComplex:
	case ERARomanBuildingType::PublicFountain: return TEXT("CivicCenter");
	case ERARomanBuildingType::MetalWorkshop:
	case ERARomanBuildingType::ServiceYard: return TEXT("ProductiveDistrict");
	case ERARomanBuildingType::AqueductSection: return TEXT("PeripheralDistrict");
	case ERARomanBuildingType::UrbanGarden: return TEXT("MediumResidential");
	default: return NAME_None;
	}
}

bool IsPrompt29AccessibleType(const ERARomanBuildingType Type)
{
	return Type == ERARomanBuildingType::PopularHouse || Type == ERARomanBuildingType::DomusMedia
		|| Type == ERARomanBuildingType::Taberna || Type == ERARomanBuildingType::Thermopolium
		|| Type == ERARomanBuildingType::BathComplex || Type == ERARomanBuildingType::MetalWorkshop;
}

const TCHAR* DecorationMaterialPath(const ERAPompeianDecorativeStyle Style, const int32 Variant)
{
	if (Style == ERAPompeianDecorativeStyle::ServicePlaster) return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_ServicePlaster.MI_RA_Decoration_ServicePlaster");
	if (Style == ERAPompeianDecorativeStyle::PlainPlaster) return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_PlainPlaster.MI_RA_Decoration_PlainPlaster");
	switch (FMath::Abs(Variant) % 3)
	{
	case 0: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_PompeianRed.MI_RA_Decoration_PompeianRed");
	case 1: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_Ochre.MI_RA_Decoration_Ochre");
	default: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_BlackPanel.MI_RA_Decoration_BlackPanel");
	}
}

const TCHAR* FloorMaterialPath(const ERARomanFloorDecorationType Type)
{
	switch (Type)
	{
	case ERARomanFloorDecorationType::OpusSigninum: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_OpusSigninum.MI_RA_Decoration_OpusSigninum");
	case ERARomanFloorDecorationType::GeometricMosaic: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_GeometricMosaic.MI_RA_Decoration_GeometricMosaic");
	case ERARomanFloorDecorationType::SimplePolychromeMosaic: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_PolychromeMosaic.MI_RA_Decoration_PolychromeMosaic");
	case ERARomanFloorDecorationType::OpusSectileInspired: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_OpusSectile.MI_RA_Decoration_OpusSectile");
	case ERARomanFloorDecorationType::ThermalFloor: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_ThermalFloor.MI_RA_Decoration_ThermalFloor");
	case ERARomanFloorDecorationType::ProductiveFloor: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_ProductiveFloor.MI_RA_Decoration_ProductiveFloor");
	default: return TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_BrickFloor.MI_RA_Decoration_BrickFloor");
	}
}
}

ARARomanProceduralBuildingActor::ARARomanProceduralBuildingActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RomanModularRoot"));
	RootComponent = SceneRoot;
}

void ARARomanProceduralBuildingActor::BeginPlay()
{
	Super::BeginPlay();
	RefreshVisualCatalogFromLocalAssets();
	if (bGenerateOnBeginPlay) { GenerateBuilding(); }
}

void ARARomanProceduralBuildingActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (!VisualCatalog) { RefreshVisualCatalogFromLocalAssets(); }
	if (bAutoRebuildInEditor && !GetWorld()->IsGameWorld()) { GenerateBuilding(); }
}

void ARARomanProceduralBuildingActor::RefreshVisualCatalogFromLocalAssets()
{
	VisualCatalog = URARomanVisualCatalog::LoadLocalCatalog(false);
	if (VisualCatalog)
	{
		VisualCatalog->ClearResolutionCache();
	}
}

bool ARARomanProceduralBuildingActor::IsUsingLocalAssetCatalog() const
{
	return VisualCatalog && VisualCatalog->GetPathName() == URARomanVisualCatalog::GetLocalCatalogPath().ToString();
}

TArray<FRARomanPlaceholderVisualRule> ARARomanProceduralBuildingActor::CreateDefaultVisualRules() const
{
	return {
		{ERARomanModuleCategory::Wall, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(180, 35, 300), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Gray},
		{ERARomanModuleCategory::Door, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(90, 18, 220), FVector(0, 0, 110), FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::Window, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(80, 14, 90), FVector(0, 0, 180), FRotator::ZeroRotator, FLinearColor::Blue},
		{ERARomanModuleCategory::Corner, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(50, 50, 300), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::White},
		{ERARomanModuleCategory::Column, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CylinderPath)), FVector(55, 55, 300), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Green},
		{ERARomanModuleCategory::Capital, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(80, 80, 28), FVector(0, 0, 160), FRotator::ZeroRotator, FLinearColor::Green},
		{ERARomanModuleCategory::Base, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(90, 90, 25), FVector(0, 0, 12), FRotator::ZeroRotator, FLinearColor::Green},
		{ERARomanModuleCategory::Arch, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(130, 25, 45), FVector(0, 0, 250), FRotator::ZeroRotator, FLinearColor::Red},
		{ERARomanModuleCategory::Beam, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(180, 35, 35), FVector(0, 0, 300), FRotator::ZeroRotator, FLinearColor::Red},
		{ERARomanModuleCategory::Floor, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(180, 180, 12), FVector(0, 0, 6), FRotator::ZeroRotator, FLinearColor(0.35f,0.25f,0.15f)},
		{ERARomanModuleCategory::Roof, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(190, 190, 35), FVector(0, 0, 330), FRotator(0,0,8), FLinearColor(0.55f,0.1f,0.05f)},
		{ERARomanModuleCategory::Stair, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(110, 80, 35), FVector(0, 0, 18), FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::Podium, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(220, 220, 80), FVector(0, 0, 40), FRotator::ZeroRotator, FLinearColor::White},
		{ERARomanModuleCategory::Portico, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CylinderPath)), FVector(45, 45, 260), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Green},
		{ERARomanModuleCategory::Prop, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(45, 45, 45), FVector(0, 0, 22), FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::Vegetation, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(SpherePath)), FVector(90, 90, 90), FVector(0, 0, 170), FRotator::ZeroRotator, FLinearColor::Green},
		{ERARomanModuleCategory::Decoration, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(ConePath)), FVector(35, 35, 60), FVector(0, 0, 30), FRotator::ZeroRotator, FLinearColor::Red},
		{ERARomanModuleCategory::Counter, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(220,80,100), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::Dolium, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CylinderPath)), FVector(70,70,90), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor(0.5f,0.25f,0.1f)},
		{ERARomanModuleCategory::Basin, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(120,90,35), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Blue},
		{ERARomanModuleCategory::WaterChannel, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(260,22,18), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Blue},
		{ERARomanModuleCategory::Millstone, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CylinderPath)), FVector(120,120,45), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Gray},
		{ERARomanModuleCategory::Oven, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CylinderPath)), FVector(140,140,110), FVector::ZeroVector, FRotator(90,0,0), FLinearColor::Red},
		{ERARomanModuleCategory::Furnace, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(100,80,70), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Red},
		{ERARomanModuleCategory::LatrineSeat, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(65,45,55), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::White},
		{ERARomanModuleCategory::Drain, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(260,18,12), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Blue},
		{ERARomanModuleCategory::Altar, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(120,80,80), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::White},
		{ERARomanModuleCategory::StatueMarker, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(ConePath)), FVector(55,55,140), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::White},
		{ERARomanModuleCategory::Shelf, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(140,35,150), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::StorageContainer, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CylinderPath)), FVector(80,80,80), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::DryingRack, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(200,35,180), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Green},
		{ERARomanModuleCategory::WorkPlatform, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(120,90,25), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Gray},
		{ERARomanModuleCategory::RotationArm, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(170,18,18), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Gray},
		{ERARomanModuleCategory::ServiceBasin, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(90,70,45), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Blue},
		{ERARomanModuleCategory::Bed, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(180,80,45), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::Table, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(120,80,70), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::Bench, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(140,35,45), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::WritingDesk, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(120,60,80), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::ScrollStorage, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CylinderPath)), FVector(60,60,120), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::MirrorMarker, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(60,8,100), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Blue},
		{ERARomanModuleCategory::FeedingTrough, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(160,45,40), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Green},
		{ERARomanModuleCategory::WateringTrough, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(160,45,40), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Blue},
		{ERARomanModuleCategory::Balcony, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(140,60,18), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::White},
		{ERARomanModuleCategory::SharedStair, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(100,90,35), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::ApartmentDoor, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(85,18,205), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::ShopOpening, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(180,18,230), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Yellow},
		{ERARomanModuleCategory::ValueStorageMarker, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(CubePath)), FVector(90,90,90), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::Red},
		{ERARomanModuleCategory::InteractionMarker, TSoftObjectPtr<UStaticMesh>(FSoftObjectPath(SpherePath)), FVector(35,35,35), FVector::ZeroVector, FRotator::ZeroRotator, FLinearColor::White}
	};
}

FRARomanPlaceholderVisualRule ARARomanProceduralBuildingActor::GetVisualRule(ERARomanModuleCategory Category, const FRARomanBuildingParameters& Parameters) const
{
	for (FRARomanPlaceholderVisualRule Rule : CreateDefaultVisualRules())
	{
		if (Rule.Category == Category)
		{
			FRARomanVisualCatalogEntry CatalogEntry;
			int32 VariantIndex = 0;
			if (VisualCatalog && VisualCatalog->ResolveEntry(Category, Parameters.BuildingType,
				Parameters.WealthLevel, URARomanVisualCatalog::ConvertDegradationLevel(Parameters.DegradationLevel),
				GetDistrictForArchetype(Parameters.BuildingType), Parameters.RandomSeed, CatalogEntry, VariantIndex))
			{
				if (!CatalogEntry.Mesh.IsNull()) Rule.Mesh = CatalogEntry.Mesh;
				if (!CatalogEntry.Material.IsNull()) Rule.Material = CatalogEntry.Material;
				Rule.SizeCm *= CatalogEntry.ScaleCorrection;
				Rule.ExtraRotation += CatalogEntry.RotationCorrection;
				Rule.SurfaceRole = CatalogEntry.SurfaceRole;
				Rule.MaterialVariant = CatalogEntry.MaterialVariant;
				Rule.VariantIndex = VariantIndex;
				Rule.bResolvedLocally = Rule.Material.ToSoftObjectPath().ToString().StartsWith(TEXT("/Game/LocalAssets/"));
			}
			else
			{
				Rule.SurfaceRole = URARomanVisualCatalog::GetDefaultSurfaceRole(Category);
			}
			if (Rule.Mesh.IsNull()) Rule.Mesh = TSoftObjectPtr<UStaticMesh>(URARomanVisualCatalog::GetFallbackMeshPath(Category));
			if (Rule.Material.IsNull()) Rule.Material = TSoftObjectPtr<UMaterialInterface>(URARomanVisualCatalog::GetTechnicalMaterialPath(Category));
			const float Bay = FMath::Max(Parameters.WidthCm / FMath::Max(1, Parameters.BayCount), 25.f);
			if (Category == ERARomanModuleCategory::Wall || Category == ERARomanModuleCategory::Beam) Rule.SizeCm.X = Bay;
			if (Category == ERARomanModuleCategory::Wall || Category == ERARomanModuleCategory::Column || Category == ERARomanModuleCategory::Corner) Rule.SizeCm.Z = Parameters.FloorHeightCm;
			if (Category == ERARomanModuleCategory::Floor || Category == ERARomanModuleCategory::Roof || Category == ERARomanModuleCategory::Podium) Rule.SizeCm = FVector(FMath::Min(Parameters.WidthCm, Bay * 2.f), FMath::Min(Parameters.DepthCm, Bay * 2.f), Rule.SizeCm.Z);
			return Rule;
		}
	}
	for (FRARomanPlaceholderVisualRule Rule : CreateDefaultVisualRules())
	{
		if (Rule.Category == ERARomanModuleCategory::Prop) { Rule.Category = Category; return Rule; }
	}
	return FRARomanPlaceholderVisualRule();
}

bool ARARomanProceduralBuildingActor::GenerateBuilding()
{
	TArray<FRARomanGenerationMessage> Warnings, Errors;
	BuildingParameters = URARomanBuildingRuleLibrary::NormalizeBuildingParameters(BuildingParameters);
	ValidateConfiguration(Warnings, Errors);
	FRARomanGenerationResult NewResult;
	NewResult.Warnings.Append(Warnings); NewResult.Errors.Append(Errors);
	if (Errors.Num() > 0) { ClearVisualInstances(); LastGenerationResult = NewResult; return false; }

	NewResult = URARomanBuildingRuleLibrary::GenerateBuildingByType(BuildingParameters);
	NewResult.Warnings.Append(Warnings);
	TArray<FRARomanGenerationMessage> PlacementWarnings, PlacementErrors;
	URARomanConstructionValidator::ValidatePlacements(NewResult.GeneratedPlacements, BuildingParameters.MaximumModuleCount, PlacementWarnings, PlacementErrors);
	NewResult.Warnings.Append(PlacementWarnings); NewResult.Errors.Append(PlacementErrors);
	if (!NewResult.bSuccess || NewResult.GeneratedPlacements.Num() <= 0 || NewResult.GeneratedPlacements.Num() > BuildingParameters.MaximumModuleCount || NewResult.Errors.Num() > 0)
	{
		ClearVisualInstances(); LastGenerationResult = NewResult; return false;
	}
	ClearVisualInstances();
	LastGenerationResult = NewResult;
	const bool bBuilt = BuildVisualInstances(LastGenerationResult);
	const bool bInteriorBuilt = !IsAccessibleInteriorArchetype() || BuildAccessibleInterior();
	DrawRuntimeDebug();
	return bBuilt && bInteriorBuilt;
}

void ARARomanProceduralBuildingActor::ClearGeneratedBuilding(){ ClearVisualInstances(); LastGenerationResult = FRARomanGenerationResult(); }
bool ARARomanProceduralBuildingActor::RebuildBuilding(){ ClearVisualInstances(); return GenerateBuilding(); }
bool ARARomanProceduralBuildingActor::GenerateFromParameters(const FRARomanBuildingParameters& Parameters){ BuildingParameters = Parameters; return GenerateBuilding(); }
FRARomanGenerationResult ARARomanProceduralBuildingActor::GenerateLayout(){ GenerateBuilding(); return LastGenerationResult; }
void ARARomanProceduralBuildingActor::RebuildInstances(){ ClearVisualInstances(); BuildVisualInstances(LastGenerationResult); }
void ARARomanProceduralBuildingActor::ClearGeneratedLayout(){ ClearGeneratedBuilding(); }

bool ARARomanProceduralBuildingActor::ValidateConfiguration(TArray<FRARomanGenerationMessage>& W,TArray<FRARomanGenerationMessage>& E) const
{
	URARomanConstructionValidator::ValidateParameters(BuildingParameters,W,E);
	if (ModuleCatalog.IsNull()) W.Add(MakeMessage("NullCatalog", TEXT("Catalogo non impostato: runtime placeholder Engine attivo."), false));
	if (!GetWorld()) E.Add(MakeMessage("NullWorld", TEXT("World nullo: impossibile generare componenti runtime."), true));
	return E.Num() == 0;
}

bool ARARomanProceduralBuildingActor::BuildVisualInstances(const FRARomanGenerationResult& Result)
{
	if (!bUseDebugPlaceholders) return true;
	LocallyResolvedCategoryCount = 0;
	FallbackCategoryCount = 0;
	ActiveMaterialVariants.Reset();
	bool bAllMeshesLoaded = true;
	for (const FRARomanModulePlacement& Placement : Result.GeneratedPlacements)
	{
		if (Placement.Transform.ContainsNaN() || Placement.Transform.GetScale3D().GetMin() <= 0.f) { bAllMeshesLoaded = false; continue; }
		const FRARomanPlaceholderVisualRule Rule = GetVisualRule(Placement.Category, BuildingParameters);
		UStaticMesh* Mesh = Rule.Mesh.LoadSynchronous();
		if (!Mesh) { LastGenerationResult.Errors.Add(MakeMessage("MissingPlaceholderMesh", FString::Printf(TEXT("Mesh placeholder non trovata per categoria %d."), static_cast<int32>(Placement.Category)), true)); bAllMeshesLoaded = false; continue; }
		TObjectPtr<UInstancedStaticMeshComponent>& Component = CategoryInstanceComponents.FindOrAdd(Placement.Category);
		if (!Component)
		{
			Component = NewObject<UInstancedStaticMeshComponent>(this, NAME_None, RF_Transient);
			Component->SetupAttachment(RootComponent);
			Component->SetStaticMesh(Mesh);
			if (UMaterialInterface* Material = Rule.Material.LoadSynchronous()) Component->SetMaterial(0, Material);
			Component->SetMobility(EComponentMobility::Movable);
			const bool bPassageCategory = Placement.Category == ERARomanModuleCategory::Door
				|| Placement.Category == ERARomanModuleCategory::ShopOpening
				|| Placement.Category == ERARomanModuleCategory::ApartmentDoor;
			const bool bReplacedAccessibleWall = IsAccessibleInteriorArchetype() && Placement.Category == ERARomanModuleCategory::Wall;
			Component->SetCollisionEnabled(bPassageCategory || bReplacedAccessibleWall ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
			Component->SetCollisionResponseToAllChannels(bPassageCategory || bReplacedAccessibleWall ? ECR_Ignore : ECR_Block);
			Component->SetNumCustomDataFloats(4);
			Component->RegisterComponent();
			GeneratedInstanceComponents.Add(Component);
			if (Rule.bResolvedLocally)
			{
				++LocallyResolvedCategoryCount;
				const FName VariantName = Rule.MaterialVariant.IsNone()
					? FName(*Rule.Material.ToSoftObjectPath().GetAssetName()) : Rule.MaterialVariant;
				ActiveMaterialVariants.AddUnique(VariantName);
			}
			else
			{
				++FallbackCategoryCount;
			}
		}
		FTransform VisualTransform = Placement.Transform;
		VisualTransform.ConcatenateRotation(Rule.ExtraRotation.Quaternion());
		VisualTransform.AddToTranslation(Rule.OffsetCm);
		VisualTransform.SetScale3D(Rule.SizeCm / EngineBasicShapeSizeCm);
		const int32 InstanceIndex = Component->AddInstance(VisualTransform);
		Component->SetCustomDataValue(InstanceIndex, 0, Rule.DebugColor.R, false);
		Component->SetCustomDataValue(InstanceIndex, 1, Rule.DebugColor.G, false);
		Component->SetCustomDataValue(InstanceIndex, 2, Rule.DebugColor.B, false);
		Component->SetCustomDataValue(InstanceIndex, 3, Rule.DebugColor.A, true);
		++GeneratedInstanceCount;
	}
	return bAllMeshesLoaded && GeneratedInstanceCount > 0;
}

bool ARARomanProceduralBuildingActor::IsAccessibleInteriorArchetype() const
{
	return IsPrompt29AccessibleType(BuildingParameters.BuildingType);
}

bool ARARomanProceduralBuildingActor::IsUsingLocalDecorationAssets() const
{
	return bDecorationEnabled && !bForceDecorationFallback
		&& FSoftObjectPath(DecorationMaterialPath(CurrentDecorativeStyle, DecorationVariant)).ResolveObject() != nullptr;
}

bool ARARomanProceduralBuildingActor::BuildAccessibleInterior()
{
	if (!IsAccessibleInteriorArchetype()) return true;
	UStaticMesh* Cube = LoadObject<UStaticMesh>(nullptr, CubePath);
	if (!Cube) return false;

	switch (BuildingParameters.BuildingType)
	{
	case ERARomanBuildingType::PopularHouse:
		CurrentDecorativeStyle = ERAPompeianDecorativeStyle::PlainPlaster;
		CurrentFloorDecoration = ERARomanFloorDecorationType::PackedEarth;
		break;
	case ERARomanBuildingType::DomusMedia:
		CurrentDecorativeStyle = FMath::Abs(DecorationVariant) % 2 == 0 ? ERAPompeianDecorativeStyle::ThirdStyleInspired : ERAPompeianDecorativeStyle::FourthStyleInspired;
		CurrentFloorDecoration = FMath::Abs(DecorationVariant) % 2 == 0 ? ERARomanFloorDecorationType::OpusSigninum : ERARomanFloorDecorationType::GeometricMosaic;
		break;
	case ERARomanBuildingType::Taberna:
		CurrentDecorativeStyle = ERAPompeianDecorativeStyle::PlainPlaster;
		CurrentFloorDecoration = ERARomanFloorDecorationType::BrickFloor;
		break;
	case ERARomanBuildingType::Thermopolium:
		CurrentDecorativeStyle = ERAPompeianDecorativeStyle::FirstStyleInspired;
		CurrentFloorDecoration = ERARomanFloorDecorationType::OpusSigninum;
		break;
	case ERARomanBuildingType::BathComplex:
		CurrentDecorativeStyle = ERAPompeianDecorativeStyle::FirstStyleInspired;
		CurrentFloorDecoration = ERARomanFloorDecorationType::ThermalFloor;
		break;
	default:
		CurrentDecorativeStyle = ERAPompeianDecorativeStyle::ServicePlaster;
		CurrentFloorDecoration = ERARomanFloorDecorationType::ProductiveFloor;
		break;
	}

	AccessibleRoomCount = BuildingParameters.BuildingType == ERARomanBuildingType::BathComplex ? 3 : 2;
	CurrentRoomName = BuildingParameters.BuildingType == ERARomanBuildingType::BathComplex ? TEXT("Apodyterium") : TEXT("Ingresso");
	DecorationPanelCount = 0;
	DecorationFallbackCount = 0;

	auto MakeComponent = [&](const TCHAR* Name, const TCHAR* RequestedMaterial, const TCHAR* FallbackMaterial, const bool bCollision)
	{
		UInstancedStaticMeshComponent* Component = NewObject<UInstancedStaticMeshComponent>(this, FName(Name), RF_Transient);
		Component->SetupAttachment(RootComponent);
		Component->SetStaticMesh(Cube);
		UMaterialInterface* Material = nullptr;
		if (bDecorationEnabled && !bForceDecorationFallback)
		{
			Material = LoadObject<UMaterialInterface>(nullptr, RequestedMaterial);
		}
		if (!Material)
		{
			Material = LoadObject<UMaterialInterface>(nullptr, FallbackMaterial);
			++DecorationFallbackCount;
		}
		if (Material) Component->SetMaterial(0, Material);
		Component->SetMobility(EComponentMobility::Movable);
		Component->SetCollisionEnabled(bCollision ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
		Component->SetCollisionResponseToAllChannels(bCollision ? ECR_Block : ECR_Ignore);
		Component->RegisterComponent();
		InteriorInstanceComponents.Add(Component);
		GeneratedInstanceComponents.Add(Component);
		return Component;
	};
	auto AddBox = [&](UInstancedStaticMeshComponent* Component, const FVector& Location, const FVector& Size, const FRotator& Rotation = FRotator::ZeroRotator)
	{
		const int32 Index = Component->AddInstance(FTransform(Rotation, Location, Size / EngineBasicShapeSizeCm));
		++GeneratedInstanceCount;
		return Index;
	};

	UInstancedStaticMeshComponent* Shell = MakeComponent(
		TEXT("RAAccessibleShell"), TEXT("/Game/LocalAssets/RomaAeterna/Materials/MI_RA_Local_Plaster_Light.MI_RA_Local_Plaster_Light"),
		TEXT("/Game/Technical/Materials/MI_RA_PlasterLight.MI_RA_PlasterLight"), true);
	UInstancedStaticMeshComponent* Floor = MakeComponent(
		TEXT("RAAccessibleFloor"), FloorMaterialPath(CurrentFloorDecoration),
		TEXT("/Game/Technical/Materials/MI_RA_Ground.MI_RA_Ground"), true);
	UInstancedStaticMeshComponent* Painted = MakeComponent(
		TEXT("RAPaintedPanels"), DecorationMaterialPath(CurrentDecorativeStyle, DecorationVariant),
		TEXT("/Game/Technical/Materials/MI_RA_PlasterColor.MI_RA_PlasterColor"), false);
	UInstancedStaticMeshComponent* Frame = MakeComponent(
		TEXT("RADecorationFrames"), TEXT("/Game/LocalAssets/RomaAeterna/Decoration/Materials/MI_RA_Decoration_Frame.MI_RA_Decoration_Frame"),
		TEXT("/Game/Technical/Materials/MI_RA_RoughMasonry.MI_RA_RoughMasonry"), false);
	UInstancedStaticMeshComponent* Roof = MakeComponent(
		TEXT("RAAccessibleRoof"), TEXT("/Game/LocalAssets/RomaAeterna/Materials/MI_RA_Local_Roof_Terracotta.MI_RA_Local_Roof_Terracotta"),
		TEXT("/Game/Technical/Materials/MI_RA_RoofTile.MI_RA_RoofTile"), false);
	RoofInstanceComponents.Add(Roof);

	const float Width = FMath::Clamp(BuildingParameters.WidthCm * 0.75f, 720.f, 1100.f);
	const float Depth = FMath::Clamp(BuildingParameters.DepthCm * 0.48f, 760.f, 1200.f);
	const float Height = FMath::Clamp(BuildingParameters.FloorHeightCm, 290.f, 360.f);
	const float WallThickness = 28.f;
	const float EntranceWidth = BuildingParameters.BuildingType == ERARomanBuildingType::Taberna
		|| BuildingParameters.BuildingType == ERARomanBuildingType::Thermopolium ? 260.f : 180.f;
	const float FrontSegment = (Width - EntranceWidth) * 0.5f;
	AddBox(Shell, FVector(-(EntranceWidth + FrontSegment) * .25f, -Depth * .5f, Height * .5f), FVector(FrontSegment, WallThickness, Height));
	AddBox(Shell, FVector((EntranceWidth + FrontSegment) * .25f, -Depth * .5f, Height * .5f), FVector(FrontSegment, WallThickness, Height));
	AddBox(Shell, FVector(0, -Depth * .5f, Height - 28.f), FVector(EntranceWidth, WallThickness, 56.f));
	AddBox(Shell, FVector(0, Depth * .5f, Height * .5f), FVector(Width, WallThickness, Height));
	AddBox(Shell, FVector(-Width * .5f, 0, Height * .5f), FVector(WallThickness, Depth, Height));
	AddBox(Shell, FVector(Width * .5f, 0, Height * .5f), FVector(WallThickness, Depth, Height));
	const float PassageWidth = 150.f;
	AddBox(Shell, FVector(-(PassageWidth + (Width - PassageWidth) * .5f) * .5f, 0, Height * .5f), FVector((Width - PassageWidth) * .5f, WallThickness, Height));
	AddBox(Shell, FVector((PassageWidth + (Width - PassageWidth) * .5f) * .5f, 0, Height * .5f), FVector((Width - PassageWidth) * .5f, WallThickness, Height));
	AddBox(Shell, FVector(0, 0, Height - 28.f), FVector(PassageWidth, WallThickness, 56.f));

	AddBox(Floor, FVector(0, -Depth * .25f, -2.f), FVector(Width, Depth * .5f, 12.f));
	AddBox(Floor, FVector(0, Depth * .25f, -2.f), FVector(Width, Depth * .5f, 12.f));
	AddBox(Roof, FVector(0, -Depth * .25f, Height + 24.f), FVector(Width + 30.f, Depth * .5f + 20.f, 34.f), FRotator(0, 0, 5.f));
	AddBox(Roof, FVector(0, Depth * .25f, Height + 24.f), FVector(Width + 30.f, Depth * .5f + 20.f, 34.f), FRotator(0, 0, -5.f));
	Roof->SetVisibility(bRoofsVisible, true);

	if (bDecorationEnabled)
	{
		const float PanelZ = Height * .55f;
		const float PanelHeight = Height * .38f;
		const float PanelWidth = FMath::Max(120.f, Width * .22f);
		for (int32 Index = -1; Index <= 1; ++Index)
		{
			AddBox(Painted, FVector(Index * Width * .27f, Depth * .5f - WallThickness, PanelZ), FVector(PanelWidth, 6.f, PanelHeight));
			++DecorationPanelCount;
		}
		AddBox(Frame, FVector(0, Depth * .5f - WallThickness - 2.f, Height * .24f), FVector(Width - 50.f, 8.f, 16.f));
		AddBox(Frame, FVector(0, Depth * .5f - WallThickness - 2.f, Height * .84f), FVector(Width - 50.f, 8.f, 14.f));
		AddBox(Painted, FVector(-Width * .5f + WallThickness, -Depth * .23f, PanelZ), FVector(6.f, Depth * .32f, PanelHeight));
		AddBox(Painted, FVector(Width * .5f - WallThickness, Depth * .23f, PanelZ), FVector(6.f, Depth * .32f, PanelHeight));
		DecorationPanelCount += 2;
	}

	for (int32 LightIndex = 0; LightIndex < AccessibleRoomCount; ++LightIndex)
	{
		UPointLightComponent* Light = NewObject<UPointLightComponent>(this, NAME_None, RF_Transient);
		Light->SetupAttachment(RootComponent);
		Light->SetRelativeLocation(FVector(0, (LightIndex - (AccessibleRoomCount - 1) * .5f) * Depth / AccessibleRoomCount, Height * .72f));
		Light->SetIntensity(350.f);
		Light->SetAttenuationRadius(FMath::Max(Width, Depth) * .65f);
		Light->SetLightColor(FLinearColor(1.f, .76f, .52f));
		Light->SetMobility(EComponentMobility::Movable);
		Light->RegisterComponent();
		InteriorAuxiliaryComponents.Add(Light);
	}
	return AccessibleRoomCount >= 2 && Shell->GetInstanceCount() >= 9 && Floor->GetInstanceCount() == 2;
}

bool ARARomanProceduralBuildingActor::GenerateRoomDecoration()
{
	if (!IsAccessibleInteriorArchetype()) return false;
	ClearRoomDecoration();
	return BuildAccessibleInterior();
}

void ARARomanProceduralBuildingActor::ClearRoomDecoration()
{
	for (UInstancedStaticMeshComponent* Component : InteriorInstanceComponents)
	{
		if (Component)
		{
			GeneratedInstanceCount = FMath::Max(0, GeneratedInstanceCount - Component->GetInstanceCount());
			GeneratedInstanceComponents.Remove(Component);
			Component->ClearInstances();
			Component->DestroyComponent();
		}
	}
	for (UActorComponent* Component : InteriorAuxiliaryComponents) if (Component) Component->DestroyComponent();
	InteriorInstanceComponents.Reset();
	RoofInstanceComponents.Reset();
	InteriorAuxiliaryComponents.Reset();
	AccessibleRoomCount = 0;
	DecorationPanelCount = 0;
	DecorationFallbackCount = 0;
}

bool ARARomanProceduralBuildingActor::RebuildRoomDecoration()
{
	ClearRoomDecoration();
	return BuildAccessibleInterior();
}

void ARARomanProceduralBuildingActor::SetDecorationEnabled(const bool bEnabled)
{
	bDecorationEnabled = bEnabled;
	if (IsAccessibleInteriorArchetype()) RebuildRoomDecoration();
}

void ARARomanProceduralBuildingActor::SetDecorationVariant(const int32 Variant)
{
	DecorationVariant = FMath::Abs(Variant) % 16;
	if (IsAccessibleInteriorArchetype()) RebuildRoomDecoration();
}

void ARARomanProceduralBuildingActor::SetDecorationFallbackEnabled(const bool bFallback)
{
	bForceDecorationFallback = bFallback;
	if (IsAccessibleInteriorArchetype()) RebuildRoomDecoration();
}

void ARARomanProceduralBuildingActor::SetRoofVisibility(const bool bVisible)
{
	bRoofsVisible = bVisible;
	for (UInstancedStaticMeshComponent* Component : RoofInstanceComponents) if (Component) Component->SetVisibility(bVisible, true);
}

FString ARARomanProceduralBuildingActor::GetDecorationSummary() const
{
	return FString::Printf(TEXT("stanze=%d pannelli=%d stile=%d pavimento=%d fallback=%d seed=%d"),
		AccessibleRoomCount, DecorationPanelCount, static_cast<int32>(CurrentDecorativeStyle),
		static_cast<int32>(CurrentFloorDecoration), DecorationFallbackCount,
		BuildingParameters.RandomSeed + DecorationVariant);
}

void ARARomanProceduralBuildingActor::ClearVisualInstances()
{
	ClearRoomDecoration();
	for (TObjectPtr<UInstancedStaticMeshComponent> Component : GeneratedInstanceComponents)
	{
		if (Component) { Component->ClearInstances(); Component->DestroyComponent(); }
	}
	GeneratedInstanceComponents.Empty(); CategoryInstanceComponents.Empty(); GeneratedInstanceCount = 0;
	LocallyResolvedCategoryCount = 0; FallbackCategoryCount = 0; ActiveMaterialVariants.Reset();
}

FString ARARomanProceduralBuildingActor::GetActiveMaterialSummary() const
{
	TArray<FString> Names;
	for (const FName Variant : ActiveMaterialVariants)
	{
		Names.Add(Variant.ToString());
	}
	return Names.Num() > 0 ? FString::Join(Names, TEXT(", ")) : TEXT("solo fallback");
}

int32 ARARomanProceduralBuildingActor::GetInstanceCountByCategory(ERARomanModuleCategory Category) const
{
	const TObjectPtr<UInstancedStaticMeshComponent>* Component = CategoryInstanceComponents.Find(Category);
	return Component && *Component ? (*Component)->GetInstanceCount() : 0;
}

void ARARomanProceduralBuildingActor::DrawRuntimeDebug()
{
	if (!GetWorld()) return;
	if (bShowDebugBounds && LastGenerationResult.Bounds.IsValid) DrawDebugBox(GetWorld(), LastGenerationResult.Bounds.GetCenter(), LastGenerationResult.Bounds.GetExtent(), FColor::Cyan, false, 5.f);
	if (bShowDebugLabels) DrawDebugString(GetWorld(), FVector::ZeroVector, FString::Printf(TEXT("Roma Aeterna: tipo=%d seed=%d moduli=%d warning=%d errori=%d"), static_cast<int32>(BuildingParameters.BuildingType), BuildingParameters.RandomSeed, GeneratedInstanceCount, LastGenerationResult.Warnings.Num(), LastGenerationResult.Errors.Num()), this, FColor::White, 5.f, false);
	if (bShowInteractionPoints)
	{
		for (const FRARomanBuildingInteractionPoint& Point : LastGenerationResult.InteractionPoints)
		{
			DrawDebugSphere(GetWorld(), Point.Position, 24.f, 8, FColor::Emerald, false, 5.f);
		}
	}
	if (bShowUtilityNodes && (LastGenerationResult.UtilityConnectionCount > 0 || LastGenerationResult.WaterFeatureCount > 0))
	{
		DrawDebugDirectionalArrow(GetWorld(), FVector::ZeroVector, FVector(0, 0, 180), 45.f, FColor::Blue, false, 5.f, 0, 8.f);
	}
}

FString ARARomanProceduralBuildingActor::GetGenerationSummary() const
{
	return FString::Printf(TEXT("Successo=%s, Moduli=%d, Istanze=%d, Warning=%d, Errori=%d"), LastGenerationResult.bSuccess?TEXT("true"):TEXT("false"), LastGenerationResult.GeneratedPlacements.Num(), GeneratedInstanceCount, LastGenerationResult.Warnings.Num(), LastGenerationResult.Errors.Num());
}

bool ARARomanProceduralBuildingActor::GenerateBuildingByType(ERARomanBuildingType Type){ BuildingParameters.BuildingType = Type; return GenerateBuilding(); }
bool ARARomanProceduralBuildingActor::GenerateDomusMedia(){ return GenerateBuildingByType(ERARomanBuildingType::DomusMedia); }
bool ARARomanProceduralBuildingActor::GeneratePeristyleDomus(){ return GenerateBuildingByType(ERARomanBuildingType::PeristyleDomus); }
bool ARARomanProceduralBuildingActor::GenerateRichDomus(){ return GenerateBuildingByType(ERARomanBuildingType::RichDomus); }
bool ARARomanProceduralBuildingActor::GeneratePopularHouse(){ return GenerateBuildingByType(ERARomanBuildingType::PopularHouse); }
bool ARARomanProceduralBuildingActor::GenerateInsula(){ return GenerateBuildingByType(ERARomanBuildingType::Insula); }
bool ARARomanProceduralBuildingActor::GenerateCenaculum(){ return GenerateBuildingByType(ERARomanBuildingType::Cenaculum); }
bool ARARomanProceduralBuildingActor::GenerateMixedUseHouse(){ return GenerateBuildingByType(ERARomanBuildingType::MixedUseHouse); }
bool ARARomanProceduralBuildingActor::GenerateTaberna(){ return GenerateBuildingByType(ERARomanBuildingType::Taberna); }
bool ARARomanProceduralBuildingActor::GeneratePopina(){ return GenerateBuildingByType(ERARomanBuildingType::Popina); }
bool ARARomanProceduralBuildingActor::GenerateCaupona(){ return GenerateBuildingByType(ERARomanBuildingType::Caupona); }
bool ARARomanProceduralBuildingActor::GenerateBookshop(){ return GenerateBuildingByType(ERARomanBuildingType::Bookshop); }
bool ARARomanProceduralBuildingActor::GenerateBrothel(){ return GenerateBuildingByType(ERARomanBuildingType::Brothel); }
bool ARARomanProceduralBuildingActor::GenerateMedicalShop(){ return GenerateBuildingByType(ERARomanBuildingType::MedicalShop); }
bool ARARomanProceduralBuildingActor::GenerateBarberShop(){ return GenerateBuildingByType(ERARomanBuildingType::BarberShop); }
bool ARARomanProceduralBuildingActor::GenerateMensaArgentaria(){ return GenerateBuildingByType(ERARomanBuildingType::MensaArgentaria); }
bool ARARomanProceduralBuildingActor::GenerateStabulum(){ return GenerateBuildingByType(ERARomanBuildingType::Stabulum); }
bool ARARomanProceduralBuildingActor::GenerateBathComplex(){return GenerateBuildingByType(ERARomanBuildingType::BathComplex);} bool ARARomanProceduralBuildingActor::GeneratePalaestra(){return GenerateBuildingByType(ERARomanBuildingType::Palaestra);} bool ARARomanProceduralBuildingActor::GenerateCastellumAquae(){return GenerateBuildingByType(ERARomanBuildingType::CastellumAquae);} bool ARARomanProceduralBuildingActor::GenerateAqueductSection(){return GenerateBuildingByType(ERARomanBuildingType::AqueductSection);} bool ARARomanProceduralBuildingActor::GenerateSewerSection(){return GenerateBuildingByType(ERARomanBuildingType::SewerSection);} bool ARARomanProceduralBuildingActor::GeneratePublicFountain(){return GenerateBuildingByType(ERARomanBuildingType::PublicFountain);} bool ARARomanProceduralBuildingActor::GenerateCistern(){return GenerateBuildingByType(ERARomanBuildingType::Cistern);} bool ARARomanProceduralBuildingActor::GenerateWell(){return GenerateBuildingByType(ERARomanBuildingType::Well);} bool ARARomanProceduralBuildingActor::GenerateTinctoria(){return GenerateBuildingByType(ERARomanBuildingType::Tinctoria);} bool ARARomanProceduralBuildingActor::GenerateTannery(){return GenerateBuildingByType(ERARomanBuildingType::Tannery);} bool ARARomanProceduralBuildingActor::GenerateTextileWorkshop(){return GenerateBuildingByType(ERARomanBuildingType::TextileWorkshop);} bool ARARomanProceduralBuildingActor::GenerateMetalWorkshop(){return GenerateBuildingByType(ERARomanBuildingType::MetalWorkshop);} bool ARARomanProceduralBuildingActor::GeneratePotteryWorkshop(){return GenerateBuildingByType(ERARomanBuildingType::PotteryWorkshop);} bool ARARomanProceduralBuildingActor::GenerateOilWorkshop(){return GenerateBuildingByType(ERARomanBuildingType::OilWorkshop);} bool ARARomanProceduralBuildingActor::GenerateWinery(){return GenerateBuildingByType(ERARomanBuildingType::Winery);} bool ARARomanProceduralBuildingActor::GeneratePressingWorkshop(){return GenerateBuildingByType(ERARomanBuildingType::PressingWorkshop);} bool ARARomanProceduralBuildingActor::GenerateStandaloneOven(){return GenerateBuildingByType(ERARomanBuildingType::StandaloneOven);} bool ARARomanProceduralBuildingActor::GenerateHorrea(){return GenerateBuildingByType(ERARomanBuildingType::Horrea);} bool ARARomanProceduralBuildingActor::GenerateUrbanGarden(){return GenerateBuildingByType(ERARomanBuildingType::UrbanGarden);} bool ARARomanProceduralBuildingActor::GenerateServiceYard(){return GenerateBuildingByType(ERARomanBuildingType::ServiceYard);}
bool ARARomanProceduralBuildingActor::GenerateAtriumDomus(){ return GenerateBuildingByType(ERARomanBuildingType::AtriumDomus); }
bool ARARomanProceduralBuildingActor::GenerateThermopolium(){ return GenerateBuildingByType(ERARomanBuildingType::Thermopolium); }
bool ARARomanProceduralBuildingActor::GenerateFullonica(){ return GenerateBuildingByType(ERARomanBuildingType::Fullonica); }
bool ARARomanProceduralBuildingActor::GeneratePistrinum(){ return GenerateBuildingByType(ERARomanBuildingType::Pistrinum); }
bool ARARomanProceduralBuildingActor::GeneratePublicLatrine(){ return GenerateBuildingByType(ERARomanBuildingType::PublicLatrine); }
bool ARARomanProceduralBuildingActor::GenerateSmallTemple(){ return GenerateBuildingByType(ERARomanBuildingType::SmallTemple); }
FString ARARomanProceduralBuildingActor::GetBuildingPlanSummary() const { return GetGenerationSummary(); }
TArray<ERARomanBuildingType> ARARomanProceduralBuildingActor::GetImplementedArchetypes() const { return URARomanBuildingRuleLibrary::GetImplementedArchetypes(); }
bool ARARomanProceduralBuildingActor::IsArchetypeImplemented(ERARomanBuildingType Type) const { return URARomanBuildingRuleLibrary::IsArchetypeImplemented(Type); }
