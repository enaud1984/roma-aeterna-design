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
    MonumentalArch, CityGate, CityWall, WatchTower, AqueductSection, StreetSection, Plaza, StatueBase, Monument, FountainMonument, ForumSection
};

enum class ArchetypeImplementationState : std::uint8_t { Implemented, ARCHETYPE_PLANNED };
enum class BuildingFunction : std::uint8_t { Residential, Commercial, Productive, Religious, Civic, Entertainment, Hospitality, Sanitary, Hydraulic, Monumental, MixedUse };
enum class BuildingScale : std::uint8_t { Small, Medium, Large, Monumental };
enum class AccessType : std::uint8_t { StreetAccess, SecondaryAccess, ServiceAccess, CourtyardAccess, MonumentalAccess, ShopfrontAccess, InternalAccess };
enum class ZoneFunction : std::uint8_t { Public, Private, Service, Commercial, Productive, Religious, Sanitary, Hydraulic, Circulation, Storage, AnimalWork, OpenSpace };

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
    ServiceBasin, InteractionMarker
};

enum class RoomType : std::uint8_t
{
    Fauces, Vestibulum, Atrium, Impluvium, Ala, Cubiculum, Tablinum, Triclinium, Oecus, Exedra, Culina, DomesticLatrine, Corridor, Stair, Peristyle, Hortus, ServiceRoom, Storage, UpperRoom,
    Shopfront, CounterArea, DiningArea, KitchenArea, CustomerArea, BackRoom, StreetPortico, CommercialStorage,
    WorkshopArea, MillingArea, OvenArea, PressArea, WashingArea, DryingArea, DyeingArea, AnimalDriveArea, FurnaceArea, RawMaterialStorage, FinishedGoodsStorage, PreparationArea,
    Nave, Aisle, Tribunal, CouncilHall, AssemblyArea, BathHall, Apodyterium, Frigidarium, Tepidarium, Calidarium, Laconicum, Palaestra, Auditorium, Cavea, Orchestra, Scaena, Arena, Vomitorium, PublicLatrineHall,
    Cella, Pronaos, Podium, AltarArea, SacredCourt, ProcessionalArea,
    ForumPlaza, MarketCourt, Portico, FountainCourt, MonumentCourt, Garden, Street, Alley, ServiceYard
};

enum class InteractionPointType : std::uint8_t { Entrance, Exit, WorkerPosition, CustomerPosition, QueuePosition, VendorPosition, ServicePosition, StoragePosition, WorshipPosition, SeatingPosition, AnimalPathPoint, RestrictedPosition, InteractionPosition };

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
struct BuildingPlan { std::vector<RoomDefinition> Rooms; std::vector<BuildingZone> Zones; std::vector<RoomConnection> Connections; std::vector<CourtyardDefinition> Courtyards; std::vector<OpenSpaceDefinition> OpenSpaces; std::vector<ProductionDeviceDefinition> ProductionDevices; std::vector<WaterFeatureDefinition> WaterFeatures; std::vector<ReligiousFeatureDefinition> ReligiousFeatures; std::vector<MonumentFeatureDefinition> MonumentFeatures; std::vector<BuildingInteractionPoint> InteractionPoints; Bounds PlanBounds; std::vector<GenerationMessage> Warnings; std::vector<GenerationMessage> Errors; std::int32_t Seed=0; BuildingType Type=BuildingType::SimpleHouse; ArchetypeImplementationState ImplementationState=ArchetypeImplementationState::ARCHETYPE_PLANNED; };
struct BuildingPlanResult { bool bSuccess=false; BuildingPlan Plan; std::vector<ModulePlacement> Placements; std::vector<GenerationMessage> Warnings; std::vector<GenerationMessage> Errors; };
struct ArchetypeMetadata { BuildingType Type; const char* Name; BuildingFunction Function; BuildingScale Scale; ArchetypeImplementationState State; const char* Requirements; int FuturePriority; };

inline bool HasTag(const std::vector<std::string>& Tags,const std::string& T){return std::find(Tags.begin(),Tags.end(),T)!=Tags.end();}
inline RoomDefinition MakeRoom(std::string Id, RoomType Type, ZoneFunction Function, Vector3 Pos, double W, double D, std::vector<std::string> Tags){RoomDefinition R; R.Id=std::move(Id); R.Type=Type; R.Function=Function; R.Position=Pos; R.WidthCm=W; R.DepthCm=D; R.Tags=std::move(Tags); R.bStreetFacing=HasTag(R.Tags,"street_facing"); R.bHasWater=HasTag(R.Tags,"water_required"); R.bHasDrainage=HasTag(R.Tags,"drainage_required"); R.bHasFire=HasTag(R.Tags,"fire_hazard_area"); return R;}
inline void Connect(BuildingPlan& P,const std::string& A,const std::string& B,AccessType T=AccessType::InternalAccess){P.Connections.push_back({A,B,T});}
inline void AddPoint(BuildingPlan& P,std::string Id,InteractionPointType T,Vector3 Pos,std::string Zone,std::vector<std::string> Tags,std::string Role){P.InteractionPoints.push_back({std::move(Id),T,Pos,0,0,1,std::move(Tags),std::move(Zone),true,std::move(Role)});}
inline bool IsArchetypeImplemented(BuildingType T){return T==BuildingType::AtriumDomus||T==BuildingType::Thermopolium||T==BuildingType::Fullonica||T==BuildingType::Pistrinum||T==BuildingType::PublicLatrine||T==BuildingType::SmallTemple;}
inline std::vector<BuildingType> GetImplementedArchetypes(){return {BuildingType::AtriumDomus,BuildingType::Thermopolium,BuildingType::Fullonica,BuildingType::Pistrinum,BuildingType::PublicLatrine,BuildingType::SmallTemple};}
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
inline GenerationResult ConvertBuildingPlanToPlacements(const BuildingPlan& Plan,const BuildingParameters& Params){GenerationResult G; for(const auto& R:Plan.Rooms) RoomToPlacements(R,G); for(const auto& C:Plan.Connections) AddPlacement(G,"door_"+C.FromId+"_"+C.ToId,ModuleCategory::Door,{0,0,0}); for(const auto& D:Plan.ProductionDevices) AddPlacement(G,D.Id,D.Category,D.Position); for(const auto& W:Plan.WaterFeatures) AddPlacement(G,W.Id,W.Category,W.Position); for(const auto& R:Plan.ReligiousFeatures) AddPlacement(G,R.Id,R.Category,R.Position); for(const auto& M:Plan.MonumentFeatures) AddPlacement(G,M.Id,M.Category,M.Position); for(const auto& I:Plan.InteractionPoints) AddPlacement(G,I.Id,ModuleCategory::InteractionMarker,I.Position); G.BuildingBounds=Plan.PlanBounds; G.Warnings=Plan.Warnings; G.Errors=Plan.Errors; return FinishGeneration(std::move(G),Params);}
inline BuildingPlan GenerateAtriumDomusPlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::AtriumDomus); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("fauces",RoomType::Fauces,ZoneFunction::Circulation,{W*.5,60,0},W*.2,120,{"public_room","street_facing"}),MakeRoom("atrium",RoomType::Atrium,ZoneFunction::Private,{W*.5,D*.28,0},W*.55,D*.28,{"private_room","mosaic_candidate"}),MakeRoom("cubiculum_left",RoomType::Cubiculum,ZoneFunction::Private,{W*.18,D*.28,0},W*.22,D*.18,{"private_room","fresco_candidate"}),MakeRoom("cubiculum_right",RoomType::Cubiculum,ZoneFunction::Private,{W*.82,D*.28,0},W*.22,D*.18,{"private_room","fresco_candidate"}),MakeRoom("ala_left",RoomType::Ala,ZoneFunction::Private,{W*.2,D*.43,0},W*.18,D*.12,{"private_room"}),MakeRoom("ala_right",RoomType::Ala,ZoneFunction::Private,{W*.8,D*.43,0},W*.18,D*.12,{"private_room"}),MakeRoom("tablinum",RoomType::Tablinum,ZoneFunction::Private,{W*.5,D*.55,0},W*.32,D*.15,{"private_room","mosaic_candidate"}),MakeRoom("triclinium",RoomType::Triclinium,ZoneFunction::Private,{W*.2,D*.62,0},W*.25,D*.18,{"private_room","fresco_candidate"}),MakeRoom("culina",RoomType::Culina,ZoneFunction::Service,{W*.82,D*.62,0},W*.18,D*.16,{"service_room","food_preparation","fire_hazard_area"}),MakeRoom("domestic_latrine",RoomType::DomesticLatrine,ZoneFunction::Sanitary,{W*.9,D*.78,0},W*.12,D*.12,{"service_room","water_required","drainage_required"}),MakeRoom("service_room",RoomType::ServiceRoom,ZoneFunction::Service,{W*.75,D*.8,0},W*.18,D*.14,{"service_room","storage_area"})}; if(N.HasImpluvium){auto R=MakeRoom("impluvium",RoomType::Impluvium,ZoneFunction::Hydraulic,{W*.5,D*.28,0},W*.18,D*.1,{"water_required","drainage_required","fountain_candidate"}); P.Rooms.push_back(R); P.WaterFeatures.push_back({"impluvium_basin",ModuleCategory::Basin,"impluvium",R.Position,true,"roof","drain",{"water_required","drainage_required"}});} if(N.HasPeristyle||N.HasCourtyard){P.Rooms.push_back(MakeRoom("peristyle",RoomType::Peristyle,ZoneFunction::OpenSpace,{W*.5,D*.78,0},W*.55,D*.22,{"open_court","fountain_candidate"}));} if(N.HasHortus){P.Rooms.push_back(MakeRoom("hortus",RoomType::Hortus,ZoneFunction::OpenSpace,{W*.5,D*.9,0},W*.5,D*.14,{"open_court"})); P.MonumentFeatures.push_back({"garden_marker",ModuleCategory::GardenFeature,"hortus",{W*.5,D*.9,0},{"fountain_candidate"}});} if(N.HasUpperFloor||N.FloorCount>1){P.Rooms.push_back(MakeRoom("stair",RoomType::Stair,ZoneFunction::Circulation,{W*.1,D*.52,0},W*.12,D*.16,{"service_room","upper_floor"})); P.Rooms.push_back(MakeRoom("upper_room",RoomType::UpperRoom,ZoneFunction::Private,{W*.5,D*.35,N.FloorHeightCm},W*.35,D*.2,{"private_room","upper_floor"})); Connect(P,"stair","upper_room");} if(N.HasFrontTabernae){P.Rooms.push_back(MakeRoom("front_taberna_left",RoomType::Shopfront,ZoneFunction::Commercial,{W*.18,50,0},W*.18,100,{"commercial_area","street_facing","shop_sign_candidate"}));} if(N.HasImpluvium){Connect(P,"atrium","impluvium");} Connect(P,"fauces","atrium",AccessType::StreetAccess); Connect(P,"atrium","tablinum"); Connect(P,"atrium","cubiculum_left"); Connect(P,"atrium","cubiculum_right"); Connect(P,"atrium","ala_left"); Connect(P,"atrium","ala_right"); Connect(P,"tablinum",(N.HasPeristyle||N.HasCourtyard)?"peristyle":"service_room"); Connect(P,"atrium","triclinium"); Connect(P,"service_room","domestic_latrine"); Connect(P,"culina","service_room"); AddPoint(P,"entrance",InteractionPointType::Entrance,{W*.5,0,0},"fauces",{"street_facing"},"accesso"); AddPoint(P,"domestic_work",InteractionPointType::ServicePosition,{W*.82,D*.62,0},"culina",{"npc_workstation"},"servizio"); return P;}
inline BuildingPlan GenerateThermopoliumPlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::Thermopolium); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("shopfront",RoomType::Shopfront,ZoneFunction::Commercial,{W*.5,70,0},W*.8,140,{"commercial_area","customer_area","street_facing","food_sales","shop_sign_candidate"}),MakeRoom("counter_area",RoomType::CounterArea,ZoneFunction::Commercial,{W*.5,150,0},W*.7,120,{"commercial_area","food_sales"}),MakeRoom("backroom",RoomType::BackRoom,ZoneFunction::Service,{W*.5,D*.5,0},W*.65,D*.25,{"service_room"}),MakeRoom("storage",RoomType::CommercialStorage,ZoneFunction::Storage,{W*.25,D*.78,0},W*.3,D*.18,{"storage_area"}),MakeRoom("preparation",RoomType::PreparationArea,ZoneFunction::Service,{W*.72,D*.72,0},W*.25,D*.2,{"food_preparation","fire_hazard_area"})}; Connect(P,"shopfront","counter_area",AccessType::ShopfrontAccess); Connect(P,"counter_area","backroom"); Connect(P,"backroom","storage"); Connect(P,"backroom","preparation"); P.Zones.push_back({"customer_area",ZoneFunction::Commercial,{W*.5,35,0},W,70,300,0,{AccessType::StreetAccess},0,true,false,4,"vendita",0,false,false,false,false,{"customer_area","street_facing"}}); P.ProductionDevices.push_back({"counter",ModuleCategory::Counter,"counter_area",{W*.5,95,90},60,{},{"food_sales"}}); P.ProductionDevices.push_back({"dolium_0",ModuleCategory::Dolium,"counter_area",{W*.35,110,70},45,{},{"food_sales"}}); P.ProductionDevices.push_back({"shelf",ModuleCategory::Shelf,"backroom",{W*.7,D*.5,90},20,{},{"storage_area"}}); P.ProductionDevices.push_back({"storage_container",ModuleCategory::StorageContainer,"storage",{W*.25,D*.78,40},30,{},{"storage_area"}}); P.ProductionDevices.push_back({"fire_area",ModuleCategory::Furnace,"preparation",{W*.8,D*.75,0},45,{},{"fire_hazard_area"}}); AddPoint(P,"customer",InteractionPointType::CustomerPosition,{W*.5,20,0},"shopfront",{"npc_customer_position"},"cliente"); AddPoint(P,"vendor",InteractionPointType::VendorPosition,{W*.5,170,0},"counter_area",{"npc_workstation"},"venditore"); AddPoint(P,"queue",InteractionPointType::QueuePosition,{W*.35,20,0},"shopfront",{"npc_queue_position"},"coda"); return P;}
inline BuildingPlan GenerateFullonicaPlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::Fullonica); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("reception",RoomType::WorkshopArea,ZoneFunction::Productive,{W*.5,D*.12,0},W*.6,D*.15,{"production_area","textile_processing"}),MakeRoom("washing",RoomType::WashingArea,ZoneFunction::Productive,{W*.3,D*.35,0},W*.35,D*.22,{"production_area","textile_processing","water_required","drainage_required"}),MakeRoom("treatment",RoomType::DyeingArea,ZoneFunction::Productive,{W*.7,D*.35,0},W*.35,D*.22,{"production_area","textile_processing","water_required","drainage_required"}),MakeRoom("drying",RoomType::DryingArea,ZoneFunction::Productive,{W*.5,D*.65,0},W*.7,D*.18,{"production_area","textile_processing"}),MakeRoom("storage",RoomType::FinishedGoodsStorage,ZoneFunction::Storage,{W*.5,D*.85,0},W*.5,D*.12,{"storage_area"}),MakeRoom("office",RoomType::BackRoom,ZoneFunction::Service,{W*.85,D*.15,0},W*.18,D*.16,{"service_room"})}; Connect(P,"reception","office");Connect(P,"reception","washing");Connect(P,"washing","treatment");Connect(P,"treatment","drying");Connect(P,"drying","storage"); P.ProductionDevices.push_back({"washing_basin",ModuleCategory::Basin,"washing",{W*.3,D*.35,0},60,{},{"water_required","drainage_required"}}); P.ProductionDevices.push_back({"treatment_basin",ModuleCategory::Basin,"treatment",{W*.7,D*.35,0},60,{},{"water_required","drainage_required"}}); P.ProductionDevices.push_back({"work_platform",ModuleCategory::WorkPlatform,"washing",{W*.3,D*.45,0},40,{},{"npc_workstation"}}); P.ProductionDevices.push_back({"drying_rack",ModuleCategory::DryingRack,"drying",{W*.5,D*.65,0},70,{},{"textile_processing"}}); P.WaterFeatures.push_back({"drain",ModuleCategory::Drain,"washing",{W*.5,D*.5,0},true,"washing","street_drain",{"drainage_required"}}); P.WaterFeatures.push_back({"water_channel",ModuleCategory::WaterChannel,"treatment",{W*.5,D*.42,0},true,"cistern","drain",{"water_required"}}); AddPoint(P,"worker",InteractionPointType::WorkerPosition,{W*.35,D*.38,0},"washing",{"npc_workstation"},"fullone"); AddPoint(P,"service",InteractionPointType::ServicePosition,{W*.9,D*.95,0},"storage",{"npc_service_route"},"servizio"); return P;}
inline BuildingPlan GeneratePistrinumPlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::Pistrinum); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("grain_storage",RoomType::RawMaterialStorage,ZoneFunction::Storage,{W*.2,D*.15,0},W*.25,D*.15,{"storage_area","grain_processing"}),MakeRoom("milling",RoomType::MillingArea,ZoneFunction::Productive,{W*.35,D*.42,0},W*.35,D*.3,{"production_area","grain_processing","animal_work_area"}),MakeRoom("flour_storage",RoomType::FinishedGoodsStorage,ZoneFunction::Storage,{W*.18,D*.72,0},W*.22,D*.14,{"storage_area"}),MakeRoom("preparation",RoomType::PreparationArea,ZoneFunction::Productive,{W*.5,D*.72,0},W*.25,D*.15,{"food_preparation"}),MakeRoom("oven",RoomType::OvenArea,ZoneFunction::Productive,{W*.78,D*.62,0},W*.22,D*.22,{"production_area","fire_hazard_area"}),MakeRoom("bread_storage",RoomType::FinishedGoodsStorage,ZoneFunction::Storage,{W*.75,D*.85,0},W*.25,D*.12,{"storage_area","food_sales"})}; Connect(P,"grain_storage","milling");Connect(P,"milling","flour_storage");Connect(P,"flour_storage","preparation");Connect(P,"preparation","oven");Connect(P,"oven","bread_storage"); std::vector<Vector3> path; for(int i=0;i<8;++i){double a=6.28318530718*i/8.0; path.push_back({W*.35+std::cos(a)*90,D*.42+std::sin(a)*90,0}); AddPoint(P,"donkey_path_"+std::to_string(i),InteractionPointType::AnimalPathPoint,path.back(),"milling",{"npc_animal_route","animal_work_area"},"percorso animale");} P.ProductionDevices.push_back({"millstone_base",ModuleCategory::Millstone,"milling",{W*.35,D*.42,0},90,path,{"animal_work_area","grain_processing"}}); P.ProductionDevices.push_back({"millstone_upper",ModuleCategory::Millstone,"milling",{W*.35,D*.42,70},60,{}, {"grain_processing"}}); P.ProductionDevices.push_back({"rotation_arm",ModuleCategory::RotationArm,"milling",{W*.43,D*.42,80},90,{}, {"animal_work_area"}}); P.ProductionDevices.push_back({"oven",ModuleCategory::Oven,"oven",{W*.78,D*.62,0},70,{}, {"fire_hazard_area"}}); AddPoint(P,"baker",InteractionPointType::WorkerPosition,{W*.5,D*.72,0},"preparation",{"npc_workstation"},"panettiere"); return P;}
inline BuildingPlan GeneratePublicLatrinePlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::PublicLatrine); double W=N.WidthCm,D=N.DepthCm; int cap=std::max(2,N.PublicCapacity); P.Rooms={MakeRoom("entrance",RoomType::Vestibulum,ZoneFunction::Circulation,{W*.5,40,0},W*.35,80,{"public_room","street_facing"}),MakeRoom("latrine_hall",RoomType::PublicLatrineHall,ZoneFunction::Sanitary,{W*.5,D*.5,0},W*.8,D*.7,{"public_room","water_required","drainage_required"})}; Connect(P,"entrance","latrine_hall",AccessType::StreetAccess); for(int i=0;i<cap;++i){double x=80+i*(std::max(40.0,(W-160)/cap)); P.ProductionDevices.push_back({"latrine_seat_"+std::to_string(i),ModuleCategory::LatrineSeat,"latrine_hall",{x,D*.82,45},25,{}, {"water_required","drainage_required"}}); AddPoint(P,"seat_point_"+std::to_string(i),InteractionPointType::SeatingPosition,{x,D*.72,0},"latrine_hall",{"npc_customer_position"},"seduta");} P.WaterFeatures.push_back({"continuous_drain",ModuleCategory::Drain,"latrine_hall",{W*.5,D*.86,0},true,"channel","sewer",{"drainage_required"}}); P.WaterFeatures.push_back({"front_water_channel",ModuleCategory::WaterChannel,"latrine_hall",{W*.5,D*.66,0},true,"supply","drain",{"water_required"}}); P.WaterFeatures.push_back({"service_basin",ModuleCategory::ServiceBasin,"latrine_hall",{W*.85,D*.25,0},true,"supply","drain",{"water_required"}}); AddPoint(P,"latrine_entrance",InteractionPointType::Entrance,{W*.5,0,0},"entrance",{"street_facing"},"accesso pubblico"); return P;}
inline BuildingPlan GenerateSmallTemplePlan(const BuildingParameters& In){auto N=NormalizeBuildingParameters(In); auto P=BasePlan(N,BuildingType::SmallTemple); double W=N.WidthCm,D=N.DepthCm; P.Rooms={MakeRoom("podium",RoomType::Podium,ZoneFunction::Religious,{W*.5,D*.5,60},W*.8,D*.75,{"religious_area","monumental_area"}),MakeRoom("pronaos",RoomType::Pronaos,ZoneFunction::Religious,{W*.5,D*.28,100},W*.55,D*.18,{"religious_area"}),MakeRoom("cella",RoomType::Cella,ZoneFunction::Religious,{W*.5,D*.58,100},W*.48,D*.35,{"religious_area","restricted_area","statue_candidate"}),MakeRoom("processional",RoomType::ProcessionalArea,ZoneFunction::Public,{W*.5,-80,0},W*.5,120,{"public_room"})}; Connect(P,"processional","pronaos",AccessType::MonumentalAccess); Connect(P,"pronaos","cella"); P.MonumentFeatures.push_back({"podium_marker",ModuleCategory::Podium,"podium",{W*.5,D*.5,60},{"monumental_area"}}); P.MonumentFeatures.push_back({"front_stair",ModuleCategory::Stair,"processional",{W*.5,0,0},{"monumental_area"}}); for(int i=0;i<4;++i){double x=W*.25+i*(W*.5/3); P.MonumentFeatures.push_back({"column_"+std::to_string(i),ModuleCategory::Column,"pronaos",{x,D*.18,100},{"religious_area"}}); P.MonumentFeatures.push_back({"capital_"+std::to_string(i),ModuleCategory::Capital,"pronaos",{x,D*.18,300},{"religious_area"}});} P.MonumentFeatures.push_back({"beam",ModuleCategory::Beam,"pronaos",{W*.5,D*.18,310},{"religious_area"}}); P.MonumentFeatures.push_back({"roof",ModuleCategory::Roof,"cella",{W*.5,D*.45,360},{"religious_area"}}); P.ReligiousFeatures.push_back({"statue_marker",ModuleCategory::StatueMarker,"cella",{W*.5,D*.62,100},{"statue_candidate"}}); if(N.HasExternalAltar) P.ReligiousFeatures.push_back({"altar",ModuleCategory::Altar,"processional",{W*.5,-140,0},{"religious_area"}}); AddPoint(P,"worship",InteractionPointType::WorshipPosition,{W*.5,-60,0},"processional",{"npc_customer_position"},"culto"); return P;}
inline BuildingPlan GenerateBuildingPlan(const BuildingParameters& P){switch(P.Type){case BuildingType::AtriumDomus: return GenerateAtriumDomusPlan(P); case BuildingType::Thermopolium: return GenerateThermopoliumPlan(P); case BuildingType::Fullonica: return GenerateFullonicaPlan(P); case BuildingType::Pistrinum: return GeneratePistrinumPlan(P); case BuildingType::PublicLatrine: return GeneratePublicLatrinePlan(P); case BuildingType::SmallTemple: return GenerateSmallTemplePlan(P); default: {auto B=BasePlan(P,P.Type); AddMessage(B.Warnings,"ARCHETYPE_PLANNED","Archetipo registrato ma non implementato.",false); return B;}}}
inline BuildingPlanResult GenerateBuildingPlanResult(const BuildingParameters& P){BuildingPlanResult R; R.Plan=GenerateBuildingPlan(P); ValidateBuildingPlan(R.Plan,R.Warnings,R.Errors); R.Placements=ConvertBuildingPlanToPlacements(R.Plan,P).Placements; R.bSuccess=R.Errors.empty()&&R.Plan.ImplementationState==ArchetypeImplementationState::Implemented; return R;}
inline GenerationResult BuildPlanLayout(BuildingParameters P, BuildingType T){P.Type=T; auto Plan=GenerateBuildingPlan(P); std::vector<GenerationMessage> W,E; ValidateBuildingPlan(Plan,W,E); Plan.Warnings.insert(Plan.Warnings.end(),W.begin(),W.end()); Plan.Errors.insert(Plan.Errors.end(),E.begin(),E.end()); return ConvertBuildingPlanToPlacements(Plan,P);}
inline GenerationResult GenerateAtriumDomusLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::AtriumDomus);} inline GenerationResult GenerateThermopoliumLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Thermopolium);} inline GenerationResult GenerateFullonicaLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Fullonica);} inline GenerationResult GeneratePistrinumLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::Pistrinum);} inline GenerationResult GeneratePublicLatrineLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::PublicLatrine);} inline GenerationResult GenerateSmallTempleLayout(const BuildingParameters& P){return BuildPlanLayout(P,BuildingType::SmallTemple);}

} // namespace RomaAeternaCore
