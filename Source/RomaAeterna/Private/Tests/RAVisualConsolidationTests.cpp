#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Components/LightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Engine/Light.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/SkyLight.h"
#include "Engine/TextRenderActor.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Misc/PackageName.h"
#include "Player/RACharacter.h"
#include "Tests/AutomationCommon.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "World/Modular/RARomanVisualCatalog.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRAVisualConsolidationTest,
	"RomaAeterna.Prompt25.VisualConsolidation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRAVisualConsolidationTest::RunTest(const FString& Parameters)
{
	FString MapFilename;
	TestTrue(TEXT("La mappa consolidata esiste"), FPackageName::DoesPackageExist(TEXT("/Game/Maps/RomaAeternaVerticalSlice"), &MapFilename));
	if (!AutomationOpenMap(TEXT("/Game/Maps/RomaAeternaVerticalSlice"), true))
	{
		AddError(TEXT("Caricamento della vertical slice consolidata fallito."));
		return false;
	}
	UWorld* World = GWorld;
	TestNotNull(TEXT("Mondo consolidato caricato"), World);
	if (!World) return false;

	int32 ArchetypeCount = 0;
	int32 NorthFrontCount = 0;
	int32 SouthFrontCount = 0;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
	{
		ARARomanProceduralBuildingActor* Building = *It;
		++ArchetypeCount;
		NorthFrontCount += Building->ActorHasTag(TEXT("RA_URBAN_FRONT_NORTH")) ? 1 : 0;
		SouthFrontCount += Building->ActorHasTag(TEXT("RA_URBAN_FRONT_SOUTH")) ? 1 : 0;
		TestTrue(TEXT("Generazione consolidata riuscita"), Building->GenerateBuilding());
		const int32 FirstCount = Building->GetGeneratedInstanceCount();
		TestTrue(TEXT("Ogni archetipo genera componenti"), FirstCount > 0);
		bool bMaterialAssigned = false;
		bool bCollisionAssigned = false;
		for (const UInstancedStaticMeshComponent* Component : Building->GeneratedInstanceComponents)
		{
			bMaterialAssigned |= Component && Component->GetMaterial(0) != nullptr;
			bCollisionAssigned |= Component && Component->GetCollisionEnabled() == ECollisionEnabled::QueryAndPhysics;
		}
		TestTrue(TEXT("Materiale tecnico assegnato"), bMaterialAssigned);
		TestTrue(TEXT("Collisione runtime assegnata"), bCollisionAssigned);
		Building->ClearGeneratedBuilding();
		TestTrue(TEXT("Rebuild consolidato riuscito"), Building->RebuildBuilding());
		TestEqual(TEXT("Seed invariato e conteggio deterministico"), Building->GetGeneratedInstanceCount(), FirstCount);
	}
	TestTrue(TEXT("Almeno nove archetipi"), ArchetypeCount >= 9);
	TestTrue(TEXT("Fronte urbano nord continuo"), NorthFrontCount >= 4);
	TestTrue(TEXT("Fronte urbano sud continuo"), SouthFrontCount >= 4);

	int32 RoadStoneCount = 0;
	int32 SidewalkCount = 0;
	int32 CrossingStoneCount = 0;
	bool bHasAlley = false;
	bool bHasPlaza = false;
	for (TActorIterator<AStaticMeshActor> It(World); It; ++It)
	{
		RoadStoneCount += It->ActorHasTag(TEXT("RA_ROMAN_ROAD")) ? 1 : 0;
		SidewalkCount += It->ActorHasTag(TEXT("RA_SIDEWALK")) ? 1 : 0;
		CrossingStoneCount += It->ActorHasTag(TEXT("RA_CROSSING_STONE")) ? 1 : 0;
		bHasAlley |= It->ActorHasTag(TEXT("RA_ALLEY"));
		bHasPlaza |= It->ActorHasTag(TEXT("RA_PLAZA"));
	}
	TestTrue(TEXT("Basolato modulare presente"), RoadStoneCount >= 40);
	TestTrue(TEXT("Marciapiedi presenti"), SidewalkCount >= 4);
	TestTrue(TEXT("Pietre di attraversamento presenti"), CrossingStoneCount >= 4);
	TestTrue(TEXT("Vicolo laterale presente"), bHasAlley);
	TestTrue(TEXT("Slargo presente"), bHasPlaza);

	int32 MovableLightCount = 0;
	for (TActorIterator<ALight> It(World); It; ++It)
	{
		TestEqual(TEXT("Nessuna luce statica"), It->GetLightComponent()->Mobility, EComponentMobility::Movable);
		MovableLightCount += It->GetLightComponent()->Mobility == EComponentMobility::Movable ? 1 : 0;
	}
	for (TActorIterator<ASkyLight> It(World); It; ++It)
	{
		TestEqual(TEXT("Sky Light non statica"), It->GetLightComponent()->Mobility, EComponentMobility::Movable);
		MovableLightCount += It->GetLightComponent()->Mobility == EComponentMobility::Movable ? 1 : 0;
	}
	TestTrue(TEXT("Illuminazione dinamica presente"), MovableLightCount >= 2);

	int32 LabelCount = 0;
	for (TActorIterator<ATextRenderActor> It(World); It; ++It) LabelCount += It->ActorHasTag(TEXT("RA_TECHNICAL_LABEL")) ? 1 : 0;
	TestTrue(TEXT("Label tecniche presenti"), LabelCount >= 9);
	TestNotNull(TEXT("Character tecnico valido"), GetDefault<ARACharacter>());
	TestTrue(TEXT("Silhouette e input restano validi"), GetDefault<ARACharacter>()->HasValidPlayableFoundation());

	TestTrue(TEXT("Fallback mesh catalogo valido"), URARomanVisualCatalog::GetFallbackMeshPath(ERARomanModuleCategory::Wall).IsValid());
	TestTrue(TEXT("Materiale catalogo disponibile"), URARomanVisualCatalog::GetTechnicalMaterialPath(ERARomanModuleCategory::Wall).IsValid());
	return true;
}

#endif
