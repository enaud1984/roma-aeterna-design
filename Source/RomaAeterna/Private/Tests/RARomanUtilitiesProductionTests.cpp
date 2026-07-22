#if WITH_DEV_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "World/Modular/RARomanBuildingRuleLibrary.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRARomanUtilitiesProductionTest, "RomaAeterna.Prompt24.UtilitiesProduction", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRARomanUtilitiesProductionTest::RunTest(const FString& Parameters)
{
	AddInfo(TEXT("LOCAL_UNREAL_TEST_REQUIRED: verifica locale UE 5.8 senza dichiarare PIE."));
	FRARomanBuildingParameters P; P.WidthCm=1600; P.DepthCm=2000; P.MaximumModuleCount=4000;
	const ERARomanBuildingType Types[]={ERARomanBuildingType::BathComplex,ERARomanBuildingType::Palaestra,ERARomanBuildingType::CastellumAquae,ERARomanBuildingType::AqueductSection,ERARomanBuildingType::SewerSection,ERARomanBuildingType::PublicFountain,ERARomanBuildingType::Cistern,ERARomanBuildingType::Well,ERARomanBuildingType::Tinctoria,ERARomanBuildingType::Tannery,ERARomanBuildingType::TextileWorkshop,ERARomanBuildingType::MetalWorkshop,ERARomanBuildingType::PotteryWorkshop,ERARomanBuildingType::OilWorkshop,ERARomanBuildingType::Winery,ERARomanBuildingType::PressingWorkshop,ERARomanBuildingType::StandaloneOven,ERARomanBuildingType::Horrea,ERARomanBuildingType::UrbanGarden,ERARomanBuildingType::ServiceYard};
	for(ERARomanBuildingType Type:Types){P.BuildingType=Type;const FRARomanGenerationResult A=URARomanBuildingRuleLibrary::GenerateBuildingByType(P);const FRARomanGenerationResult B=URARomanBuildingRuleLibrary::GenerateBuildingByType(P);TestTrue(TEXT("generazione Prompt 24"),A.bSuccess&&A.GeneratedPlacements.Num()>0);TestEqual(TEXT("determinismo Prompt 24"),A.GeneratedPlacements.Num(),B.GeneratedPlacements.Num());TestTrue(TEXT("MaximumModuleCount"),A.GeneratedPlacements.Num()<=P.MaximumModuleCount);TestTrue(TEXT("stanze e punti NPC"),A.GeneratedRoomCount>0&&A.GeneratedInteractionPointCount>0);}
	P.BuildingType=ERARomanBuildingType::BathComplex;const auto Baths=URARomanBuildingRuleLibrary::GenerateBathComplexPlan(P);TestTrue(TEXT("terme utilities"),Baths.WaterDemand>0&&Baths.DrainageDemand>0&&Baths.HeatDemand>0&&Baths.UtilityConnectionCount>=3);
	P.BuildingType=ERARomanBuildingType::MetalWorkshop;const auto Metal=URARomanBuildingRuleLibrary::GenerateMetalWorkshopPlan(P);TestTrue(TEXT("officina pericoli"),Metal.HeatDemand>0&&Metal.HazardZoneCount>0&&Metal.ProductionStageCount>=4);
	P.BuildingType=ERARomanBuildingType::Horrea;const auto Horrea=URARomanBuildingRuleLibrary::GenerateHorreaPlan(P);TestTrue(TEXT("horrea capacita"),Horrea.StorageCapacity>=1000&&Horrea.ProductionStageCount>=4);
	return true;
}
#endif
