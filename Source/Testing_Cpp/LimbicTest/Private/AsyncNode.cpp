// Fill out your copyright notice in the Description page of Project Settings.

#include "Testing_Cpp/LimbicTest/Public/AsyncNode.h"

#include "Testing_Cpp/LimbicTest/Public/TargetActor.h"

// Static function to create a new UAsyncNode and set the target actor
UAsyncNode* UAsyncNode::ListenForBoolChange(UObject* WorldContextObject, ATargetActor* InTargetActor)
{
	if (!InTargetActor)
	{
		return nullptr;
	}

	// Create a new UAsyncNode and set the target actor
	UAsyncNode* Node = NewObject<UAsyncNode>(WorldContextObject);
	Node->TargetActor = InTargetActor;
	return Node;
}

// Activates the async node and binds to the target actor's OnBoolChanged event
void UAsyncNode::Activate()
{
	if (TargetActor.IsValid())
	{
		// Bind to the target actor's OnBoolChanged event
		TargetActor->OnBoolChanged.AddDynamic(this, &UAsyncNode::OnBoolChanged);
	}
}

// Called when the target actor's boolean value changes
void UAsyncNode::OnBoolChanged(const bool NewValue)
{
	OnBooleanChanged.Broadcast(NewValue);
}