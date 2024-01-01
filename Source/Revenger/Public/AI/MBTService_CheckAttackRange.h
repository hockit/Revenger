
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UMBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	float AttackRangeDistance;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
