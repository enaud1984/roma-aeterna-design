#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#include "Camera/CameraComponent.h"
#include "Game/RAGameModeBase.h"
#include "InputMappingContext.h"
#include "Misc/PackageName.h"
#include "Player/RACharacter.h"
#include "Player/RAPlayerController.h"
#include "UI/RATechnicalHUD.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRAGameModeDefaultsTest,
	"RomaAeterna.PlayableFoundation.GameModeDefaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRAGameModeDefaultsTest::RunTest(const FString& Parameters)
{
	const ARAGameModeBase* GameMode = GetDefault<ARAGameModeBase>();
	TestNotNull(TEXT("GameMode class default object exists"), GameMode);
	if (!GameMode)
	{
		return false;
	}

	TestTrue(TEXT("Default pawn is ARACharacter"), GameMode->DefaultPawnClass.Get() == ARACharacter::StaticClass());
	TestTrue(TEXT("PlayerController is ARAPlayerController"), GameMode->PlayerControllerClass.Get() == ARAPlayerController::StaticClass());
	TestTrue(TEXT("HUD is the prototype technical HUD"), GameMode->HUDClass.Get() == ARATechnicalHUD::StaticClass());
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRACharacterConfigurationTest,
	"RomaAeterna.PlayableFoundation.CharacterConfiguration",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRACharacterConfigurationTest::RunTest(const FString& Parameters)
{
	const ARACharacter* Character = GetDefault<ARACharacter>();
	TestNotNull(TEXT("Character class default object exists"), Character);
	if (!Character)
	{
		return false;
	}

	TestTrue(TEXT("Playable foundation references are valid"), Character->HasValidPlayableFoundation());
	TestTrue(TEXT("Walk speed is positive"), Character->GetConfiguredWalkSpeed() > 0.0f);
	TestTrue(TEXT("Sprint speed exceeds walk speed"), Character->GetConfiguredSprintSpeed() > Character->GetConfiguredWalkSpeed());
	TestEqual(TEXT("Default camera mode is third person"), Character->GetViewMode(), ERAViewMode::ThirdPerson);
	TestNotNull(TEXT("First-person camera exists"), Character->GetFirstPersonCamera());
	TestNotNull(TEXT("Third-person camera exists"), Character->GetThirdPersonCamera());
	TestNotNull(TEXT("IMC_Player exists"), Character->GetPlayerMappingContext());
	if (const UInputMappingContext* MappingContext = Character->GetPlayerMappingContext())
	{
		TestEqual(TEXT("IMC_Player contains eight keyboard/mouse mappings"), MappingContext->GetMappings().Num(), 8);
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRACameraToggleTest,
	"RomaAeterna.PlayableFoundation.CameraToggle",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRACameraToggleTest::RunTest(const FString& Parameters)
{
	ARACharacter* Character = GetMutableDefault<ARACharacter>();
	TestNotNull(TEXT("Mutable Character class default object exists"), Character);
	if (!Character)
	{
		return false;
	}

	Character->SetViewMode(ERAViewMode::ThirdPerson);
	Character->ToggleViewMode();
	TestEqual(TEXT("First toggle selects first person"), Character->GetViewMode(), ERAViewMode::FirstPerson);
	TestTrue(TEXT("First-person camera is active"), Character->GetFirstPersonCamera()->IsActive());
	TestFalse(TEXT("Third-person camera is inactive"), Character->GetThirdPersonCamera()->IsActive());

	Character->ToggleViewMode();
	TestEqual(TEXT("Second toggle restores third person"), Character->GetViewMode(), ERAViewMode::ThirdPerson);
	TestTrue(TEXT("Third-person camera is active"), Character->GetThirdPersonCamera()->IsActive());
	TestFalse(TEXT("First-person camera is inactive"), Character->GetFirstPersonCamera()->IsActive());
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRATechnicalSandboxPackageTest,
	"RomaAeterna.PlayableFoundation.TechnicalSandboxPackage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRATechnicalSandboxPackageTest::RunTest(const FString& Parameters)
{
	FString MapFilename;
	const bool bMapExists = FPackageName::DoesPackageExist(TEXT("/Game/RA/Dev/Maps/TechnicalSandbox"), &MapFilename);
	TestTrue(TEXT("TechnicalSandbox map package exists"), bMapExists);
	TestTrue(TEXT("TechnicalSandbox resolves to a .umap file"), MapFilename.EndsWith(TEXT(".umap")));
	return true;
}

#endif
