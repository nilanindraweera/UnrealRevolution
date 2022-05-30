
#include "blueprint/GameContextBPLibrary.h"
#include "api/Context.h"
#include <unordered_map>

struct  GameContextBPLibraryImpl
{
	static GameContextBPLibraryImpl& GetGameContextBPLibraryImpl()
	{
		static GameContextBPLibraryImpl impl;
		return impl;
	}
	int32 Handle = 0;
	std::unordered_map<int32, FDelegateHandle> HandleMap;
	FString LevelDifficulty;
};

void UGameContextBPLibrary::BeginPlay()
{
	Context::GetContext().BeginPlay();
}

void UGameContextBPLibrary::EndPlay()
{
	Context::GetContext().EndPlay();
}

void UGameContextBPLibrary::Play(FString level)
{
	GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().LevelDifficulty = level;
	Context::GetContext().Play(level);
}

void UGameContextBPLibrary::OpenCell(int x, int y)
{
	Context::GetContext().OpenCell(x, y);
}

FString UGameContextBPLibrary::GetLevelDifficulty()
{
	return GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().LevelDifficulty;
}

int32 UGameContextBPLibrary::AddOnLevelProcessingCompletedEventDelegate(const FOnLevelProcessingCompletedEventDelegate& Callback)
{
	auto delegateHandle = Context::GetContext().OnLevelProcessingCompletedEvent.AddLambda(
	[Callback]()
	{		
		Callback.ExecuteIfBound();		
	});

	int32 handle = GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().Handle++;
	GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.insert({ handle , delegateHandle});
	return handle;
}

void UGameContextBPLibrary::RemoveOnLevelProcessingCompletedEventDelegate(const int32 handle)
{
	auto foundItr = GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.find(handle);
	if (foundItr == GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.end())
	{
		return;
	}
	Context::GetContext().OnLevelProcessingCompletedEvent.Remove(foundItr->second);
	GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.erase(foundItr);
}

int32 UGameContextBPLibrary::AddOnStopEventDelegate(const FOnStopCompletedEventDelegate& Callback)
{
	auto delegateHandle = Context::GetContext().OnStopEvent.AddLambda(
		[Callback](bool val)
	{
		Callback.ExecuteIfBound();
	});

	int32 handle = GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().Handle++;
	GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.insert({ handle , delegateHandle });
	return handle;
}

void UGameContextBPLibrary::RemoveOnStopEventDelegate(const int32 handle)
{
	auto foundItr = GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.find(handle);
	if(foundItr == GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.end())
	{
		return;
	}
	Context::GetContext().OnStopEvent.Remove(foundItr->second);
	GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.erase(foundItr);
}

int32 UGameContextBPLibrary::AddOnConnectionCompletedEventDelegate(const FOnConnectionCompletedEventDelegate& Callback)
{
	auto delegateHandle = Context::GetContext().OnConnectionCompletedEvent.AddLambda(
		[Callback](bool val)
	{
		Callback.ExecuteIfBound();
	});

	int32 handle = GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().Handle++;
	GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.insert({ handle , delegateHandle });
	return handle;
}

void UGameContextBPLibrary::RemoveOnConnectionCompletedEventDelegate(const int32 handle)
{
	auto foundItr = GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.find(handle);
	if(foundItr == GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.end())
	{
		return;
	}
	Context::GetContext().OnConnectionCompletedEvent.Remove(foundItr->second);
	GameContextBPLibraryImpl::GetGameContextBPLibraryImpl().HandleMap.erase(foundItr);
}
