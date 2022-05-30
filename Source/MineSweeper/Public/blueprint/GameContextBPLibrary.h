// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameContextBPLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnConnectionCompletedEventDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnLevelProcessingCompletedEventDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnStopCompletedEventDelegate);

UCLASS()
class UGameContextBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static void EndPlay();

	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static void Play(FString level);

	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static void OpenCell(int x, int y);

	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static FString GetLevelDifficulty();

	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static int32 AddOnLevelProcessingCompletedEventDelegate(const FOnLevelProcessingCompletedEventDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static void RemoveOnLevelProcessingCompletedEventDelegate(const int32 handle);


	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static int32 AddOnStopEventDelegate(const FOnStopCompletedEventDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static void RemoveOnStopEventDelegate(const int32 handle);


	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static int32 AddOnConnectionCompletedEventDelegate(const FOnConnectionCompletedEventDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = "MineSweeper")
		static void RemoveOnConnectionCompletedEventDelegate(const int32 handle);
	
};
