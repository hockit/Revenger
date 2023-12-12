#include "AI/MBTTask_FindRandomPoint.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

UMBTTask_FindRandomPoint::UMBTTask_FindRandomPoint()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UMBTTask_FindRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (BlackboardComp)
	{
		APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();		
		if (ControlledPawn)
		{
			FVector RandomLocation;
			UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
			if (NavSystem)
			{
				FNavLocation NavLocation;
				if (NavSystem->GetRandomReachablePointInRadius(ControlledPawn->GetActorLocation(), 1000.f, NavLocation))
				{
					RandomLocation = NavLocation.Location;
					BlackboardComp->SetValueAsVector("PatrolLocation", RandomLocation);
					return EBTNodeResult::Succeeded;
				}
			}
							
		}
	}
	return EBTNodeResult::Failed;
}