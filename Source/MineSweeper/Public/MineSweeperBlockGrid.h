// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <unordered_map>
#include <api/Types.h>

#include "MineSweeperBlockGrid.generated.h"

class AMineSweeperBlock;

UCLASS(minimalapi)
class AMineSweeperBlockGrid : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

public:
	AMineSweeperBlockGrid();

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

protected:
	virtual void BeginPlay() override;

public:	
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }	
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }

public:
	IndexToMineMapType IndexToMineMap;
	IndexToCellPosMapType IndexToCellPosMap;
};



