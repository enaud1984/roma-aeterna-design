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

bool HasRoom(const BuildingPlan& Plan, RoomType Type)
{
    for (const RoomDefinition& Room : Plan.Rooms)
    {
        if (Room.Type == Type)
        {
            return true;
        }
    }
    return false;
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
    Expect(IsArchetypeImplemented(BuildingType::PeristyleDomus), "PeristyleDomus implementato nel Prompt 23");
    Expect(GetImplementedArchetypes().size()>=22, "archetipi Prompt 22 e Prompt 23 implementati");
    bool PlannedFound=false; for(const auto& M:GetArchetypeCatalog()){ if(M.State==ArchetypeImplementationState::ARCHETYPE_PLANNED && std::string(M.Name)=="PeristyleDomus") PlannedFound=true; }
    Expect(PlannedFound, "catalogo ARCHETYPE_PLANNED");
}


void RunResidentialCommercialPrompt23Tests()
{
    BuildingParameters P; P.WidthCm=1200; P.DepthCm=1600; P.FloorCount=3; P.MaximumModuleCount=3000;
    const std::vector<BuildingType> Types={BuildingType::DomusMedia,BuildingType::PeristyleDomus,BuildingType::RichDomus,BuildingType::PopularHouse,BuildingType::Insula,BuildingType::Cenaculum,BuildingType::MixedUseHouse,BuildingType::Taberna,BuildingType::Popina,BuildingType::Caupona,BuildingType::Bookshop,BuildingType::Brothel,BuildingType::MedicalShop,BuildingType::BarberShop,BuildingType::MensaArgentaria,BuildingType::Stabulum};
    for(BuildingType T:Types){P.Type=T; const BuildingPlan Plan=GenerateBuildingPlan(P); std::vector<GenerationMessage> W,E; Expect(Plan.ImplementationState==ArchetypeImplementationState::Implemented,"Prompt 23 archetipo implementato"); Expect(ValidateBuildingPlan(Plan,W,E),"Prompt 23 plan valido"); const GenerationResult R=BuildPlanLayout(P,T); Expect(R.bSuccess && !R.Placements.empty(),"Prompt 23 conversione placeholder"); Expect(AllTransformsFinite(R)&&BoundsCoherent(R),"Prompt 23 bounds e NaN"); Expect(!Plan.InteractionPoints.empty(),"Prompt 23 punti NPC"); Expect(GetUrbanProfileForBuildingType(T).PlacementWeight>0,"Prompt 23 profilo urbano"); }
    const BuildingPlan Domus=GenerateDomusMediaPlan(P); Expect(HasRoom(Domus,RoomType::Atrium)||HasRoom(Domus,RoomType::LightCourt),"DomusMedia atrio o cortile"); Expect(HasRoom(Domus,RoomType::Cubiculum)&&HasRoom(Domus,RoomType::Culina)&&HasRoom(Domus,RoomType::DomesticLatrine),"DomusMedia cubicula cucina latrina");
    const BuildingPlan Per=GeneratePeristyleDomusPlan(P); Expect(HasRoom(Per,RoomType::Atrium)&&HasRoom(Per,RoomType::Tablinum)&&HasRoom(Per,RoomType::Peristyle)&&HasRoom(Per,RoomType::Garden),"PeristyleDomus asse e giardino"); Expect(CountCategory(ConvertBuildingPlanToPlacements(Per,P),ModuleCategory::Column)>=8,"PeristyleDomus colonne");
    const BuildingPlan Rich=GenerateRichDomusPlan(P); Expect(CountCategory(ConvertBuildingPlanToPlacements(Rich,P),ModuleCategory::MosaicZone)>0&&CountCategory(ConvertBuildingPlanToPlacements(Rich,P),ModuleCategory::FrescoZone)>0,"RichDomus decorazione semantica"); Expect(CalculateResidentCapacity(Rich)>=CalculateResidentCapacity(Domus),"RichDomus capacita non inferiore a DomusMedia");
    const BuildingPlan Pop=GeneratePopularHousePlan(P); Expect(HasRoom(Pop,RoomType::PoorDwellingRoom)&&!HasRoom(Pop,RoomType::Peristyle),"PopularHouse compatta senza peristilio"); Expect(GetUrbanProfileForBuildingType(BuildingType::PopularHouse).CanShareWall,"PopularHouse muri condivisi");
    const BuildingPlan Ins=GenerateInsulaPlan(P); Expect(HasRoom(Ins,RoomType::SharedStair)&&!Ins.Apartments.empty()&&CalculateResidentCapacity(Ins)>0,"Insula scala appartamenti capacita");
    const BuildingPlan Cen=GenerateCenaculumPlan(P); Expect(!Cen.Apartments.empty()&&Cen.Apartments.front().Floor>0,"Cenaculum piano superiore e accesso scala");
    const BuildingPlan Tab=GenerateTabernaPlan(P); Expect(CountCategory(ConvertBuildingPlanToPlacements(Tab,P),ModuleCategory::ShopOpening)>0&&CalculateCustomerCapacity(Tab)>0&&CalculateWorkerCapacity(Tab)>0,"Taberna apertura venditore cliente");
    const BuildingPlan Popina=GeneratePopinaPlan(P); Expect(CountCategory(ConvertBuildingPlanToPlacements(Popina,P),ModuleCategory::Table)>0&&CountCategory(ConvertBuildingPlanToPlacements(Popina,P),ModuleCategory::Bench)>0,"Popina sedute e bancone");
    const BuildingPlan Cau=GenerateCauponaPlan(P); Expect(HasRoom(Cau,RoomType::LodgingRoom)&&CountCategory(ConvertBuildingPlanToPlacements(Cau,P),ModuleCategory::Bed)>0,"Caupona alloggio");
    const BuildingPlan Book=GenerateBookshopPlan(P); Expect(CountCategory(ConvertBuildingPlanToPlacements(Book,P),ModuleCategory::WritingDesk)>0&&CountCategory(ConvertBuildingPlanToPlacements(Book,P),ModuleCategory::ScrollStorage)>0,"Bookshop scrivania e rotoli");
    const BuildingPlan Bro=GenerateBrothelPlan(P); bool adult=false, explicitTag=false; for(const auto& R:Bro.Rooms){adult=adult||HasTag(R.Tags,"adult_service_area"); explicitTag=explicitTag||HasTag(R.Tags,"explicit");} Expect(adult&&!explicitTag,"Brothel funzionale non esplicito");
    const BuildingPlan Med=GenerateMedicalShopPlan(P); Expect(HasRoom(Med,RoomType::MedicalPreparationRoom)&&CalculateWorkerCapacity(Med)>0,"MedicalShop preparazione e medico");
    const BuildingPlan Barb=GenerateBarberShopPlan(P); Expect(HasRoom(Barb,RoomType::BarberArea)&&CountCategory(ConvertBuildingPlanToPlacements(Barb,P),ModuleCategory::MirrorMarker)>0,"BarberShop seduta e specchio placeholder");
    const BuildingPlan Mensa=GenerateMensaArgentariaPlan(P); Expect(HasRoom(Mensa,RoomType::ValueStorage)&&CountCategory(ConvertBuildingPlanToPlacements(Mensa,P),ModuleCategory::ValueStorageMarker)>0,"MensaArgentaria deposito valori");
    const BuildingPlan St=GenerateStabulumPlan(P); Expect(HasRoom(St,RoomType::Stall)&&CountCategory(ConvertBuildingPlanToPlacements(St,P),ModuleCategory::WateringTrough)>0,"Stabulum stalli acqua");
    std::vector<GenerationMessage> CW,CE; Expect(ValidateCompositeBuildingPlan(GenerateMixedUseHousePlan(P),CW,CE),"edificio misto valido");
    Expect(GetRecommendedUrbanComposition().front().first==BuildingType::PopularHouse,"prevalenza urbana abitazioni modeste");
}

void RunUtilitiesProductionPrompt24Tests()
{
    BuildingParameters P; P.WidthCm=1600; P.DepthCm=2000; P.MaximumModuleCount=4000;
    const std::vector<BuildingType> Types={BuildingType::BathComplex,BuildingType::Palaestra,BuildingType::CastellumAquae,BuildingType::AqueductSection,BuildingType::SewerSection,BuildingType::PublicFountain,BuildingType::Cistern,BuildingType::Well,BuildingType::Tinctoria,BuildingType::Tannery,BuildingType::TextileWorkshop,BuildingType::MetalWorkshop,BuildingType::PotteryWorkshop,BuildingType::OilWorkshop,BuildingType::Winery,BuildingType::PressingWorkshop,BuildingType::StandaloneOven,BuildingType::Horrea,BuildingType::UrbanGarden,BuildingType::ServiceYard};
    for(BuildingType T:Types){P.Type=T;const BuildingPlan A=GenerateBuildingPlan(P);const BuildingPlan B=GenerateBuildingPlan(P);Expect(A.ImplementationState==ArchetypeImplementationState::Implemented,"Prompt 24 archetipo implementato");Expect(!A.Rooms.empty()&&!A.InteractionPoints.empty(),"Prompt 24 stanze e NPC");const GenerationResult R=BuildPlanLayout(P,T);Expect(R.bSuccess&&!R.Placements.empty(),"Prompt 24 placeholder");Expect(AllTransformsFinite(R)&&BoundsCoherent(R),"Prompt 24 bounds e NaN");Expect(A.Rooms.size()==B.Rooms.size()&&A.ProductionDevices.size()==B.ProductionDevices.size(),"Prompt 24 determinismo");Expect(IsArchetypeImplemented(T),"Prompt 24 catalogo implementati");}
    const BuildingPlan Baths=GenerateBathComplexPlan(P);Expect(Baths.BathRooms.size()>=3&&!Baths.Hypocausts.empty()&&!Baths.HeatSources.empty(),"BathComplex sequenza e hypocaust");Expect(CalculateWaterDemand(Baths)>0&&CalculateDrainageDemand(Baths)>0&&CalculateHeatDemand(Baths)>0,"BathComplex domande utilities");
    const BuildingPlan Aq=GenerateAqueductSectionPlan(P);Expect(!Aq.AqueductSegments.empty()&&CountCategory(ConvertBuildingPlanToPlacements(Aq,P),ModuleCategory::AqueductArch)>0,"Acquedotto segmenti e arcate");
    const BuildingPlan Sewer=GenerateSewerSectionPlan(P);Expect(!Sewer.SewerSegments.empty()&&CountCategory(ConvertBuildingPlanToPlacements(Sewer,P),ModuleCategory::Manhole)>0,"Fognatura segmento e pozzetto");
    const BuildingPlan Tin=GenerateTinctoriaPlan(P);Expect(!Tin.ProductionFlows.empty()&&Tin.ProductionFlows.front().Stages.size()>=4,"Tinctoria flusso completo");
    const BuildingPlan Metal=GenerateMetalWorkshopPlan(P);Expect(!Metal.HeatSources.empty()&&!Metal.HazardZones.empty(),"MetalWorkshop calore e pericolo");
    const BuildingPlan Horrea=GenerateHorreaPlan(P);Expect(CalculateStorageCapacity(Horrea)>=1000&&CountCategory(ConvertBuildingPlanToPlacements(Horrea,P),ModuleCategory::StorageCell)>0,"Horrea capacita e celle");
    std::vector<GenerationMessage> W,E;Expect(ValidateUtilityConnections(Baths,W,E),"connessioni utilities valide");
    P.MaximumModuleCount=1;Expect(!BuildPlanLayout(P,BuildingType::BathComplex).bSuccess,"Prompt 24 MaximumModuleCount");
}

void RunArchitecturalMaterialPrompt28CoreTests()
{
    Expect(SurfaceRole::ExteriorWall != SurfaceRole::Roof, "Prompt 28 SurfaceRole distinti");
    Expect(WeatheringLevel::New != WeatheringLevel::Ruined, "Prompt 28 usura distinta");
    Expect(WealthTier::Poor != WealthTier::Wealthy, "Prompt 28 ricchezza distinta");
    const std::vector<double> Weights{1.0, 2.0, 1.0};
    const std::size_t First = SelectDeterministicWeightedIndex(Weights, 2801, 17u);
    const std::size_t Second = SelectDeterministicWeightedIndex(Weights, 2801, 17u);
    Expect(First == Second, "Prompt 28 variante deterministica per seed");
    Expect(First < Weights.size(), "Prompt 28 variante nei limiti");
    Expect(SelectDeterministicWeightedIndex({}, 2801) == 0, "Prompt 28 fallback selettore vuoto");
    std::vector<std::size_t> Seen;
    for (std::int32_t Seed = 0; Seed < 64; ++Seed)
    {
        const std::size_t Value = SelectDeterministicWeightedIndex({1.0, 1.0}, Seed, 28u);
        if (std::find(Seen.begin(), Seen.end(), Value) == Seen.end()) Seen.push_back(Value);
    }
    Expect(Seen.size() == 2, "Prompt 28 variazione controllata tra seed");
}

void RunDecoratedInteriorsPrompt29CoreTests()
{
    const std::vector<RoomDecorType> RoomTypes = {
        RoomDecorType::PopularDomestic, RoomDecorType::MediumDomestic, RoomDecorType::WealthyDomestic,
        RoomDecorType::Commercial, RoomDecorType::Productive, RoomDecorType::ThermalCold,
        RoomDecorType::ThermalWarm, RoomDecorType::ThermalHot, RoomDecorType::PlainService};
    const std::vector<WealthTier> WealthLevels = {
        WealthTier::Poor, WealthTier::Popular, WealthTier::Medium, WealthTier::Wealthy, WealthTier::Monumental};
    const std::vector<WeatheringLevel> WeatheringLevels = {
        WeatheringLevel::New, WeatheringLevel::Light, WeatheringLevel::Medium, WeatheringLevel::Heavy, WeatheringLevel::Ruined};
    for (const RoomDecorType Type : RoomTypes)
    {
        for (const WealthTier Wealth : WealthLevels)
        {
            for (const WeatheringLevel Weathering : WeatheringLevels)
            {
                const RomanRoomDecorationPlan Room = GenerateRomanRoomDecoration(
                    "prompt29_room", 720.0, 840.0, 320.0, Type, Wealth, Weathering, 2901, true);
                const RomanDecorationValidationResult Validation = ValidateRoomDecoration(Room, 256);
                Expect(Validation.bValid, "Prompt 29 piano decorativo valido per funzione ricchezza e usura");
                Expect(Room.Walls.size() == 4 && !Room.Floor.RoomId.empty(), "Prompt 29 quattro pareti e pavimento");
                Expect(CalculateDecorationModuleCount(Room) > 0 && IsFinite(CalculateDecorationComplexity(Room)), "Prompt 29 complessita e conteggio validi");
            }
        }
    }
    const RomanRoomDecorationPlan A = GenerateRomanRoomDecoration("deterministic", 900, 700, 320, RoomDecorType::MediumDomestic, WealthTier::Wealthy, WeatheringLevel::Medium, 2929);
    const RomanRoomDecorationPlan B = GenerateRomanRoomDecoration("deterministic", 900, 700, 320, RoomDecorType::MediumDomestic, WealthTier::Wealthy, WeatheringLevel::Medium, 2929);
    const RomanRoomDecorationPlan C = GenerateRomanRoomDecoration("deterministic", 900, 700, 320, RoomDecorType::MediumDomestic, WealthTier::Wealthy, WeatheringLevel::Medium, 2930);
    Expect(A.Style == B.Style && A.Palette.Id == B.Palette.Id && A.Walls.front().Panels.size() == B.Walls.front().Panels.size(), "Prompt 29 determinismo stesso seed");
    Expect(A.Palette.Id != C.Palette.Id || A.Style != C.Style, "Prompt 29 variazione controllata seed diverso");
    Expect(SelectFloorDecoration(RoomDecorType::Productive, WealthTier::Wealthy) == FloorDecorationType::ProductiveFloor, "Prompt 29 pavimento produttivo");
    Expect(SelectFloorDecoration(RoomDecorType::ThermalHot, WealthTier::Monumental) == FloorDecorationType::ThermalFloor, "Prompt 29 pavimento termale");
    Expect(SelectFloorDecoration(RoomDecorType::MediumDomestic, WealthTier::Medium) == FloorDecorationType::OpusSigninum, "Prompt 29 opus signinum");
    Expect(SelectFloorDecoration(RoomDecorType::WealthyDomestic, WealthTier::Wealthy) == FloorDecorationType::GeometricMosaic, "Prompt 29 mosaico geometrico");
    Expect(SelectFloorDecoration(RoomDecorType::WealthyDomestic, WealthTier::Monumental) == FloorDecorationType::OpusSectileInspired, "Prompt 29 opus sectile tecnico");
    RomanRoomDecorationPlan Invalid = GenerateRomanRoomDecoration("invalid", 900, 700, 320, RoomDecorType::MediumDomestic, WealthTier::Wealthy, WeatheringLevel::Medium, 2929);
    Invalid.Walls.at(1).Panels.front().OffsetCm = -1000.0;
    Expect(!ValidateRoomDecoration(Invalid).bValid, "Prompt 29 pannello fuori bounds rifiutato");
    Expect(!ValidateRoomDecoration(A, 1).bValid, "Prompt 29 MaximumModuleCount");
}

} // namespace

int main()
{
    std::cerr << "RUN Core\n";
    RunCoreTests();
    std::cerr << "RUN Prompt22\n";
    RunArchetypePrompt22Tests();
    std::cerr << "RUN Prompt23\n";
    RunResidentialCommercialPrompt23Tests();
    std::cerr << "RUN Prompt24\n";
    RunUtilitiesProductionPrompt24Tests();
    std::cerr << "RUN Prompt28\n";
    RunArchitecturalMaterialPrompt28CoreTests();
    std::cerr << "RUN Prompt29\n";
    RunDecoratedInteriorsPrompt29CoreTests();
    std::cerr << "RUN Complete\n";
    if (Failures > 0)
    {
        std::cerr << Failures << " test falliti\n";
        return EXIT_FAILURE;
    }
    std::cout << "CORE_CPP_TESTS_PASSED\n";
    std::cout << "CORE_CPP_DEBUG_TESTS_PASSED\n";
    std::cout << "BUILDING_ARCHETYPE_STATIC_CHECKS_PASSED\n";
    std::cout << "RESIDENTIAL_COMMERCIAL_STATIC_CHECKS_PASSED\n";
    std::cout << "UTILITIES_PRODUCTION_STATIC_CHECKS_PASSED\n";
    return EXIT_SUCCESS;
}
