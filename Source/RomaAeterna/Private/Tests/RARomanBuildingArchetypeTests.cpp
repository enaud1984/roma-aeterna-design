#if WITH_DEV_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "World/Modular/RARomanBuildingRuleLibrary.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRARomanBuildingArchetypeRuntimeTest, "RomaAeterna.Prompt23.ResidentialCommercial", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRARomanBuildingArchetypeRuntimeTest::RunTest(const FString& Parameters)
{
	AddInfo(TEXT("LOCAL_UNREAL_TEST_REQUIRED: eseguire localmente con UE 5.8; il cloud non dichiara questi test superati."));
	FRARomanBuildingParameters P;
	P.MaximumModuleCount = 1000;
	const ERARomanBuildingType Types[] = {
		ERARomanBuildingType::AtriumDomus, ERARomanBuildingType::Thermopolium,
		ERARomanBuildingType::Fullonica, ERARomanBuildingType::Pistrinum,
		ERARomanBuildingType::PublicLatrine, ERARomanBuildingType::SmallTemple,
		ERARomanBuildingType::DomusMedia, ERARomanBuildingType::PeristyleDomus,
		ERARomanBuildingType::RichDomus, ERARomanBuildingType::PopularHouse,
		ERARomanBuildingType::Insula, ERARomanBuildingType::Cenaculum,
		ERARomanBuildingType::MixedUseHouse, ERARomanBuildingType::Taberna,
		ERARomanBuildingType::Popina, ERARomanBuildingType::Caupona,
		ERARomanBuildingType::Bookshop, ERARomanBuildingType::Brothel,
		ERARomanBuildingType::MedicalShop, ERARomanBuildingType::BarberShop,
		ERARomanBuildingType::MensaArgentaria, ERARomanBuildingType::Stabulum
	};
	for (ERARomanBuildingType Type : Types)
	{
		P.BuildingType = Type;
		const FRARomanGenerationResult Result = URARomanBuildingRuleLibrary::GenerateBuildingByType(P);
		TestTrue(TEXT("generazione archetipo"), Result.GeneratedPlacements.Num() > 0);
		TestTrue(TEXT("MaximumModuleCount"), Result.GeneratedPlacements.Num() <= P.MaximumModuleCount);
	}
	TestEqual(TEXT("catalogo implementati Prompt 20-23"), URARomanBuildingRuleLibrary::GetImplementedArchetypes().Num(), static_cast<int32>(UE_ARRAY_COUNT(Types)));
	TestTrue(TEXT("PeristyleDomus implementata"), URARomanBuildingRuleLibrary::IsArchetypeImplemented(ERARomanBuildingType::PeristyleDomus));
	return true;
}
#endif
