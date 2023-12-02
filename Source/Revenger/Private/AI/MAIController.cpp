
#include "AI/MAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AMAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BehaviorTree);
	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
}