
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MBTTask_FindRandomPoint.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UMBTTask_FindRandomPoint : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UMBTTask_FindRandomPoint();
	
};
