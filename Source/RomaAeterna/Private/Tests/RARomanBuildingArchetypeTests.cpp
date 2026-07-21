#if WITH_DEV_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "World/Modular/RARomanBuildingRuleLibrary.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRARomanBuildingArchetypeRuntimeTest, "RomaAeterna.BuildingArchetypes.RuntimePlaceholder", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRARomanBuildingArchetypeRuntimeTest::RunTest(const FString& Parameters)
{
	AddInfo(TEXT("LOCAL_UNREAL_TEST_REQUIRED: eseguire localmente con UE 5.8; il cloud non dichiara questi test superati."));
	FRARomanBuildingParameters P;
	P.MaximumModuleCount = 1000;
	const ERARomanBuildingType Types[] = { ERARomanBuildingType::AtriumDomus, ERARomanBuildingType::Thermopolium, ERARomanBuildingType::Fullonica, ERARomanBuildingType::Pistrinum, ERARomanBuildingType::PublicLatrine, ERARomanBuildingType::SmallTemple };
	for (ERARomanBuildingType Type : Types)
	{
		P.BuildingType = Type;
		const FRARomanGenerationResult Result = URARomanBuildingRuleLibrary::GenerateBuildingByType(P);
		TestTrue(TEXT("generazione archetipo"), Result.GeneratedPlacements.Num() > 0);
		TestTrue(TEXT("MaximumModuleCount"), Result.GeneratedPlacements.Num() <= P.MaximumModuleCount);
	}
	TestTrue(TEXT("catalogo implementati"), URARomanBuildingRuleLibrary::GetImplementedArchetypes().Num() == 6);
	TestFalse(TEXT("pianificato non implementato"), URARomanBuildingRuleLibrary::IsArchetypeImplemented(ERARomanBuildingType::PeristyleDomus));
	return true;
}
#endif
