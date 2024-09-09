// Fill out your copyright notice in the Description page of Project Settings.


#include "Testing_Cpp/LimbicTest/Public/ListenerActor.h"

#include "Testing_Cpp/LimbicTest/Public/AsyncNode.h"
#include "Testing_Cpp/LimbicTest/Public/TargetActor.h"


AListeningActor::AListeningActor(): AsyncNode(nullptr), TargetActor(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AListeningActor::BeginPlay()
{
	Super::BeginPlay();

	// Check if TargetActor is valid
	if (TargetActor.IsValid())
	{
		// Create the async node and bind to the event
		AsyncNode = UAsyncNode::ListenForBoolChange(this, TargetActor.Get());
		if (AsyncNode)
		{
			AsyncNode->OnBooleanChanged.AddDynamic(this, &AListeningActor::OnBooleanChanged);
			AsyncNode->Activate();
		}
	}
}

// Called when the boolean value changes
void AListeningActor::OnBooleanChanged(const bool NewValue)
{
	if (NewValue)
	{
		Destroy();

		if (AsyncNode)
		{
			AsyncNode = nullptr;
		}
	}
}

AListeningActor::~AListeningActor()
{
	if (AsyncNode)
	{
		AsyncNode->ConditionalBeginDestroy();
		AsyncNode = nullptr;
	}
}