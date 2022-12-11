// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopping: %s"), *GetNameSafe(this));
}

UWorld* USAction::GetWorld() const
{
	// Outer is set when crearing action via NewObject<T>
	UActorComponent* Component = Cast<UActorComponent>(GetOuter());
	if (Component)
	{
		return Component->GetWorld();
	}

	return nullptr;
}
