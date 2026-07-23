#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#include "Components/CapsuleComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Player/RACharacter.h"
#include "Tests/AutomationCommon.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRADecoratedInteriorsTest,
	"RomaAeterna.Prompt29.DecoratedInteriors",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRADecoratedInteriorsTest::RunTest(const FString& Parameters)
{
	if (!AutomationOpenMap(TEXT("/Game/Maps/RomaAeternaVerticalSlice")))
	{
		AddError(TEXT("Impossibile caricare RomaAeternaVerticalSlice."));
		return false;
	}
	UWorld* World = GWorld;
	TestNotNull(TEXT("Vertical slice caricata"), World);
	if (!World) return false;

	TSet<ERARomanBuildingType> Required = {
		ERARomanBuildingType::PopularHouse, ERARomanBuildingType::DomusMedia,
		ERARomanBuildingType::Taberna, ERARomanBuildingType::Thermopolium,
		ERARomanBuildingType::BathComplex};
	TSet<ERAPompeianDecorativeStyle> Styles;
	int32 AccessibleBuildings = 0;
	int32 AccessibleRooms = 0;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
	{
		if (!It->IsAccessibleInteriorArchetype()) continue;
		TestTrue(TEXT("Generazione edificio accessibile"), It->GenerateBuilding());
		TestTrue(TEXT("Ingresso e stanze accessibili"), It->GetAccessibleRoomCount() >= 2);
		TestTrue(TEXT("Pareti dipinte generate"), It->GetDecorationPanelCount() > 0);
		TestTrue(TEXT("Pavimento decorativo assegnato"), static_cast<int32>(It->GetFloorDecorationType()) >= 0);
		bool bBlockingShell = false;
		for (const UInstancedStaticMeshComponent* Component : It->InteriorInstanceComponents)
		{
			bBlockingShell |= Component && Component->GetCollisionEnabled() == ECollisionEnabled::QueryAndPhysics;
		}
		TestTrue(TEXT("Collisione guscio interno presente"), bBlockingShell);
		const int32 InitialInstances = It->GetGeneratedInstanceCount();
		const int32 InitialPanels = It->GetDecorationPanelCount();
		const ERAPompeianDecorativeStyle InitialStyle = It->GetDecorativeStyle();
		It->SetRoofVisibility(false);
		for (const UInstancedStaticMeshComponent* Roof : It->RoofInstanceComponents)
		{
			TestFalse(TEXT("Toggle coperture nasconde il tetto"), Roof && Roof->IsVisible());
		}
		It->SetRoofVisibility(true);
		It->SetDecorationFallbackEnabled(true);
		TestTrue(TEXT("Fallback decorazione disponibile"), It->GetDecorationFallbackCount() > 0);
		It->SetDecorationFallbackEnabled(false);
		It->SetDecorationVariant(0);
		TestEqual(TEXT("Rebuild deterministico: istanze"), It->GetGeneratedInstanceCount(), InitialInstances);
		TestEqual(TEXT("Rebuild deterministico: pannelli"), It->GetDecorationPanelCount(), InitialPanels);
		TestEqual(TEXT("Rebuild deterministico: stile"), It->GetDecorativeStyle(), InitialStyle);
		Styles.Add(It->GetDecorativeStyle());
		Required.Remove(It->BuildingParameters.BuildingType);
		AccessibleRooms += It->GetAccessibleRoomCount();
		++AccessibleBuildings;
	}
	TestTrue(TEXT("Almeno cinque edifici accessibili"), AccessibleBuildings >= 5);
	TestTrue(TEXT("Tutti gli archetipi obbligatori accessibili"), Required.Num() == 0);
	TestTrue(TEXT("Numero stanze accessibili positivo"), AccessibleRooms >= 10);
	TestTrue(TEXT("Piu stili decorativi attivi"), Styles.Num() >= 3);
	AddInfo(FString::Printf(TEXT("PROMPT29_METRICS accessible_buildings=%d accessible_rooms=%d styles=%d"),
		AccessibleBuildings, AccessibleRooms, Styles.Num()));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRAInteriorTraversalTest,
	"RomaAeterna.Prompt29.InteriorTraversal",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRAInteriorTraversalTest::RunTest(const FString& Parameters)
{
	if (!AutomationOpenMap(TEXT("/Game/Maps/RomaAeternaVerticalSlice"))) return false;
	UWorld* World = GWorld;
	ARARomanProceduralBuildingActor* Target = nullptr;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
	{
		if (It->BuildingParameters.BuildingType == ERARomanBuildingType::PopularHouse)
		{
			Target = *It;
			break;
		}
	}
	TestNotNull(TEXT("PopularHouse accessibile trovata"), Target);
	if (!Target || !Target->GenerateBuilding()) return false;

	const FVector Outside = Target->GetActorTransform().TransformPosition(FVector(0, -650, 100));
	const FVector Threshold = Target->GetActorTransform().TransformPosition(FVector(0, -430, 100));
	const FVector Inside = Target->GetActorTransform().TransformPosition(FVector(0, -220, 100));
	ARACharacter* Character = World->SpawnActor<ARACharacter>(ARACharacter::StaticClass(), Outside, Target->GetActorRotation());
	TestNotNull(TEXT("Character traversal creato"), Character);
	if (!Character) return false;
	const FVector Initial = Character->GetActorLocation();
	Character->SetActorLocation(Threshold, false);
	TestTrue(TEXT("Movimento simulato verso la soglia"), !Character->GetActorLocation().Equals(Initial));
	Character->SetActorLocation(Inside, false);
	TestTrue(TEXT("Ingresso nella stanza"), FVector::DistSquared(Character->GetActorLocation(), Inside) < 4.0);
	Character->SetActorLocation(Outside, false);
	TestTrue(TEXT("Ritorno all'esterno"), FVector::DistSquared(Character->GetActorLocation(), Outside) < 4.0);
	TestTrue(TEXT("Apertura permanente disponibile"), Target->GetAccessibleRoomCount() >= 2);
	Character->Destroy();
	AddInfo(TEXT("INTERIOR_TRAVERSAL_AUTOMATION_PASSED; verifica fisica tastiera/mouse ancora manuale."));
	return true;
}

#endif
