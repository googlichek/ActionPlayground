// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SActionComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASMagicProjectile::ASMagicProjectile()
{
	SphereComponent->SetSphereRadius(20.0f);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

	DamageAmount = 20.0f;
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USActionComponent* ActionComponent = Cast<USActionComponent>(OtherActor->GetComponentByClass(USActionComponent::StaticClass()));

		if (ActionComponent && ActionComponent->ActiveGameplayTags.HasTag(ParryTag))
		{
			MovementComponent->Velocity = -MovementComponent->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}

		//if (AttributeComponent)
		//{
		//	// minus in front of DamageAmount to apply the change as damage, not healing
		//	AttributeComponent->ApplyHealthChange(GetInstigator(), -DamageAmount);

		//	// Only explode when we hit something valid
		//	Explode();
		//}

		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			Explode();
		}
	}
}
