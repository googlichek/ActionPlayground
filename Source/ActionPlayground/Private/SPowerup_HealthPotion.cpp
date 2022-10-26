// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealthPotion.h"
#include "SAttributeComponent.h"

ASPowerup_HealthPotion::ASPowerup_HealthPotion()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	// Disable collision, instead we use SphereComp to handle interaction queries
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);
}


void ASPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	// Check if not already at max health
	if (ensure(AttributeComponent) && !AttributeComponent->IsFullHealth())
	{
		// Only activate if healed successfully
		if (AttributeComponent->ApplyHealthChange(AttributeComponent->GetHealthMax()))
		{
			HideAndCooldownPowerup();
		}
	}
}