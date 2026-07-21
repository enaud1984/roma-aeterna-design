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
        if (Placement.Category == Category)
        {
            ++Count;
        }
    }
    return Count;
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

    const GenerationResult HouseLayout = BuildSimpleHouseLayout(Defaults);
    Expect(HouseLayout.Placements.size() > 0, "layout casa semplice");
    Expect(CountCategory(HouseLayout, ModuleCategory::Wall) > 0, "casa: muri presenti");
    Expect(CountCategory(HouseLayout, ModuleCategory::Door) > 0, "casa: porta presente");
    Expect(CountCategory(HouseLayout, ModuleCategory::Floor) > 0, "casa: pavimento presente");
    Expect(CountCategory(HouseLayout, ModuleCategory::Roof) > 0, "casa: tetto presente");
    Expect(HouseLayout.EstimatedModuleCount <= Defaults.MaximumModuleCount, "casa: limite moduli rispettato");
    Expect(HouseLayout.BuildingBounds.Max.X == Defaults.WidthCm && HouseLayout.BuildingBounds.Max.Y == Defaults.DepthCm, "casa: bounds coerenti");
    BuildingParameters Taberna = Defaults;
    Taberna.Type = BuildingType::Taberna;
    const GenerationResult TabernaLayout = BuildTabernaLayout(Taberna);
    Expect(TabernaLayout.Placements.size() > HouseLayout.Placements.size(), "layout taberna");
    Expect(CountCategory(TabernaLayout, ModuleCategory::Prop) > 0, "taberna: prop banco presente");
    Expect(CountCategory(TabernaLayout, ModuleCategory::Door) > 1, "taberna: apertura commerciale presente");
    BuildingParameters Temple = Defaults;
    Temple.Type = BuildingType::Temple;
    Temple.Order = ArchitecturalOrder::Doric;
    const GenerationResult TempleLayout = BuildTempleLayout(Temple);
    Expect(TempleLayout.Placements.size() > 0, "layout tempio");
    Expect(CountCategory(TempleLayout, ModuleCategory::Podium) > 0, "tempio: podio presente");
    Expect(CountCategory(TempleLayout, ModuleCategory::Column) > 0, "tempio: colonne presenti");
    Expect(CountCategory(TempleLayout, ModuleCategory::Beam) > 0, "tempio: travi presenti");
    BuildingParameters Street = Defaults;
    Street.Type = BuildingType::StreetSection;
    Street.DoorCount = 0;
    const GenerationResult StreetLayout = BuildStreetSectionLayout(Street);
    Expect(StreetLayout.Placements.size() == 5, "layout tratto strada");
    Expect(CountCategory(StreetLayout, ModuleCategory::Floor) >= 4, "strada: carreggiata e marciapiedi presenti");
    Expect(CountCategory(StreetLayout, ModuleCategory::Decoration) > 0, "strada: spazio facciata presente");

    Expect(AllTransformsFinite(BuildSimpleHouseLayout(Defaults)), "assenza trasformazioni non finite");
    const GenerationResult Repeat1 = BuildTabernaLayout(Taberna);
    const GenerationResult Repeat2 = BuildTabernaLayout(Taberna);
    Expect(SamePlacements(Repeat1, Repeat2), "risultato coerente dopo chiamate ripetute");
    Expect(SamePlacements(HouseLayout, BuildSimpleHouseLayout(Defaults)), "ordine stabile dei placement casa");
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
} // namespace

int main()
{
    RunCoreTests();
    if (Failures > 0)
    {
        std::cerr << Failures << " test falliti\n";
        return EXIT_FAILURE;
    }
    std::cout << "CORE_CPP_TESTS_PASSED\n";
    return EXIT_SUCCESS;
}
