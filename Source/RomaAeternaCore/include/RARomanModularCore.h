#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <string>
#include <utility>
#include <vector>

namespace RomaAeternaCore
{

enum class BuildingType : std::uint8_t
{
    SimpleHouse,
    Taberna,
    Domus,
    Insula,
    Temple,
    Basilica,
    Portico,
    AdministrativeBuilding,
    StreetSection,
    Plaza,
    ForumSection
};

enum class RoofType : std::uint8_t
{
    Flat,
    SingleSlope,
    DoubleSlope,
    Portico,
    Compluvium,
    Monumental
};

enum class ArchitecturalOrder : std::uint8_t
{
    None,
    Tuscan,
    Doric,
    Ionic,
    Corinthian,
    Composite
};

enum class ModuleCategory : std::uint8_t
{
    Wall,
    Door,
    Window,
    Corner,
    Column,
    Capital,
    Base,
    Arch,
    Beam,
    Floor,
    Roof,
    Stair,
    Podium,
    Portico,
    Prop,
    Vegetation,
    Decoration
};

struct Vector3
{
    double X = 0.0;
    double Y = 0.0;
    double Z = 0.0;
};

struct Transform
{
    Vector3 Location;
    Vector3 RotationDegrees;
    Vector3 Scale{1.0, 1.0, 1.0};
};

struct Bounds
{
    Vector3 Min;
    Vector3 Max;
};

struct BuildingParameters
{
    BuildingType Type = BuildingType::SimpleHouse;
    double WidthCm = 800.0;
    double DepthCm = 600.0;
    std::int32_t FloorCount = 1;
    std::int32_t BayCount = 4;
    double FloorHeightCm = 320.0;
    double WallThicknessCm = 40.0;
    std::int32_t DoorCount = 1;
    std::int32_t WindowCount = 2;
    RoofType Roof = RoofType::DoubleSlope;
    ArchitecturalOrder Order = ArchitecturalOrder::None;
    std::int32_t RandomSeed = 1337;
    std::int32_t MaximumModuleCount = 256;
};

struct ModulePlacement
{
    std::string ModuleId;
    Transform TransformValue;
    ModuleCategory Category = ModuleCategory::Wall;
    std::int32_t FloorIndex = 0;
    std::int32_t BayIndex = 0;
    bool bMirrored = false;
    std::vector<std::string> Tags;
};

struct GenerationMessage
{
    std::string Code;
    std::string Message;
    bool bIsError = false;
};

struct GenerationResult
{
    bool bSuccess = false;
    std::vector<ModulePlacement> Placements;
    std::vector<GenerationMessage> Warnings;
    std::vector<GenerationMessage> Errors;
    std::int32_t EstimatedModuleCount = 0;
    std::int32_t EstimatedTriangleBudget = 0;
    Bounds BuildingBounds;
};

inline bool IsFinite(double Value)
{
    return std::isfinite(Value);
}

inline bool IsFinite(const Vector3& Value)
{
    return IsFinite(Value.X) && IsFinite(Value.Y) && IsFinite(Value.Z);
}

inline bool IsScaleValid(const Vector3& Scale)
{
    return IsFinite(Scale) && Scale.X > 0.0 && Scale.Y > 0.0 && Scale.Z > 0.0;
}

inline double ClampDouble(double Value, double Min, double Max)
{
    return std::max(Min, std::min(Value, Max));
}

inline std::int32_t ClampInt(std::int32_t Value, std::int32_t Min, std::int32_t Max)
{
    return std::max(Min, std::min(Value, Max));
}

inline BuildingParameters NormalizeBuildingParameters(const BuildingParameters& Parameters)
{
    BuildingParameters Normalized = Parameters;
    Normalized.WidthCm = std::max(IsFinite(Normalized.WidthCm) ? Normalized.WidthCm : 800.0, 100.0);
    Normalized.DepthCm = std::max(IsFinite(Normalized.DepthCm) ? Normalized.DepthCm : 600.0, 100.0);
    Normalized.FloorCount = ClampInt(Normalized.FloorCount, 1, 8);
    Normalized.BayCount = ClampInt(Normalized.BayCount, 1, 64);
    Normalized.FloorHeightCm = ClampDouble(IsFinite(Normalized.FloorHeightCm) ? Normalized.FloorHeightCm : 320.0, 220.0, 800.0);
    Normalized.WallThicknessCm = ClampDouble(IsFinite(Normalized.WallThicknessCm) ? Normalized.WallThicknessCm : 40.0, 10.0, 200.0);
    Normalized.DoorCount = ClampInt(Normalized.DoorCount, Normalized.Type == BuildingType::StreetSection ? 0 : 1, Normalized.BayCount);
    Normalized.WindowCount = ClampInt(Normalized.WindowCount, 0, Normalized.BayCount * Normalized.FloorCount * 4);
    Normalized.MaximumModuleCount = ClampInt(Normalized.MaximumModuleCount, 1, 10000);
    if (Normalized.Type == BuildingType::Temple && Normalized.Order == ArchitecturalOrder::None)
    {
        Normalized.Order = ArchitecturalOrder::Tuscan;
    }
    return Normalized;
}

inline double CalculateBayWidth(const BuildingParameters& Parameters)
{
    const BuildingParameters Normalized = NormalizeBuildingParameters(Parameters);
    return Normalized.WidthCm / static_cast<double>(std::max(1, Normalized.BayCount));
}

inline double CalculateFloorHeight(const BuildingParameters& Parameters)
{
    return NormalizeBuildingParameters(Parameters).FloorHeightCm;
}

inline double CalculateGridAlignedValue(double Value, double GridSize)
{
    const double SafeGrid = std::max(IsFinite(GridSize) ? GridSize : 1.0, 1.0);
    return std::round(Value / SafeGrid) * SafeGrid;
}

inline Transform CalculateGridAlignedTransform(const Vector3& Location, const Vector3& RotationDegrees, const Vector3& Scale, double GridSizeCm, double RotationStepDegrees)
{
    const double SafeRotationStep = std::max(IsFinite(RotationStepDegrees) ? RotationStepDegrees : 1.0, 1.0);
    Transform Result;
    Result.Location = {
        CalculateGridAlignedValue(Location.X, GridSizeCm),
        CalculateGridAlignedValue(Location.Y, GridSizeCm),
        CalculateGridAlignedValue(Location.Z, GridSizeCm)};
    Result.RotationDegrees = {0.0, CalculateGridAlignedValue(RotationDegrees.Y, SafeRotationStep), 0.0};
    Result.Scale = {std::max(Scale.X, 0.01), std::max(Scale.Y, 0.01), std::max(Scale.Z, 0.01)};
    return Result;
}

inline Bounds CalculateBuildingBounds(const BuildingParameters& Parameters)
{
    const BuildingParameters Normalized = NormalizeBuildingParameters(Parameters);
    return {{0.0, 0.0, 0.0}, {Normalized.WidthCm, Normalized.DepthCm, static_cast<double>(Normalized.FloorCount) * Normalized.FloorHeightCm}};
}

inline std::int32_t EstimateRequiredModules(const BuildingParameters& Parameters)
{
    const BuildingParameters Normalized = NormalizeBuildingParameters(Parameters);
    const double BayWidth = CalculateBayWidth(Normalized);
    const std::int32_t DepthBays = std::max(1, static_cast<std::int32_t>(std::llround(Normalized.DepthCm / std::max(BayWidth, 1.0))));
    const std::int32_t Perimeter = Normalized.BayCount * 2 + DepthBays * 2;
    const std::int32_t TempleExtra = Normalized.Type == BuildingType::Temple ? Normalized.BayCount * 2 + 4 : 0;
    return Perimeter * Normalized.FloorCount + Normalized.DoorCount + Normalized.WindowCount + 2 + TempleExtra;
}

inline void AddMessage(std::vector<GenerationMessage>& Messages, std::string Code, std::string Message, bool bIsError)
{
    Messages.push_back({std::move(Code), std::move(Message), bIsError});
}

inline bool ValidateBuildingParameters(const BuildingParameters& Parameters, std::vector<GenerationMessage>& Warnings, std::vector<GenerationMessage>& Errors)
{
    if (!IsFinite(Parameters.WidthCm) || !IsFinite(Parameters.DepthCm) || !IsFinite(Parameters.FloorHeightCm) || !IsFinite(Parameters.WallThicknessCm))
    {
        AddMessage(Errors, "NonFinite", "Valore numerico non finito.", true);
    }
    if (Parameters.WidthCm <= 0.0 || Parameters.DepthCm <= 0.0)
    {
        AddMessage(Errors, "InvalidDimensions", "Dimensioni non positive.", true);
    }
    if (Parameters.FloorCount < 1)
    {
        AddMessage(Errors, "InvalidFloorCount", "Numero piani non valido.", true);
    }
    if (Parameters.BayCount < 1)
    {
        AddMessage(Errors, "InvalidBayCount", "Numero campate non valido.", true);
    }
    if (Parameters.FloorHeightCm < 220.0)
    {
        AddMessage(Warnings, "LowFloorHeight", "Altezza piano bassa.", false);
    }
    if (Parameters.DoorCount < 1 && Parameters.Type != BuildingType::StreetSection)
    {
        AddMessage(Errors, "MissingAccess", "Edificio senza accesso.", true);
    }
    if (Parameters.DoorCount > Parameters.BayCount)
    {
        AddMessage(Errors, "TooManyDoors", "Porte superiori alle campate.", true);
    }
    if (Parameters.WindowCount > Parameters.BayCount * std::max(1, Parameters.FloorCount) * 4)
    {
        AddMessage(Errors, "TooManyWindows", "Finestre eccessive.", true);
    }
    if (Parameters.MaximumModuleCount < 1)
    {
        AddMessage(Errors, "InvalidModuleLimit", "MaximumModuleCount non valido.", true);
    }
    if (Parameters.Type == BuildingType::Temple && Parameters.Order == ArchitecturalOrder::None)
    {
        AddMessage(Warnings, "TempleOrderApproximation", "Tempio senza ordine: verra normalizzato.", false);
    }
    if (EstimateRequiredModules(Parameters) > Parameters.MaximumModuleCount)
    {
        AddMessage(Errors, "ModuleLimitExceeded", "Stima moduli superiore al limite.", true);
    }
    return Errors.empty();
}

inline void AddPlacement(GenerationResult& Result, std::string ModuleId, ModuleCategory Category, Vector3 Location, std::int32_t BayIndex = 0, std::int32_t FloorIndex = 0)
{
    ModulePlacement Placement;
    Placement.ModuleId = std::move(ModuleId);
    Placement.Category = Category;
    Placement.TransformValue.Location = Location;
    Placement.BayIndex = BayIndex;
    Placement.FloorIndex = FloorIndex;
    Result.Placements.push_back(std::move(Placement));
}

inline bool ValidatePlacements(const std::vector<ModulePlacement>& Placements, std::int32_t MaximumModuleCount, std::vector<GenerationMessage>& Warnings, std::vector<GenerationMessage>& Errors)
{
    if (static_cast<std::int32_t>(Placements.size()) > MaximumModuleCount)
    {
        AddMessage(Errors, "ModuleLimitExceeded", "Placement oltre MaximumModuleCount.", true);
    }
    for (const ModulePlacement& Placement : Placements)
    {
        if (!IsFinite(Placement.TransformValue.Location) || !IsFinite(Placement.TransformValue.RotationDegrees))
        {
            AddMessage(Errors, "NonFiniteTransform", "Transform non finita.", true);
        }
        if (!IsScaleValid(Placement.TransformValue.Scale))
        {
            AddMessage(Errors, "InvalidScale", "Scala nulla o negativa.", true);
        }
        if (Placement.ModuleId.empty())
        {
            AddMessage(Warnings, "AbstractModuleId", "Placement astratto senza ID asset specifico.", false);
        }
    }
    return Errors.empty();
}

inline bool EnforceMaximumModuleCount(GenerationResult& Result, std::int32_t MaximumModuleCount)
{
    if (Result.EstimatedModuleCount > MaximumModuleCount)
    {
        AddMessage(Result.Errors, "ModuleLimitExceeded", "Limite moduli superato.", true);
        Result.bSuccess = false;
        return false;
    }
    return true;
}

inline std::int32_t SeedVariantOffset(std::int32_t RandomSeed, std::int32_t Modulo)
{
    if (Modulo <= 1)
    {
        return 0;
    }
    const std::uint32_t Mixed = static_cast<std::uint32_t>(RandomSeed) * 1664525u + 1013904223u;
    return static_cast<std::int32_t>(Mixed % static_cast<std::uint32_t>(Modulo));
}

inline GenerationResult FinishGeneration(GenerationResult Result, const BuildingParameters& Parameters)
{
    const BuildingParameters Normalized = NormalizeBuildingParameters(Parameters);
    Result.EstimatedModuleCount = static_cast<std::int32_t>(Result.Placements.size());
    Result.EstimatedTriangleBudget = Result.EstimatedModuleCount * 500;
    Result.BuildingBounds = CalculateBuildingBounds(Normalized);
    std::vector<GenerationMessage> PlacementWarnings;
    ValidatePlacements(Result.Placements, Normalized.MaximumModuleCount, PlacementWarnings, Result.Errors);
    Result.Warnings.insert(Result.Warnings.end(), PlacementWarnings.begin(), PlacementWarnings.end());
    Result.bSuccess = Result.Errors.empty() && Result.EstimatedModuleCount <= Normalized.MaximumModuleCount;
    EnforceMaximumModuleCount(Result, Normalized.MaximumModuleCount);
    return Result;
}

inline GenerationResult BuildSimpleHouseLayout(const BuildingParameters& Parameters)
{
    const BuildingParameters Normalized = NormalizeBuildingParameters(Parameters);
    GenerationResult Result;
    ValidateBuildingParameters(Normalized, Result.Warnings, Result.Errors);
    const double BayWidth = CalculateBayWidth(Normalized);
    const std::int32_t DoorBay = SeedVariantOffset(Normalized.RandomSeed, Normalized.BayCount);

    for (std::int32_t Bay = 0; Bay < Normalized.BayCount; ++Bay)
    {
        AddPlacement(Result, "wall", ModuleCategory::Wall, {Bay * BayWidth, 0.0, 0.0}, Bay);
        AddPlacement(Result, "wall", ModuleCategory::Wall, {Bay * BayWidth, Normalized.DepthCm, 0.0}, Bay);
    }
    AddPlacement(Result, "door", ModuleCategory::Door, {DoorBay * BayWidth, 0.0, 0.0}, DoorBay);
    for (std::int32_t Index = 0; Index < Normalized.WindowCount; ++Index)
    {
        const std::int32_t Bay = (Index + 1 + DoorBay) % Normalized.BayCount;
        AddPlacement(Result, "window", ModuleCategory::Window, {Bay * BayWidth, Normalized.DepthCm, 140.0}, Bay);
    }
    AddPlacement(Result, "floor", ModuleCategory::Floor, {Normalized.WidthCm / 2.0, Normalized.DepthCm / 2.0, 0.0});
    AddPlacement(Result, "roof", ModuleCategory::Roof, {Normalized.WidthCm / 2.0, Normalized.DepthCm / 2.0, Normalized.FloorHeightCm});
    return FinishGeneration(std::move(Result), Normalized);
}

inline GenerationResult BuildTabernaLayout(const BuildingParameters& Parameters)
{
    BuildingParameters Normalized = NormalizeBuildingParameters(Parameters);
    Normalized.Type = BuildingType::Taberna;
    GenerationResult Result = BuildSimpleHouseLayout(Normalized);
    AddPlacement(Result, "shop_opening", ModuleCategory::Door, {Normalized.WidthCm / 2.0, 0.0, 0.0});
    AddPlacement(Result, "counter_prop", ModuleCategory::Prop, {Normalized.WidthCm / 2.0, 120.0, 90.0});
    AddPlacement(Result, "backroom_wall", ModuleCategory::Wall, {0.0, Normalized.DepthCm * 0.65, 0.0});
    AddMessage(Result.Warnings, "HISTORICAL_APPROXIMATION", "Retrobottega semplificato in partizione astratta.", false);
    return FinishGeneration(std::move(Result), Normalized);
}

inline GenerationResult BuildTempleLayout(const BuildingParameters& Parameters)
{
    BuildingParameters Normalized = NormalizeBuildingParameters(Parameters);
    Normalized.Type = BuildingType::Temple;
    Normalized.DoorCount = std::max(1, Normalized.DoorCount);
    GenerationResult Result;
    ValidateBuildingParameters(Normalized, Result.Warnings, Result.Errors);
    AddPlacement(Result, "podium", ModuleCategory::Podium, {Normalized.WidthCm / 2.0, Normalized.DepthCm / 2.0, 30.0});
    AddPlacement(Result, "front_stair", ModuleCategory::Stair, {Normalized.WidthCm / 2.0, -100.0, 0.0});
    const double BayWidth = CalculateBayWidth(Normalized);
    for (std::int32_t Bay = 0; Bay < Normalized.BayCount; ++Bay)
    {
        AddPlacement(Result, "column", ModuleCategory::Column, {Bay * BayWidth, 0.0, 80.0}, Bay);
        AddPlacement(Result, "beam", ModuleCategory::Beam, {Bay * BayWidth, 0.0, Normalized.FloorHeightCm}, Bay);
    }
    AddPlacement(Result, "cella_wall", ModuleCategory::Wall, {Normalized.WidthCm / 2.0, Normalized.DepthCm / 2.0, 80.0});
    AddPlacement(Result, "roof", ModuleCategory::Roof, {Normalized.WidthCm / 2.0, Normalized.DepthCm / 2.0, Normalized.FloorHeightCm + 120.0});
    AddMessage(Result.Warnings, "HISTORICAL_APPROXIMATION", "Colonnato e cella sono modelli astratti.", false);
    return FinishGeneration(std::move(Result), Normalized);
}

inline GenerationResult BuildStreetSectionLayout(const BuildingParameters& Parameters)
{
    BuildingParameters Normalized = NormalizeBuildingParameters(Parameters);
    Normalized.Type = BuildingType::StreetSection;
    Normalized.DoorCount = 0;
    GenerationResult Result;
    ValidateBuildingParameters(Normalized, Result.Warnings, Result.Errors);
    AddPlacement(Result, "roadway", ModuleCategory::Floor, {Normalized.WidthCm / 2.0, Normalized.DepthCm / 2.0, 0.0});
    AddPlacement(Result, "left_sidewalk", ModuleCategory::Floor, {0.0, Normalized.DepthCm / 2.0, 15.0});
    AddPlacement(Result, "right_sidewalk", ModuleCategory::Floor, {Normalized.WidthCm, Normalized.DepthCm / 2.0, 15.0});
    AddPlacement(Result, "raised_crossing", ModuleCategory::Floor, {Normalized.WidthCm / 2.0, Normalized.DepthCm / 2.0, 25.0});
    AddPlacement(Result, "facade_space", ModuleCategory::Decoration, {Normalized.WidthCm + 100.0, Normalized.DepthCm / 2.0, 0.0});
    AddMessage(Result.Warnings, "HISTORICAL_APPROXIMATION", "Sezione stradale parametrica senza materiali finali.", false);
    return FinishGeneration(std::move(Result), Normalized);
}

} // namespace RomaAeternaCore
