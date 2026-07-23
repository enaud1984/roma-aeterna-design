#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "EngineUtils.h"
#include "Tests/AutomationCommon.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"

namespace
{
UWorld* OpenPrompt30Map(FAutomationTestBase& Test)
{
	if (!AutomationOpenMap(TEXT("/Game/Maps/RomaAeternaVerticalSlice"), true))
	{
		Test.AddError(TEXT("Impossibile caricare la strada pompeiana compatta."));
		return nullptr;
	}
	return GWorld;
}

bool HasComponentTag(const ARARomanProceduralBuildingActor* Building, const FName Tag)
{
	for (const UInstancedStaticMeshComponent* Component : Building->GeneratedInstanceComponents)
	{
		if (Component && Component->ComponentHasTag(Tag) && Component->GetInstanceCount() > 0) return true;
	}
	return false;
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRACompactPompeianCompositionTest,
	"RomaAeterna.Prompt30.CompactPompeianComposition",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRACompactPompeianCompositionTest::RunTest(const FString& Parameters)
{
	UWorld* World = OpenPrompt30Map(*this);
	if (!World) return false;
	int32 North = 0, South = 0, OneStorey = 0, TwoStorey = 0;
	int32 Popular = 0, Domus = 0, Shops = 0, Thermopolia = 0, Bakeries = 0;
	int32 Fountains = 0, GardensOrYards = 0, Generated = 0;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
	{
		if (It->ActorHasTag(TEXT("RA_URBAN_FRONT_NORTH"))) ++North;
		if (It->ActorHasTag(TEXT("RA_URBAN_FRONT_SOUTH"))) ++South;
		if (It->BuildingParameters.FloorCount > 1) ++TwoStorey; else ++OneStorey;
		switch (It->BuildingParameters.BuildingType)
		{
		case ERARomanBuildingType::PopularHouse: ++Popular; break;
		case ERARomanBuildingType::DomusMedia: ++Domus; break;
		case ERARomanBuildingType::Taberna: ++Shops; break;
		case ERARomanBuildingType::Thermopolium: ++Thermopolia; break;
		case ERARomanBuildingType::Pistrinum: ++Bakeries; break;
		case ERARomanBuildingType::PublicFountain: ++Fountains; break;
		case ERARomanBuildingType::UrbanGarden:
		case ERARomanBuildingType::ServiceYard: ++GardensOrYards; break;
		default: break;
		}
		TestTrue(TEXT("Generazione edificio Prompt 30"), It->GenerateBuilding());
		Generated += It->GetGeneratedInstanceCount();
	}
	TestTrue(TEXT("Fronte nord continuo e popolato"), North >= 10);
	TestTrue(TEXT("Fronte sud continuo e popolato"), South >= 10);
	TestTrue(TEXT("Almeno due case popolari"), Popular >= 2);
	TestTrue(TEXT("Almeno due domus medie"), Domus >= 2);
	TestTrue(TEXT("Almeno due tabernae"), Shops >= 2);
	TestTrue(TEXT("Thermopolium presente"), Thermopolia >= 1);
	TestTrue(TEXT("Pistrinum presente"), Bakeries >= 1);
	TestTrue(TEXT("Fontana pubblica presente"), Fountains >= 1);
	TestTrue(TEXT("Giardino o corte di servizio presente"), GardensOrYards >= 1);
	TestTrue(TEXT("Alternanza fra uno e due piani"), OneStorey >= 6 && TwoStorey >= 6);
	TestTrue(TEXT("Moduli procedurali prodotti"), Generated > 250);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRACompactPompeianFacadesTest,
	"RomaAeterna.Prompt30.FacadesAndInteriors",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRACompactPompeianFacadesTest::RunTest(const FString& Parameters)
{
	UWorld* World = OpenPrompt30Map(*this);
	if (!World) return false;
	int32 Accessible = 0, Decorated = 0, Balconies = 0;
	bool bShopInterior = false, bThermopoliumCounter = false, bBakeryOven = false, bAtrium = false;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
	{
		if (!It->GenerateBuilding()) continue;
		if (It->GetAccessibleRoomCount() > 0) ++Accessible;
		if (It->GetDecorationPanelCount() > 0) ++Decorated;
		Balconies += HasComponentTag(*It, TEXT("RA_URBAN_BALCONY")) ? 1 : 0;
		bShopInterior |= HasComponentTag(*It, TEXT("RA_SHOP_INTERIOR"));
		bThermopoliumCounter |= HasComponentTag(*It, TEXT("RA_THERMOPOLIUM_COUNTER"));
		bBakeryOven |= HasComponentTag(*It, TEXT("RA_PISTRINUM_OVEN"));
		bAtrium |= HasComponentTag(*It, TEXT("RA_DOMUS_ATRIUM"));
	}
	TestTrue(TEXT("Interni accessibili distribuiti"), Accessible >= 15);
	TestTrue(TEXT("Facciate dipinte distribuite"), Decorated >= 15);
	TestTrue(TEXT("Balconi o sporti lignei presenti"), Balconies >= 4);
	TestTrue(TEXT("Interno semplice di taberna"), bShopInterior);
	TestTrue(TEXT("Bancone del thermopolium"), bThermopoliumCounter);
	TestTrue(TEXT("Forno del pistrinum"), bBakeryOven);
	TestTrue(TEXT("Atrio della domus"), bAtrium);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRACompactPompeianRuntimeStabilityTest,
	"RomaAeterna.Prompt30.RuntimeStability",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRACompactPompeianRuntimeStabilityTest::RunTest(const FString& Parameters)
{
	UWorld* World = OpenPrompt30Map(*this);
	if (!World) return false;
	int32 Checked = 0;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
	{
		TestTrue(TEXT("Generazione iniziale"), It->GenerateBuilding());
		const int32 InitialInstances = It->GetGeneratedInstanceCount();
		const int32 InitialPanels = It->GetDecorationPanelCount();
		It->SetRoofVisibility(false);
		TestEqual(TEXT("F10 nasconde i tetti"), It->GetVisibleRoofInstanceCount(), 0);
		It->SetRoofVisibility(true);
		TestTrue(TEXT("F10 ripristina i tetti"), It->GetVisibleRoofInstanceCount() > 0 || !It->IsAccessibleInteriorArchetype());
		It->SetDecorationFallbackEnabled(true);
		It->SetDecorationFallbackEnabled(false);
		TestEqual(TEXT("F11 non accumula pannelli"), It->GetDecorationPanelCount(), InitialPanels);
		TestTrue(TEXT("F5/rebuild deterministico"), It->RebuildBuilding());
		TestEqual(TEXT("Numero istanze deterministico"), It->GetGeneratedInstanceCount(), InitialInstances);
		++Checked;
	}
	TestTrue(TEXT("Intero tessuto verificato"), Checked >= 20);
	return true;
}

#endif
