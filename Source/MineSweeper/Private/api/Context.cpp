#include "api/Context.h"
#include <Kismet/GameplayStatics.h>

void Context::BeginPlay()
{
	if (m_currentState != ERequestTypes::None || m_webSocket)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Connecting..."));

	m_levels.insert({ {"Level 01", 1}, {"Level 02", 2}, {"Level 03", 3}, {"Level 04", 4} });
	m_webSocket = std::make_unique<WebAPI>();
	m_levelContext = std::make_unique<LevelContext>();

	m_onConnectDelegateHandle = m_webSocket->OnConnectEvent.AddLambda([this](){OnConnect();});
	m_onDisconnectDelegateHandle = m_webSocket->OnDisconnectEvent.AddLambda([this](){OnDisconnect();});
	m_onDisconnectDelegateHandle = m_webSocket->OnErrorEvent.AddLambda([this](FString errorMsg){OnError(errorMsg);});
	m_onDisconnectDelegateHandle = m_webSocket->OnDataRecievedEvent.AddLambda([this](FString msg){ OnDataRecieved(msg);	});

	m_currentState = ERequestTypes::Connecting;
	m_webSocket->Connect();	
}

void Context::EndPlay()
{
	if(!m_webSocket || m_currentState < ERequestTypes::Connected)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Disconnecting..."));
	m_currentState = ERequestTypes::Disconnecting;
	m_webSocket->Disconnect();
}

void Context::Play(FString level)
{
	if (!m_isConnected || m_currentState != ERequestTypes::Connected)
	{
		return;
	}
	
 	auto levelPtr = m_levels.find(std::string(TCHAR_TO_UTF8(*level)));
 	if (levelPtr == m_levels.end())
 	{
 		return;
 	}

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Creating New Level..."));
	m_currentState = ERequestTypes::NewLevelStarting;
	FString newLevelData = NewLevel + TEXT(" ") + FString::FromInt(levelPtr->second);
	m_webSocket->Send(newLevelData);	
}

void Context::OpenCell(int x, int y)
{
	if(!m_isConnected || m_currentState != ERequestTypes::RecievedLevelInfo)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Opening Cell..."));

	m_currentState = ERequestTypes::OpeningCell;
	FString data = Open + TEXT(" ") + FString::FromInt(x) + TEXT(" ") + FString::FromInt(y);
	m_webSocket->Send(data);
}

std::unique_ptr<LevelContext>& Context::GetLevelContext()
{
	return m_levelContext;
}

void Context::OnConnect()
{
	if(m_currentState != ERequestTypes::Connecting  || m_isConnected)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Connected"));
	m_isConnected = true;
	m_currentState = ERequestTypes::Connected;
	OnConnectionCompletedEvent.Broadcast(true);
}

void Context::OnDisconnect()
{
	if(m_currentState != ERequestTypes::Disconnecting || !m_isConnected)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Disconnected"));
	m_isConnected = false;
	m_currentState = ERequestTypes::None;
	m_webSocket->OnConnectEvent.Remove(m_onConnectDelegateHandle);
	m_webSocket->OnDisconnectEvent.Remove(m_onDisconnectDelegateHandle);
	m_webSocket->OnErrorEvent.Remove(m_onErrorDelegateHandle);
	m_webSocket->OnDataRecievedEvent.Remove(m_onDataReceivedDelegateHandle);
	m_webSocket.reset(nullptr);
	m_levelContext.reset(nullptr);

	OnStopEvent.Broadcast(true);

	ClearEvent();
}

void Context::OnError(const FString& errorMsg)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("Error: ") + errorMsg);
	OnErrorEvent.Broadcast(errorMsg);
}

void Context::OnDataRecieved(const FString& msg)
{	
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, msg);
	if (m_currentState == ERequestTypes::NewLevelStarting)
	{
		if(msg.Contains(TEXT("OK")))
		{
			m_currentState = ERequestTypes::NewLevelStarted;
			GetLevelInfo();
		}
	}	
	else if (m_currentState == ERequestTypes::RequestingLevelInfo)
	{
		m_currentState = ERequestTypes::RecievedLevelInfo;
		if (!m_levelContext->HasInitialized())
		{
			m_levelContext->InitializeLevel(msg);
		}
		else
		{
			m_levelContext->UpdateLevel(msg);
		}
		OnLevelProcessingCompletedEvent.Broadcast();
	}
	else if(m_currentState == ERequestTypes::OpeningCell)
	{
		m_currentState = ERequestTypes::OpenedCell;
		OnOpenCellCompletedEvent.Broadcast(msg);

		GetLevelInfo();
	}
}

void Context::ClearEvent()
{
	OnConnectionCompletedEvent.Clear();
	OnLevelProcessingCompletedEvent.Clear();
	OnOpenCellCompletedEvent.Clear();
	OnStopEvent.Clear();
	OnErrorEvent.Clear();
}

void Context::GetLevelInfo()
{
	if(m_currentState < ERequestTypes::NewLevelStarted)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Getting Level Info..."));		
	m_webSocket->Send(TEXT("map"));
	m_currentState = ERequestTypes::RequestingLevelInfo;
}