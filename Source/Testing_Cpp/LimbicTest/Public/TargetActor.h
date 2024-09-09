// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoolChanged, bool, NewValue);

UCLASS()
class TESTING_CPP_API ATargetActor : public AActor
{
	GENERATED_BODY()
    
public:    
	ATargetActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:    
	
	UPROPERTY(BlueprintAssignable)
	FOnBoolChanged OnBoolChanged;

	UFUNCTION(BlueprintCallable)
	void SetTargetBool(bool NewValue);

	UFUNCTION(BlueprintCallable)
	bool GetTargetBool() const {return bTargetBool;}

private:
	UFUNCTION()
	void OnRep_BoolValue() const;
	
	UPROPERTY(ReplicatedUsing = OnRep_BoolValue)
	bool bTargetBool;
};
