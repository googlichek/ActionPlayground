// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = StaticMeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("Radial Force");
	RadialForceComponent->SetupAttachment(StaticMeshComponent);

	RadialForceComponent->SetAutoActivate(false);
	RadialForceComponent->Radius = 750;
	RadialForceComponent->ImpulseStrength = 2500;
	RadialForceComponent->bImpulseVelChange = true;
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	// Don't forget to call parent function
	Super::PostInitializeComponents();

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnComponentHit);
}

void ASExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnComponentHit reached (ExplosiveBarrel)"));
}

