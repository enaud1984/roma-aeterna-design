#include "RARomanModularCore.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

using namespace RomaAeternaCore;

namespace
{
int Failures = 0;

void Expect(bool Condition, const std::string& Message)
{
    if (!Condition)
    {
        ++Failures;
        std::cerr << "FAIL: " << Message << '\n';
    }
}

bool HasErrorCode(const GenerationResult& Result, const std::string& Code)
{
    for (const GenerationMessage& Error : Result.Errors)
    {
        if (Error.Code == Code)
        {
            return true;
        }
    }
    return false;
}

bool SamePlacements(const GenerationResult& A, const GenerationResult& B)
{
    if (A.Placements.size() != B.Placements.size())
    {
        return false;
    }
    for (std::size_t Index = 0; Index < A.Placements.size(); ++Index)
    {
        const ModulePlacement& Left = A.Placements[Index];
        const ModulePlacement& Right = B.Placements[Index];
        if (Left.ModuleId != Right.ModuleId || Left.Category != Right.Category || Left.BayIndex != Right.BayIndex ||
            Left.TransformValue.Location.X != Right.TransformValue.Location.X ||
            Left.TransformValue.Location.Y != Right.TransformValue.Location.Y ||
            Left.TransformValue.Location.Z != Right.TransformValue.Location.Z)
        {
            return false;
        }
    }
    return true;
}


std::size_t CountCategory(const GenerationResult& Result, ModuleCategory Category)
{
    std::size_t Count = 0;
    for (const ModulePlacement& Placement : Result.Placements)
    {
        if (Placement.Category == Category) { ++Count; }
    }
    return Count;
}

bool BoundsCoherent(const GenerationResult& Result)
{
    return IsFinite(Result.BuildingBounds.Min) && IsFinite(Result.BuildingBounds.Max) &&
        Result.BuildingBounds.Max.X >= Result.BuildingBounds.Min.X &&
        Result.BuildingBounds.Max.Y >= Result.BuildingBounds.Min.Y &&
        Result.BuildingBounds.Max.Z >= Result.BuildingBounds.Min.Z;
}

bool AllTransformsFinite(const GenerationResult& Result)
{
    for (const ModulePlacement& Placement : Result.Placements)
    {
        if (!IsFinite(Placement.TransformValue.Location) || !IsFinite(Placement.TransformValue.RotationDegrees) || !IsScaleValid(Placement.TransformValue.Scale))
        {
            return false;
        }
    }
    return true;
}

void RunCoreTests()
{
    BuildingParameters Defaults;
    Expect(Defaults.Type == BuildingType::SimpleHouse, "valori predefiniti: tipo casa semplice");
    Expect(Defaults.WidthCm == 800.0 && Defaults.DepthCm == 600.0, "valori predefiniti: dimensioni");

    BuildingParameters Invalid = Defaults;
    Invalid.WidthCm = -10.0;
    Invalid.DepthCm = -5.0;
    Invalid.BayCount = 0;
    Invalid.FloorCount = 0;
    Invalid.MaximumModuleCount = 0;
    const BuildingParameters Normalized = NormalizeBuildingParameters(Invalid);
    Expect(Normalized.WidthCm > 0.0 && Normalized.DepthCm > 0.0, "normalizzazione dimensioni");
    Expect(Normalized.BayCount == 1 && Normalized.FloorCount == 1, "normalizzazione conteggi");
    Expect(Normalized.MaximumModuleCount == 1, "normalizzazione MaximumModuleCount");

    Expect(CalculateBayWidth(Defaults) == 200.0, "calcolo campata");
    Expect(CalculateGridAlignedValue(123.0, 50.0) == 100.0, "snap griglia valore");
    const Transform Snapped = CalculateGridAlignedTransform({123.0, 177.0, 0.0}, {0.0, 44.0, 0.0}, {1.0, 1.0, 1.0}, 50.0, 90.0);
    Expect(Snapped.Location.X == 100.0 && Snapped.Location.Y == 200.0 && Snapped.RotationDegrees.Y == 0.0, "snap transform");
    Expect(CalculateBuildingBounds(Defaults).Max.Z == 320.0, "altezza edificio");
    Expect(EstimateRequiredModules(Defaults) > 0, "stima moduli positiva");

    BuildingParameters Limited = Defaults;
    Limited.MaximumModuleCount = 1;
    Expect(HasErrorCode(BuildSimpleHouseLayout(Limited), "ModuleLimitExceeded"), "MaximumModuleCount rispettato");

    std::vector<GenerationMessage> Warnings;
    std::vector<GenerationMessage> Errors;
    BuildingParameters Negative = Defaults;
    Negative.DepthCm = -1.0;
    ValidateBuildingParameters(Negative, Warnings, Errors);
    Expect(!Errors.empty(), "dimensioni negative rifiutate");

    Warnings.clear();
    Errors.clear();
    BuildingParameters ZeroWidth = Defaults;
    ZeroWidth.WidthCm = 0.0;
    ValidateBuildingParameters(ZeroWidth, Warnings, Errors);
    Expect(!Errors.empty(), "larghezza zero rifiutata");
    Expect(CalculateGridAlignedValue(17.0, 0.0) == 17.0, "GridSize zero protetto");

    Warnings.clear();
    Errors.clear();
    BuildingParameters NanValue = Defaults;
    NanValue.WidthCm = std::numeric_limits<double>::quiet_NaN();
    ValidateBuildingParameters(NanValue, Warnings, Errors);
    Expect(!Errors.empty(), "NaN rifiutato");

    Warnings.clear();
    Errors.clear();
    BuildingParameters PosInf = Defaults;
    PosInf.WidthCm = std::numeric_limits<double>::infinity();
    ValidateBuildingParameters(PosInf, Warnings, Errors);
    Expect(!Errors.empty(), "infinito positivo rifiutato");

    Warnings.clear();
    Errors.clear();
    BuildingParameters NegInf = Defaults;
    NegInf.WidthCm = -std::numeric_limits<double>::infinity();
    ValidateBuildingParameters(NegInf, Warnings, Errors);
    Expect(!Errors.empty(), "infinito negativo rifiutato");

    Expect(!IsScaleValid({0.0, 1.0, 1.0}), "scala zero rifiutata");
    Expect(!IsScaleValid({-1.0, 1.0, 1.0}), "scala negativa rifiutata");

    BuildingParameters SeedA = Defaults;
    SeedA.RandomSeed = 1;
    BuildingParameters SeedB = Defaults;
    SeedB.RandomSeed = 1;
    BuildingParameters SeedC = Defaults;
    SeedC.RandomSeed = 2;
    const GenerationResult SameA = BuildSimpleHouseLayout(SeedA);
    const GenerationResult SameB = BuildSimpleHouseLayout(SeedB);
    const GenerationResult Different = BuildSimpleHouseLayout(SeedC);
    Expect(SamePlacements(SameA, SameB), "determinismo stesso seed");
    Expect(!SamePlacements(SameA, Different), "variazione con seed diverso");

    const GenerationResult HouseResult = BuildSimpleHouseLayout(Defaults);
    Expect(HouseResult.Placements.size() > 0, "layout casa semplice");
    Expect(CountCategory(HouseResult, ModuleCategory::Wall) > 0, "casa: muri presenti");
    Expect(CountCategory(HouseResult, ModuleCategory::Door) > 0, "casa: porte presenti");
    Expect(CountCategory(HouseResult, ModuleCategory::Window) > 0, "casa: finestre presenti");
    Expect(HouseResult.Placements.size() <= static_cast<std::size_t>(NormalizeBuildingParameters(Defaults).MaximumModuleCount), "casa entro MaximumModuleCount");
    Expect(BoundsCoherent(HouseResult), "casa: bounds coerenti");
    BuildingParameters Taberna = Defaults;
    Taberna.Type = BuildingType::Taberna;
    const GenerationResult TabernaResult = BuildTabernaLayout(Taberna);
    Expect(TabernaResult.Placements.size() > HouseResult.Placements.size(), "layout taberna");
    Expect(CountCategory(TabernaResult, ModuleCategory::Prop) > 0 && CountCategory(TabernaResult, ModuleCategory::Door) > 0, "taberna: categorie attese");
    Expect(BoundsCoherent(TabernaResult), "taberna: bounds coerenti");
    BuildingParameters Temple = Defaults;
    Temple.Type = BuildingType::Temple;
    Temple.Order = ArchitecturalOrder::Doric;
    const GenerationResult TempleResult = BuildTempleLayout(Temple);
    Expect(TempleResult.Placements.size() > 0, "layout tempio");
    Expect(CountCategory(TempleResult, ModuleCategory::Column) > 0 && CountCategory(TempleResult, ModuleCategory::Podium) > 0, "tempio: categorie attese");
    Expect(BoundsCoherent(TempleResult), "tempio: bounds coerenti");
    BuildingParameters Street = Defaults;
    Street.Type = BuildingType::StreetSection;
    Street.DoorCount = 0;
    const GenerationResult StreetResult = BuildStreetSectionLayout(Street);
    Expect(StreetResult.Placements.size() == 5, "layout tratto strada");
    Expect(CountCategory(StreetResult, ModuleCategory::Floor) > 0 && CountCategory(StreetResult, ModuleCategory::Decoration) > 0, "strada: categorie attese");
    Expect(BoundsCoherent(StreetResult), "strada: bounds coerenti");

    Expect(AllTransformsFinite(BuildSimpleHouseLayout(Defaults)), "assenza trasformazioni non finite");
    const GenerationResult Repeat1 = BuildTabernaLayout(Taberna);
    const GenerationResult Repeat2 = BuildTabernaLayout(Taberna);
    Expect(SamePlacements(Repeat1, Repeat2), "risultato coerente dopo chiamate ripetute");
    Expect(Repeat1.Placements.size() == Repeat2.Placements.size(), "nessun accumulo di stato");

    BuildingParameters Huge = Defaults;
    Huge.WidthCm = 1.0e9;
    Huge.DepthCm = 1.0e9;
    Huge.BayCount = 64;
    Huge.MaximumModuleCount = 10000;
    const GenerationResult HugeResult = BuildSimpleHouseLayout(Huge);
    Expect(HugeResult.BuildingBounds.Max.X == 1.0e9 && AllTransformsFinite(HugeResult), "input estremamente grandi gestiti");

    std::vector<ModulePlacement> Placements;
    ModulePlacement BadScale;
    BadScale.ModuleId = "bad";
    BadScale.TransformValue.Scale = {0.0, 1.0, 1.0};
    Placements.push_back(BadScale);
    Warnings.clear();
    Errors.clear();
    ValidatePlacements(Placements, 10, Warnings, Errors);
    Expect(!Errors.empty(), "ValidatePlacements intercetta scala zero");
}


void RunArchetypePrompt22Tests()
{
    BuildingParameters P; P.WidthCm=1200; P.DepthCm=1800; P.MaximumModuleCount=1000; P.HasPeristyle=true; P.HasCourtyard=true; P.HasUpperFloor=true; P.FloorCount=2;
    const BuildingPlan Atrium = GenerateAtriumDomusPlan(P);
    Expect(Atrium.ImplementationState == ArchetypeImplementationState::Implemented, "AtriumDomus implementato");
    Expect(!Atrium.Rooms.empty() && Atrium.Connections.size() >= 8, "AtriumDomus stanze e connessioni");
    std::vector<GenerationMessage> AW, AE; Expect(ValidateBuildingPlan(Atrium, AW, AE), "AtriumDomus valida");
    const GenerationResult AtriumPlacements = GenerateAtriumDomusLayout(P);
    Expect(AtriumPlacements.bSuccess && CountCategory(AtriumPlacements, ModuleCategory::InteractionMarker) > 0, "AtriumDomus conversione placement");

    P = BuildingParameters(); P.WidthCm=700; P.DepthCm=900; P.MaximumModuleCount=1000;
    const BuildingPlan Thermo = GenerateThermopoliumPlan(P);
    Expect(Thermo.ProductionDevices.size() >= 5, "Thermopolium bancone dolia scaffale deposito fuoco");
    Expect(GenerateThermopoliumLayout(P).bSuccess && CountCategory(GenerateThermopoliumLayout(P), ModuleCategory::Counter) == 1, "Thermopolium placement bancone");

    P = BuildingParameters(); P.WidthCm=1100; P.DepthCm=1400; P.MaximumModuleCount=1000;
    const BuildingPlan Fullonica = GenerateFullonicaPlan(P);
    Expect(Fullonica.WaterFeatures.size() >= 2 && Fullonica.ProductionDevices.size() >= 4, "Fullonica vasche drenaggio asciugatura");
    Expect(CountCategory(GenerateFullonicaLayout(P), ModuleCategory::DryingRack) > 0, "Fullonica placement rack");

    P = BuildingParameters(); P.WidthCm=1200; P.DepthCm=1300; P.MaximumModuleCount=1000;
    const BuildingPlan Pistrinum = GeneratePistrinumPlan(P);
    Expect(Pistrinum.ProductionDevices.size() >= 4 && Pistrinum.InteractionPoints.size() >= 8, "Pistrinum macina forno percorso animale");
    Expect(GeneratePistrinumLayout(P).bSuccess && CountCategory(GeneratePistrinumLayout(P), ModuleCategory::Oven) > 0 && CountCategory(GeneratePistrinumLayout(P), ModuleCategory::RotationArm) > 0, "Pistrinum placement produttivi");

    P = BuildingParameters(); P.WidthCm=1000; P.DepthCm=800; P.PublicCapacity=6; P.MaximumModuleCount=1000;
    const BuildingPlan Latrine = GeneratePublicLatrinePlan(P);
    Expect(Latrine.ProductionDevices.size() >= 6 && Latrine.WaterFeatures.size() >= 2, "Latrina sedute acqua drenaggio");
    Expect(GeneratePublicLatrineLayout(P).bSuccess && CountCategory(GeneratePublicLatrineLayout(P), ModuleCategory::LatrineSeat) >= 6, "Latrina placement sedute");

    P = BuildingParameters(); P.WidthCm=900; P.DepthCm=1100; P.MaximumModuleCount=1000; P.HasExternalAltar=true;
    const BuildingPlan Temple = GenerateSmallTemplePlan(P);
    Expect(Temple.MonumentFeatures.size() >= 8 && Temple.ReligiousFeatures.size() >= 2, "SmallTemple podio scala colonne statua altare");
    Expect(CountCategory(GenerateSmallTempleLayout(P), ModuleCategory::StatueMarker) == 1, "SmallTemple marker statua");

    P.Type = BuildingType::AtriumDomus; P.RandomSeed = 44; const GenerationResult A=GenerateAtriumDomusLayout(P); const GenerationResult B=GenerateAtriumDomusLayout(P); P.RandomSeed=45; const GenerationResult C=GenerateAtriumDomusLayout(P);
    Expect(SamePlacements(A,B), "Prompt22 determinismo stesso seed");
    Expect(A.Placements.size() == C.Placements.size(), "Prompt22 variazione controllata seed diverso");
    Expect(AllTransformsFinite(A) && BoundsCoherent(A), "Prompt22 bounds e transform validi");
    P.MaximumModuleCount=1; Expect(!GenerateSmallTempleLayout(P).bSuccess, "Prompt22 MaximumModuleCount");
    Expect(IsArchetypeImplemented(BuildingType::AtriumDomus), "IsArchetypeImplemented vero");
    Expect(!IsArchetypeImplemented(BuildingType::PeristyleDomus), "ARCHETYPE_PLANNED non implementato");
    Expect(GetImplementedArchetypes().size()==6, "sei archetipi implementati");
    bool PlannedFound=false; for(const auto& M:GetArchetypeCatalog()){ if(M.State==ArchetypeImplementationState::ARCHETYPE_PLANNED && std::string(M.Name)=="PeristyleDomus") PlannedFound=true; }
    Expect(PlannedFound, "catalogo ARCHETYPE_PLANNED");
}

} // namespace

int main()
{
    RunCoreTests();
    RunArchetypePrompt22Tests();
    if (Failures > 0)
    {
        std::cerr << Failures << " test falliti\n";
        return EXIT_FAILURE;
    }
    std::cout << "CORE_CPP_TESTS_PASSED\n";
    std::cout << "CORE_CPP_DEBUG_TESTS_PASSED\n";
    std::cout << "BUILDING_ARCHETYPE_STATIC_CHECKS_PASSED\n";
    return EXIT_SUCCESS;
}
