
#include "AI/MBTTask_MeleeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/MAICharacter_Base.h"


EBTNodeResult::Type UMBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyAIController = OwnerComp.GetAIOwner();
	if (ensure(MyAIController))
	{
		AMAICharacter_Base* MyAICharacter = Cast<AMAICharacter_Base>(MyAIController->GetPawn());
		if (MyAICharacter == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		MyAICharacter->Attack();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}