
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MAIController.generated.h"

class UBehaviorTree;

UCLASS()
class REVENGER_API AMAIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;
};
