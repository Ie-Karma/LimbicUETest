// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBooleanChanged, bool, NewValue);

class ATargetActor;

UCLASS()
class TESTING_CPP_API UAsyncNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnBooleanChanged OnBooleanChanged;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Async Node")
	static UAsyncNode* ListenForBoolChange(UObject* WorldContextObject, ATargetActor* InTargetActor);

	virtual void Activate() override;

private:

	UPROPERTY()
	TWeakObjectPtr<ATargetActor> TargetActor;
	
	UFUNCTION()
	void OnBoolChanged(bool NewValue);
};