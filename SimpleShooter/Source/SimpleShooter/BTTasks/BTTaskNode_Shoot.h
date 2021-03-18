// Copyright Cameron Davis 2021. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Shoot.generated.h"

UCLASS()
class SIMPLESHOOTER_API UBTTaskNode_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_Shoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};