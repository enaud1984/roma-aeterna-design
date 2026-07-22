#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#include "Camera/CameraComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "Game/RAVerticalSliceGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/SpringArmComponent.h"
#include "Misc/PackageName.h"
#include "Player/RACharacter.h"
#include "Player/RAPlayerController.h"
#include "Tests/AutomationCommon.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRAVerticalSliceTest,
	"RomaAeterna.Prompt24Bis.VerticalSlice",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRAVerticalSliceTest::RunTest(const FString& Parameters)
{
	FString MapFilename;
	TestTrue(
		TEXT("Il package RomaAeternaVerticalSlice esiste"),
		FPackageName::DoesPackageExist(TEXT("/Game/Maps/RomaAeternaVerticalSlice"), &MapFilename));
	TestTrue(TEXT("La vertical slice e una mappa .umap"), MapFilename.EndsWith(TEXT(".umap")));
	if (!AutomationOpenMap(TEXT("/Game/Maps/RomaAeternaVerticalSlice")))
	{
		AddError(TEXT("Impossibile caricare RomaAeternaVerticalSlice."));
		return false;
	}

	UWorld* World = GWorld;
	TestNotNull(TEXT("Il mondo della vertical slice e caricato"), World);
	if (!World)
	{
		return false;
	}

	const ARAVerticalSliceGameMode* GameMode = GetDefault<ARAVerticalSliceGameMode>();
	TestNotNull(TEXT("Il GameMode dedicato esiste"), GameMode);
	TestTrue(TEXT("DefaultPawnClass usa ARACharacter"), GameMode && GameMode->DefaultPawnClass == ARACharacter::StaticClass());
	TestTrue(TEXT("PlayerControllerClass usa ARAPlayerController"), GameMode && GameMode->PlayerControllerClass == ARAPlayerController::StaticClass());
	TestTrue(
		TEXT("La mappa usa il GameMode dedicato"),
		World->GetWorldSettings()->DefaultGameMode == ARAVerticalSliceGameMode::StaticClass());

	APlayerStart* PlayerStart = nullptr;
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		PlayerStart = *It;
		break;
	}
	TestNotNull(TEXT("PlayerStart presente"), PlayerStart);

	ARACharacter* Character = World->SpawnActor<ARACharacter>(
		ARACharacter::StaticClass(),
		PlayerStart ? PlayerStart->GetActorTransform() : FTransform(FVector(0, 0, 150)));
	TestNotNull(TEXT("Il Pawn tecnico viene creato"), Character);
	if (Character)
	{
		TestNotNull(TEXT("SpringArm presente"), Character->GetThirdPersonSpringArm());
		TestNotNull(TEXT("Camera terza persona presente"), Character->GetThirdPersonCamera());
		TestNotNull(TEXT("CharacterMovement presente"), Character->GetCharacterMovement());
		TestTrue(TEXT("Capsule e componenti gameplay validi"), Character->HasValidPlayableFoundation());
		Character->Destroy();
	}

	const TArray<FName> RequiredRoleTags = {
		TEXT("RA_RESIDENTIAL"), TEXT("RA_COMMERCIAL"), TEXT("RA_BATH"),
		TEXT("RA_WATER"), TEXT("RA_PRODUCTIVE"), TEXT("RA_UTILITY")};
	TSet<FName> FoundRoleTags;
	int32 GeneratedActors = 0;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
	{
		ARARomanProceduralBuildingActor* Building = *It;
		for (const FName RoleTag : RequiredRoleTags)
		{
			if (Building->ActorHasTag(RoleTag))
			{
				FoundRoleTags.Add(RoleTag);
			}
		}

		TestTrue(TEXT("La generazione runtime produce moduli"), Building->GenerateBuilding());
		const int32 FirstCount = Building->GetGeneratedInstanceCount();
		TestTrue(TEXT("Il conteggio moduli e positivo"), FirstCount > 0);
		bool bHasBlockingCollision = false;
		for (const UInstancedStaticMeshComponent* Component : Building->GeneratedInstanceComponents)
		{
			bHasBlockingCollision |= Component
				&& Component->GetCollisionEnabled() == ECollisionEnabled::QueryAndPhysics
				&& Component->GetCollisionResponseToChannel(ECC_Pawn) == ECR_Block;
		}
		TestTrue(TEXT("I placeholder generati bloccano il Pawn"), bHasBlockingCollision);

		Building->ClearGeneratedBuilding();
		TestEqual(TEXT("Clear elimina tutte le istanze"), Building->GetGeneratedInstanceCount(), 0);
		TestTrue(TEXT("Rebuild riesce"), Building->RebuildBuilding());
		TestEqual(TEXT("Il rebuild con lo stesso seed e deterministico"), Building->GetGeneratedInstanceCount(), FirstCount);
		++GeneratedActors;
	}

	TestTrue(TEXT("Sono presenti almeno sei generatori reali"), GeneratedActors >= 6);
	for (const FName RoleTag : RequiredRoleTags)
	{
		TestTrue(*FString::Printf(TEXT("Archetipo richiesto presente: %s"), *RoleTag.ToString()), FoundRoleTags.Contains(RoleTag));
	}

	AStaticMeshActor* Road = nullptr;
	for (TActorIterator<AStaticMeshActor> It(World); It; ++It)
	{
		if (It->ActorHasTag(TEXT("RA_RomanRoad")))
		{
			Road = *It;
			break;
		}
	}
	TestNotNull(TEXT("La strada tecnica e presente"), Road);
	TestTrue(
		TEXT("La strada ha collisione fisica e di query"),
		Road && Road->GetStaticMeshComponent()->GetCollisionEnabled() == ECollisionEnabled::QueryAndPhysics);
	return true;
}

#endif
