#include "World/Modular/RARomanProceduralBuildingActor.h"

#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"

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
	if (bGenerateOnBeginPlay) { GenerateBuilding(); }
}

void ARARomanProceduralBuildingActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (bAutoRebuildInEditor && !GetWorld()->IsGameWorld()) { GenerateBuilding(); }
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
			const float Bay = FMath::Max(Parameters.WidthCm / FMath::Max(1, Parameters.BayCount), 25.f);
			if (Category == ERARomanModuleCategory::Wall || Category == ERARomanModuleCategory::Beam) Rule.SizeCm.X = Bay;
			if (Category == ERARomanModuleCategory::Wall || Category == ERARomanModuleCategory::Column || Category == ERARomanModuleCategory::Corner) Rule.SizeCm.Z = Parameters.FloorHeightCm;
			if (Category == ERARomanModuleCategory::Floor || Category == ERARomanModuleCategory::Roof || Category == ERARomanModuleCategory::Podium) Rule.SizeCm = FVector(FMath::Min(Parameters.WidthCm, Bay * 2.f), FMath::Min(Parameters.DepthCm, Bay * 2.f), Rule.SizeCm.Z);
			return Rule;
		}
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

	switch (BuildingParameters.BuildingType)
	{
	case ERARomanBuildingType::AtriumDomus: NewResult = URARomanBuildingRuleLibrary::GenerateAtriumDomusPlan(BuildingParameters); break;
	case ERARomanBuildingType::Thermopolium: NewResult = URARomanBuildingRuleLibrary::GenerateThermopoliumPlan(BuildingParameters); break;
	case ERARomanBuildingType::Fullonica: NewResult = URARomanBuildingRuleLibrary::GenerateFullonicaPlan(BuildingParameters); break;
	case ERARomanBuildingType::Pistrinum: NewResult = URARomanBuildingRuleLibrary::GeneratePistrinumPlan(BuildingParameters); break;
	case ERARomanBuildingType::PublicLatrine: NewResult = URARomanBuildingRuleLibrary::GeneratePublicLatrinePlan(BuildingParameters); break;
	case ERARomanBuildingType::SmallTemple: NewResult = URARomanBuildingRuleLibrary::GenerateSmallTemplePlan(BuildingParameters); break;
	case ERARomanBuildingType::DomusMedia: NewResult = URARomanBuildingRuleLibrary::GenerateBuildingByType(BuildingParameters); break;
	case ERARomanBuildingType::Taberna: NewResult = URARomanBuildingRuleLibrary::GenerateTabernaPlan(BuildingParameters); break;
	case ERARomanBuildingType::Temple: NewResult = URARomanBuildingRuleLibrary::BuildTempleLayout(BuildingParameters); break;
	case ERARomanBuildingType::StreetSection: NewResult = URARomanBuildingRuleLibrary::BuildStreetSectionLayout(BuildingParameters); break;
	default: NewResult = URARomanBuildingRuleLibrary::BuildSimpleHouseLayout(BuildingParameters); break;
	}
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
	DrawRuntimeDebug();
	return bBuilt;
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
			Component->SetMobility(EComponentMobility::Movable);
			Component->SetNumCustomDataFloats(4);
			Component->RegisterComponent();
			GeneratedInstanceComponents.Add(Component);
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

void ARARomanProceduralBuildingActor::ClearVisualInstances()
{
	for (TObjectPtr<UInstancedStaticMeshComponent> Component : GeneratedInstanceComponents)
	{
		if (Component) { Component->ClearInstances(); Component->DestroyComponent(); }
	}
	GeneratedInstanceComponents.Empty(); CategoryInstanceComponents.Empty(); GeneratedInstanceCount = 0;
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
bool ARARomanProceduralBuildingActor::GenerateAtriumDomus(){ return GenerateBuildingByType(ERARomanBuildingType::AtriumDomus); }
bool ARARomanProceduralBuildingActor::GenerateThermopolium(){ return GenerateBuildingByType(ERARomanBuildingType::Thermopolium); }
bool ARARomanProceduralBuildingActor::GenerateFullonica(){ return GenerateBuildingByType(ERARomanBuildingType::Fullonica); }
bool ARARomanProceduralBuildingActor::GeneratePistrinum(){ return GenerateBuildingByType(ERARomanBuildingType::Pistrinum); }
bool ARARomanProceduralBuildingActor::GeneratePublicLatrine(){ return GenerateBuildingByType(ERARomanBuildingType::PublicLatrine); }
bool ARARomanProceduralBuildingActor::GenerateSmallTemple(){ return GenerateBuildingByType(ERARomanBuildingType::SmallTemple); }
FString ARARomanProceduralBuildingActor::GetBuildingPlanSummary() const { return GetGenerationSummary(); }
TArray<ERARomanBuildingType> ARARomanProceduralBuildingActor::GetImplementedArchetypes() const { return URARomanBuildingRuleLibrary::GetImplementedArchetypes(); }
bool ARARomanProceduralBuildingActor::IsArchetypeImplemented(ERARomanBuildingType Type) const { return URARomanBuildingRuleLibrary::IsArchetypeImplemented(Type); }
