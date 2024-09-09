#include "Testing_Cpp//LimbicTest/Public/TargetActor.h"

#include "Net/UnrealNetwork.h"


ATargetActor::ATargetActor(): bTargetBool(false)
{
}

void ATargetActor::BeginPlay()
{
	Super::BeginPlay();
}

// Sets the target boolean value and triggers replication
void ATargetActor::SetTargetBool(const bool NewValue)
{
	if (bTargetBool != NewValue)
	{
		bTargetBool = NewValue;
		OnRep_BoolValue();
	}
}

void ATargetActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the replicated property bTargetBool changes
void ATargetActor::OnRep_BoolValue() const
{
	OnBoolChanged.Broadcast(bTargetBool);
}

// Sets up replication for the bTargetBool property
void ATargetActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATargetActor, bTargetBool);
}

