#pragma once

#include "CoreMinimal.h"

#include <memory>
#include <unordered_map>
#include <string>

#include "api/WebAPI.h"
#include "api/Types.h"
#include "api/LevelContext.h"

class Context
{
public:
	static Context& GetContext()
	{
		static Context context;
		return context;
	}

	void BeginPlay();
	void EndPlay();

	void Play(FString level);
	void OpenCell(int x, int y);
	
	FOnConnectEvent OnConnectionCompletedEvent;	
	FOnLevelProcessingCompletedEvent OnLevelProcessingCompletedEvent;
	FOnOpenCellCompletedEvent OnOpenCellCompletedEvent;
	FOnStopEvent OnStopEvent;
	FOnErrorEvent OnErrorEvent;

	std::unique_ptr<LevelContext>& GetLevelContext();

private:
	void OnConnect();
	void OnDisconnect();
	void OnError(const FString& errorMsg);
	void OnDataRecieved(const FString& msg);

	void ClearEvent();

	
private:
	void GetLevelInfo();

private:
	std::unique_ptr<WebAPI> m_webSocket = nullptr;
	std::unique_ptr<LevelContext> m_levelContext = nullptr;

	bool m_isConnected = false;
	ERequestTypes m_currentState = ERequestTypes::None;

	FDelegateHandle m_onConnectDelegateHandle;
	FDelegateHandle m_onDisconnectDelegateHandle;
	FDelegateHandle m_onErrorDelegateHandle;
	FDelegateHandle m_onDataReceivedDelegateHandle;

	const FString Help = TEXT("help");
	const FString NewLevel = TEXT("new");
	const FString GetMap = TEXT("map");
	const FString Open = TEXT("open");

	std::unordered_map<std::string, int> m_levels;
};
