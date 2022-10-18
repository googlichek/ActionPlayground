// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float Distance = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithinRange = Distance < 2000.0f;
					bool bHasLineOfSight = false;

					if (bWithinRange)
					{
						bHasLineOfSight = MyController->LineOfSightTo(TargetActor);
					}

					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLineOfSight);
				}
			}
		}
	}
}
