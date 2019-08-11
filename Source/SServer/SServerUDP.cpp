// Fill out your copyright notice in the Description page of Project Settings.


#include "SServerUDP.h"

// Sets default values
ASServerUDP::ASServerUDP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASServerUDP::BeginPlay()
{
	Super::BeginPlay();
	MessageBus = FMessageEndpoint::Builder("ApplicationCommunicator").Handling<FCompanionMessage>(this, &ASServerUDP::MessageHandlingMethod);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("BeginPlay ApplicationCommunicator"));

	if (MessageBus.IsValid())
	{
		MessageBus->Subscribe<FCompanionMessage>();
	}
	
}

void ASServerUDP::CommunicatorSendMessage(FString Message)
{
	if (MessageBus.IsValid())
	{
		MessageBus->Publish<FApplicationMessage>(new FApplicationMessage(Message));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SendMessage"));
	}
}

void ASServerUDP::MessageHandlingMethod(const FCompanionMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)
{
	MessageReceived.Broadcast(*Message.MessageContent);
}

