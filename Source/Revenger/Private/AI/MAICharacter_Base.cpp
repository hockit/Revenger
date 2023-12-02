
#include "AI/MAICharacter_Base.h"
#include "MAttributeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"


AMAICharacter_Base::AMAICharacter_Base()
{
	AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");

}

void AMAICharacter_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChange.AddDynamic(this, &AMAICharacter_Base::OnHealthChange);
}

void AMAICharacter_Base::OnHealthChange(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		if (NewHealth <= 0.f)
		{
			AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController)
			{
				AIController->GetBrainComponent()->StopLogic("Killed");
			}
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			SetLifeSpan(10.f);
		}
	}
}