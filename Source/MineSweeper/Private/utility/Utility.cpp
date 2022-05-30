#include "utility/Utility.h"
#include <api/Context.h>
#include <MineSweeperBlock.h>
#include <MineSweeperBlockGrid.h>

void Utility::FindNumOfColumnsAndRows(const FString& data, int& numOfRow, int& numOfColumns)
{
	auto startingIndex = 0;
	auto row = 0;
	auto col = 0;

	auto find = data.Find(InitStr);
	if(find >= 0)
	{
		startingIndex = find + InitStr.Len();
	}

	auto msgArray = data.GetCharArray();

	for(auto index = startingIndex; index < data.Len(); index++)
	{
		auto currChar = msgArray[index];
		if(currChar != NewLineStr)
		{
			continue;
		}

		auto width = index - startingIndex;
		if(width == 0)
		{
			startingIndex = index + 1;
			continue;
		}

		row++;
		startingIndex = index + 1;

		numOfRow = row;
		numOfColumns = width;
	}
}

void Utility::InitializeMineSweeper()
{	
	int32 RowCount = 0;
	int32 ColumnCount = 0;

	if(Context::GetContext().GetLevelContext())
	{
		RowCount = Context::GetContext().GetLevelContext()->GetHeight();
		ColumnCount = Context::GetContext().GetLevelContext()->GetWidth();
	}

	float HalfBlockSpacing = MineSweeperBlockGrid->BlockSpacing / 2;
	float HalfColumnCount = ColumnCount / 2;
	float HalfRowCount = RowCount / 2;

	for(int32 row = 0; row < HalfRowCount; row++)
	{
		const float XOffset = ((row % RowCount) * MineSweeperBlockGrid->BlockSpacing) + HalfBlockSpacing;

		for(int32 col = 0; col < HalfColumnCount; col++)
		{
 			const float YOffset = ((col % ColumnCount) * MineSweeperBlockGrid->BlockSpacing) + HalfBlockSpacing;
 
 			auto cellPos1 = std::make_shared<FCellPosition>();
 			cellPos1->X = HalfColumnCount + col;
 			cellPos1->Y = HalfRowCount - row - 1;           
 			auto mine1 = InsertNewMine(XOffset, YOffset);
 			mine1->CellPosition = cellPos1;
            auto index1 = (cellPos1->Y * ColumnCount) + cellPos1->X + 1;
 			MineSweeperBlockGrid->IndexToMineMap.insert({ index1, mine1 });
			MineSweeperBlockGrid->IndexToCellPosMap.insert({ index1, cellPos1 });

 			auto cellPos2 = std::make_shared<FCellPosition>();
 			cellPos2->X = HalfColumnCount + col;
 			cellPos2->Y = HalfRowCount + row;
 			auto mine2 = InsertNewMine(-XOffset, YOffset);
 			mine2->CellPosition = cellPos2;
            auto index2 = (cellPos2->Y * ColumnCount) + cellPos2->X + 1;
			MineSweeperBlockGrid->IndexToMineMap.insert({ index2, mine2 });
			MineSweeperBlockGrid->IndexToCellPosMap.insert({ index2, cellPos2 });
 
 			auto cellPos3 = std::make_shared<FCellPosition>();
 			cellPos3->X = HalfColumnCount - col - 1;
 			cellPos3->Y = HalfRowCount - row - 1;
 			auto mine3 = InsertNewMine(XOffset, -YOffset);
 			mine3->CellPosition = cellPos3;
            auto index3 = (cellPos3->Y * ColumnCount) + cellPos3->X + 1;
			MineSweeperBlockGrid->IndexToMineMap.insert({ index3, mine3 });
			MineSweeperBlockGrid->IndexToCellPosMap.insert({ index3, cellPos3 });
 
 			auto cellPos4 = std::make_shared<FCellPosition>();
 			cellPos4->X = HalfColumnCount - col;
 			cellPos4->Y = HalfRowCount + row;
 			auto mine4 = InsertNewMine(-XOffset, -YOffset);
 			mine4->CellPosition = cellPos4;
            auto index4 = (cellPos4->Y * ColumnCount) + cellPos4->X;
			MineSweeperBlockGrid->IndexToMineMap.insert({ index4, mine4 });
			MineSweeperBlockGrid->IndexToCellPosMap.insert({ index4, cellPos4 });
		}
	}
}

void Utility::UpdateMines(const FString& data)
{
 	int32 RowCount = 0;
 	int32 ColumnCount = 0;
 
 	if(Context::GetContext().GetLevelContext())
 	{
 		RowCount = Context::GetContext().GetLevelContext()->GetHeight();
 		ColumnCount = Context::GetContext().GetLevelContext()->GetWidth();
 	}
 
 	auto startingIndex = 0;
 	auto row = 0;
 	auto col = 0;
 
 	auto find = data.Find(InitStr);
 	if(find >= 0)
 	{
 		startingIndex = find + InitStr.Len();
 	}
 
 	auto msgArray = data.GetCharArray();

 	std::shared_ptr<FCellPosition> cellPosition = nullptr;
    AMineSweeperBlock* mineSweeperBlock = nullptr;

    unsigned int minesIndex = 1;
 	for(auto indexOfString = startingIndex; indexOfString < data.Len(); )
 	{
 		auto currChar = msgArray[indexOfString];
 		if(currChar == NewLineStr)
 		{
 			indexOfString++;
 			continue;
 		}
        
 		for (auto i = 0; i < ColumnCount; i++, minesIndex++)
 		{
 			auto charVal = msgArray[indexOfString  + i];
 
            mineSweeperBlock = MineSweeperBlockGrid->IndexToMineMap[minesIndex];
            cellPosition = MineSweeperBlockGrid->IndexToCellPosMap[minesIndex];

 			FString debugText;
			if(charVal == ZeroStr)
			{
				debugText = FString::Printf(TEXT("0 (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
				mineSweeperBlock->UpdateBlock(EBlockStates::Zero);
			}
 			else if (charVal == OneStr)
 			{				
 				debugText = FString::Printf(TEXT("1 (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
                mineSweeperBlock->UpdateBlock(EBlockStates::One);
 			}
 			else if (charVal == TwoStr)
 			{
                mineSweeperBlock->UpdateBlock(EBlockStates::Two);
 				debugText = FString::Printf(TEXT("2 (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
 			}
 			else if(charVal == ThreeStr)
 			{
                mineSweeperBlock->UpdateBlock(EBlockStates::Three);
 				debugText = FString::Printf(TEXT("3 (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
 			}
 			else if(charVal == FourStr)
 			{
                mineSweeperBlock->UpdateBlock(EBlockStates::Four);
 				debugText = FString::Printf(TEXT("4 (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
 			}
			else if(charVal == FiveStr)
			{
				mineSweeperBlock->UpdateBlock(EBlockStates::Five);
				debugText = FString::Printf(TEXT("5 (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
			}
			else if(charVal == SixStr)
			{
				mineSweeperBlock->UpdateBlock(EBlockStates::Six);
				debugText = FString::Printf(TEXT("6 (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
			}
			else if(charVal == SevenStr)
			{
				mineSweeperBlock->UpdateBlock(EBlockStates::Seven);
				debugText = FString::Printf(TEXT("7 (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
			}
			else if(charVal == EightStr)
			{
				mineSweeperBlock->UpdateBlock(EBlockStates::Eight);
				debugText = FString::Printf(TEXT("8 (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
			}			
 			else if(charVal == StarStr)
 			{
                mineSweeperBlock->UpdateBlock(EBlockStates::Explode);
 				debugText = FString::Printf(TEXT("* (%s, %s)"), *FString::FromInt(cellPosition->X), *FString::FromInt(cellPosition->Y));
 			}
 			else
 			{
 				continue;
 			}
 			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, debugText);
 		}
 		indexOfString += ColumnCount;
 		row++;
 	}
}

AMineSweeperBlock* Utility::InsertNewMine(const float XOffset, const float YOffset)
{
	const FVector NewBlockLocation = FVector(XOffset, YOffset, 0.f) + MineSweeperBlockGrid->GetActorLocation();
	AMineSweeperBlock* NewBlock = UWorldPtr->SpawnActor<AMineSweeperBlock>(NewBlockLocation, FRotator(0, 0, 0));

	if(NewBlock != nullptr)
	{
		NewBlock->OwningGrid = MineSweeperBlockGrid;
	}

	return NewBlock;
}
