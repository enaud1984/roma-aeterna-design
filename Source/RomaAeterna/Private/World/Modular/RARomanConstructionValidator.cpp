#include "World/Modular/RARomanConstructionValidator.h"

#include "RARomanModularCore.h"

namespace
{
FRARomanGenerationMessage MakeValidatorMessage(FName Code, const FString& Message, bool bIsError)
{
	FRARomanGenerationMessage Result;
	Result.Code = Code;
	Result.Message = Message;
	Result.bIsError = bIsError;
	return Result;
}

FRARomanGenerationMessage FromCoreValidatorMessage(const RomaAeternaCore::GenerationMessage& Message)
{
	return MakeValidatorMessage(FName(UTF8_TO_TCHAR(Message.Code.c_str())), UTF8_TO_TCHAR(Message.Message.c_str()), Message.bIsError);
}

RomaAeternaCore::ModuleCategory ToCoreCategory(ERARomanModuleCategory Category)
{
	switch (Category)
	{
	case ERARomanModuleCategory::Door: return RomaAeternaCore::ModuleCategory::Door;
	case ERARomanModuleCategory::Window: return RomaAeternaCore::ModuleCategory::Window;
	case ERARomanModuleCategory::Corner: return RomaAeternaCore::ModuleCategory::Corner;
	case ERARomanModuleCategory::Column: return RomaAeternaCore::ModuleCategory::Column;
	case ERARomanModuleCategory::Capital: return RomaAeternaCore::ModuleCategory::Capital;
	case ERARomanModuleCategory::Base: return RomaAeternaCore::ModuleCategory::Base;
	case ERARomanModuleCategory::Arch: return RomaAeternaCore::ModuleCategory::Arch;
	case ERARomanModuleCategory::Beam: return RomaAeternaCore::ModuleCategory::Beam;
	case ERARomanModuleCategory::Floor: return RomaAeternaCore::ModuleCategory::Floor;
	case ERARomanModuleCategory::Roof: return RomaAeternaCore::ModuleCategory::Roof;
	case ERARomanModuleCategory::Stair: return RomaAeternaCore::ModuleCategory::Stair;
	case ERARomanModuleCategory::Podium: return RomaAeternaCore::ModuleCategory::Podium;
	case ERARomanModuleCategory::Portico: return RomaAeternaCore::ModuleCategory::Portico;
	case ERARomanModuleCategory::Prop: return RomaAeternaCore::ModuleCategory::Prop;
	case ERARomanModuleCategory::Vegetation: return RomaAeternaCore::ModuleCategory::Vegetation;
	case ERARomanModuleCategory::Decoration: return RomaAeternaCore::ModuleCategory::Decoration;
	case ERARomanModuleCategory::Wall:
	default: return RomaAeternaCore::ModuleCategory::Wall;
	}
}

RomaAeternaCore::ModulePlacement ToCorePlacement(const FRARomanModulePlacement& Placement)
{
	RomaAeternaCore::ModulePlacement Core;
	Core.ModuleId = TCHAR_TO_UTF8(*Placement.ModuleId.ToString());
	Core.Category = ToCoreCategory(Placement.Category);
	Core.FloorIndex = Placement.FloorIndex;
	Core.BayIndex = Placement.BayIndex;
	Core.bMirrored = Placement.bMirrored;
	const FVector Location = Placement.Transform.GetLocation();
	const FRotator Rotation = Placement.Transform.Rotator();
	const FVector Scale = Placement.Transform.GetScale3D();
	Core.TransformValue.Location = {Location.X, Location.Y, Location.Z};
	Core.TransformValue.RotationDegrees = {Rotation.Pitch, Rotation.Yaw, Rotation.Roll};
	Core.TransformValue.Scale = {Scale.X, Scale.Y, Scale.Z};
	for (FName Tag : Placement.PlacementTags)
	{
		Core.Tags.push_back(TCHAR_TO_UTF8(*Tag.ToString()));
	}
	return Core;
}
} // namespace

bool URARomanConstructionValidator::ValidateParameters(const FRARomanBuildingParameters& Parameters, TArray<FRARomanGenerationMessage>& OutWarnings, TArray<FRARomanGenerationMessage>& OutErrors)
{
	return URARomanBuildingRuleLibrary::ValidateBuildingParameters(Parameters, OutWarnings, OutErrors);
}

bool URARomanConstructionValidator::ValidateCatalog(const URARomanModuleCatalog* Catalog, TArray<FRARomanGenerationMessage>& OutWarnings, TArray<FRARomanGenerationMessage>& OutErrors)
{
	if (!Catalog)
	{
		OutWarnings.Add(MakeValidatorMessage("NullCatalog", TEXT("Catalogo nullo consentito per layout astratti."), false));
		return true;
	}
	Catalog->ValidateCatalog(OutWarnings, OutErrors);
	return OutErrors.Num() == 0;
}

bool URARomanConstructionValidator::ValidatePlacements(const TArray<FRARomanModulePlacement>& Placements, int32 MaximumModuleCount, TArray<FRARomanGenerationMessage>& OutWarnings, TArray<FRARomanGenerationMessage>& OutErrors)
{
	std::vector<RomaAeternaCore::ModulePlacement> CorePlacements;
	CorePlacements.reserve(Placements.Num());
	for (const FRARomanModulePlacement& Placement : Placements)
	{
		CorePlacements.push_back(ToCorePlacement(Placement));
	}
	std::vector<RomaAeternaCore::GenerationMessage> CoreWarnings;
	std::vector<RomaAeternaCore::GenerationMessage> CoreErrors;
	const bool bValid = RomaAeternaCore::ValidatePlacements(CorePlacements, MaximumModuleCount, CoreWarnings, CoreErrors);
	for (const RomaAeternaCore::GenerationMessage& Warning : CoreWarnings)
	{
		OutWarnings.Add(FromCoreValidatorMessage(Warning));
	}
	for (const RomaAeternaCore::GenerationMessage& Error : CoreErrors)
	{
		OutErrors.Add(FromCoreValidatorMessage(Error));
	}
	return bValid;
}
