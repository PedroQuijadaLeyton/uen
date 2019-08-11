// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <MessageEndpoint.h>
#include <MessageEndpointBuilder.h>
#include "Engine/GameEngine.h"
#include "SServerUDP.generated.h"

UCLASS()
class SSERVER_API ASServerUDP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASServerUDP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe>MessageBus;
	void MessageHandlingMethod(const struct FCompanionMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);

public:
	UFUNCTION(BlueprintCallable, Category = "Communicator - Send Message")
	void CommunicatorSendMessage(FString Message);

	/**
	Declare a broadcast-style delegate type, which is used for the load completed event.
	Dynamic multicast delegates are the only type of event delegates that Blueprint scripts can bind to.
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageReceived, FString, Message);

	/** This accessor function allows C++ code to bind to the event. */
	FMessageReceived& OnMessageReceived()
	{
		return MessageReceived;
	}

private:
	/**
	Holds the load completed event delegate.
	Giving Blueprint access to this private variable allows Blueprint scripts to bind to the event.
	*/
	UPROPERTY(BlueprintAssignable, Category = ImageLoader, meta = (AllowPrivateAccess = true))
	FMessageReceived MessageReceived;

};

USTRUCT()
struct FApplicationMessage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Message")
	FString MessageContent;

	// default constructor for the receiver
	FApplicationMessage() = default;
	// helper constructor for the sender
	FApplicationMessage(const FString& TheMessage)
		: MessageContent(TheMessage) {}
};

USTRUCT()
struct FCompanionMessage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Message")
	FString MessageContent;

	// default constructor for the receiver
	FCompanionMessage() = default;
	// helper constructor for the sender
	FCompanionMessage(const FString& TheMessage)
		: MessageContent(TheMessage) {}
};
