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
    SimpleHouse, Domus, AtriumDomus, PeristyleDomus, RichDomus, UrbanVilla, SuburbanVilla, Insula, UpperFloorApartment,
    Taberna, Thermopolium, Popina, Caupona, BakeryShop, MarketStall, Bookshop, ArtisanShop, Warehouse, Horrea, Macellum, Market,
    Fullonica, Pistrinum, Winery, OilWorkshop, DyeWorkshop, PotteryWorkshop, MetalWorkshop, TextileWorkshop, MillingWorkshop, BakeryProduction, PressingWorkshop,
    Forum, Basilica, Curia, Comitium, AdministrativeBuilding, PublicLatrine, PublicFountain, BathComplex, Palaestra, Theatre, Odeon, Amphitheatre, Portico, PublicGarden,
    SmallTemple, Temple, Sanctuary, Shrine, Lararium, Sacellum, ImperialCultBuilding,
    Brothel, Tavern, Inn, Stable, MedicalShop, BarberShop, School, Library,
    MonumentalArch, CityGate, CityWall, WatchTower, AqueductSection, StreetSection, Plaza, StatueBase, Monument, FountainMonument, ForumSection, DomusMedia, PopularHouse, Cenaculum, MixedUseHouse, MensaArgentaria, Stabulum,
    CastellumAquae, SewerSection, Cistern, Well, Tinctoria, Tannery, StandaloneOven, UrbanGarden, ServiceYard
};

enum class ArchetypeImplementationState : std::uint8_t { Implemented, ARCHETYPE_PLANNED };
enum class BuildingFunction : std::uint8_t { Residential, Commercial, Productive, Religious, Civic, Entertainment, Hospitality, Sanitary, Hydraulic, Monumental, MixedUse };
enum class BuildingScale : std::uint8_t { Small, Medium, Large, Monumental };
enum class AccessType : std::uint8_t { StreetAccess, SecondaryAccess, ServiceAccess, CourtyardAccess, MonumentalAccess, ShopfrontAccess, InternalAccess };
enum class ZoneFunction : std::uint8_t { Public, Private, Service, Commercial, Productive, Religious, Sanitary, Hydraulic, Circulation, Storage, AnimalWork, OpenSpace };
enum class SurfaceRole : std::uint8_t { ExteriorWall, InteriorWall, StructuralBrick, RoadSurface, SecondaryPaving, Sidewalk, Kerb, Roof, Timber, Ground, Courtyard, ProductiveFloor, ServiceArea, WaterEdge, UtilitySurface };
enum class WeatheringLevel : std::uint8_t { New, Light, Medium, Heavy, Ruined };
enum class WealthTier : std::uint8_t { Poor, Popular, Medium, Wealthy, Monumental };
enum class RoomDecorType : std::uint8_t { None, PlainService, PopularDomestic, MediumDomestic, WealthyDomestic, Commercial, Productive, ThermalCold, ThermalWarm, ThermalHot, ReligiousSimple, PublicSimple, Courtyard, Garden, Storage };
enum class PompeianDecorativeStyle : std::uint8_t { FirstStyleInspired, SecondStyleInspired, ThirdStyleInspired, FourthStyleInspired, PlainPlaster, ServicePlaster };
enum class FloorDecorationType : std::uint8_t { OpusSigninum, GeometricMosaic, SimplePolychromeMosaic, OpusSectileInspired, BrickFloor, StoneFloor, PackedEarth, ProductiveFloor, ThermalFloor };
enum class WallDecorationZone : std::uint8_t { LowerDado, MiddleBand, CentralPanel, SidePanel, UpperFrame, Frieze, UpperWall, FigurativePlaceholder };

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
    Wall, Door, Window, Corner, Column, Capital, Base, Arch, Beam, Floor, Roof, Stair, Podium, Portico, Prop, Vegetation, Decoration,
    Counter, Dolium, Basin, WaterChannel, Millstone, Oven, Furnace, Workbench, Seat, LatrineSeat, Drain, Altar, Shrine, StatueMarker,
    AnimalPath, ShopSign, Shelf, StorageContainer, GardenFeature, Fountain, MosaicZone, FrescoZone, DryingRack, WorkPlatform, RotationArm,
    ServiceBasin, InteractionMarker, Bed, Table, Bench, WritingDesk, ScrollStorage, MirrorMarker, StablePartition, FeedingTrough, WateringTrough, Balcony, SharedStair, ApartmentDoor, ShopOpening, ValueStorageMarker,
    AqueductArch, AqueductChannel, SewerChannel, Manhole, WaterOutlet, FountainBasin, WellHead, CisternTank, HypocaustPillar, Boiler, Press, Loom, PotteryWheel, Anvil, DryingFrame, StorageCell, CargoArea, FuelStorage, WasteArea, IrrigationChannel
};

enum class RoomType : std::uint8_t
{
    Fauces, Vestibulum, Atrium, Impluvium, Ala, Cubiculum, Tablinum, Triclinium, Oecus, Exedra, Culina, DomesticLatrine, Corridor, Stair, Peristyle, Hortus, ServiceRoom, Storage, UpperRoom,
    Shopfront, CounterArea, DiningArea, KitchenArea, CustomerArea, BackRoom, StreetPortico, CommercialStorage,
    WorkshopArea, MillingArea, OvenArea, PressArea, WashingArea, DryingArea, DyeingArea, AnimalDriveArea, FurnaceArea, RawMaterialStorage, FinishedGoodsStorage, PreparationArea,
    Nave, Aisle, Tribunal, CouncilHall, AssemblyArea, BathHall, Apodyterium, Frigidarium, Tepidarium, Calidarium, Laconicum, Palaestra, Auditorium, Cavea, Orchestra, Scaena, Arena, Vomitorium, PublicLatrineHall,
    Cella, Pronaos, Podium, AltarArea, SacredCourt, ProcessionalArea,
    ForumPlaza, MarketCourt, Portico, FountainCourt, MonumentCourt, Garden, Street, Alley, ServiceYard, Apartment, SharedHall, SharedStair, LightCourt, GuestRoom, LodgingRoom, StableHall, Stall, WritingRoom, CopyingRoom, MedicalPreparationRoom, BarberArea, FinancialCounterArea, ValueStorage, CommonRoom, PoorDwellingRoom
};

enum class InteractionPointType : std::uint8_t { Entrance, Exit, WorkerPosition, CustomerPosition, QueuePosition, VendorPosition, ServicePosition, StoragePosition, WorshipPosition, SeatingPosition, AnimalPathPoint, RestrictedPosition, InteractionPosition, ResidentPosition, SleepingPosition, CookingPosition, DiningPosition, ShopkeeperPosition, ScribePosition, MedicalWorkerPosition, BarberPosition, BankerPosition, GuestPosition, StableWorkerPosition, AnimalPosition, FeedingPosition, WateringPosition, SecurityPosition, BathAttendantPosition, BatherPosition, AthletePosition, WaterCarrierPosition, FountainUserPosition, SewerWorkerPosition, TannerPosition, DyerPosition, WeaverPosition, SmithPosition, PotterPosition, PressOperatorPosition, WarehouseWorkerPosition, GuardPosition, LoaderPosition, UnloaderPosition, GardenerPosition };

struct Vector3
{
    double X = 0.0;
    double Y = 0.0;
    double Z = 0.0;
};

struct RomanDecorationPalette
{
    std::string Id;
    Vector3 BaseColor{0.72, 0.55, 0.35};
    Vector3 AccentColor{0.42, 0.12, 0.08};
    Vector3 BorderColor{0.10, 0.09, 0.08};
    double Saturation = 0.75;
    std::vector<std::string> Tags{"HISTORICAL_APPROXIMATION"};
};

struct RomanDecorationBand
{
    WallDecorationZone Zone = WallDecorationZone::MiddleBand;
    double StartHeightCm = 0.0;
    double HeightCm = 30.0;
    Vector3 Color;
};

struct RomanDecorationPanel
{
    std::string Id;
    WallDecorationZone Zone = WallDecorationZone::CentralPanel;
    double OffsetCm = 0.0;
    double BottomCm = 0.0;
    double WidthCm = 100.0;
    double HeightCm = 100.0;
    bool bFigurativePlaceholder = false;
    std::vector<std::string> Tags;
};

struct RomanWallDecorationPlan
{
    std::string WallId;
    double WidthCm = 100.0;
    double HeightCm = 300.0;
    bool bHasDoor = false;
    bool bHasWindow = false;
    double OpeningCenterCm = 0.0;
    double OpeningWidthCm = 0.0;
    PompeianDecorativeStyle Style = PompeianDecorativeStyle::PlainPlaster;
    RomanDecorationPalette Palette;
    std::vector<RomanDecorationBand> Bands;
    std::vector<RomanDecorationPanel> Panels;
};

struct RomanFloorDecorationPlan
{
    std::string RoomId;
    FloorDecorationType Type = FloorDecorationType::PackedEarth;
    double WidthCm = 100.0;
    double DepthCm = 100.0;
    std::int32_t PatternDensity = 1;
    RomanDecorationPalette Palette;
};

struct RomanRoomDecorationPlan
{
    std::string RoomId;
    RoomDecorType DecorType = RoomDecorType::None;
    PompeianDecorativeStyle Style = PompeianDecorativeStyle::PlainPlaster;
    WealthTier Wealth = WealthTier::Popular;
    WeatheringLevel Weathering = WeatheringLevel::Medium;
    RomanDecorationPalette Palette;
    std::vector<RomanWallDecorationPlan> Walls;
    RomanFloorDecorationPlan Floor;
    bool bAccessible = false;
};

struct RomanDecorationPlan
{
    std::int32_t Seed = 0;
    std::vector<RomanRoomDecorationPlan> Rooms;
    std::vector<std::string> Tags{"HISTORICAL_APPROXIMATION", "FIGURATIVE_FRESCO_ART_NOT_STARTED"};
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
    BuildingScale Scale = BuildingScale::Medium;
    std::int32_t SocialStatusRank = 2;
    std::int32_t DecorationLevel = 1;
    std::int32_t UrbanDensityLevel = 2;
    AccessType StreetFacingSide = AccessType::StreetAccess;
    bool HasUpperFloor = false;
    bool HasCourtyard = false;
    bool HasWater = false;
    bool HasDrainage = false;
    bool HasFireArea = false;
    bool HasServiceAccess = false;
    bool HasCustomerArea = false;
    bool HasProductionArea = false;
    bool HasStorage = true;
    std::int32_t MaximumRoomCount = 64;
    bool HasImpluvium = true;
    bool HasPeristyle = false;
    bool HasHortus = false;
    bool HasFrontTabernae = false;
    bool HasDomesticApartment = false;
    bool HasExternalCustomerArea = false;
    std::int32_t DeviceCount = 2;
    std::int32_t PublicCapacity = 8;
    bool HasExternalAltar = true;
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

struct RomanDecorationValidationResult
{
    bool bValid = true;
    std::vector<GenerationMessage> Warnings;
    std::vector<GenerationMessage> Errors;
};

struct GenerationResult
{
    bool bSuccess = false;
    std::vector<ModulePlacement> Placements;
    std::vector<GenerationMessage> Warnings;
    std::vector<GenerationMessage> Errors;
    std::int32_t EstimatedModuleCount = 0;
    std::int32_t EstimatedTriangleBudget = 0;
    std::int32_t RoomCount = 0, InteractionPointCount = 0, ProductionDeviceCount = 0, WaterFeatureCount = 0, UtilityConnectionCount = 0, HazardZoneCount = 0, ProductionStageCount = 0;
    double WaterDemand = 0, DrainageDemand = 0, HeatDemand = 0, StorageCapacity = 0;
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

inline std::size_t SelectDeterministicWeightedIndex(
    const std::vector<double>& Weights, std::int32_t Seed, std::uint32_t Salt = 0u)
{
    if (Weights.empty()) return 0;
    double Total = 0.0;
    for (double Weight : Weights) Total += std::max(Weight, 0.001);
    std::uint32_t State = static_cast<std::uint32_t>(Seed) ^ Salt ^ 0x9e3779b9u;
    State ^= State >> 16u;
    State *= 0x7feb352du;
    State ^= State >> 15u;
    State *= 0x846ca68bu;
    State ^= State >> 16u;
    const double Unit = static_cast<double>(State) / static_cast<double>(std::numeric_limits<std::uint32_t>::max());
    const double Choice = Unit * Total;
    double Cursor = 0.0;
    for (std::size_t Index = 0; Index < Weights.size(); ++Index)
    {
        Cursor += std::max(Weights[Index], 0.001);
        if (Choice <= Cursor) return Index;
    }
    return Weights.size() - 1;
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


struct BuildingZone { std::string Id; ZoneFunction Function=ZoneFunction::Public; Vector3 Position; double WidthCm=100, DepthCm=100, HeightCm=300; std::int32_t Floor=0; std::vector<AccessType> Accesses; double OrientationDegrees=0; bool bStreetFacing=false; bool bCourtyardFacing=false; std::int32_t Capacity=1; std::string Activity; std::int32_t DecorationLevel=0; bool bHasWater=false,bHasDrainage=false,bHasFire=false,bHasEquipment=false; std::vector<std::string> Tags; };
struct RoomDefinition : BuildingZone { RoomType Type=RoomType::ServiceRoom; std::vector<std::string> Connections; };
struct RoomConnection { std::string FromId; std::string ToId; AccessType Type=AccessType::InternalAccess; };
struct CourtyardDefinition : BuildingZone {};
struct OpenSpaceDefinition : BuildingZone {};
struct WorkAreaDefinition : BuildingZone {};
struct CommercialCounterDefinition { std::string Id; std::string ZoneId; Vector3 Position; double WidthCm=200, DepthCm=80; std::int32_t DoliaCount=0; std::vector<std::string> Tags; };
struct ProductionDeviceDefinition { std::string Id; ModuleCategory Category=ModuleCategory::Workbench; std::string ZoneId; Vector3 Position; double RadiusCm=50; std::vector<Vector3> PathPoints; std::vector<std::string> Tags; };
struct WaterFeatureDefinition { std::string Id; ModuleCategory Category=ModuleCategory::WaterChannel; std::string ZoneId; Vector3 Position; bool bRequiresDrainage=true; std::string FlowFrom; std::string FlowTo; std::vector<std::string> Tags; };
struct ReligiousFeatureDefinition { std::string Id; ModuleCategory Category=ModuleCategory::Shrine; std::string ZoneId; Vector3 Position; std::vector<std::string> Tags; };
struct MonumentFeatureDefinition { std::string Id; ModuleCategory Category=ModuleCategory::Podium; std::string ZoneId; Vector3 Position; std::vector<std::string> Tags; };
struct BuildingInteractionPoint { std::string Id; InteractionPointType Type=InteractionPointType::InteractionPosition; Vector3 Position; double OrientationDegrees=0; std::int32_t Floor=0; std::int32_t Capacity=1; std::vector<std::string> Tags; std::string ZoneId; bool bAccessible=true; std::string Role; };
using BuildingPlanParameters = BuildingParameters;
using BuildingPlanMessage = GenerationMessage;
enum class FrequencyClass : std::uint8_t { VeryCommon, Common, Uncommon, Rare, Unique };
enum class UrbanZone : std::uint8_t { CivicCenter, ReligiousCenter, CommercialAxis, WealthyResidential, MediumResidential, PopularResidential, ProductiveDistrict, EntertainmentDistrict, PortDistrict, PeripheralDistrict, NearCityWall, Suburb, ExtraUrban, NecropolisZone };
enum class StreetClass : std::uint8_t { MainRoad, SecondaryRoad, Alley, ForumEdge, MarketStreet, PortRoad, ExtraUrbanRoad };
enum class ImpactLevel : std::uint8_t { None, Low, Medium, High, VeryHigh };
struct RomanBuildingUrbanProfile { BuildingType BuildingTypeValue=BuildingType::SimpleHouse; BuildingFunction BuildingFunctionValue=BuildingFunction::Residential; BuildingScale BuildingScaleValue=BuildingScale::Small; FrequencyClass FrequencyClassValue=FrequencyClass::Common; std::vector<UrbanZone> UrbanZoneCompatibility; std::vector<StreetClass> PreferredStreetClass; bool RequiresStreetFrontage=false, RequiresServiceAccess=false, RequiresWater=false, RequiresDrainage=false; ImpactLevel FireRisk=ImpactLevel::Low, NoiseLevel=ImpactLevel::Low, OdorLevel=ImpactLevel::Low, PrestigeLevel=ImpactLevel::Low, CustomerTraffic=ImpactLevel::Low, WorkerDensity=ImpactLevel::Low, ResidentCapacity=ImpactLevel::Low; std::int32_t TypicalFloorCount=1; double MinimumPlotWidthCm=300, MinimumPlotDepthCm=300, MaximumPlotWidthCm=3000, MaximumPlotDepthCm=5000; bool CanShareWall=true, CanHaveUpperFloor=false, CanContainShop=false, CanContainResidence=false, CanContainCourtyard=false, CanExistOutsideWalls=false; double PlacementWeight=1.0; std::vector<std::string> Tags; };
struct ApartmentUnitDefinition { std::string Id; std::int32_t Floor=0, RoomCount=1, Capacity=1; std::string AccessId; bool bConnectedToStair=false, bStreetFacing=false, bCourtyardFacing=false, bHasKitchen=false, bHasLatrine=false; std::string EconomicLevel; std::vector<std::string> Tags; };
struct BuildingUseUnit { std::string Id; std::int32_t Floor=0; BuildingFunction Function=BuildingFunction::Residential; std::int32_t ResidentCapacity=0, WorkerCapacity=0, CustomerCapacity=0; std::string AccessId, FutureOwner, FutureWorkers, FutureCustomers, FutureSchedule; std::vector<std::string> Tags; };
struct BuildingSubArchetype { BuildingType Type=BuildingType::SimpleHouse; std::string UnitId; std::vector<std::string> Tags; };
struct CompositeBuildingPlan { std::vector<BuildingSubArchetype> SubArchetypes; std::vector<BuildingUseUnit> UseUnits; };
enum class UtilityType : std::uint8_t { WaterSupply, Drainage, Sewer, Heating, Fire, Storage, Ventilation, AnimalPower };
enum class WaterSourceType : std::uint8_t { Aqueduct, Castellum, PublicFountain, Cistern, Well, Basin, Channel, Pipe, Reservoir };
enum class DrainageType : std::uint8_t { SurfaceDrain, CoveredDrain, Sewer, Channel, WastePit };
enum class HeatSourceType : std::uint8_t { Hearth, Oven, Furnace, Hypocaust, Brazier, Boiler };
enum class ProductionFlowType : std::uint8_t { Textile, Dyeing, Tanning, Metalworking, Pottery, Oil, Wine, Baking, Storage };
struct UtilityConnection { std::string Id, FromNodeId, ToNodeId; UtilityType Type=UtilityType::WaterSupply; double Capacity=1; bool bConnected=true; std::vector<std::string> Tags; };
struct WaterNetworkNode { std::string Id; WaterSourceType Type=WaterSourceType::Basin; Vector3 Position; double Capacity=1; bool bInlet=false,bOutlet=false; std::vector<std::string> Tags; };
struct DrainageNetworkNode { std::string Id; DrainageType Type=DrainageType::SurfaceDrain; Vector3 Position; double Capacity=1,Slope=0.01; bool bInlet=false,bOutlet=false; std::vector<std::string> Tags; };
struct HeatSourceDefinition { std::string Id,ZoneId; HeatSourceType Type=HeatSourceType::Hearth; Vector3 Position; double Output=1; std::vector<std::string> Tags; };
struct HazardZoneDefinition { std::string Id,ZoneId,Hazard; Vector3 Position; double RadiusCm=100; ImpactLevel Level=ImpactLevel::Medium; std::vector<std::string> Tags; };
struct ProductionStageDefinition { std::string Id,ZoneId; std::int32_t Order=0; ModuleCategory Equipment=ModuleCategory::Workbench; std::vector<std::string> Tags; };
struct ProductionFlowDefinition { std::string Id; ProductionFlowType Type=ProductionFlowType::Storage; std::vector<ProductionStageDefinition> Stages; std::vector<std::string> Tags; };
struct StorageUnitDefinition { std::string Id,ZoneId; double Capacity=1; bool bVentilated=false,bSecure=false; std::vector<std::string> Tags; };
struct BathRoomDefinition { std::string RoomId; double TargetTemperatureC=20; bool bPublic=true,bRequiresWater=true,bRequiresDrainage=true,bRequiresHeat=false; };
struct HypocaustDefinition { std::string Id,HeatedRoomId,PraefurniumRoomId; std::int32_t PillarCount=4; double HeatOutput=1; };
struct AqueductSegmentDefinition { std::string Id,InletNodeId,OutletNodeId; Vector3 Start,End; double Slope=0.001,Capacity=1; bool bArcaded=true; };
struct SewerSegmentDefinition { std::string Id,InletNodeId,OutletNodeId; Vector3 Start,End; double Slope=0.01,Capacity=1; bool bCovered=true,bMaintenanceAccess=true; };
struct BuildingPlan { CompositeBuildingPlan Composite; std::vector<ApartmentUnitDefinition> Apartments; RomanBuildingUrbanProfile UrbanProfile; std::vector<RoomDefinition> Rooms; std::vector<BuildingZone> Zones; std::vector<RoomConnection> Connections; std::vector<CourtyardDefinition> Courtyards; std::vector<OpenSpaceDefinition> OpenSpaces; std::vector<ProductionDeviceDefinition> ProductionDevices; std::vector<WaterFeatureDefinition> WaterFeatures; std::vector<ReligiousFeatureDefinition> ReligiousFeatures; std::vector<MonumentFeatureDefinition> MonumentFeatures; std::vector<BuildingInteractionPoint> InteractionPoints; std::vector<UtilityConnection> UtilityConnections; std::vector<WaterNetworkNode> WaterNodes; std::vector<DrainageNetworkNode> DrainageNodes; std::vector<HeatSourceDefinition> HeatSources; std::vector<HazardZoneDefinition> HazardZones; std::vector<ProductionFlowDefinition> ProductionFlows; std::vector<StorageUnitDefinition> StorageUnits; std::vector<BathRoomDefinition> BathRooms; std::vector<HypocaustDefinition> Hypocausts; std::vector<AqueductSegmentDefinition> AqueductSegments; std::vector<SewerSegmentDefinition> SewerSegments; Bounds PlanBounds; std::vector<GenerationMessage> Warnings; std::vector<GenerationMessage> Errors; std::int32_t Seed=0; BuildingType Type=BuildingType::SimpleHouse; ArchetypeImplementationState ImplementationState=ArchetypeImplementationState::ARCHETYPE_PLANNED; };
struct BuildingPlanResult { bool bSuccess=false; BuildingPlan Plan; std::vector<ModulePlacement> Placements; std::vector<GenerationMessage> Warnings; std::vector<GenerationMessage> Errors; };
struct ArchetypeMetadata { BuildingType Type; const char* Name; BuildingFunction Function; BuildingScale Scale; ArchetypeImplementationState State; const char* Requirements; int FuturePriority; };

inline bool HasTag(const std::vector<std::string>& Tags,const std::string& T){return std::find(Tags.begin(),Tags.end(),T)!=Tags.end();}
inline RoomDefinition MakeRoom(std::string Id, RoomType Type, ZoneFunction Function, Vector3 Pos, double W, double D, std::vector<std::string> Tags){RoomDefinition R; R.Id=std::move(Id); R.Type=Type; R.Function=Function; R.Position=Pos; R.WidthCm=W; R.DepthCm=D; R.Tags=std::move(Tags); R.bStreetFacing=HasTag(R.Tags,"street_facing"); R.bHasWater=HasTag(R.Tags,"water_required"); R.bHasDrainage=HasTag(R.Tags,"drainage_required"); R.bHasFire=HasTag(R.Tags,"fire_hazard_area"); return R;}
inline void Connect(BuildingPlan& P,const std::string& A,const std::string& B,AccessType T=AccessType::InternalAccess){P.Connections.push_back({A,B,T});}
inline void AddPoint(BuildingPlan& P,std::string Id,InteractionPointType T,Vector3 Pos,std::string Zone,std::vector<std::string> Tags,std::string Role){P.InteractionPoints.push_back({std::move(Id),T,Pos,0,0,1,std::move(Tags),std::move(Zone),true,std::move(Role)});}
inline bool IsArchetypeImplemented(BuildingType T){switch(T){case BuildingType::AtriumDomus:case BuildingType::Thermopolium:case BuildingType::Fullonica:case BuildingType::Pistrinum:case BuildingType::PublicLatrine:case BuildingType::SmallTemple:case BuildingType::DomusMedia:case BuildingType::PeristyleDomus:case BuildingType::RichDomus:case BuildingType::PopularHouse:case BuildingType::Insula:case BuildingType::Cenaculum:case BuildingType::MixedUseHouse:case BuildingType::Taberna:case BuildingType::Popina:case BuildingType::Caupona:case BuildingType::Bookshop:case BuildingType::Brothel:case BuildingType::MedicalShop:case BuildingType::BarberShop:case BuildingType::MensaArgentaria:case BuildingType::Stabulum:case BuildingType::BathComplex:case BuildingType::Palaestra:case BuildingType::CastellumAquae:case BuildingType::AqueductSection:case BuildingType::SewerSection:case BuildingType::PublicFountain:case BuildingType::Cistern:case BuildingType::Well:case BuildingType::Tinctoria:case BuildingType::Tannery:case BuildingType::TextileWorkshop:case BuildingType::MetalWorkshop:case BuildingType::PotteryWorkshop:case BuildingType::OilWorkshop:case BuildingType::Winery:case BuildingType::PressingWorkshop:case BuildingType::StandaloneOven:case BuildingType::Horrea:case BuildingType::UrbanGarden:case BuildingType::ServiceYard:return true; default:return false;}}
inline std::vector<BuildingType> GetImplementedArchetypes(){return {BuildingType::AtriumDomus,BuildingType::Thermopolium,BuildingType::Fullonica,BuildingType::Pistrinum,BuildingType::PublicLatrine,BuildingType::SmallTemple,BuildingType::DomusMedia,BuildingType::PeristyleDomus,BuildingType::RichDomus,BuildingType::PopularHouse,BuildingType::Insula,BuildingType::Cenaculum,BuildingType::MixedUseHouse,BuildingType::Taberna,BuildingType::Popina,BuildingType::Caupona,BuildingType::Bookshop,BuildingType::Brothel,BuildingType::MedicalShop,BuildingType::BarberShop,BuildingType::MensaArgentaria,BuildingType::Stabulum,BuildingType::BathComplex,BuildingType::Palaestra,BuildingType::CastellumAquae,BuildingType::AqueductSection,BuildingType::SewerSection,BuildingType::PublicFountain,BuildingType::Cistern,BuildingType::Well,BuildingType::Tinctoria,BuildingType::Tannery,BuildingType::TextileWorkshop,BuildingType::MetalWorkshop,BuildingType::PotteryWorkshop,BuildingType::OilWorkshop,BuildingType::Winery,BuildingType::PressingWorkshop,BuildingType::StandaloneOven,BuildingType::Horrea,BuildingType::UrbanGarden,BuildingType::ServiceYard};}
inline const std::vector<ArchetypeMetadata>& GetArchetypeCatalog(){static const std::vector<ArchetypeMetadata> C={{BuildingType::AtriumDomus,"AtriumDomus",BuildingFunction::Residential,BuildingScale::Medium,ArchetypeImplementationState::Implemented,"fauces, atrium, tablinum",1},{BuildingType::Thermopolium,"Thermopolium",BuildingFunction::Commercial,BuildingScale::Small,ArchetypeImplementationState::Implemented,"counter, dolia, customer access",1},{BuildingType::Fullonica,"Fullonica",BuildingFunction::Productive,BuildingScale::Medium,ArchetypeImplementationState::Implemented,"basins, drainage, drying",1},{BuildingType::Pistrinum,"Pistrinum",BuildingFunction::Productive,BuildingScale::Medium,ArchetypeImplementationState::Implemented,"millstone, animal path, oven",1},{BuildingType::PublicLatrine,"PublicLatrine",BuildingFunction::Sanitary,BuildingScale::Medium,ArchetypeImplementationState::Implemented,"seats, drain, water channel",1},{BuildingType::SmallTemple,"SmallTemple",BuildingFunction::Religious,BuildingScale::Small,ArchetypeImplementationState::Implemented,"podium, stair, pronaos, cella",1},{BuildingType::PeristyleDomus,"PeristyleDomus",BuildingFunction::Residential,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"peristyle house",2},{BuildingType::RichDomus,"RichDomus",BuildingFunction::Residential,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"elite decoration",2},{BuildingType::UrbanVilla,"UrbanVilla",BuildingFunction::Residential,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"urban villa",3},{BuildingType::SuburbanVilla,"SuburbanVilla",BuildingFunction::Residential,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"suburban estate",3},{BuildingType::Insula,"Insula",BuildingFunction::MixedUse,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"multi floor apartments",2},{BuildingType::Taberna,"Taberna",BuildingFunction::Commercial,BuildingScale::Small,ArchetypeImplementationState::ARCHETYPE_PLANNED,"shopfront",2},{BuildingType::Popina,"Popina",BuildingFunction::Commercial,BuildingScale::Small,ArchetypeImplementationState::ARCHETYPE_PLANNED,"food service",3},{BuildingType::Caupona,"Caupona",BuildingFunction::Hospitality,BuildingScale::Medium,ArchetypeImplementationState::ARCHETYPE_PLANNED,"inn rooms",3},{BuildingType::Bookshop,"Bookshop",BuildingFunction::Commercial,BuildingScale::Small,ArchetypeImplementationState::ARCHETYPE_PLANNED,"shelves",4},{BuildingType::Brothel,"Brothel",BuildingFunction::Entertainment,BuildingScale::Small,ArchetypeImplementationState::ARCHETYPE_PLANNED,"small rooms",4},{BuildingType::Macellum,"Macellum",BuildingFunction::Commercial,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"market court",3},{BuildingType::Market,"Market",BuildingFunction::Commercial,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"stalls",3},{BuildingType::Horrea,"Horrea",BuildingFunction::Commercial,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"warehouses",3},{BuildingType::BathComplex,"BathComplex",BuildingFunction::Sanitary,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"heated rooms",2},{BuildingType::Forum,"Forum",BuildingFunction::Civic,BuildingScale::Monumental,ArchetypeImplementationState::ARCHETYPE_PLANNED,"civic plaza",2},{BuildingType::Basilica,"Basilica",BuildingFunction::Civic,BuildingScale::Monumental,ArchetypeImplementationState::ARCHETYPE_PLANNED,"tribunal",3},{BuildingType::Curia,"Curia",BuildingFunction::Civic,BuildingScale::Medium,ArchetypeImplementationState::ARCHETYPE_PLANNED,"council hall",4},{BuildingType::Theatre,"Theatre",BuildingFunction::Entertainment,BuildingScale::Monumental,ArchetypeImplementationState::ARCHETYPE_PLANNED,"cavea",3},{BuildingType::Odeon,"Odeon",BuildingFunction::Entertainment,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"covered auditorium",4},{BuildingType::Amphitheatre,"Amphitheatre",BuildingFunction::Entertainment,BuildingScale::Monumental,ArchetypeImplementationState::ARCHETYPE_PLANNED,"arena",3},{BuildingType::Temple,"LargeTemple",BuildingFunction::Religious,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"large temple",3},{BuildingType::Sanctuary,"Sanctuary",BuildingFunction::Religious,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"sacred precinct",4},{BuildingType::CityGate,"CityGate",BuildingFunction::Monumental,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"gate",4},{BuildingType::CityWall,"CityWall",BuildingFunction::Monumental,BuildingScale::Monumental,ArchetypeImplementationState::ARCHETYPE_PLANNED,"wall",4},{BuildingType::MonumentalArch,"MonumentalArch",BuildingFunction::Monumental,BuildingScale::Large,ArchetypeImplementationState::ARCHETYPE_PLANNED,"arch",4},{BuildingType::PublicFountain,"PublicFountain",BuildingFunction::Hydraulic,BuildingScale::Small,ArchetypeImplementationState::ARCHETYPE_PLANNED,"basin",3},{BuildingType::FountainMonument,"FountainMonument",BuildingFunction::Hydraulic,BuildingScale::Medium,ArchetypeImplementationState::ARCHETYPE_PLANNED,"monumental water",4},{BuildingType::Library,"Library",BuildingFunction::Civic,BuildingScale::Medium,ArchetypeImplementationState::ARCHETYPE_PLANNED,"reading rooms",5},{BuildingType::School,"School",BuildingFunction::Civic,BuildingScale::Small,ArchetypeImplementationState::ARCHETYPE_PLANNED,"teaching",5},{BuildingType::Stable,"Stable",BuildingFunction::Hospitality,BuildingScale::Medium,ArchetypeImplementationState::ARCHETYPE_PLANNED,"animals",5},{BuildingType::MedicalShop,"MedicalShop",BuildingFunction::Commercial,BuildingScale::Small,ArchetypeImplementationState::ARCHETYPE_PLANNED,"medical counter",5},{BuildingType::BarberShop,"BarberShop",BuildingFunction::Commercial,BuildingScale::Small,ArchetypeImplementationState::ARCHETYPE_PLANNED,"service chairs",5}};return C;}
inline BuildingPlan BasePlan(const BuildingParameters& In, BuildingType Type){auto N=NormalizeBuildingParameters(In); BuildingPlan P; P.Type=Type; P.Seed=N.RandomSeed; P.PlanBounds=CalculateBuildingBounds(N); P.ImplementationState=IsArchetypeImplemented(Type)?ArchetypeImplementationState::Implemented:ArchetypeImplementationState::ARCHETYPE_PLANNED; return P;}

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

inline bool ValidateRoomConnectivity(const BuildingPlan& Plan,std::vector<GenerationMessage>& Errors){for(const RoomDefinition& R:Plan.Rooms){if(R.WidthCm<=0||R.DepthCm<=0||!IsFinite(R.Position)){AddMessage(Errors,"InvalidRoom","Stanza con dimensioni o posizione non valida.",true);} if(!HasTag(R.Tags,"optional")&&R.Id!="entrance"&&Plan.Rooms.size()>1){bool ok=false; for(const auto& C:Plan.Connections) ok=ok||(C.FromId==R.Id||C.ToId==R.Id); if(!ok) AddMessage(Errors,"IsolatedRequiredRoom",R.Id+" isolata.",true);}} return Errors.empty();}
inline bool ValidateProductionFlow(const BuildingPlan& Plan,std::vector<GenerationMessage>& Errors){bool Prod=false,Store=false; for(const auto& R:Plan.Rooms){Prod=Prod||R.Function==ZoneFunction::Productive; Store=Store||R.Function==ZoneFunction::Storage||HasTag(R.Tags,"storage_area");} if(Prod&&!Store) AddMessage(Errors,"MissingProductionStorage","Area produttiva senza deposito.",true); return Errors.empty();}
inline bool ValidateWaterFlow(const BuildingPlan& Plan,std::vector<GenerationMessage>& Errors){for(const auto& W:Plan.WaterFeatures){if(W.bRequiresDrainage&&W.FlowTo.empty()) AddMessage(Errors,"MissingDrainageFlow","Elemento idraulico senza scarico.",true);} return Errors.empty();}
inline bool ValidateInteractionPoints(const BuildingPlan& Plan,std::vector<GenerationMessage>& Errors){for(const auto& P:Plan.InteractionPoints){if(!IsFinite(P.Position)||P.Position.X<Plan.PlanBounds.Min.X-200||P.Position.X>Plan.PlanBounds.Max.X+200||P.Position.Y<Plan.PlanBounds.Min.Y-200||P.Position.Y>Plan.PlanBounds.Max.Y+200) AddMessage(Errors,"InteractionOutOfBounds",P.Id+" fuori bounds.",true); if(P.Capacity<=0) AddMessage(Errors,"InvalidInteractionCapacity",P.Id+" capacity non positiva.",true);} return Errors.empty();}
inline bool ValidateArchetypeRequirements(const BuildingPlan& Plan,std::vector<GenerationMessage>& Errors){auto hasRoom=[&](RoomType T){for(const auto& R:Plan.Rooms) if(R.Type==T) return true; return false;}; auto hasCat=[&](ModuleCategory C){for(const auto& D:Plan.ProductionDevices) if(D.Category==C) return true; for(const auto& W:Plan.WaterFeatures) if(W.Category==C) return true; for(const auto& R:Plan.ReligiousFeatures) if(R.Category==C) return true; for(const auto& M:Plan.MonumentFeatures) if(M.Category==C) return true; return false;}; if(Plan.InteractionPoints.empty()) AddMessage(Errors,"MissingAccess","Nessun accesso valido.",true); if(Plan.Type==BuildingType::SmallTemple&&(!hasRoom(RoomType::Cella)||!hasRoom(RoomType::Pronaos))) AddMessage(Errors,"TempleRequirements","Tempio senza cella o pronao.",true); if(Plan.Type==BuildingType::PublicLatrine&&(!hasCat(ModuleCategory::LatrineSeat)||Plan.WaterFeatures.empty())) AddMessage(Errors,"LatrineRequirements","Latrina senza sedute o acqua.",true); return Errors.empty();}
inline bool ValidateBuildingPlan(const BuildingPlan& Plan,std::vector<GenerationMessage>& Warnings,std::vector<GenerationMessage>& Errors){if(!IsFinite(Plan.PlanBounds.Min)||!IsFinite(Plan.PlanBounds.Max)||Plan.PlanBounds.Max.X<=Plan.PlanBounds.Min.X||Plan.PlanBounds.Max.Y<=Plan.PlanBounds.Min.Y) AddMessage(Errors,"InvalidBounds","Bounds planimetrici non validi.",true); ValidateRoomConnectivity(Plan,Errors); ValidateProductionFlow(Plan,Errors); ValidateWaterFlow(Plan,Errors); ValidateInteractionPoints(Plan,Errors); ValidateArchetypeRequirements(Plan,Errors); if(Plan.Warnings.empty()) AddMessage(Warnings,"HISTORICAL_APPROXIMATION","Regole pompeiane semplificate per generazione deterministica.",false); return Errors.empty();}
inline void RoomToPlacements(const RoomDefinition& R,GenerationResult& G){AddPlacement(G,R.Id+"_floor",ModuleCategory::Floor,{R.Position.X,R.Position.Y,0}); AddPlacement(G,R.Id+"_wall",ModuleCategory::Wall,{R.Position.X,R.Position.Y,R.HeightCm/2});}
inline GenerationResult ConvertBuildingPlanToPlacements(const BuildingPlan& Plan,const BuildingParameters& Params){GenerationResult G; for(const auto& R:Plan.Rooms) RoomToPlacements(R,G); for(const auto& C:Plan.Connections) AddPlacement(G,"door_"+C.FromId+"_"+C.ToId,ModuleCategory::Door,{0,0,0}); for(const auto& D:Plan.ProductionDevices) AddPlacement(G,D.Id,D.Category,D.Position); for(const auto& W:Plan.WaterFeatures) AddPlacement(G,W.Id,W.Category,W.Position); for(const auto& R:Plan.ReligiousFeatures) AddPlacement(G,R.Id,R.Category,R.Position); for(const auto& M:Plan.MonumentFeatures) AddPlacement(G,M.Id,M.Category,M.Position); for(const auto& I:Plan.InteractionPoints) AddPlacement(G,I.Id,ModuleCategory::InteractionMarker,I.Position);G.RoomCount=static_cast<std::int32_t>(Plan.Rooms.size());G.InteractionPointCount=static_cast<std::int32_t>(Plan.InteractionPoints.size());G.ProductionDeviceCount=static_cast<std::int32_t>(Plan.ProductionDevices.size());G.WaterFeatureCount=static_cast<std::int32_t>(Plan.WaterFeatures.size());G.UtilityConnectionCount=static_cast<std::int32_t>(Plan.UtilityConnections.size());G.HazardZoneCount=static_cast<std::int32_t>(Plan.HazardZones.size());for(const auto& F:Plan.ProductionFlows)G.ProductionStageCount+=static_cast<std::int32_t>(F.Stages.size());G.WaterDemand=Plan.WaterNodes.size()*10.0+Plan.BathRooms.size()*25.0+Plan.ProductionFlows.size()*5.0;G.DrainageDemand=Plan.DrainageNodes.size()*10.0+Plan.BathRooms.size()*20.0+Plan.ProductionFlows.size()*5.0;for(const auto& H:Plan.HeatSources)G.HeatDemand+=H.Output;for(const auto& S:Plan.StorageUnits)G.StorageCapacity+=S.Capacity;G.BuildingBounds=Plan.PlanBounds; G.Warnings=Plan.Warnings; G.Errors=Plan.Errors; return FinishGeneration(std::move(G),Params);}
inline BuildingPlan GenerateAtriumDomusPlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::AtriumDomus); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("fauces",RoomType::Fauces,ZoneFunction::Circulation,{W*.5,60,0},W*.2,120,{"public_room","street_facing"}),MakeRoom("atrium",RoomType::Atrium,ZoneFunction::Private,{W*.5,D*.28,0},W*.55,D*.28,{"private_room","mosaic_candidate"}),MakeRoom("cubiculum_left",RoomType::Cubiculum,ZoneFunction::Private,{W*.18,D*.28,0},W*.22,D*.18,{"private_room","fresco_candidate"}),MakeRoom("cubiculum_right",RoomType::Cubiculum,ZoneFunction::Private,{W*.82,D*.28,0},W*.22,D*.18,{"private_room","fresco_candidate"}),MakeRoom("ala_left",RoomType::Ala,ZoneFunction::Private,{W*.2,D*.43,0},W*.18,D*.12,{"private_room"}),MakeRoom("ala_right",RoomType::Ala,ZoneFunction::Private,{W*.8,D*.43,0},W*.18,D*.12,{"private_room"}),MakeRoom("tablinum",RoomType::Tablinum,ZoneFunction::Private,{W*.5,D*.55,0},W*.32,D*.15,{"private_room","mosaic_candidate"}),MakeRoom("triclinium",RoomType::Triclinium,ZoneFunction::Private,{W*.2,D*.62,0},W*.25,D*.18,{"private_room","fresco_candidate"}),MakeRoom("culina",RoomType::Culina,ZoneFunction::Service,{W*.82,D*.62,0},W*.18,D*.16,{"service_room","food_preparation","fire_hazard_area"}),MakeRoom("domestic_latrine",RoomType::DomesticLatrine,ZoneFunction::Sanitary,{W*.9,D*.78,0},W*.12,D*.12,{"service_room","water_required","drainage_required"}),MakeRoom("service_room",RoomType::ServiceRoom,ZoneFunction::Service,{W*.75,D*.8,0},W*.18,D*.14,{"service_room","storage_area"})}; if(N.HasImpluvium){auto R=MakeRoom("impluvium",RoomType::Impluvium,ZoneFunction::Hydraulic,{W*.5,D*.28,0},W*.18,D*.1,{"water_required","drainage_required","fountain_candidate"}); P.Rooms.push_back(R); P.WaterFeatures.push_back({"impluvium_basin",ModuleCategory::Basin,"impluvium",R.Position,true,"roof","drain",{"water_required","drainage_required"}});} if(N.HasPeristyle||N.HasCourtyard){P.Rooms.push_back(MakeRoom("peristyle",RoomType::Peristyle,ZoneFunction::OpenSpace,{W*.5,D*.78,0},W*.55,D*.22,{"open_court","fountain_candidate"}));} if(N.HasHortus){P.Rooms.push_back(MakeRoom("hortus",RoomType::Hortus,ZoneFunction::OpenSpace,{W*.5,D*.9,0},W*.5,D*.14,{"open_court"})); P.MonumentFeatures.push_back({"garden_marker",ModuleCategory::GardenFeature,"hortus",{W*.5,D*.9,0},{"fountain_candidate"}});} if(N.HasUpperFloor||N.FloorCount>1){P.Rooms.push_back(MakeRoom("stair",RoomType::Stair,ZoneFunction::Circulation,{W*.1,D*.52,0},W*.12,D*.16,{"service_room","upper_floor"})); P.Rooms.push_back(MakeRoom("upper_room",RoomType::UpperRoom,ZoneFunction::Private,{W*.5,D*.35,N.FloorHeightCm},W*.35,D*.2,{"private_room","upper_floor"})); Connect(P,"stair","upper_room");} if(N.HasFrontTabernae){P.Rooms.push_back(MakeRoom("front_taberna_left",RoomType::Shopfront,ZoneFunction::Commercial,{W*.18,50,0},W*.18,100,{"commercial_area","street_facing","shop_sign_candidate"}));} if(N.HasImpluvium){Connect(P,"atrium","impluvium");} Connect(P,"fauces","atrium",AccessType::StreetAccess); Connect(P,"atrium","tablinum"); Connect(P,"atrium","cubiculum_left"); Connect(P,"atrium","cubiculum_right"); Connect(P,"atrium","ala_left"); Connect(P,"atrium","ala_right"); Connect(P,"tablinum",(N.HasPeristyle||N.HasCourtyard)?"peristyle":"service_room"); Connect(P,"atrium","triclinium"); Connect(P,"service_room","domestic_latrine"); Connect(P,"culina","service_room"); AddPoint(P,"entrance",InteractionPointType::Entrance,{W*.5,0,0},"fauces",{"street_facing"},"accesso"); AddPoint(P,"domestic_work",InteractionPointType::ServicePosition,{W*.82,D*.62,0},"culina",{"npc_workstation"},"servizio"); return P;}
inline BuildingPlan GenerateThermopoliumPlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::Thermopolium); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("shopfront",RoomType::Shopfront,ZoneFunction::Commercial,{W*.5,70,0},W*.8,140,{"commercial_area","customer_area","street_facing","food_sales","shop_sign_candidate"}),MakeRoom("counter_area",RoomType::CounterArea,ZoneFunction::Commercial,{W*.5,150,0},W*.7,120,{"commercial_area","food_sales"}),MakeRoom("backroom",RoomType::BackRoom,ZoneFunction::Service,{W*.5,D*.5,0},W*.65,D*.25,{"service_room"}),MakeRoom("storage",RoomType::CommercialStorage,ZoneFunction::Storage,{W*.25,D*.78,0},W*.3,D*.18,{"storage_area"}),MakeRoom("preparation",RoomType::PreparationArea,ZoneFunction::Service,{W*.72,D*.72,0},W*.25,D*.2,{"food_preparation","fire_hazard_area"})}; Connect(P,"shopfront","counter_area",AccessType::ShopfrontAccess); Connect(P,"counter_area","backroom"); Connect(P,"backroom","storage"); Connect(P,"backroom","preparation"); P.Zones.push_back({"customer_area",ZoneFunction::Commercial,{W*.5,35,0},W,70,300,0,{AccessType::StreetAccess},0,true,false,4,"vendita",0,false,false,false,false,{"customer_area","street_facing"}}); P.ProductionDevices.push_back({"counter",ModuleCategory::Counter,"counter_area",{W*.5,95,90},60,{},{"food_sales"}}); P.ProductionDevices.push_back({"dolium_0",ModuleCategory::Dolium,"counter_area",{W*.35,110,70},45,{},{"food_sales"}}); P.ProductionDevices.push_back({"shelf",ModuleCategory::Shelf,"backroom",{W*.7,D*.5,90},20,{},{"storage_area"}}); P.ProductionDevices.push_back({"storage_container",ModuleCategory::StorageContainer,"storage",{W*.25,D*.78,40},30,{},{"storage_area"}}); P.ProductionDevices.push_back({"fire_area",ModuleCategory::Furnace,"preparation",{W*.8,D*.75,0},45,{},{"fire_hazard_area"}}); AddPoint(P,"customer",InteractionPointType::CustomerPosition,{W*.5,20,0},"shopfront",{"npc_customer_position"},"cliente"); AddPoint(P,"vendor",InteractionPointType::VendorPosition,{W*.5,170,0},"counter_area",{"npc_workstation"},"venditore"); AddPoint(P,"queue",InteractionPointType::QueuePosition,{W*.35,20,0},"shopfront",{"npc_queue_position"},"coda"); return P;}
inline BuildingPlan GenerateFullonicaPlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::Fullonica); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("reception",RoomType::WorkshopArea,ZoneFunction::Productive,{W*.5,D*.12,0},W*.6,D*.15,{"production_area","textile_processing"}),MakeRoom("washing",RoomType::WashingArea,ZoneFunction::Productive,{W*.3,D*.35,0},W*.35,D*.22,{"production_area","textile_processing","water_required","drainage_required"}),MakeRoom("treatment",RoomType::DyeingArea,ZoneFunction::Productive,{W*.7,D*.35,0},W*.35,D*.22,{"production_area","textile_processing","water_required","drainage_required"}),MakeRoom("drying",RoomType::DryingArea,ZoneFunction::Productive,{W*.5,D*.65,0},W*.7,D*.18,{"production_area","textile_processing"}),MakeRoom("storage",RoomType::FinishedGoodsStorage,ZoneFunction::Storage,{W*.5,D*.85,0},W*.5,D*.12,{"storage_area"}),MakeRoom("office",RoomType::BackRoom,ZoneFunction::Service,{W*.85,D*.15,0},W*.18,D*.16,{"service_room"})}; Connect(P,"reception","office");Connect(P,"reception","washing");Connect(P,"washing","treatment");Connect(P,"treatment","drying");Connect(P,"drying","storage"); P.ProductionDevices.push_back({"washing_basin",ModuleCategory::Basin,"washing",{W*.3,D*.35,0},60,{},{"water_required","drainage_required"}}); P.ProductionDevices.push_back({"treatment_basin",ModuleCategory::Basin,"treatment",{W*.7,D*.35,0},60,{},{"water_required","drainage_required"}}); P.ProductionDevices.push_back({"work_platform",ModuleCategory::WorkPlatform,"washing",{W*.3,D*.45,0},40,{},{"npc_workstation"}}); P.ProductionDevices.push_back({"drying_rack",ModuleCategory::DryingRack,"drying",{W*.5,D*.65,0},70,{},{"textile_processing"}}); P.WaterFeatures.push_back({"drain",ModuleCategory::Drain,"washing",{W*.5,D*.5,0},true,"washing","street_drain",{"drainage_required"}}); P.WaterFeatures.push_back({"water_channel",ModuleCategory::WaterChannel,"treatment",{W*.5,D*.42,0},true,"cistern","drain",{"water_required"}}); AddPoint(P,"worker",InteractionPointType::WorkerPosition,{W*.35,D*.38,0},"washing",{"npc_workstation"},"fullone"); AddPoint(P,"service",InteractionPointType::ServicePosition,{W*.9,D*.95,0},"storage",{"npc_service_route"},"servizio"); return P;}
inline BuildingPlan GeneratePistrinumPlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::Pistrinum); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("grain_storage",RoomType::RawMaterialStorage,ZoneFunction::Storage,{W*.2,D*.15,0},W*.25,D*.15,{"storage_area","grain_processing"}),MakeRoom("milling",RoomType::MillingArea,ZoneFunction::Productive,{W*.35,D*.42,0},W*.35,D*.3,{"production_area","grain_processing","animal_work_area"}),MakeRoom("flour_storage",RoomType::FinishedGoodsStorage,ZoneFunction::Storage,{W*.18,D*.72,0},W*.22,D*.14,{"storage_area"}),MakeRoom("preparation",RoomType::PreparationArea,ZoneFunction::Productive,{W*.5,D*.72,0},W*.25,D*.15,{"food_preparation"}),MakeRoom("oven",RoomType::OvenArea,ZoneFunction::Productive,{W*.78,D*.62,0},W*.22,D*.22,{"production_area","fire_hazard_area"}),MakeRoom("bread_storage",RoomType::FinishedGoodsStorage,ZoneFunction::Storage,{W*.75,D*.85,0},W*.25,D*.12,{"storage_area","food_sales"})}; Connect(P,"grain_storage","milling");Connect(P,"milling","flour_storage");Connect(P,"flour_storage","preparation");Connect(P,"preparation","oven");Connect(P,"oven","bread_storage"); std::vector<Vector3> path; for(int i=0;i<8;++i){double a=6.28318530718*i/8.0; path.push_back({W*.35+std::cos(a)*90,D*.42+std::sin(a)*90,0}); AddPoint(P,"donkey_path_"+std::to_string(i),InteractionPointType::AnimalPathPoint,path.back(),"milling",{"npc_animal_route","animal_work_area"},"percorso animale");} P.ProductionDevices.push_back({"millstone_base",ModuleCategory::Millstone,"milling",{W*.35,D*.42,0},90,path,{"animal_work_area","grain_processing"}}); P.ProductionDevices.push_back({"millstone_upper",ModuleCategory::Millstone,"milling",{W*.35,D*.42,70},60,{}, {"grain_processing"}}); P.ProductionDevices.push_back({"rotation_arm",ModuleCategory::RotationArm,"milling",{W*.43,D*.42,80},90,{}, {"animal_work_area"}}); P.ProductionDevices.push_back({"oven",ModuleCategory::Oven,"oven",{W*.78,D*.62,0},70,{}, {"fire_hazard_area"}}); AddPoint(P,"baker",InteractionPointType::WorkerPosition,{W*.5,D*.72,0},"preparation",{"npc_workstation"},"panettiere"); return P;}
inline BuildingPlan GeneratePublicLatrinePlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::PublicLatrine); double W=N.WidthCm,D=N.DepthCm; int cap=std::max(2,N.PublicCapacity); P.Rooms={MakeRoom("entrance",RoomType::Vestibulum,ZoneFunction::Circulation,{W*.5,40,0},W*.35,80,{"public_room","street_facing"}),MakeRoom("latrine_hall",RoomType::PublicLatrineHall,ZoneFunction::Sanitary,{W*.5,D*.5,0},W*.8,D*.7,{"public_room","water_required","drainage_required"})}; Connect(P,"entrance","latrine_hall",AccessType::StreetAccess); for(int i=0;i<cap;++i){double x=80+i*(std::max(40.0,(W-160)/cap)); P.ProductionDevices.push_back({"latrine_seat_"+std::to_string(i),ModuleCategory::LatrineSeat,"latrine_hall",{x,D*.82,45},25,{}, {"water_required","drainage_required"}}); AddPoint(P,"seat_point_"+std::to_string(i),InteractionPointType::SeatingPosition,{x,D*.72,0},"latrine_hall",{"npc_customer_position"},"seduta");} P.WaterFeatures.push_back({"continuous_drain",ModuleCategory::Drain,"latrine_hall",{W*.5,D*.86,0},true,"channel","sewer",{"drainage_required"}}); P.WaterFeatures.push_back({"front_water_channel",ModuleCategory::WaterChannel,"latrine_hall",{W*.5,D*.66,0},true,"supply","drain",{"water_required"}}); P.WaterFeatures.push_back({"service_basin",ModuleCategory::ServiceBasin,"latrine_hall",{W*.85,D*.25,0},true,"supply","drain",{"water_required"}}); AddPoint(P,"latrine_entrance",InteractionPointType::Entrance,{W*.5,0,0},"entrance",{"street_facing"},"accesso pubblico"); return P;}
inline BuildingPlan GenerateSmallTemplePlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::SmallTemple); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("podium",RoomType::Podium,ZoneFunction::Religious,{W*.5,D*.5,60},W*.8,D*.75,{"religious_area","monumental_area"}),MakeRoom("pronaos",RoomType::Pronaos,ZoneFunction::Religious,{W*.5,D*.28,100},W*.55,D*.18,{"religious_area"}),MakeRoom("cella",RoomType::Cella,ZoneFunction::Religious,{W*.5,D*.58,100},W*.48,D*.35,{"religious_area","restricted_area","statue_candidate"}),MakeRoom("processional",RoomType::ProcessionalArea,ZoneFunction::Public,{W*.5,-80,0},W*.5,120,{"public_room"})}; Connect(P,"processional","pronaos",AccessType::MonumentalAccess); Connect(P,"pronaos","cella"); P.MonumentFeatures.push_back({"podium_marker",ModuleCategory::Podium,"podium",{W*.5,D*.5,60},{"monumental_area"}}); P.MonumentFeatures.push_back({"front_stair",ModuleCategory::Stair,"processional",{W*.5,0,0},{"monumental_area"}}); for(int i=0;i<4;++i){double x=W*.25+i*(W*.5/3); P.MonumentFeatures.push_back({"column_"+std::to_string(i),ModuleCategory::Column,"pronaos",{x,D*.18,100},{"religious_area"}}); P.MonumentFeatures.push_back({"capital_"+std::to_string(i),ModuleCategory::Capital,"pronaos",{x,D*.18,300},{"religious_area"}});} P.MonumentFeatures.push_back({"beam",ModuleCategory::Beam,"pronaos",{W*.5,D*.18,310},{"religious_area"}}); P.MonumentFeatures.push_back({"roof",ModuleCategory::Roof,"cella",{W*.5,D*.45,360},{"religious_area"}}); P.ReligiousFeatures.push_back({"statue_marker",ModuleCategory::StatueMarker,"cella",{W*.5,D*.62,100},{"statue_candidate"}}); if(N.HasExternalAltar) P.ReligiousFeatures.push_back({"altar",ModuleCategory::Altar,"processional",{W*.5,-140,0},{"religious_area"}}); AddPoint(P,"worship",InteractionPointType::WorshipPosition,{W*.5,-60,0},"processional",{"npc_customer_position"},"culto"); return P;}

inline RomanBuildingUrbanProfile GetUrbanProfileForBuildingType(BuildingType T){RomanBuildingUrbanProfile P; P.BuildingTypeValue=T; P.Tags={"HISTORICAL_APPROXIMATION"}; switch(T){case BuildingType::PopularHouse:P.FrequencyClassValue=FrequencyClass::VeryCommon;P.UrbanZoneCompatibility={UrbanZone::PopularResidential,UrbanZone::PeripheralDistrict};P.PreferredStreetClass={StreetClass::SecondaryRoad,StreetClass::Alley};P.PrestigeLevel=ImpactLevel::Low;P.ResidentCapacity=ImpactLevel::Medium;P.PlacementWeight=18;P.CanContainResidence=true;break;case BuildingType::MixedUseHouse:case BuildingType::Taberna:P.BuildingFunctionValue=BuildingFunction::MixedUse;P.FrequencyClassValue=FrequencyClass::VeryCommon;P.UrbanZoneCompatibility={UrbanZone::CommercialAxis,UrbanZone::MediumResidential,UrbanZone::PopularResidential};P.PreferredStreetClass={StreetClass::MarketStreet,StreetClass::SecondaryRoad};P.RequiresStreetFrontage=true;P.CustomerTraffic=ImpactLevel::High;P.PlacementWeight=16;P.CanContainShop=true;P.CanContainResidence=T==BuildingType::MixedUseHouse;break;case BuildingType::DomusMedia:P.BuildingScaleValue=BuildingScale::Medium;P.FrequencyClassValue=FrequencyClass::Common;P.UrbanZoneCompatibility={UrbanZone::MediumResidential,UrbanZone::WealthyResidential};P.PreferredStreetClass={StreetClass::SecondaryRoad};P.ResidentCapacity=ImpactLevel::Medium;P.PlacementWeight=8;P.CanContainCourtyard=true;P.CanContainResidence=true;break;case BuildingType::Insula:P.BuildingFunctionValue=BuildingFunction::MixedUse;P.BuildingScaleValue=BuildingScale::Large;P.FrequencyClassValue=FrequencyClass::Common;P.UrbanZoneCompatibility={UrbanZone::PopularResidential,UrbanZone::CommercialAxis};P.TypicalFloorCount=4;P.FireRisk=ImpactLevel::High;P.ResidentCapacity=ImpactLevel::VeryHigh;P.PlacementWeight=10;P.CanHaveUpperFloor=true;P.CanShareWall=true;break;case BuildingType::RichDomus:P.BuildingScaleValue=BuildingScale::Large;P.FrequencyClassValue=FrequencyClass::Rare;P.UrbanZoneCompatibility={UrbanZone::WealthyResidential};P.PrestigeLevel=ImpactLevel::VeryHigh;P.RequiresStreetFrontage=true;P.CanContainCourtyard=true;P.PlacementWeight=1;break;case BuildingType::Caupona:P.BuildingFunctionValue=BuildingFunction::Hospitality;P.FrequencyClassValue=FrequencyClass::Uncommon;P.UrbanZoneCompatibility={UrbanZone::CommercialAxis,UrbanZone::NearCityWall,UrbanZone::PortDistrict};P.CustomerTraffic=ImpactLevel::High;P.CanExistOutsideWalls=true;P.PlacementWeight=3;break;case BuildingType::MensaArgentaria:P.BuildingFunctionValue=BuildingFunction::Commercial;P.FrequencyClassValue=FrequencyClass::Rare;P.UrbanZoneCompatibility={UrbanZone::CivicCenter,UrbanZone::CommercialAxis};P.PreferredStreetClass={StreetClass::ForumEdge,StreetClass::MarketStreet};P.PrestigeLevel=ImpactLevel::High;P.Tags.push_back("financial_service");P.PlacementWeight=1;break;case BuildingType::Stabulum:P.BuildingFunctionValue=BuildingFunction::Hospitality;P.FrequencyClassValue=FrequencyClass::Uncommon;P.UrbanZoneCompatibility={UrbanZone::NearCityWall,UrbanZone::PeripheralDistrict,UrbanZone::PortDistrict,UrbanZone::Suburb};P.OdorLevel=ImpactLevel::High;P.RequiresWater=true;P.Tags.push_back("waste_area");P.PlacementWeight=3;break;case BuildingType::SmallTemple:P.BuildingFunctionValue=BuildingFunction::Religious;P.FrequencyClassValue=FrequencyClass::Uncommon;P.PlacementWeight=2;break;case BuildingType::Forum:case BuildingType::Amphitheatre:P.FrequencyClassValue=FrequencyClass::Unique;P.PlacementWeight=.1;break;default:P.FrequencyClassValue=FrequencyClass::Common;P.PlacementWeight=5;break;}return P;}
inline std::vector<std::pair<BuildingType,double>> GetRecommendedUrbanComposition(){return {{BuildingType::PopularHouse,18},{BuildingType::MixedUseHouse,16},{BuildingType::Taberna,16},{BuildingType::Insula,10},{BuildingType::DomusMedia,8},{BuildingType::Thermopolium,6},{BuildingType::AtriumDomus,4},{BuildingType::Fullonica,2},{BuildingType::SmallTemple,2},{BuildingType::RichDomus,1},{BuildingType::Forum,.1},{BuildingType::Amphitheatre,.1}};}
inline void AddDevice(BuildingPlan& P,std::string Id,ModuleCategory C,std::string Z,Vector3 Pos,std::vector<std::string> Tags={}){P.ProductionDevices.push_back({std::move(Id),C,std::move(Z),Pos,40,{},std::move(Tags)});}
inline BuildingPlan GenerateRectilinearUrbanPlan(const BuildingParameters& In,BuildingType T){auto N=NormalizeBuildingParameters(In);auto P=BasePlan(N,T);P.UrbanProfile=GetUrbanProfileForBuildingType(T);double W=N.WidthCm,D=N.DepthCm,H=N.FloorHeightCm;auto room=[&](std::string id,RoomType rt,ZoneFunction f,double x,double y,double w,double d,std::vector<std::string> tags){P.Rooms.push_back(MakeRoom(id,rt,f,{W*x,D*y,0},W*w,D*d,tags));};room("entrance",RoomType::Vestibulum,ZoneFunction::Circulation,.5,.05,.25,.10,{"street_facing","access"});AddPoint(P,"entrance",InteractionPointType::Entrance,{W*.5,0,0},"entrance",{"street_facing"},"accesso");
if(T==BuildingType::DomusMedia){room("atrium_or_courtyard",RoomType::Atrium,ZoneFunction::Private,.5,.25,.45,.25,{"private_room","HISTORICAL_APPROXIMATION"});room("cubiculum_a",RoomType::Cubiculum,ZoneFunction::Private,.2,.42,.25,.18,{"sleeping_area"});room("cubiculum_b",RoomType::Cubiculum,ZoneFunction::Private,.8,.42,.25,.18,{"sleeping_area"});room("triclinium",RoomType::Triclinium,ZoneFunction::Private,.35,.62,.3,.18,{"dining_area"});room("culina",RoomType::Culina,ZoneFunction::Service,.75,.62,.22,.18,{"food_preparation","fire_hazard_area"});room("latrina",RoomType::DomesticLatrine,ZoneFunction::Sanitary,.85,.82,.16,.14,{"drainage_required"});room("storage",RoomType::Storage,ZoneFunction::Storage,.25,.82,.2,.14,{"storage_area"});Connect(P,"entrance","atrium_or_courtyard",AccessType::StreetAccess);Connect(P,"atrium_or_courtyard","cubiculum_a");Connect(P,"atrium_or_courtyard","cubiculum_b");Connect(P,"atrium_or_courtyard","triclinium");Connect(P,"triclinium","culina");Connect(P,"culina","latrina");Connect(P,"culina","storage");AddPoint(P,"resident",InteractionPointType::ResidentPosition,{W*.5,D*.25,0},"atrium_or_courtyard",{},"residente");AddPoint(P,"cook",InteractionPointType::CookingPosition,{W*.75,D*.62,0},"culina",{},"cottura");}
else if(T==BuildingType::PeristyleDomus||T==BuildingType::RichDomus){room("fauces",RoomType::Fauces,ZoneFunction::Circulation,.5,.08,.2,.12,{"street_facing"});room("atrium",RoomType::Atrium,ZoneFunction::Private,.5,.25,.55,.22,{"mosaic_candidate"});room("tablinum",RoomType::Tablinum,ZoneFunction::Private,.5,.43,.32,.14,{"axis_room"});room("peristyle",RoomType::Peristyle,ZoneFunction::OpenSpace,.5,.68,.65,.28,{"open_court"});room("garden",RoomType::Garden,ZoneFunction::OpenSpace,.5,.70,.42,.16,{"garden_inside_peristyle"});room("triclinium",RoomType::Triclinium,ZoneFunction::Private,.25,.55,.25,.15,{"representation_room"});room("oecus",RoomType::Oecus,ZoneFunction::Private,.75,.55,.25,.15,{"representation_room"});room("culina",RoomType::Culina,ZoneFunction::Service,.15,.84,.18,.12,{"service_room","food_preparation"});room("latrina",RoomType::DomesticLatrine,ZoneFunction::Sanitary,.85,.84,.14,.12,{"service_room","drainage_required"});Connect(P,"entrance","fauces",AccessType::StreetAccess);Connect(P,"fauces","atrium");Connect(P,"atrium","tablinum");Connect(P,"tablinum","peristyle");Connect(P,"peristyle","garden");Connect(P,"peristyle","triclinium");Connect(P,"peristyle","oecus");Connect(P,"peristyle","culina");Connect(P,"culina","latrina");for(int i=0;i<8;i++)AddDevice(P,"peristyle_column_"+std::to_string(i),ModuleCategory::Column,"peristyle",{W*(.2+.6*(i%4)/3.0),D*(i<4?.56:.80),0},{"portico_colonnato"});P.MonumentFeatures.push_back({"fountain",ModuleCategory::Fountain,"garden",{W*.5,D*.70,0},{"water_feature_placeholder"}});P.MonumentFeatures.push_back({"mosaic_zone",ModuleCategory::MosaicZone,"atrium",{W*.5,D*.25,1},{"future_decoration"}});P.MonumentFeatures.push_back({"fresco_zone",ModuleCategory::FrescoZone,"oecus",{W*.75,D*.55,1},{"future_decoration"}});AddPoint(P,"resident",InteractionPointType::ResidentPosition,{W*.5,D*.25,0},"atrium",{},"dominus");AddPoint(P,"dining",InteractionPointType::DiningPosition,{W*.25,D*.55,0},"triclinium",{},"convivio");if(T==BuildingType::RichDomus){room("guest_room",RoomType::GuestRoom,ZoneFunction::Private,.5,.90,.24,.12,{"guest_lodging"});room("service_quarter",RoomType::ServiceRoom,ZoneFunction::Service,.15,.70,.2,.15,{"service_quarter"});Connect(P,"peristyle","guest_room");Connect(P,"service_quarter","culina");AddPoint(P,"guest",InteractionPointType::GuestPosition,{W*.5,D*.90,0},"guest_room",{},"ospite");}}
else if(T==BuildingType::PopularHouse||T==BuildingType::Cenaculum){room("poor_dwelling",RoomType::PoorDwellingRoom,ZoneFunction::Private,.5,.32,.7,.42,{"multifunctional_room","sleeping_area"});room("cooking_corner",RoomType::Culina,ZoneFunction::Service,.25,.68,.24,.18,{"food_preparation"});room("storage",RoomType::Storage,ZoneFunction::Storage,.75,.68,.2,.18,{"storage_area"});Connect(P,"entrance","poor_dwelling",AccessType::StreetAccess);Connect(P,"poor_dwelling","cooking_corner");Connect(P,"poor_dwelling","storage");AddPoint(P,"resident",InteractionPointType::ResidentPosition,{W*.5,D*.32,(T==BuildingType::Cenaculum?H:0)},"poor_dwelling",{},"residente");AddPoint(P,"sleep",InteractionPointType::SleepingPosition,{W*.6,D*.4,(T==BuildingType::Cenaculum?H:0)},"poor_dwelling",{},"riposo");if(T==BuildingType::Cenaculum){P.Rooms.push_back(MakeRoom("shared_stair",RoomType::SharedStair,ZoneFunction::Circulation,{W*.12,D*.2,0},W*.16,D*.22,{"upper_floor","shared_access"}));Connect(P,"entrance","shared_stair");Connect(P,"shared_stair","poor_dwelling");P.Apartments.push_back({"cenaculum_unit",1,2,3,"shared_stair",true,true,false,true,false,"modest",{"cenaculum"}});AddDevice(P,"apartment_door",ModuleCategory::ApartmentDoor,"poor_dwelling",{W*.5,D*.12,H},{"upper_floor"});}}
else {bool shop=T==BuildingType::Taberna||T==BuildingType::Popina||T==BuildingType::Bookshop||T==BuildingType::MedicalShop||T==BuildingType::BarberShop||T==BuildingType::MensaArgentaria||T==BuildingType::MixedUseHouse;room("customer_area",shop?RoomType::CustomerArea:RoomType::CommonRoom,ZoneFunction::Commercial,.5,.25,.65,.28,{"customer_area","street_facing"});room("counter_area",T==BuildingType::MensaArgentaria?RoomType::FinancialCounterArea:RoomType::CounterArea,ZoneFunction::Commercial,.5,.42,.55,.16,{T==BuildingType::MensaArgentaria?"counter_area financial_service":"counter_area"});room("storage",T==BuildingType::MensaArgentaria?RoomType::ValueStorage:RoomType::CommercialStorage,ZoneFunction::Storage,.25,.70,.25,.18,{"storage_area"});Connect(P,"entrance","customer_area",AccessType::StreetAccess);Connect(P,"customer_area","counter_area",AccessType::ShopfrontAccess);Connect(P,"counter_area","storage");AddDevice(P,"shop_opening",ModuleCategory::ShopOpening,"entrance",{W*.5,0,0},{"street_frontage"});AddDevice(P,"counter",ModuleCategory::Counter,"counter_area",{W*.5,D*.42,0},{"sales"});AddDevice(P,"storage_container",T==BuildingType::MensaArgentaria?ModuleCategory::ValueStorageMarker:ModuleCategory::StorageContainer,"storage",{W*.25,D*.70,0},{"storage_area"});AddPoint(P,"customer",InteractionPointType::CustomerPosition,{W*.5,D*.25,0},"customer_area",{},"cliente");AddPoint(P,"vendor",T==BuildingType::MedicalShop?InteractionPointType::MedicalWorkerPosition:T==BuildingType::BarberShop?InteractionPointType::BarberPosition:T==BuildingType::MensaArgentaria?InteractionPointType::BankerPosition:InteractionPointType::ShopkeeperPosition,{W*.5,D*.42,0},"counter_area",{},"addetto");AddPoint(P,"queue",InteractionPointType::QueuePosition,{W*.35,D*.12,0},"customer_area",{},"coda");
if(T==BuildingType::Popina||T==BuildingType::Caupona){room("kitchen",RoomType::KitchenArea,ZoneFunction::Service,.75,.65,.25,.2,{"food_preparation"});Connect(P,"counter_area","kitchen");AddDevice(P,"table",ModuleCategory::Table,"customer_area",{W*.4,D*.28,0},{"dining"});AddDevice(P,"bench",ModuleCategory::Bench,"customer_area",{W*.6,D*.28,0},{"seating"});AddPoint(P,"dining",InteractionPointType::DiningPosition,{W*.45,D*.28,0},"customer_area",{},"seduta");}
if(T==BuildingType::Caupona){room("lodging_room",RoomType::LodgingRoom,ZoneFunction::Private,.75,.82,.28,.16,{"guest_lodging"});Connect(P,"kitchen","lodging_room");AddDevice(P,"bed",ModuleCategory::Bed,"lodging_room",{W*.75,D*.82,0},{"guest_bed"});AddPoint(P,"guest",InteractionPointType::GuestPosition,{W*.75,D*.82,0},"lodging_room",{},"ospite");}
if(T==BuildingType::Bookshop){room("copying_room",RoomType::CopyingRoom,ZoneFunction::Productive,.75,.70,.25,.18,{"copying_area"});Connect(P,"counter_area","copying_room");AddDevice(P,"shelf",ModuleCategory::Shelf,"customer_area",{W*.2,D*.25,0},{"scroll_display"});AddDevice(P,"writing_desk",ModuleCategory::WritingDesk,"copying_room",{W*.75,D*.70,0},{"scribe_station"});AddDevice(P,"scroll_storage",ModuleCategory::ScrollStorage,"storage",{W*.25,D*.70,0},{"ScrollStorageMarker"});AddPoint(P,"scribe",InteractionPointType::ScribePosition,{W*.75,D*.70,0},"copying_room",{},"scriba");}
if(T==BuildingType::Brothel){P.Rooms.clear();room("corridor",RoomType::Corridor,ZoneFunction::Circulation,.5,.35,.25,.5,{"privacy_limited"});room("cubiculum_a",RoomType::Cubiculum,ZoneFunction::Private,.25,.35,.22,.18,{"adult_service_area","non_explicit"});room("cubiculum_b",RoomType::Cubiculum,ZoneFunction::Private,.75,.35,.22,.18,{"adult_service_area","non_explicit"});room("common_room",RoomType::CommonRoom,ZoneFunction::Public,.5,.70,.55,.2,{"common_area"});Connect(P,"entrance","corridor",AccessType::StreetAccess);Connect(P,"corridor","cubiculum_a");Connect(P,"corridor","cubiculum_b");Connect(P,"corridor","common_room");}
if(T==BuildingType::MedicalShop){room("preparation",RoomType::MedicalPreparationRoom,ZoneFunction::Service,.75,.70,.25,.18,{"medical_service","medicine_storage","preparation_area"});Connect(P,"counter_area","preparation");AddDevice(P,"workbench",ModuleCategory::Workbench,"preparation",{W*.75,D*.70,0},{"medical_service"});}
if(T==BuildingType::BarberShop){room("barber_area",RoomType::BarberArea,ZoneFunction::Commercial,.75,.60,.25,.20,{"barber_service"});Connect(P,"counter_area","barber_area");AddDevice(P,"seat",ModuleCategory::Seat,"barber_area",{W*.75,D*.60,0},{"barber_chair"});AddDevice(P,"mirror",ModuleCategory::MirrorMarker,"barber_area",{W*.8,D*.56,100},{"MirrorMarker"});}
if(T==BuildingType::Stabulum){P.Rooms.clear();room("stable_hall",RoomType::StableHall,ZoneFunction::AnimalWork,.5,.35,.75,.45,{"animal_area"});room("stall_a",RoomType::Stall,ZoneFunction::AnimalWork,.25,.35,.2,.25,{"stall"});room("stall_b",RoomType::Stall,ZoneFunction::AnimalWork,.75,.35,.2,.25,{"stall"});room("fodder_storage",RoomType::Storage,ZoneFunction::Storage,.25,.78,.25,.16,{"fodder_storage"});Connect(P,"entrance","stable_hall",AccessType::StreetAccess);Connect(P,"stable_hall","stall_a");Connect(P,"stable_hall","stall_b");Connect(P,"stable_hall","fodder_storage");AddDevice(P,"feeding_trough",ModuleCategory::FeedingTrough,"stable_hall",{W*.35,D*.45,0},{"FeedingPosition"});AddDevice(P,"watering_trough",ModuleCategory::WateringTrough,"stable_hall",{W*.65,D*.45,0},{"WateringPosition"});AddPoint(P,"animal",InteractionPointType::AnimalPosition,{W*.35,D*.35,0},"stall_a",{},"animale");AddPoint(P,"feeding",InteractionPointType::FeedingPosition,{W*.35,D*.45,0},"stable_hall",{},"foraggio");AddPoint(P,"watering",InteractionPointType::WateringPosition,{W*.65,D*.45,0},"stable_hall",{},"acqua");AddPoint(P,"stable_worker",InteractionPointType::StableWorkerPosition,{W*.5,D*.55,0},"stable_hall",{},"stalliere");}}
if(T==BuildingType::Insula){P.Rooms.clear();room("common_entrance",RoomType::SharedHall,ZoneFunction::Circulation,.5,.08,.25,.12,{"street_facing"});room("shared_stair",RoomType::SharedStair,ZoneFunction::Circulation,.15,.35,.18,.30,{"shared_access"});room("light_court",RoomType::LightCourt,ZoneFunction::OpenSpace,.5,.45,.25,.25,{"light_court"});room("ground_taberna",RoomType::Shopfront,ZoneFunction::Commercial,.75,.18,.35,.25,{"street_facing","commercial_area"});Connect(P,"common_entrance","shared_stair",AccessType::StreetAccess);Connect(P,"shared_stair","light_court");Connect(P,"ground_taberna","storage",AccessType::ShopfrontAccess);for(int f=1;f<std::max(2,N.FloorCount);++f){P.Apartments.push_back({"apartment_"+std::to_string(f),f,2,4,"shared_stair",true,f%2==0,f%2==1,true,false,"modest",{"cenaculum","apartment_accessible"}});P.Rooms.push_back(MakeRoom("apartment_"+std::to_string(f),RoomType::Apartment,ZoneFunction::Private,{W*.55,D*.35,H*f},W*.55,D*.25,{"upper_floor","apartment"}));Connect(P,"shared_stair","apartment_"+std::to_string(f));}AddDevice(P,"shared_stair_marker",ModuleCategory::SharedStair,"shared_stair",{W*.15,D*.35,0},{"shared_stair"});AddDevice(P,"balcony_placeholder",ModuleCategory::Balcony,"apartment_1",{W*.75,0,H},{"balcony_placeholder"});AddPoint(P,"resident",InteractionPointType::ResidentPosition,{W*.55,D*.35,H},"apartment_1",{},"inquilino");}
if(T==BuildingType::MixedUseHouse){P.Composite.UseUnits.push_back({"shop",0,BuildingFunction::Commercial,0,1,4,"entrance","future_owner","future_workers","future_customers","future_hours",{"taberna_plus_residence"}});P.Composite.UseUnits.push_back({"residence",1,BuildingFunction::Residential,4,0,0,"stair","future_owner","","","future_hours",{"owner_dwelling"}});room("stair",RoomType::SharedStair,ZoneFunction::Circulation,.15,.70,.16,.22,{"residential_access"});room("upper_room",RoomType::UpperRoom,ZoneFunction::Private,.55,.70,.4,.20,{"upper_floor","residence"});Connect(P,"customer_area","stair");Connect(P,"stair","upper_room");}
return P;}
inline BuildingPlan GenerateDomusMediaPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::DomusMedia);} inline BuildingPlan GeneratePeristyleDomusPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::PeristyleDomus);} inline BuildingPlan GenerateRichDomusPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::RichDomus);} inline BuildingPlan GeneratePopularHousePlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::PopularHouse);} inline BuildingPlan GenerateInsulaPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::Insula);} inline BuildingPlan GenerateCenaculumPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::Cenaculum);} inline BuildingPlan GenerateMixedUseHousePlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::MixedUseHouse);} inline BuildingPlan GenerateTabernaPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::Taberna);} inline BuildingPlan GeneratePopinaPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::Popina);} inline BuildingPlan GenerateCauponaPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::Caupona);} inline BuildingPlan GenerateBookshopPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::Bookshop);} inline BuildingPlan GenerateBrothelPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::Brothel);} inline BuildingPlan GenerateMedicalShopPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::MedicalShop);} inline BuildingPlan GenerateBarberShopPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::BarberShop);} inline BuildingPlan GenerateMensaArgentariaPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::MensaArgentaria);} inline BuildingPlan GenerateStabulumPlan(const BuildingParameters& P){return GenerateRectilinearUrbanPlan(P,BuildingType::Stabulum);}
inline void ConnectBuildingToWater(BuildingPlan& P,std::string From="supply"){P.WaterNodes.push_back({From,WaterSourceType::Aqueduct,{0,0,0},100,true,true,{"water_supply"}});P.UtilityConnections.push_back({"water_connection",From,"building",UtilityType::WaterSupply,100,true,{"water_required"}});}
inline void ConnectBuildingToDrainage(BuildingPlan& P){P.DrainageNodes.push_back({"drain",DrainageType::CoveredDrain,{0,0,0},100,.01,true,true,{"drainage_required"}});P.UtilityConnections.push_back({"drainage_connection","building","drain",UtilityType::Drainage,100,true,{"drainage_required"}});}
inline void ConnectBuildingToSewer(BuildingPlan& P){P.UtilityConnections.push_back({"sewer_connection","drain","sewer",UtilityType::Sewer,100,true,{"sewer"}});}
inline void ConnectBuildingToHeat(BuildingPlan& P,std::string Zone="work"){P.HeatSources.push_back({"heat_source",Zone,HeatSourceType::Furnace,{P.PlanBounds.Max.X*.75,P.PlanBounds.Max.Y*.75,0},50,{"heat_required"}});P.UtilityConnections.push_back({"heat_connection","heat_source",Zone,UtilityType::Heating,50,true,{"heating"}});}
inline bool ValidateUtilityConnections(const BuildingPlan& P,std::vector<GenerationMessage>& W,std::vector<GenerationMessage>& E){(void)W;for(const auto& U:P.UtilityConnections)if(!U.bConnected||U.FromNodeId.empty()||U.ToNodeId.empty())AddMessage(E,"InvalidUtilityConnection","Connessione utility incompleta.",true);if(P.UrbanProfile.RequiresWater&&P.WaterNodes.empty())AddMessage(E,"MissingWaterConnection","Acqua richiesta ma non collegata.",true);if(P.UrbanProfile.RequiresDrainage&&P.DrainageNodes.empty())AddMessage(E,"MissingDrainageConnection","Drenaggio richiesto ma non collegato.",true);return E.empty();}
inline double CalculateWaterDemand(const BuildingPlan& P){return P.WaterNodes.size()*10.0+P.BathRooms.size()*25.0+P.ProductionFlows.size()*5.0;}
inline double CalculateDrainageDemand(const BuildingPlan& P){return P.DrainageNodes.size()*10.0+P.BathRooms.size()*20.0+P.ProductionFlows.size()*5.0;}
inline double CalculateHeatDemand(const BuildingPlan& P){double N=0;for(const auto& H:P.HeatSources)N+=H.Output;return N;}
inline double CalculateStorageCapacity(const BuildingPlan& P){double N=0;for(const auto& S:P.StorageUnits)N+=S.Capacity;return N;}
inline BuildingPlan GenerateUtilitiesProductionPlan(const BuildingParameters& In,BuildingType T){auto N=NormalizeBuildingParameters(In);auto P=BasePlan(N,T);P.UrbanProfile=GetUrbanProfileForBuildingType(T);P.UrbanProfile.BuildingFunctionValue=BuildingFunction::Productive;P.UrbanProfile.RequiresServiceAccess=true;P.UrbanProfile.Tags.push_back("HISTORICAL_APPROXIMATION");double W=N.WidthCm,D=N.DepthCm;auto room=[&](std::string id,RoomType rt,ZoneFunction f,double x,double y,ModuleCategory equipment,std::vector<std::string> tags){P.Rooms.push_back(MakeRoom(id,rt,f,{W*x,D*y,0},W*.55,D*.18,tags));if(equipment!=ModuleCategory::Prop)AddDevice(P,id+"_equipment",equipment,id,{W*x,D*y,0},tags);};room("entrance",RoomType::Vestibulum,ZoneFunction::Circulation,.5,.06,ModuleCategory::Prop,{"street_facing"});AddPoint(P,"entrance",InteractionPointType::Entrance,{W*.5,0,0},"entrance",{"street_facing"},"accesso");
auto stage=[&](std::string id,int order,ModuleCategory equipment){ProductionStageDefinition S;S.Id=id;S.ZoneId=id;S.Order=order;S.Equipment=equipment;S.Tags={"production_stage"};return S;};
if(T==BuildingType::BathComplex){P.UrbanProfile.BuildingFunctionValue=BuildingFunction::Sanitary;P.UrbanProfile.FrequencyClassValue=FrequencyClass::Rare;P.UrbanProfile.RequiresWater=P.UrbanProfile.RequiresDrainage=true;room("apodyterium",RoomType::Apodyterium,ZoneFunction::Public,.25,.22,ModuleCategory::Bench,{"public_room"});room("frigidarium",RoomType::Frigidarium,ZoneFunction::Hydraulic,.7,.25,ModuleCategory::FountainBasin,{"cold_room","water_required"});room("tepidarium",RoomType::Tepidarium,ZoneFunction::Sanitary,.3,.48,ModuleCategory::HypocaustPillar,{"warm_room"});room("calidarium",RoomType::Calidarium,ZoneFunction::Sanitary,.7,.50,ModuleCategory::HypocaustPillar,{"hot_room","water_required"});room("praefurnium",RoomType::FurnaceArea,ZoneFunction::Service,.8,.78,ModuleCategory::Furnace,{"service_room","fire_hazard_area"});room("latrina",RoomType::PublicLatrineHall,ZoneFunction::Sanitary,.2,.78,ModuleCategory::Drain,{"drainage_required"});P.BathRooms={{"frigidarium",18,true,true,true,false},{"tepidarium",32,true,true,true,true},{"calidarium",42,true,true,true,true}};P.Hypocausts.push_back({"hypocaust","calidarium","praefurnium",12,80});ConnectBuildingToWater(P,"cistern");ConnectBuildingToDrainage(P);ConnectBuildingToSewer(P);ConnectBuildingToHeat(P,"calidarium");AddPoint(P,"bather",InteractionPointType::BatherPosition,{W*.7,D*.25,0},"frigidarium",{},"bagnante");AddPoint(P,"attendant",InteractionPointType::BathAttendantPosition,{W*.25,D*.22,0},"apodyterium",{},"addetto");}
else if(T==BuildingType::Palaestra){P.UrbanProfile.BuildingFunctionValue=BuildingFunction::Civic;room("exercise_court",RoomType::Palaestra,ZoneFunction::OpenSpace,.5,.42,ModuleCategory::Portico,{"open_court","exercise_area"});room("equipment_storage",RoomType::Storage,ZoneFunction::Storage,.25,.75,ModuleCategory::StorageContainer,{"storage_area"});ConnectBuildingToWater(P,"fountain");AddPoint(P,"athlete",InteractionPointType::AthletePosition,{W*.5,D*.42,0},"exercise_court",{},"atleta");}
else if(T==BuildingType::CastellumAquae||T==BuildingType::AqueductSection||T==BuildingType::SewerSection||T==BuildingType::PublicFountain||T==BuildingType::Cistern||T==BuildingType::Well){P.UrbanProfile.BuildingFunctionValue=BuildingFunction::Hydraulic;P.UrbanProfile.RequiresWater=true;ModuleCategory C=T==BuildingType::AqueductSection?ModuleCategory::AqueductChannel:T==BuildingType::SewerSection?ModuleCategory::SewerChannel:T==BuildingType::PublicFountain?ModuleCategory::FountainBasin:T==BuildingType::Cistern?ModuleCategory::CisternTank:T==BuildingType::Well?ModuleCategory::WellHead:ModuleCategory::WaterOutlet;room("hydraulic_structure",RoomType::FountainCourt,ZoneFunction::Hydraulic,.5,.45,C,{"water_required","inspection_access"});ConnectBuildingToWater(P,T==BuildingType::Well?"well":T==BuildingType::Cistern?"cistern":"aqueduct");if(T!=BuildingType::Well){P.UrbanProfile.RequiresDrainage=true;ConnectBuildingToDrainage(P);}if(T==BuildingType::AqueductSection){AddDevice(P,"aqueduct_arch",ModuleCategory::AqueductArch,"hydraulic_structure",{W*.25,D*.45,0},{"arcade"});P.AqueductSegments.push_back({"aqueduct_segment","inlet","outlet",{0,D*.5,300},{W,D*.5,299},.001,100,true});}if(T==BuildingType::SewerSection){P.SewerSegments.push_back({"sewer_segment","inlet","outlet",{0,D*.5,-100},{W,D*.5,-110},.01,100,true,true});AddDevice(P,"manhole",ModuleCategory::Manhole,"hydraulic_structure",{W*.5,D*.5,0},{"maintenance"});AddPoint(P,"sewer_worker",InteractionPointType::SewerWorkerPosition,{W*.5,D*.5,0},"hydraulic_structure",{},"manutentore");}if(T==BuildingType::PublicFountain){AddPoint(P,"fountain_user",InteractionPointType::FountainUserPosition,{W*.5,D*.25,0},"hydraulic_structure",{},"utente");AddPoint(P,"water_carrier",InteractionPointType::WaterCarrierPosition,{W*.35,D*.25,0},"hydraulic_structure",{},"portatore");}}
else if(T==BuildingType::UrbanGarden||T==BuildingType::ServiceYard){P.UrbanProfile.BuildingFunctionValue=BuildingFunction::Productive;room(T==BuildingType::UrbanGarden?"garden":"service_yard",T==BuildingType::UrbanGarden?RoomType::Garden:RoomType::ServiceYard,T==BuildingType::UrbanGarden?ZoneFunction::OpenSpace:ZoneFunction::Service,.5,.45,T==BuildingType::UrbanGarden?ModuleCategory::IrrigationChannel:ModuleCategory::CargoArea,{T==BuildingType::UrbanGarden?"domestic_production":"loading_area"});if(T==BuildingType::UrbanGarden){ConnectBuildingToWater(P,"cistern");AddPoint(P,"gardener",InteractionPointType::GardenerPosition,{W*.5,D*.45,0},"garden",{},"ortolano");}else{AddDevice(P,"waste_area",ModuleCategory::WasteArea,"service_yard",{W*.75,D*.65,0},{"waste_area"});AddPoint(P,"loader",InteractionPointType::LoaderPosition,{W*.4,D*.45,0},"service_yard",{},"carico");}}
else {ProductionFlowType F=ProductionFlowType::Storage;InteractionPointType Worker=InteractionPointType::WorkerPosition;ModuleCategory Main=ModuleCategory::Workbench;bool water=false,drain=false,heat=false;switch(T){case BuildingType::Tinctoria:F=ProductionFlowType::Dyeing;Worker=InteractionPointType::DyerPosition;Main=ModuleCategory::Basin;water=drain=heat=true;break;case BuildingType::Tannery:F=ProductionFlowType::Tanning;Worker=InteractionPointType::TannerPosition;Main=ModuleCategory::Basin;water=drain=true;break;case BuildingType::TextileWorkshop:F=ProductionFlowType::Textile;Worker=InteractionPointType::WeaverPosition;Main=ModuleCategory::Loom;break;case BuildingType::MetalWorkshop:F=ProductionFlowType::Metalworking;Worker=InteractionPointType::SmithPosition;Main=ModuleCategory::Anvil;heat=true;break;case BuildingType::PotteryWorkshop:F=ProductionFlowType::Pottery;Worker=InteractionPointType::PotterPosition;Main=ModuleCategory::PotteryWheel;heat=true;break;case BuildingType::OilWorkshop:F=ProductionFlowType::Oil;Worker=InteractionPointType::PressOperatorPosition;Main=ModuleCategory::Press;drain=true;break;case BuildingType::Winery:F=ProductionFlowType::Wine;Worker=InteractionPointType::PressOperatorPosition;Main=ModuleCategory::Press;drain=true;break;case BuildingType::PressingWorkshop:F=ProductionFlowType::Oil;Worker=InteractionPointType::PressOperatorPosition;Main=ModuleCategory::Press;break;case BuildingType::StandaloneOven:F=ProductionFlowType::Baking;Main=ModuleCategory::Oven;heat=true;break;case BuildingType::Horrea:F=ProductionFlowType::Storage;Worker=InteractionPointType::WarehouseWorkerPosition;Main=ModuleCategory::StorageCell;break;default:break;}room("reception",RoomType::RawMaterialStorage,ZoneFunction::Storage,.25,.22,ModuleCategory::CargoArea,{"raw_material"});room("preparation",RoomType::PreparationArea,ZoneFunction::Productive,.65,.30,ModuleCategory::Workbench,{"production_area"});room("work",RoomType::WorkshopArea,ZoneFunction::Productive,.45,.55,Main,{"production_area"});room("finished_storage",RoomType::FinishedGoodsStorage,ZoneFunction::Storage,.65,.80,ModuleCategory::StorageCell,{"storage_area"});P.ProductionFlows.push_back({"production_flow",F,{stage("reception",0,ModuleCategory::CargoArea),stage("preparation",1,ModuleCategory::Workbench),stage("work",2,Main),stage("finished_storage",3,ModuleCategory::StorageCell)},{"complete_flow"}});P.StorageUnits.push_back({"storage","finished_storage",T==BuildingType::Horrea?1000.0:100.0,T==BuildingType::Horrea,T==BuildingType::Horrea,{"storage_capacity"}});if(water){P.UrbanProfile.RequiresWater=true;ConnectBuildingToWater(P);}if(drain){P.UrbanProfile.RequiresDrainage=true;ConnectBuildingToDrainage(P);}if(heat){ConnectBuildingToHeat(P,"work");P.HazardZones.push_back({"heat_hazard","work","heat",{W*.45,D*.55,0},100,ImpactLevel::VeryHigh,{"fire_hazard_area"}});AddDevice(P,"fuel_storage",ModuleCategory::FuelStorage,"work",{W*.8,D*.55,0},{"fuel"});}AddPoint(P,"worker",Worker,{W*.45,D*.55,0},"work",{"npc_workstation"},"lavoratore");if(T==BuildingType::Horrea){AddPoint(P,"guard",InteractionPointType::GuardPosition,{W*.3,D*.22,0},"reception",{},"guardia");AddPoint(P,"unloader",InteractionPointType::UnloaderPosition,{W*.2,D*.22,0},"reception",{},"scarico");}}
for(std::size_t i=1;i<P.Rooms.size();++i)Connect(P,P.Rooms[i-1].Id,P.Rooms[i].Id,i==1?AccessType::StreetAccess:AccessType::InternalAccess);return P;}
inline BuildingPlan GenerateBathComplexPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::BathComplex);} inline BuildingPlan GeneratePalaestraPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::Palaestra);} inline BuildingPlan GenerateCastellumAquaePlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::CastellumAquae);} inline BuildingPlan GenerateAqueductSectionPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::AqueductSection);} inline BuildingPlan GenerateSewerSectionPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::SewerSection);} inline BuildingPlan GeneratePublicFountainPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::PublicFountain);} inline BuildingPlan GenerateCisternPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::Cistern);} inline BuildingPlan GenerateWellPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::Well);} inline BuildingPlan GenerateTinctoriaPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::Tinctoria);} inline BuildingPlan GenerateTanneryPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::Tannery);} inline BuildingPlan GenerateTextileWorkshopPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::TextileWorkshop);} inline BuildingPlan GenerateMetalWorkshopPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::MetalWorkshop);} inline BuildingPlan GeneratePotteryWorkshopPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::PotteryWorkshop);} inline BuildingPlan GenerateOilWorkshopPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::OilWorkshop);} inline BuildingPlan GenerateWineryPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::Winery);} inline BuildingPlan GeneratePressingWorkshopPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::PressingWorkshop);} inline BuildingPlan GenerateStandaloneOvenPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::StandaloneOven);} inline BuildingPlan GenerateHorreaPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::Horrea);} inline BuildingPlan GenerateUrbanGardenPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::UrbanGarden);} inline BuildingPlan GenerateServiceYardPlan(const BuildingParameters& P){return GenerateUtilitiesProductionPlan(P,BuildingType::ServiceYard);}
inline bool ValidateCompositeBuildingPlan(const BuildingPlan& Plan,std::vector<GenerationMessage>& W,std::vector<GenerationMessage>& E){(void)W; for(const auto& U:Plan.Composite.UseUnits){if(U.AccessId.empty())AddMessage(E,"CompositeMissingAccess","Unita d'uso senza accesso.",true);}return E.empty();}
inline std::int32_t CalculateResidentCapacity(const BuildingPlan& Plan){int n=0; for(const auto& A:Plan.Apartments)n+=A.Capacity; for(const auto& U:Plan.Composite.UseUnits)n+=U.ResidentCapacity; if(n==0){for(const auto& P:Plan.InteractionPoints) if(P.Type==InteractionPointType::ResidentPosition||P.Type==InteractionPointType::SleepingPosition)n+=std::max(1,P.Capacity);} return n;}
inline std::int32_t CalculateWorkerCapacity(const BuildingPlan& Plan){int n=0; for(const auto& U:Plan.Composite.UseUnits)n+=U.WorkerCapacity; for(const auto& P:Plan.InteractionPoints) if(P.Type==InteractionPointType::WorkerPosition||P.Type==InteractionPointType::ShopkeeperPosition||P.Type==InteractionPointType::MedicalWorkerPosition||P.Type==InteractionPointType::BarberPosition||P.Type==InteractionPointType::BankerPosition||P.Type==InteractionPointType::StableWorkerPosition)n+=std::max(1,P.Capacity); return n;}
inline std::int32_t CalculateCustomerCapacity(const BuildingPlan& Plan){int n=0; for(const auto& U:Plan.Composite.UseUnits)n+=U.CustomerCapacity; for(const auto& P:Plan.InteractionPoints) if(P.Type==InteractionPointType::CustomerPosition||P.Type==InteractionPointType::DiningPosition||P.Type==InteractionPointType::GuestPosition)n+=std::max(1,P.Capacity); return n;}

inline BuildingPlan GenerateBuildingPlan(const BuildingParameters& P){switch(P.Type){
case BuildingType::BathComplex:return GenerateBathComplexPlan(P);case BuildingType::Palaestra:return GeneratePalaestraPlan(P);case BuildingType::CastellumAquae:return GenerateCastellumAquaePlan(P);case BuildingType::AqueductSection:return GenerateAqueductSectionPlan(P);case BuildingType::SewerSection:return GenerateSewerSectionPlan(P);case BuildingType::PublicFountain:return GeneratePublicFountainPlan(P);case BuildingType::Cistern:return GenerateCisternPlan(P);case BuildingType::Well:return GenerateWellPlan(P);case BuildingType::Tinctoria:return GenerateTinctoriaPlan(P);case BuildingType::Tannery:return GenerateTanneryPlan(P);case BuildingType::TextileWorkshop:return GenerateTextileWorkshopPlan(P);case BuildingType::MetalWorkshop:return GenerateMetalWorkshopPlan(P);case BuildingType::PotteryWorkshop:return GeneratePotteryWorkshopPlan(P);case BuildingType::OilWorkshop:return GenerateOilWorkshopPlan(P);case BuildingType::Winery:return GenerateWineryPlan(P);case BuildingType::PressingWorkshop:return GeneratePressingWorkshopPlan(P);case BuildingType::StandaloneOven:return GenerateStandaloneOvenPlan(P);case BuildingType::Horrea:return GenerateHorreaPlan(P);case BuildingType::UrbanGarden:return GenerateUrbanGardenPlan(P);case BuildingType::ServiceYard:return GenerateServiceYardPlan(P);
case BuildingType::DomusMedia:return GenerateDomusMediaPlan(P);case BuildingType::PeristyleDomus:return GeneratePeristyleDomusPlan(P);case BuildingType::RichDomus:return GenerateRichDomusPlan(P);case BuildingType::PopularHouse:return GeneratePopularHousePlan(P);case BuildingType::Insula:return GenerateInsulaPlan(P);case BuildingType::Cenaculum:return GenerateCenaculumPlan(P);case BuildingType::MixedUseHouse:return GenerateMixedUseHousePlan(P);case BuildingType::Taberna:return GenerateTabernaPlan(P);case BuildingType::Popina:return GeneratePopinaPlan(P);case BuildingType::Caupona:return GenerateCauponaPlan(P);case BuildingType::Bookshop:return GenerateBookshopPlan(P);case BuildingType::Brothel:return GenerateBrothelPlan(P);case BuildingType::MedicalShop:return GenerateMedicalShopPlan(P);case BuildingType::BarberShop:return GenerateBarberShopPlan(P);case BuildingType::MensaArgentaria:return GenerateMensaArgentariaPlan(P);case BuildingType::Stabulum:return GenerateStabulumPlan(P);case BuildingType::AtriumDomus:return GenerateAtriumDomusPlan(P);case BuildingType::Thermopolium:return GenerateThermopoliumPlan(P);case BuildingType::Fullonica:return GenerateFullonicaPlan(P);case BuildingType::Pistrinum:return GeneratePistrinumPlan(P);case BuildingType::PublicLatrine:return GeneratePublicLatrinePlan(P);case BuildingType::SmallTemple:return GenerateSmallTemplePlan(P);default:{auto B=BasePlan(P,P.Type);AddMessage(B.Warnings,"ARCHETYPE_PLANNED","Archetipo registrato ma non implementato.",false);return B;}}}
inline BuildingPlanResult GenerateBuildingPlanResult(const BuildingParameters& P){BuildingPlanResult R; R.Plan=GenerateBuildingPlan(P); ValidateBuildingPlan(R.Plan,R.Warnings,R.Errors); R.Placements=ConvertBuildingPlanToPlacements(R.Plan,P).Placements; R.bSuccess=R.Errors.empty()&&R.Plan.ImplementationState==ArchetypeImplementationState::Implemented; return R;}
inline GenerationResult BuildPlanLayout(BuildingParameters P, BuildingType T){P.Type=T; auto Plan=GenerateBuildingPlan(P); std::vector<GenerationMessage> W,E; ValidateBuildingPlan(Plan,W,E); Plan.Warnings.insert(Plan.Warnings.end(),W.begin(),W.end()); Plan.Errors.insert(Plan.Errors.end(),E.begin(),E.end()); return ConvertBuildingPlanToPlacements(Plan,P);}
inline GenerationResult GenerateDomusMediaLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::DomusMedia);} inline GenerationResult GeneratePeristyleDomusLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::PeristyleDomus);} inline GenerationResult GenerateRichDomusLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::RichDomus);} inline GenerationResult GeneratePopularHouseLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::PopularHouse);} inline GenerationResult GenerateInsulaLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Insula);} inline GenerationResult GenerateCenaculumLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Cenaculum);} inline GenerationResult GenerateMixedUseHouseLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::MixedUseHouse);} inline GenerationResult GenerateTabernaPlanLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Taberna);} inline GenerationResult GeneratePopinaLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Popina);} inline GenerationResult GenerateCauponaLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Caupona);} inline GenerationResult GenerateBookshopLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Bookshop);} inline GenerationResult GenerateBrothelLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Brothel);} inline GenerationResult GenerateMedicalShopLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::MedicalShop);} inline GenerationResult GenerateBarberShopLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::BarberShop);} inline GenerationResult GenerateMensaArgentariaLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::MensaArgentaria);} inline GenerationResult GenerateStabulumLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Stabulum);} inline GenerationResult GenerateAtriumDomusLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::AtriumDomus);} inline GenerationResult GenerateThermopoliumLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Thermopolium);} inline GenerationResult GenerateFullonicaLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Fullonica);} inline GenerationResult GeneratePistrinumLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Pistrinum);} inline GenerationResult GeneratePublicLatrineLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::PublicLatrine);} inline GenerationResult GenerateSmallTempleLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::SmallTemple);}

inline PompeianDecorativeStyle SelectDecorativeStyle(const RoomDecorType Type, const WealthTier Wealth, const std::int32_t Seed)
{
    if (Type == RoomDecorType::PlainService || Type == RoomDecorType::Productive || Type == RoomDecorType::Storage) return PompeianDecorativeStyle::ServicePlaster;
    if (Wealth == WealthTier::Poor || Type == RoomDecorType::PopularDomestic) return PompeianDecorativeStyle::PlainPlaster;
    if (Type == RoomDecorType::ThermalCold || Type == RoomDecorType::ThermalWarm || Type == RoomDecorType::ThermalHot) return PompeianDecorativeStyle::FirstStyleInspired;
    if (Wealth == WealthTier::Monumental) return SeedVariantOffset(Seed, 2) == 0 ? PompeianDecorativeStyle::SecondStyleInspired : PompeianDecorativeStyle::FourthStyleInspired;
    if (Wealth == WealthTier::Wealthy) return SeedVariantOffset(Seed, 2) == 0 ? PompeianDecorativeStyle::ThirdStyleInspired : PompeianDecorativeStyle::FourthStyleInspired;
    return SeedVariantOffset(Seed, 2) == 0 ? PompeianDecorativeStyle::FirstStyleInspired : PompeianDecorativeStyle::ThirdStyleInspired;
}

inline RomanDecorationPalette SelectDecorationPalette(const RoomDecorType Type, const WealthTier Wealth, const WeatheringLevel Weathering, const std::int32_t Seed)
{
    RomanDecorationPalette P;
    const std::int32_t Variant = SeedVariantOffset(Seed, 5);
    P.Id = "palette_" + std::to_string(Variant);
    const Vector3 Bases[5] = {{0.55,0.13,0.08},{0.68,0.42,0.12},{0.72,0.62,0.42},{0.12,0.12,0.10},{0.74,0.72,0.64}};
    P.BaseColor = Bases[Variant];
    P.AccentColor = Wealth == WealthTier::Wealthy || Wealth == WealthTier::Monumental ? Vector3{0.12,0.24,0.16} : Vector3{0.42,0.15,0.08};
    P.BorderColor = Type == RoomDecorType::ThermalCold ? Vector3{0.16,0.23,0.27} : Vector3{0.10,0.09,0.08};
    const double Wear = static_cast<double>(static_cast<std::uint8_t>(Weathering)) * 0.08;
    P.Saturation = std::max(0.35, 0.82 - Wear);
    return P;
}

inline FloorDecorationType SelectFloorDecoration(const RoomDecorType Type, const WealthTier Wealth)
{
    if (Type == RoomDecorType::Productive) return FloorDecorationType::ProductiveFloor;
    if (Type == RoomDecorType::ThermalCold || Type == RoomDecorType::ThermalWarm || Type == RoomDecorType::ThermalHot) return FloorDecorationType::ThermalFloor;
    if (Wealth == WealthTier::Poor) return FloorDecorationType::PackedEarth;
    if (Wealth == WealthTier::Popular) return FloorDecorationType::BrickFloor;
    if (Wealth == WealthTier::Medium) return FloorDecorationType::OpusSigninum;
    if (Wealth == WealthTier::Wealthy) return FloorDecorationType::GeometricMosaic;
    return FloorDecorationType::OpusSectileInspired;
}

inline RomanWallDecorationPlan GenerateRomanWallDecoration(
    std::string WallId, const double WidthCm, const double HeightCm, const PompeianDecorativeStyle Style,
    const RomanDecorationPalette& Palette, const std::int32_t Seed, const bool bHasDoor = false, const bool bHasWindow = false)
{
    RomanWallDecorationPlan Wall;
    Wall.WallId = std::move(WallId); Wall.WidthCm = WidthCm; Wall.HeightCm = HeightCm; Wall.Style = Style;
    Wall.Palette = Palette; Wall.bHasDoor = bHasDoor; Wall.bHasWindow = bHasWindow;
    Wall.OpeningCenterCm = WidthCm * 0.5; Wall.OpeningWidthCm = bHasDoor ? std::min(180.0, WidthCm * 0.32) : bHasWindow ? std::min(120.0, WidthCm * 0.25) : 0.0;
    Wall.Bands = {
        {WallDecorationZone::LowerDado, 0.0, std::min(75.0, HeightCm * 0.25), Palette.BorderColor},
        {WallDecorationZone::MiddleBand, HeightCm * 0.25, std::min(18.0, HeightCm * 0.08), Palette.AccentColor},
        {WallDecorationZone::UpperFrame, HeightCm * 0.82, std::min(16.0, HeightCm * 0.06), Palette.BorderColor}
    };
    const std::int32_t Count = Style == PompeianDecorativeStyle::FourthStyleInspired ? 3 : Style == PompeianDecorativeStyle::PlainPlaster || Style == PompeianDecorativeStyle::ServicePlaster ? 1 : 2;
    const double Slot = WidthCm / static_cast<double>(Count);
    for (std::int32_t Index = 0; Index < Count; ++Index)
    {
        RomanDecorationPanel Panel;
        Panel.Id = Wall.WallId + "_panel_" + std::to_string(Index);
        Panel.Zone = Count == 1 ? WallDecorationZone::CentralPanel : WallDecorationZone::SidePanel;
        Panel.OffsetCm = Slot * (Index + 0.5); Panel.BottomCm = HeightCm * 0.33;
        Panel.WidthCm = std::max(30.0, Slot * 0.72); Panel.HeightCm = HeightCm * (0.36 + 0.03 * SeedVariantOffset(Seed + Index, 3));
        const double Left = Panel.OffsetCm - Panel.WidthCm * 0.5;
        const double Right = Panel.OffsetCm + Panel.WidthCm * 0.5;
        const double OpeningLeft = Wall.OpeningCenterCm - Wall.OpeningWidthCm * 0.5;
        const double OpeningRight = Wall.OpeningCenterCm + Wall.OpeningWidthCm * 0.5;
        if (Wall.OpeningWidthCm > 0.0 && Right > OpeningLeft && Left < OpeningRight) continue;
        Panel.Tags = {"geometric_panel", "HISTORICAL_APPROXIMATION"};
        Wall.Panels.push_back(Panel);
    }
    return Wall;
}

inline RomanFloorDecorationPlan GenerateRomanFloorDecoration(
    std::string RoomId, const double WidthCm, const double DepthCm, const RoomDecorType Type,
    const WealthTier Wealth, const RomanDecorationPalette& Palette, const std::int32_t Seed)
{
    RomanFloorDecorationPlan Floor;
    Floor.RoomId = std::move(RoomId); Floor.WidthCm = WidthCm; Floor.DepthCm = DepthCm;
    Floor.Type = SelectFloorDecoration(Type, Wealth); Floor.Palette = Palette;
    Floor.PatternDensity = 1 + SeedVariantOffset(Seed, Wealth == WealthTier::Wealthy || Wealth == WealthTier::Monumental ? 5 : 3);
    return Floor;
}

inline RomanRoomDecorationPlan GenerateRomanRoomDecoration(
    std::string RoomId, const double WidthCm, const double DepthCm, const double HeightCm,
    const RoomDecorType Type, const WealthTier Wealth, const WeatheringLevel Weathering,
    const std::int32_t Seed, const bool bAccessible = true)
{
    RomanRoomDecorationPlan Room;
    Room.RoomId = std::move(RoomId); Room.DecorType = Type; Room.Wealth = Wealth; Room.Weathering = Weathering; Room.bAccessible = bAccessible;
    Room.Style = SelectDecorativeStyle(Type, Wealth, Seed);
    Room.Palette = SelectDecorationPalette(Type, Wealth, Weathering, Seed);
    Room.Walls.push_back(GenerateRomanWallDecoration(Room.RoomId + "_front", WidthCm, HeightCm, Room.Style, Room.Palette, Seed, true, false));
    Room.Walls.push_back(GenerateRomanWallDecoration(Room.RoomId + "_back", WidthCm, HeightCm, Room.Style, Room.Palette, Seed + 1, false, false));
    Room.Walls.push_back(GenerateRomanWallDecoration(Room.RoomId + "_left", DepthCm, HeightCm, Room.Style, Room.Palette, Seed + 2, false, true));
    Room.Walls.push_back(GenerateRomanWallDecoration(Room.RoomId + "_right", DepthCm, HeightCm, Room.Style, Room.Palette, Seed + 3, false, false));
    Room.Floor = GenerateRomanFloorDecoration(Room.RoomId, WidthCm, DepthCm, Type, Wealth, Room.Palette, Seed);
    return Room;
}

inline std::int32_t CalculateDecorationModuleCount(const RomanRoomDecorationPlan& Room)
{
    std::int32_t Count = 1;
    for (const auto& Wall : Room.Walls) Count += static_cast<std::int32_t>(Wall.Bands.size() + Wall.Panels.size());
    return Count;
}

inline double CalculateDecorationComplexity(const RomanRoomDecorationPlan& Room)
{
    return static_cast<double>(CalculateDecorationModuleCount(Room)) * (1.0 + static_cast<double>(static_cast<std::uint8_t>(Room.Style)) * 0.2);
}

inline RomanDecorationValidationResult ValidateRoomDecoration(const RomanRoomDecorationPlan& Room, const std::int32_t MaximumModuleCount = 256)
{
    RomanDecorationValidationResult Result;
    if (Room.RoomId.empty()) AddMessage(Result.Errors, "DecorationMissingRoomId", "Decorazione senza identificatore stanza.", true);
    if (Room.Walls.empty()) AddMessage(Result.Errors, "DecorationMissingWalls", "Stanza senza pareti decorative.", true);
    if (!IsFinite(Room.Floor.WidthCm) || !IsFinite(Room.Floor.DepthCm) || Room.Floor.WidthCm <= 0.0 || Room.Floor.DepthCm <= 0.0) AddMessage(Result.Errors, "DecorationInvalidFloor", "Pavimento decorativo non valido.", true);
    for (const auto& Wall : Room.Walls)
    {
        if (!IsFinite(Wall.WidthCm) || !IsFinite(Wall.HeightCm) || Wall.WidthCm <= 0.0 || Wall.HeightCm <= 0.0) AddMessage(Result.Errors, "DecorationInvalidWall", "Parete decorativa non valida.", true);
        for (const auto& Panel : Wall.Panels)
        {
            if (!IsFinite(Panel.OffsetCm) || !IsFinite(Panel.BottomCm) || !IsFinite(Panel.WidthCm) || !IsFinite(Panel.HeightCm) || Panel.WidthCm <= 0.0 || Panel.HeightCm <= 0.0 || Panel.OffsetCm - Panel.WidthCm * 0.5 < 0.0 || Panel.OffsetCm + Panel.WidthCm * 0.5 > Wall.WidthCm || Panel.BottomCm < 0.0 || Panel.BottomCm + Panel.HeightCm > Wall.HeightCm) AddMessage(Result.Errors, "DecorationPanelOutOfBounds", Panel.Id + " fuori bounds.", true);
            const double OpeningLeft = Wall.OpeningCenterCm - Wall.OpeningWidthCm * 0.5;
            const double OpeningRight = Wall.OpeningCenterCm + Wall.OpeningWidthCm * 0.5;
            if (Wall.OpeningWidthCm > 0.0 && Panel.OffsetCm + Panel.WidthCm * 0.5 > OpeningLeft && Panel.OffsetCm - Panel.WidthCm * 0.5 < OpeningRight) AddMessage(Result.Errors, "DecorationPanelOverOpening", Panel.Id + " sovrapposto ad apertura.", true);
        }
    }
    if (CalculateDecorationModuleCount(Room) > MaximumModuleCount) AddMessage(Result.Errors, "DecorationMaximumModuleCount", "Limite moduli decorativi superato.", true);
    if (!Room.bAccessible) AddMessage(Result.Warnings, "DecorationRoomNotAccessible", "Stanza decorata non marcata accessibile.", false);
    Result.bValid = Result.Errors.empty();
    return Result;
}

} // namespace RomaAeternaCore
