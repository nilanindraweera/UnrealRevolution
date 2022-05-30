// Copyright Epic Games, Inc. All Rights Reserved.

#include "MineSweeperGameMode.h"
#include "MineSweeperPlayerController.h"
#include "MineSweeperPawn.h"
#include <api/Context.h>

AMineSweeperGameMode::AMineSweeperGameMode()
{
	DefaultPawnClass = AMineSweeperPawn::StaticClass();
	PlayerControllerClass = AMineSweeperPlayerController::StaticClass();
}

void AMineSweeperGameMode::BeginPlay()
{
	AGameModeBase::BeginPlay();
}

void AMineSweeperGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Context::GetContext().EndPlay();

	AGameModeBase::EndPlay(EndPlayReason);
}