#pragma once
#include <unordered_map>
#include <memory>
#include <api/Types.h>
#include <GameFramework/Actor.h>

class AMineSweeperBlock;
class AMineSweeperBlockGrid;

class Utility
{
public:
	static Utility& Get()
	{
		static Utility utility;
		return utility;
	}

public:
	UWorld* UWorldPtr = nullptr;
	AMineSweeperBlockGrid* MineSweeperBlockGrid = nullptr;

public:
	void FindNumOfColumnsAndRows(const FString& data, int& numOfRow, int& numOfColumns);
	void InitializeMineSweeper();
	void UpdateMines(const FString& data);

private:
	AMineSweeperBlock* InsertNewMine(const float XOffset, const float YOffset);

private:
	const char NewLineStr = '\n';

	const char ZeroStr = '0';
	const char OneStr = '1';
	const char TwoStr = '2';
	const char ThreeStr = '3';
	const char FourStr = '4';
	const char FiveStr = '5';
	const char SixStr = '6';
	const char SevenStr = '7';
	const char EightStr = '8';
	const char StarStr = '*';
	const FString InitStr = TEXT("map:\n");

};