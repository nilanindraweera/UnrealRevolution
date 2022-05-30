// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MineSweeperPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class AMineSweeperPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMineSweeperPlayerController();		

	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
	void SetCameraPosition(const FString& level);

	virtual void Tick(float DeltaSeconds);


private:
	FString m_level;
};


