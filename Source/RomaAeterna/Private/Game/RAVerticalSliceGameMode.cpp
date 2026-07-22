#include "Game/RAVerticalSliceGameMode.h"

#include "Player/RACharacter.h"
#include "Player/RAPlayerController.h"
#include "UI/RATechnicalHUD.h"

ARAVerticalSliceGameMode::ARAVerticalSliceGameMode()
{
	DefaultPawnClass = ARACharacter::StaticClass();
	PlayerControllerClass = ARAPlayerController::StaticClass();
	HUDClass = ARATechnicalHUD::StaticClass();
}
