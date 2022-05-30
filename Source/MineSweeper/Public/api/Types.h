#pragma once
#include "CoreMinimal.h"
#include <memory>
#include <unordered_map>

#include "Types.generated.h"

class AMineSweeperBlock;

DECLARE_EVENT_OneParam(Context, FOnConnectEvent, bool);
DECLARE_EVENT_OneParam(Context, FOnStopEvent, bool);
DECLARE_EVENT_OneParam(Context, FOnErrorEvent, FString);
DECLARE_EVENT_OneParam(Context, FOnOpenCellCompletedEvent, FString);
DECLARE_EVENT(Context, FOnLevelProcessingCompletedEvent);

UENUM(BlueprintType)
enum class ERequestTypes : uint8
{
	None,
	Connecting,
	Connected,
	Disconnecting,
	NewLevelStarting,
	NewLevelStarted,
	RequestingLevelInfo,
	RecievedLevelInfo,
	OpeningCell,
	OpenedCell,
	Error
};

UENUM(BlueprintType)
enum class EBlockStates : uint8
{
	None,
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Explode,
	Flag
};

struct FCellPosition
{
	int32 X;
	int32 Y;
};

typedef std::unordered_map<unsigned int, AMineSweeperBlock*> IndexToMineMapType;
typedef std::unordered_map<unsigned int, std::shared_ptr<FCellPosition>> IndexToCellPosMapType;