#include "Game/RAGameModeBase.h"

#include "Player/RACharacter.h"
#include "Player/RAPlayerController.h"
#include "UI/RATechnicalHUD.h"

ARAGameModeBase::ARAGameModeBase()
{
	DefaultPawnClass = ARACharacter::StaticClass();
	PlayerControllerClass = ARAPlayerController::StaticClass();
	HUDClass = ARATechnicalHUD::StaticClass();
}
