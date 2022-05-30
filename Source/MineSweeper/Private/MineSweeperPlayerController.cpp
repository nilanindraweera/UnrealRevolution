// Copyright Epic Games, Inc. All Rights Reserved.

#include "MineSweeperPlayerController.h"
#include <Camera/CameraComponent.h>
#include <HeadMountedDisplayFunctionLibrary.h>

AMineSweeperPlayerController::AMineSweeperPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	PrimaryActorTick.bCanEverTick = true;
}

void AMineSweeperPlayerController::SetCameraPosition(const FString& level)
{
	m_level = level;	

	UCameraComponent* OurCamera = this->GetViewTarget()->FindComponentByClass<UCameraComponent>();

	if(m_level.ToLower().Equals(TEXT("level 01")))
	{
		OurCamera->SetWorldLocation(FVector(-586.0f, 396.0f, 3000.0f));
	}
	else if(m_level.ToLower().Equals(TEXT("level 02")))
	{
		OurCamera->SetWorldLocation(FVector(-586.0f, 396.0f, 6800.0f));
	}
	else if(m_level.ToLower().Equals(TEXT("level 03")))
	{
		OurCamera->SetWorldLocation(FVector(-586.0f, 396.0f, 16000.0f));
	}
	else if(m_level.ToLower().Equals(TEXT("level 04")))
	{
		OurCamera->SetWorldLocation(FVector(-586.0f, 396.0f, 25000.0f));
	}
}

void AMineSweeperPlayerController::Tick(float DeltaSeconds)
{
	UCameraComponent* OurCamera = this->GetViewTarget()->FindComponentByClass<UCameraComponent>();

	if(m_level.ToLower().Equals(TEXT("level 01")))
	{
		OurCamera->SetWorldLocation(FVector(-586.0f, 396.0f, 3000.0f));
	}
	else if(m_level.ToLower().Equals(TEXT("level 02")))
	{
		OurCamera->SetWorldLocation(FVector(-586.0f, 396.0f, 6800.0f));
	}
	else if(m_level.ToLower().Equals(TEXT("level 03")))
	{
		OurCamera->SetWorldLocation(FVector(-586.0f, 396.0f, 16000.0f));
	}
	else if(m_level.ToLower().Equals(TEXT("level 04")))
	{
		OurCamera->SetWorldLocation(FVector(-586.0f, 396.0f, 30000.0f));
	}
}
