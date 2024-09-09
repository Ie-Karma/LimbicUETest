// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ListenerActor.generated.h"

class ATargetActor;
class UAsyncNode;

UCLASS()
class TESTING_CPP_API AListeningActor : public AActor
{
	GENERATED_BODY()
    
public:    
	AListeningActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UAsyncNode> AsyncNode;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<ATargetActor> TargetActor;

	UFUNCTION()
	void OnBooleanChanged(bool NewValue);
	virtual ~AListeningActor() override;
};