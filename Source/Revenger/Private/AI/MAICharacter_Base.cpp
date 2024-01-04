
#include "AI/MAICharacter_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MAttributeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AMAICharacter_Base::AMAICharacter_Base()
{
	AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");
	GetCharacterMovement()->MaxWalkSpeed = 250.f;

	IsAttacking = false;
	AttackCount = 0;
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
	PlayAnimMontage(HitReaction);
}

void AMAICharacter_Base::UpdateWalkSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AMAICharacter_Base::Attack()
{
	if (!IsAttacking)
	{
		IsAttacking = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (ensure(AnimInstance))
		{
			if (AttackCount == CombatArrayMontage.Num())
			{
				AttackCount = 0;
			}
			switch (AttackCount)
			{
			case 0: SocketName = "hand_l"; break;
			case 1: SocketName = "hand_r"; break;
			case 2: SocketName = "hand_l"; break;
			case 3: SocketName = "foot_r"; break;
			}
			AnimInstance->Montage_Play(CombatArrayMontage[AttackCount]);
			AttackCount++;
			IsAttacking = false;
		}
	}
}

void AMAICharacter_Base::HitDetection()
{
	FVector StartTrace = GetMesh()->GetSocketLocation(SocketName);
	FVector EndTrace = StartTrace;
	float Radius = 20.f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetInstigator());
	FHitResult OutHit;

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetMesh(), StartTrace, EndTrace, Radius, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true);

	if (bHit)
	{
		ACharacter* HitActor = Cast<ACharacter>(OutHit.GetActor());
		if (HitActor)
		{
			UMAttributeComponent* AttributeComponent = Cast<UMAttributeComponent>(HitActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
			if (AttributeComponent)
			{
				AttributeComponent->ApplyHealthChange(-10.f);
			}
		}
	}
}