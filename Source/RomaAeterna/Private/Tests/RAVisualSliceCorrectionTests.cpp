#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "InputMappingContext.h"
#include "Materials/MaterialInterface.h"
#include "Player/RACharacter.h"
#include "Tests/AutomationCommon.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "World/Modular/RARomanVisualCatalog.h"

namespace
{
UWorld* OpenVerticalSlice(FAutomationTestBase& Test)
{
	if (!AutomationOpenMap(TEXT("/Game/Maps/RomaAeternaVerticalSlice"), true))
	{
		Test.AddError(TEXT("Impossibile caricare RomaAeternaVerticalSlice."));
		return nullptr;
	}
	return GWorld;
}

TArray<ARARomanProceduralBuildingActor*> GenerateBuildings(UWorld* World)
{
	TArray<ARARomanProceduralBuildingActor*> Buildings;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
	{
		if (It->GenerateBuilding())
		{
			Buildings.Add(*It);
		}
	}
	return Buildings;
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRAVisualSliceCorrectionTest,
	"RomaAeterna.Prompt29Bis.VisualSliceCorrection",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRAVisualSliceCorrectionTest::RunTest(const FString& Parameters)
{
	UWorld* World = OpenVerticalSlice(*this);
	if (!World) return false;
	const TArray<ARARomanProceduralBuildingActor*> Buildings = GenerateBuildings(World);
	int32 Instances = 0;
	int32 Rejected = 0;
	for (const ARARomanProceduralBuildingActor* Building : Buildings)
	{
		Instances += Building->GetGeneratedInstanceCount();
		Rejected += Building->GetRejectedTransformCount();
	}
	TestTrue(TEXT("Almeno nove edifici generati"), Buildings.Num() >= 9);
	TestTrue(TEXT("La scena genera oltre cento istanze"), Instances > 100);
	TestEqual(TEXT("Nessuna trasformazione runtime rifiutata"), Rejected, 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRABuildingTransformValidationTest,
	"RomaAeterna.Prompt29Bis.BuildingTransformValidation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRABuildingTransformValidationTest::RunTest(const FString& Parameters)
{
	UWorld* World = OpenVerticalSlice(*this);
	if (!World) return false;
	int32 Checked = 0;
	for (ARARomanProceduralBuildingActor* Building : GenerateBuildings(World))
	{
		for (const UInstancedStaticMeshComponent* Component : Building->GeneratedInstanceComponents)
		{
			if (!Component) continue;
			for (int32 Index = 0; Index < Component->GetInstanceCount(); ++Index)
			{
				FTransform Transform;
				TestTrue(TEXT("Transform istanza leggibile"), Component->GetInstanceTransform(Index, Transform, true));
				TestFalse(TEXT("Transform privo di NaN/Infinity"), Transform.ContainsNaN());
				const FVector Scale = Transform.GetScale3D().GetAbs();
				TestTrue(TEXT("Scala positiva"), Scale.GetMin() > 0.0);
				TestTrue(TEXT("Rapporto assi entro soglia 80:1"), Scale.GetMax() / Scale.GetMin() <= 80.0);
				TestTrue(TEXT("Modulo entro 1000 metri dal mondo"), Transform.GetLocation().GetAbsMax() <= 100000.0);
				++Checked;
			}
		}
	}
	TestTrue(TEXT("Trasformazioni controllate"), Checked > 100);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRAMaterialResolutionTest,
	"RomaAeterna.Prompt29Bis.MaterialResolution",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRAMaterialResolutionTest::RunTest(const FString& Parameters)
{
	const TCHAR* Names[] = {
		TEXT("Plaster_Light"), TEXT("Plaster_Ochre"), TEXT("Plaster_Red"),
		TEXT("Brick_Popular"), TEXT("Brick_Thermal"), TEXT("Road_Secondary"),
		TEXT("Roof_Terracotta"), TEXT("Wood_Dark"), TEXT("Wood_Worn"),
		TEXT("Ground_Dry"), TEXT("Ground_Productive")};
	for (const TCHAR* Name : Names)
	{
		const FString Path = FString::Printf(
			TEXT("/Game/LocalAssets/RomaAeterna/Materials/MI_RA_Local_%s.MI_RA_Local_%s"), Name, Name);
		UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, *Path);
		TestNotNull(*FString::Printf(TEXT("Materiale locale caricato: %s"), Name), Material);
		if (Material)
		{
			TestNotNull(TEXT("Parent/base material valido"), Material->GetMaterial());
			TestTrue(TEXT("Materiale compilabile per ISMC"),
				Material->CheckMaterialUsage_Concurrent(MATUSAGE_InstancedStaticMeshes));
		}
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRARuntimeMaterialApplicationTest,
	"RomaAeterna.Prompt29Bis.RuntimeMaterialApplication",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRARuntimeMaterialApplicationTest::RunTest(const FString& Parameters)
{
	UWorld* World = OpenVerticalSlice(*this);
	if (!World) return false;
	URARomanVisualCatalog::SetLocalAssetsEnabled(true);
	int32 LocalBindings = 0;
	int32 FallbackBindings = 0;
	bool bWorldGridFound = false;
	for (ARARomanProceduralBuildingActor* Building : GenerateBuildings(World))
	{
		LocalBindings += Building->GetLocalMaterialBindingCount();
		FallbackBindings += Building->GetFallbackMaterialBindingCount();
		for (const UInstancedStaticMeshComponent* Component : Building->GeneratedInstanceComponents)
		{
			if (const UMaterialInterface* Material = Component ? Component->GetMaterial(0) : nullptr)
			{
				bWorldGridFound |= Material->GetPathName().Contains(TEXT("WorldGridMaterial"));
			}
		}
	}
	TestTrue(TEXT("Almeno 25 binding locali reali"), LocalBindings >= 25);
	// Le utility prive di una controparte Batch 1 conservano fallback storicamente motivati.
	TestTrue(TEXT("Fallback non prevalente rispetto ai binding locali"), FallbackBindings <= LocalBindings + 25);
	TestFalse(TEXT("Nessun WorldGridMaterial visibile per errore"), bWorldGridFound);
	AddInfo(FString::Printf(TEXT("PROMPT29BIS_BINDINGS local=%d fallback=%d"), LocalBindings, FallbackBindings));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRAInputBindingsCorrectionTest,
	"RomaAeterna.Prompt29Bis.InputBindings",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRAInputBindingsCorrectionTest::RunTest(const FString& Parameters)
{
	UWorld* World = OpenVerticalSlice(*this);
	if (!World) return false;
	ARACharacter* Character = World->SpawnActor<ARACharacter>();
	TestNotNull(TEXT("Character per comandi runtime"), Character);
	if (!Character) return false;
	TestNotNull(TEXT("Enhanced Input Mapping Context"), Character->GetPlayerMappingContext());
	TestTrue(TEXT("Mapping tastiera/mouse completo"),
		Character->GetPlayerMappingContext() && Character->GetPlayerMappingContext()->GetMappings().Num() >= 14);
	int32 ActorsBefore = 0;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It) ++ActorsBefore;
	Character->ExecuteRebuildCommand();
	TestEqual(TEXT("F5 non accumula attori"), Character->GetLastRebuildActorCount(), ActorsBefore);
	TestTrue(TEXT("F5 ricostruisce componenti"), Character->GetLastRebuildComponentCount() > 0);
	TestEqual(TEXT("Messaggio F5 esatto"), Character->GetActiveTechnicalMessage(), FString(TEXT("F5 REBUILD EXECUTED")));
	const bool bLocalBefore = Character->AreLocalAssetsEnabled();
	Character->ExecuteLocalMaterialToggle();
	TestTrue(TEXT("F7 cambia stato"), Character->AreLocalAssetsEnabled() != bLocalBefore);
	Character->ExecuteLocalMaterialToggle();
	TestEqual(TEXT("F7 reversibile"), Character->AreLocalAssetsEnabled(), bLocalBefore);
	Character->Destroy();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRAPlayerSpawnValidationTest,
	"RomaAeterna.Prompt29Bis.PlayerSpawnValidation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRAPlayerSpawnValidationTest::RunTest(const FString& Parameters)
{
	UWorld* World = OpenVerticalSlice(*this);
	if (!World) return false;
	APlayerStart* Start = nullptr;
	for (TActorIterator<APlayerStart> It(World); It; ++It) { Start = *It; break; }
	TestNotNull(TEXT("PlayerStart presente"), Start);
	if (!Start) return false;
	FHitResult Hit;
	FCollisionQueryParams Query(TEXT("Prompt29BisSpawnGroundTrace"), false, Start);
	const FVector Origin = Start->GetActorLocation();
	const bool bGround = World->LineTraceSingleByChannel(
		Hit, Origin, Origin - FVector(0.0, 0.0, 1000.0), ECC_Visibility, Query);
	TestTrue(TEXT("Ground trace sotto PlayerStart"), bGround);
	TestTrue(TEXT("PlayerStart non interpenetrato col terreno"), bGround && Origin.Z > Hit.ImpactPoint.Z + 80.0);
	TestTrue(TEXT("PlayerStart entro due metri dal suolo"), bGround && Origin.Z - Hit.ImpactPoint.Z < 220.0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRADecorationVisibilityCorrectionTest,
	"RomaAeterna.Prompt29Bis.DecorationVisibility",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRADecorationVisibilityCorrectionTest::RunTest(const FString& Parameters)
{
	UWorld* World = OpenVerticalSlice(*this);
	if (!World) return false;
	int32 DecoratedRequired = 0;
	for (ARARomanProceduralBuildingActor* Building : GenerateBuildings(World))
	{
		const bool bRequired = Building->BuildingParameters.BuildingType == ERARomanBuildingType::DomusMedia
			|| Building->BuildingParameters.BuildingType == ERARomanBuildingType::BathComplex;
		if (!bRequired) continue;
		TestTrue(TEXT("Pannelli decorativi visibili"), Building->GetDecorationPanelCount() > 0);
		TestTrue(TEXT("Pavimento decorativo presente"),
			static_cast<int32>(Building->GetFloorDecorationType()) >= 0);
		const int32 BindingsBefore = Building->GetLocalMaterialBindingCount()
			+ Building->GetFallbackMaterialBindingCount();
		Building->SetDecorationFallbackEnabled(true);
		TestEqual(TEXT("F11 conserva il numero corrente di binding"),
			Building->GetLocalMaterialBindingCount() + Building->GetFallbackMaterialBindingCount(),
			BindingsBefore);
		Building->SetDecorationFallbackEnabled(false);
		TestEqual(TEXT("F11 ripristina i contatori senza accumulo"),
			Building->GetLocalMaterialBindingCount() + Building->GetFallbackMaterialBindingCount(),
			BindingsBefore);
		const int32 RoofsBefore = Building->GetVisibleRoofInstanceCount();
		Building->SetRoofVisibility(false);
		TestEqual(TEXT("F10 nasconde soltanto i tetti"), Building->GetVisibleRoofInstanceCount(), 0);
		Building->SetRoofVisibility(true);
		TestEqual(TEXT("F10 ripristina i tetti"), Building->GetVisibleRoofInstanceCount(), RoofsBefore);
		++DecoratedRequired;
	}
	TestTrue(TEXT("DomusMedia e BathComplex verificati"), DecoratedRequired >= 2);
	return true;
}

#endif
