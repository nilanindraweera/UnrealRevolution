// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WebSocketsModule.h" 
#include "IWebSocket.h"  

DECLARE_EVENT(WebAPI, FOnWebSocketConnectEvent);
DECLARE_EVENT(WebAPI, FOnWebSocketDisconnectEvent);
DECLARE_EVENT_OneParam(WebAPI, FOnWebSocketDataRecievedEvent, const FString&);
DECLARE_EVENT_OneParam(WebAPI, FOnWebSocketErrorEvent, const FString&);

class WebAPI
{
public:
	WebAPI();
	~WebAPI();

public:
	void Connect();
	void Disconnect();
	void Send(FString data);

	FOnWebSocketConnectEvent OnConnectEvent;
	FOnWebSocketDataRecievedEvent OnDataRecievedEvent;
	FOnWebSocketErrorEvent OnErrorEvent;
	FOnWebSocketDisconnectEvent OnDisconnectEvent;

private:
	void OnConnect();
	void OnConnectionError(const FString& error);
	void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
	void OnMessage(const FString& Message);
	void OnRawMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining);
	void OnMessageSent(const FString& MessageString);

	void ClearEvents();
private:
	const FString ServerURL = TEXT("wss://hometask.eg1236.com/game1/");
	const FString ServerProtocol = TEXT("ws");

	TSharedPtr<IWebSocket> m_socket;

	bool m_isConnected = false;

	FDelegateHandle m_onConnectDelegateHandle;
	FDelegateHandle m_onConnectionErrorDelegateHandle;
	FDelegateHandle m_onClosedDelegateHandle;
	FDelegateHandle m_onMessageDelegateHandle;
	FDelegateHandle m_onRawMessageDelegateHandle;
	FDelegateHandle m_onMessageSentDelegateHandle;
};
