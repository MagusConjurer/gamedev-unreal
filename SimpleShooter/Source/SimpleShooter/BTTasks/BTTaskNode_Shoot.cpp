// Copyright Cameron Davis 2021. All Rights Reserved.


#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SimpleShooter/ShooterCharacter.h"


UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character)
	{
		return EBTNodeResult::Failed;
	}

	Character->Shoot();

	return EBTNodeResult::Succeeded;
}
