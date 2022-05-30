#include "LobbyGameMode.h"

#include "MineSweeperPlayerController.h"
#include "MineSweeperPawn.h"
#include <api/Context.h>


ALobbyGameMode::ALobbyGameMode()
{
	DefaultPawnClass = AMineSweeperPawn::StaticClass();
	PlayerControllerClass = AMineSweeperPlayerController::StaticClass();
}

void ALobbyGameMode::BeginPlay()
{
	AGameModeBase::BeginPlay();
}

void ALobbyGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AGameModeBase::EndPlay(EndPlayReason);
}
