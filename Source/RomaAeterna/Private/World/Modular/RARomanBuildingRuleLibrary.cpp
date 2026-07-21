#include "World/Modular/RARomanBuildingRuleLibrary.h"

#include "RARomanModularCore.h"

namespace
{
using namespace RomaAeternaCore;

BuildingType ToCoreBuildingType(ERARomanBuildingType Type)
{
	switch (Type)
	{
	case ERARomanBuildingType::AtriumDomus: return BuildingType::AtriumDomus;
	case ERARomanBuildingType::Thermopolium: return BuildingType::Thermopolium;
	case ERARomanBuildingType::Fullonica: return BuildingType::Fullonica;
	case ERARomanBuildingType::Pistrinum: return BuildingType::Pistrinum;
	case ERARomanBuildingType::PublicLatrine: return BuildingType::PublicLatrine;
	case ERARomanBuildingType::SmallTemple: return BuildingType::SmallTemple;
	case ERARomanBuildingType::Taberna: return BuildingType::Taberna;
	case ERARomanBuildingType::Domus: return BuildingType::Domus;
	case ERARomanBuildingType::Insula: return BuildingType::Insula;
	case ERARomanBuildingType::Temple: return BuildingType::Temple;
	case ERARomanBuildingType::Basilica: return BuildingType::Basilica;
	case ERARomanBuildingType::Portico: return BuildingType::Portico;
	case ERARomanBuildingType::AdministrativeBuilding: return BuildingType::AdministrativeBuilding;
	case ERARomanBuildingType::StreetSection: return BuildingType::StreetSection;
	case ERARomanBuildingType::Plaza: return BuildingType::Plaza;
	case ERARomanBuildingType::ForumSection: return BuildingType::ForumSection;
	case ERARomanBuildingType::SimpleHouse:
	default: return BuildingType::SimpleHouse;
	}
}

ERARomanBuildingType FromCoreBuildingType(BuildingType Type)
{
	switch (Type)
	{
	case BuildingType::AtriumDomus: return ERARomanBuildingType::AtriumDomus;
	case BuildingType::Thermopolium: return ERARomanBuildingType::Thermopolium;
	case BuildingType::Fullonica: return ERARomanBuildingType::Fullonica;
	case BuildingType::Pistrinum: return ERARomanBuildingType::Pistrinum;
	case BuildingType::PublicLatrine: return ERARomanBuildingType::PublicLatrine;
	case BuildingType::SmallTemple: return ERARomanBuildingType::SmallTemple;
	case BuildingType::Taberna: return ERARomanBuildingType::Taberna;
	case BuildingType::Domus: return ERARomanBuildingType::Domus;
	case BuildingType::Insula: return ERARomanBuildingType::Insula;
	case BuildingType::Temple: return ERARomanBuildingType::Temple;
	case BuildingType::Basilica: return ERARomanBuildingType::Basilica;
	case BuildingType::Portico: return ERARomanBuildingType::Portico;
	case BuildingType::AdministrativeBuilding: return ERARomanBuildingType::AdministrativeBuilding;
	case BuildingType::StreetSection: return ERARomanBuildingType::StreetSection;
	case BuildingType::Plaza: return ERARomanBuildingType::Plaza;
	case BuildingType::ForumSection: return ERARomanBuildingType::ForumSection;
	case BuildingType::SimpleHouse:
	default: return ERARomanBuildingType::SimpleHouse;
	}
}

RoofType ToCoreRoofType(ERARomanRoofType Type)
{
	switch (Type)
	{
	case ERARomanRoofType::Flat: return RoofType::Flat;
	case ERARomanRoofType::SingleSlope: return RoofType::SingleSlope;
	case ERARomanRoofType::Portico: return RoofType::Portico;
	case ERARomanRoofType::Compluvium: return RoofType::Compluvium;
	case ERARomanRoofType::Monumental: return RoofType::Monumental;
	case ERARomanRoofType::DoubleSlope:
	default: return RoofType::DoubleSlope;
	}
}

ERARomanRoofType FromCoreRoofType(RoofType Type)
{
	switch (Type)
	{
	case RoofType::Flat: return ERARomanRoofType::Flat;
	case RoofType::SingleSlope: return ERARomanRoofType::SingleSlope;
	case RoofType::Portico: return ERARomanRoofType::Portico;
	case RoofType::Compluvium: return ERARomanRoofType::Compluvium;
	case RoofType::Monumental: return ERARomanRoofType::Monumental;
	case RoofType::DoubleSlope:
	default: return ERARomanRoofType::DoubleSlope;
	}
}

ArchitecturalOrder ToCoreOrder(ERARomanArchitecturalOrder Order)
{
	switch (Order)
	{
	case ERARomanArchitecturalOrder::Tuscan: return ArchitecturalOrder::Tuscan;
	case ERARomanArchitecturalOrder::Doric: return ArchitecturalOrder::Doric;
	case ERARomanArchitecturalOrder::Ionic: return ArchitecturalOrder::Ionic;
	case ERARomanArchitecturalOrder::Corinthian: return ArchitecturalOrder::Corinthian;
	case ERARomanArchitecturalOrder::Composite: return ArchitecturalOrder::Composite;
	case ERARomanArchitecturalOrder::None:
	default: return ArchitecturalOrder::None;
	}
}

ERARomanArchitecturalOrder FromCoreOrder(ArchitecturalOrder Order)
{
	switch (Order)
	{
	case ArchitecturalOrder::Tuscan: return ERARomanArchitecturalOrder::Tuscan;
	case ArchitecturalOrder::Doric: return ERARomanArchitecturalOrder::Doric;
	case ArchitecturalOrder::Ionic: return ERARomanArchitecturalOrder::Ionic;
	case ArchitecturalOrder::Corinthian: return ERARomanArchitecturalOrder::Corinthian;
	case ArchitecturalOrder::Composite: return ERARomanArchitecturalOrder::Composite;
	case ArchitecturalOrder::None:
	default: return ERARomanArchitecturalOrder::None;
	}
}


ERARomanModuleCategory FromCoreModuleCategory(RomaAeternaCore::ModuleCategory Category)
{
	switch (Category)
	{
	case RomaAeternaCore::ModuleCategory::Door: return ERARomanModuleCategory::Door;
	case RomaAeternaCore::ModuleCategory::Window: return ERARomanModuleCategory::Window;
	case RomaAeternaCore::ModuleCategory::Corner: return ERARomanModuleCategory::Corner;
	case RomaAeternaCore::ModuleCategory::Column: return ERARomanModuleCategory::Column;
	case RomaAeternaCore::ModuleCategory::Capital: return ERARomanModuleCategory::Capital;
	case RomaAeternaCore::ModuleCategory::Base: return ERARomanModuleCategory::Base;
	case RomaAeternaCore::ModuleCategory::Arch: return ERARomanModuleCategory::Arch;
	case RomaAeternaCore::ModuleCategory::Beam: return ERARomanModuleCategory::Beam;
	case RomaAeternaCore::ModuleCategory::Floor: return ERARomanModuleCategory::Floor;
	case RomaAeternaCore::ModuleCategory::Roof: return ERARomanModuleCategory::Roof;
	case RomaAeternaCore::ModuleCategory::Stair: return ERARomanModuleCategory::Stair;
	case RomaAeternaCore::ModuleCategory::Podium: return ERARomanModuleCategory::Podium;
	case RomaAeternaCore::ModuleCategory::Portico: return ERARomanModuleCategory::Portico;
	case RomaAeternaCore::ModuleCategory::Prop: return ERARomanModuleCategory::Prop;
	case RomaAeternaCore::ModuleCategory::Vegetation: return ERARomanModuleCategory::Vegetation;
	case RomaAeternaCore::ModuleCategory::Decoration: return ERARomanModuleCategory::Decoration;
	case RomaAeternaCore::ModuleCategory::Counter: return ERARomanModuleCategory::Counter;
	case RomaAeternaCore::ModuleCategory::Dolium: return ERARomanModuleCategory::Dolium;
	case RomaAeternaCore::ModuleCategory::Basin: return ERARomanModuleCategory::Basin;
	case RomaAeternaCore::ModuleCategory::WaterChannel: return ERARomanModuleCategory::WaterChannel;
	case RomaAeternaCore::ModuleCategory::Millstone: return ERARomanModuleCategory::Millstone;
	case RomaAeternaCore::ModuleCategory::Oven: return ERARomanModuleCategory::Oven;
	case RomaAeternaCore::ModuleCategory::Furnace: return ERARomanModuleCategory::Furnace;
	case RomaAeternaCore::ModuleCategory::LatrineSeat: return ERARomanModuleCategory::LatrineSeat;
	case RomaAeternaCore::ModuleCategory::Drain: return ERARomanModuleCategory::Drain;
	case RomaAeternaCore::ModuleCategory::Altar: return ERARomanModuleCategory::Altar;
	case RomaAeternaCore::ModuleCategory::StatueMarker: return ERARomanModuleCategory::StatueMarker;
	case RomaAeternaCore::ModuleCategory::Shelf: return ERARomanModuleCategory::Shelf;
	case RomaAeternaCore::ModuleCategory::StorageContainer: return ERARomanModuleCategory::StorageContainer;
	case RomaAeternaCore::ModuleCategory::GardenFeature: return ERARomanModuleCategory::GardenFeature;
	case RomaAeternaCore::ModuleCategory::DryingRack: return ERARomanModuleCategory::DryingRack;
	case RomaAeternaCore::ModuleCategory::WorkPlatform: return ERARomanModuleCategory::WorkPlatform;
	case RomaAeternaCore::ModuleCategory::RotationArm: return ERARomanModuleCategory::RotationArm;
	case RomaAeternaCore::ModuleCategory::ServiceBasin: return ERARomanModuleCategory::ServiceBasin;
	case RomaAeternaCore::ModuleCategory::InteractionMarker: return ERARomanModuleCategory::InteractionMarker;
	case RomaAeternaCore::ModuleCategory::Wall:
	default: return ERARomanModuleCategory::Wall;
	}
}

BuildingParameters ToCoreParameters(const FRARomanBuildingParameters& Parameters)
{
	BuildingParameters Core;
	Core.Type = ToCoreBuildingType(Parameters.BuildingType);
	Core.WidthCm = Parameters.WidthCm;
	Core.DepthCm = Parameters.DepthCm;
	Core.FloorCount = Parameters.FloorCount;
	Core.BayCount = Parameters.BayCount;
	Core.FloorHeightCm = Parameters.FloorHeightCm;
	Core.WallThicknessCm = Parameters.WallThicknessCm;
	Core.DoorCount = Parameters.DoorCount;
	Core.WindowCount = Parameters.WindowCount;
	Core.Roof = ToCoreRoofType(Parameters.RoofType);
	Core.Order = ToCoreOrder(Parameters.ArchitecturalOrder);
	Core.RandomSeed = Parameters.RandomSeed;
	Core.MaximumModuleCount = Parameters.MaximumModuleCount;
	Core.HasUpperFloor = Parameters.bHasUpperFloor;
	Core.HasCourtyard = Parameters.bHasCourtyard;
	Core.HasWater = Parameters.bHasWater;
	Core.HasDrainage = Parameters.bHasDrainage;
	Core.HasFireArea = Parameters.bHasFireArea;
	Core.HasServiceAccess = Parameters.bHasServiceAccess;
	Core.HasCustomerArea = Parameters.bHasCustomerArea;
	Core.HasProductionArea = Parameters.bHasProductionArea;
	Core.HasStorage = Parameters.bHasStorage;
	Core.MaximumRoomCount = Parameters.MaximumRoomCount;
	Core.HasPeristyle = Parameters.bHasPeristyle;
	return Core;
}

FRARomanBuildingParameters FromCoreParameters(const BuildingParameters& Core, const FRARomanBuildingParameters& Original)
{
	FRARomanBuildingParameters Parameters = Original;
	Parameters.BuildingType = FromCoreBuildingType(Core.Type);
	Parameters.WidthCm = static_cast<float>(Core.WidthCm);
	Parameters.DepthCm = static_cast<float>(Core.DepthCm);
	Parameters.FloorCount = Core.FloorCount;
	Parameters.BayCount = Core.BayCount;
	Parameters.FloorHeightCm = static_cast<float>(Core.FloorHeightCm);
	Parameters.WallThicknessCm = static_cast<float>(Core.WallThicknessCm);
	Parameters.DoorCount = Core.DoorCount;
	Parameters.WindowCount = Core.WindowCount;
	Parameters.RoofType = FromCoreRoofType(Core.Roof);
	Parameters.ArchitecturalOrder = FromCoreOrder(Core.Order);
	Parameters.RandomSeed = Core.RandomSeed;
	Parameters.MaximumModuleCount = Core.MaximumModuleCount;
	return Parameters;
}

FRARomanGenerationMessage FromCoreMessage(const GenerationMessage& Message)
{
	FRARomanGenerationMessage Result;
	Result.Code = FName(UTF8_TO_TCHAR(Message.Code.c_str()));
	Result.Message = UTF8_TO_TCHAR(Message.Message.c_str());
	Result.bIsError = Message.bIsError;
	return Result;
}

FRARomanGenerationResult FromCoreResult(const GenerationResult& Core)
{
	FRARomanGenerationResult Result;
	Result.bSuccess = Core.bSuccess;
	Result.EstimatedModuleCount = Core.EstimatedModuleCount;
	Result.EstimatedTriangleBudget = Core.EstimatedTriangleBudget;
	Result.GeneratedRoomCount = static_cast<int32>(Core.Placements.size());
	Result.GeneratedZoneCount = 0;
	Result.ProductionDeviceCount = 0;
	Result.WaterFeatureCount = 0;
	Result.Bounds = FBox(
		FVector(Core.BuildingBounds.Min.X, Core.BuildingBounds.Min.Y, Core.BuildingBounds.Min.Z),
		FVector(Core.BuildingBounds.Max.X, Core.BuildingBounds.Max.Y, Core.BuildingBounds.Max.Z));
	for (const GenerationMessage& Warning : Core.Warnings)
	{
		Result.Warnings.Add(FromCoreMessage(Warning));
	}
	for (const GenerationMessage& Error : Core.Errors)
	{
		Result.Errors.Add(FromCoreMessage(Error));
	}
	for (const ModulePlacement& Placement : Core.Placements)
	{
		FRARomanModulePlacement UnrealPlacement;
		UnrealPlacement.ModuleId = FName(UTF8_TO_TCHAR(Placement.ModuleId.c_str()));
		UnrealPlacement.Category = FromCoreModuleCategory(Placement.Category);
		UnrealPlacement.Transform = FTransform(
			FRotator(Placement.TransformValue.RotationDegrees.X, Placement.TransformValue.RotationDegrees.Y, Placement.TransformValue.RotationDegrees.Z),
			FVector(Placement.TransformValue.Location.X, Placement.TransformValue.Location.Y, Placement.TransformValue.Location.Z),
			FVector(Placement.TransformValue.Scale.X, Placement.TransformValue.Scale.Y, Placement.TransformValue.Scale.Z));
		UnrealPlacement.FloorIndex = Placement.FloorIndex;
		UnrealPlacement.BayIndex = Placement.BayIndex;
		UnrealPlacement.bMirrored = Placement.bMirrored;
		for (const std::string& Tag : Placement.Tags)
		{
			UnrealPlacement.PlacementTags.Add(FName(UTF8_TO_TCHAR(Tag.c_str())));
		}
		Result.GeneratedPlacements.Add(UnrealPlacement);
	}
	return Result;
}
} // namespace

bool URARomanBuildingRuleLibrary::ValidateBuildingParameters(const FRARomanBuildingParameters& Parameters, TArray<FRARomanGenerationMessage>& OutWarnings, TArray<FRARomanGenerationMessage>& OutErrors)
{
	std::vector<GenerationMessage> CoreWarnings;
	std::vector<GenerationMessage> CoreErrors;
	const bool bValid = RomaAeternaCore::ValidateBuildingParameters(ToCoreParameters(Parameters), CoreWarnings, CoreErrors);
	for (const GenerationMessage& Warning : CoreWarnings)
	{
		OutWarnings.Add(FromCoreMessage(Warning));
	}
	for (const GenerationMessage& Error : CoreErrors)
	{
		OutErrors.Add(FromCoreMessage(Error));
	}
	return bValid;
}

FRARomanBuildingParameters URARomanBuildingRuleLibrary::NormalizeBuildingParameters(const FRARomanBuildingParameters& Parameters)
{
	return FromCoreParameters(RomaAeternaCore::NormalizeBuildingParameters(ToCoreParameters(Parameters)), Parameters);
}

float URARomanBuildingRuleLibrary::CalculateBayWidth(const FRARomanBuildingParameters& Parameters)
{
	return static_cast<float>(RomaAeternaCore::CalculateBayWidth(ToCoreParameters(Parameters)));
}

float URARomanBuildingRuleLibrary::CalculateFloorHeight(const FRARomanBuildingParameters& Parameters)
{
	return static_cast<float>(RomaAeternaCore::CalculateFloorHeight(ToCoreParameters(Parameters)));
}

FBox URARomanBuildingRuleLibrary::CalculateBuildingBounds(const FRARomanBuildingParameters& Parameters)
{
	const Bounds CoreBounds = RomaAeternaCore::CalculateBuildingBounds(ToCoreParameters(Parameters));
	return FBox(FVector(CoreBounds.Min.X, CoreBounds.Min.Y, CoreBounds.Min.Z), FVector(CoreBounds.Max.X, CoreBounds.Max.Y, CoreBounds.Max.Z));
}

int32 URARomanBuildingRuleLibrary::EstimateRequiredModules(const FRARomanBuildingParameters& Parameters)
{
	return RomaAeternaCore::EstimateRequiredModules(ToCoreParameters(Parameters));
}

bool URARomanBuildingRuleLibrary::IsModuleCompatible(const FRARomanModuleDefinition& Module, const FRARomanBuildingParameters& Parameters, const TArray<FName>& RequiredTags)
{
	if (Module.ModuleId.IsNone() || Module.Dimensions.WidthCm <= 0.0f || Module.Dimensions.GridSizeCm <= 0.0f)
	{
		return false;
	}
	for (FName Tag : RequiredTags)
	{
		if (!Module.Tags.Contains(Tag))
		{
			return false;
		}
	}
	return Parameters.BuildingType != ERARomanBuildingType::Temple || Module.Category != ERARomanModuleCategory::Window;
}

TArray<FRARomanModuleDefinition> URARomanBuildingRuleLibrary::SelectCompatibleModules(const URARomanModuleCatalog* Catalog, const FRARomanBuildingParameters& Parameters, ERARomanModuleCategory Category, const TArray<FName>& RequiredTags, TArray<FRARomanGenerationMessage>& OutWarnings)
{
	TArray<FRARomanModuleDefinition> Result;
	if (!Catalog)
	{
		FRARomanGenerationMessage Warning;
		Warning.Code = "NullCatalog";
		Warning.Message = TEXT("Catalogo nullo: layout astratto senza asset reali.");
		Warning.bIsError = false;
		OutWarnings.Add(Warning);
		return Result;
	}
	for (const FRARomanModuleDefinition& Module : Catalog->Modules)
	{
		if (Module.Category == Category && IsModuleCompatible(Module, Parameters, RequiredTags))
		{
			Result.Add(Module);
		}
	}
	return Result;
}

FTransform URARomanBuildingRuleLibrary::CalculateGridAlignedTransform(const FVector& Location, const FRotator& Rotation, const FVector& Scale, float GridSizeCm, float RotationStepDegrees)
{
	const Transform CoreTransform = RomaAeternaCore::CalculateGridAlignedTransform(
		{Location.X, Location.Y, Location.Z},
		{Rotation.Pitch, Rotation.Yaw, Rotation.Roll},
		{Scale.X, Scale.Y, Scale.Z},
		GridSizeCm,
		RotationStepDegrees);
	return FTransform(
		FRotator(CoreTransform.RotationDegrees.X, CoreTransform.RotationDegrees.Y, CoreTransform.RotationDegrees.Z),
		FVector(CoreTransform.Location.X, CoreTransform.Location.Y, CoreTransform.Location.Z),
		FVector(CoreTransform.Scale.X, CoreTransform.Scale.Y, CoreTransform.Scale.Z));
}

FRARomanGenerationResult URARomanBuildingRuleLibrary::BuildSimpleHouseLayout(const FRARomanBuildingParameters& Parameters)
{
	return FromCoreResult(RomaAeternaCore::BuildSimpleHouseLayout(ToCoreParameters(Parameters)));
}

FRARomanGenerationResult URARomanBuildingRuleLibrary::BuildTabernaLayout(const FRARomanBuildingParameters& Parameters)
{
	return FromCoreResult(RomaAeternaCore::BuildTabernaLayout(ToCoreParameters(Parameters)));
}

FRARomanGenerationResult URARomanBuildingRuleLibrary::BuildTempleLayout(const FRARomanBuildingParameters& Parameters)
{
	return FromCoreResult(RomaAeternaCore::BuildTempleLayout(ToCoreParameters(Parameters)));
}

FRARomanGenerationResult URARomanBuildingRuleLibrary::BuildStreetSectionLayout(const FRARomanBuildingParameters& Parameters)
{
	return FromCoreResult(RomaAeternaCore::BuildStreetSectionLayout(ToCoreParameters(Parameters)));
}

FRARomanGenerationResult URARomanBuildingRuleLibrary::GenerateBuildingByType(const FRARomanBuildingParameters& Parameters){ return FromCoreResult(RomaAeternaCore::BuildPlanLayout(ToCoreParameters(Parameters), ToCoreBuildingType(Parameters.BuildingType))); }
FRARomanGenerationResult URARomanBuildingRuleLibrary::GenerateAtriumDomusPlan(const FRARomanBuildingParameters& Parameters){ return FromCoreResult(RomaAeternaCore::GenerateAtriumDomusLayout(ToCoreParameters(Parameters))); }
FRARomanGenerationResult URARomanBuildingRuleLibrary::GenerateThermopoliumPlan(const FRARomanBuildingParameters& Parameters){ return FromCoreResult(RomaAeternaCore::GenerateThermopoliumLayout(ToCoreParameters(Parameters))); }
FRARomanGenerationResult URARomanBuildingRuleLibrary::GenerateFullonicaPlan(const FRARomanBuildingParameters& Parameters){ return FromCoreResult(RomaAeternaCore::GenerateFullonicaLayout(ToCoreParameters(Parameters))); }
FRARomanGenerationResult URARomanBuildingRuleLibrary::GeneratePistrinumPlan(const FRARomanBuildingParameters& Parameters){ return FromCoreResult(RomaAeternaCore::GeneratePistrinumLayout(ToCoreParameters(Parameters))); }
FRARomanGenerationResult URARomanBuildingRuleLibrary::GeneratePublicLatrinePlan(const FRARomanBuildingParameters& Parameters){ return FromCoreResult(RomaAeternaCore::GeneratePublicLatrineLayout(ToCoreParameters(Parameters))); }
FRARomanGenerationResult URARomanBuildingRuleLibrary::GenerateSmallTemplePlan(const FRARomanBuildingParameters& Parameters){ return FromCoreResult(RomaAeternaCore::GenerateSmallTempleLayout(ToCoreParameters(Parameters))); }
bool URARomanBuildingRuleLibrary::IsArchetypeImplemented(ERARomanBuildingType Type){ return RomaAeternaCore::IsArchetypeImplemented(ToCoreBuildingType(Type)); }
TArray<ERARomanBuildingType> URARomanBuildingRuleLibrary::GetImplementedArchetypes(){ TArray<ERARomanBuildingType> R; for(RomaAeternaCore::BuildingType T: RomaAeternaCore::GetImplementedArchetypes()){ R.Add(FromCoreBuildingType(T)); } return R; }
