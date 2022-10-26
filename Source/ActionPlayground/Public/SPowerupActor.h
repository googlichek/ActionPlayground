// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"

class USphereComponent;

UCLASS()
class ACTIONPLAYGROUND_API ASPowerupActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:

	ASPowerupActor();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
protected:

	UPROPERTY(EditAnywhere, Category = "Powerup")
	float RespawnTime;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComponent;

	FTimerHandle TimerHandle_RespawnTimer;

	UFUNCTION()
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerupState(bool bNewIsActive);

};
