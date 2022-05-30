// Copyright Epic Games, Inc. All Rights Reserved.

#include "MineSweeperBlockGrid.h"
#include "MineSweeperBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "api/Context.h"
#include "api/LevelContext.h"
#include <utility/Utility.h>

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

AMineSweeperBlockGrid::AMineSweeperBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);
		
	BlockSpacing = 300.f;
}


void AMineSweeperBlockGrid::BeginPlay()
{
	Super::BeginPlay();
	auto uworld = GetWorld();

	Utility::Get().UWorldPtr = uworld;
	Utility::Get().MineSweeperBlockGrid = this;

	Utility::Get().InitializeMineSweeper();
}

#undef LOCTEXT_NAMESPACE
