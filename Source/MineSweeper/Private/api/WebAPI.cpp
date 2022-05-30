#include "api/WebAPI.h"

WebAPI::WebAPI()
{
	if(!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}
}

WebAPI::~WebAPI()
{
}

void WebAPI::Connect()
{
	if(m_isConnected)
	{
		return;
	}

	m_socket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);

	m_socket->OnConnected().AddLambda([&]() -> void
	{
		OnConnect();
	});

	m_socket->OnConnectionError().AddLambda([&](const FString& Error) -> void
	{
		OnConnectionError(Error);
	});

	m_socket->OnClosed().AddLambda([&](int32 StatusCode, const FString& Reason, bool bWasClean) -> void
	{
		OnClosed(StatusCode, Reason, bWasClean);
	});

	m_socket->OnMessage().AddLambda([&](const FString& Message) -> void
	{
		OnMessage(Message);
	});

	m_socket->OnRawMessage().AddLambda([&](const void* Data, SIZE_T Size, SIZE_T BytesRemaining) -> void
	{
		OnRawMessage(Data, Size, BytesRemaining);
	});

	m_socket->OnMessageSent().AddLambda([&](const FString& MessageString) -> void
	{
		OnMessageSent(MessageString);
	});

	m_socket->Connect();
	m_isConnected = true;
}

void WebAPI::Disconnect()
{
	if(!m_isConnected)
	{
		return;
	}

	if(!m_socket->IsConnected())
	{
		return;
	}
	m_socket->Close();
	m_isConnected = false;
}

void WebAPI::Send(FString data)
{
	if(!m_socket->IsConnected())
	{
		return;
	}

	m_socket->Send(data);
}

void WebAPI::OnConnect()
{
	OnConnectEvent.Broadcast();
}

void WebAPI::OnConnectionError(const FString& error)
{
	OnErrorEvent.Broadcast(error);
}

void WebAPI::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{	
	OnDisconnectEvent.Broadcast();
}

void WebAPI::OnMessage(const FString& Message)
{
	OnDataRecievedEvent.Broadcast(Message);
}

void WebAPI::OnRawMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining)
{
}

void WebAPI::OnMessageSent(const FString& MessageString)
{
}

void WebAPI::ClearEvents()
{
	if (m_socket)
	{
		m_socket->OnConnected().Remove(m_onConnectDelegateHandle);
		m_socket->OnConnectionError().Remove(m_onConnectionErrorDelegateHandle);
		m_socket->OnClosed().Remove(m_onClosedDelegateHandle);
		m_socket->OnMessage().Remove(m_onMessageDelegateHandle);
		m_socket->OnRawMessage().Remove(m_onRawMessageDelegateHandle);
		m_socket->OnMessageSent().Remove(m_onMessageSentDelegateHandle);
	}

	OnConnectEvent.Clear();
	OnDataRecievedEvent.Clear();
	OnErrorEvent.Clear();
	OnDisconnectEvent.Clear();
}
