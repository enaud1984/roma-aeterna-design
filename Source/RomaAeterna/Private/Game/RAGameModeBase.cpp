#include "Game/RAGameModeBase.h"

#include "Player/RACharacter.h"
#include "Player/RAPlayerController.h"

ARAGameModeBase::ARAGameModeBase()
{
	DefaultPawnClass = ARACharacter::StaticClass();
	PlayerControllerClass = ARAPlayerController::StaticClass();
}
