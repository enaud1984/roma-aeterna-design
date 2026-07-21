#if WITH_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "Engine/World.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRARomanProceduralBuildingRuntimeTest, "RomaAeterna.Modular.PlaceholderRuntime.LOCAL_UNREAL_TEST_REQUIRED", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRARomanProceduralBuildingRuntimeTest::RunTest(const FString& Parameters)
{
	UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
	TestNotNull(TEXT("World locale Unreal richiesto"), World);
	if (!World) { return false; }
	ARARomanProceduralBuildingActor* Actor = World->SpawnActor<ARARomanProceduralBuildingActor>();
	TestNotNull(TEXT("Actor creato"), Actor);
	if (!Actor) { return false; }
	Actor->ModuleCatalog = nullptr;
	TestTrue(TEXT("GenerateBuilding con catalogo nullo non crasha"), Actor->GenerateBuilding());
	TestTrue(TEXT("Istanze generate"), Actor->GetGeneratedInstanceCount() > 0);
	const int32 FirstCount = Actor->GetGeneratedInstanceCount();
	Actor->ClearGeneratedBuilding();
	TestEqual(TEXT("ClearGeneratedBuilding svuota"), Actor->GetGeneratedInstanceCount(), 0);
	TestTrue(TEXT("Seconda generazione"), Actor->GenerateBuilding());
	TestEqual(TEXT("Nessun accumulo"), Actor->GetGeneratedInstanceCount(), FirstCount);
	TestTrue(TEXT("Casa ha muri"), Actor->GetInstanceCountByCategory(ERARomanModuleCategory::Wall) > 0);
	Actor->BuildingParameters.BuildingType = ERARomanBuildingType::Taberna;
	TestTrue(TEXT("Taberna genera prop"), Actor->GenerateBuilding() && Actor->GetInstanceCountByCategory(ERARomanModuleCategory::Prop) > 0);
	Actor->BuildingParameters.BuildingType = ERARomanBuildingType::Temple;
	Actor->BuildingParameters.ArchitecturalOrder = ERARomanArchitecturalOrder::Doric;
	TestTrue(TEXT("Tempio genera colonne"), Actor->GenerateBuilding() && Actor->GetInstanceCountByCategory(ERARomanModuleCategory::Column) > 0);
	Actor->BuildingParameters.BuildingType = ERARomanBuildingType::StreetSection;
	Actor->BuildingParameters.DoorCount = 0;
	TestTrue(TEXT("Strada genera floor"), Actor->GenerateBuilding() && Actor->GetInstanceCountByCategory(ERARomanModuleCategory::Floor) > 0);
	Actor->BuildingParameters.MaximumModuleCount = 1;
	TestFalse(TEXT("MaximumModuleCount blocca"), Actor->GenerateBuilding());
	return true;
}
#endif
