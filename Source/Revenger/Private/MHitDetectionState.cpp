
#include "MHitDetectionState.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "MCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MAttributeComponent.h"


void UMHitDetectionState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	FVector StartTrace = MeshComp->GetSocketLocation("hand_l");
	FVector EndTrace = StartTrace;
	float Radius = 20.f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MeshComp->GetOwner());
	FHitResult OutHit;

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(MeshComp, StartTrace, EndTrace, Radius, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true);

	if (bHit)
	{
		ACharacter* HitActor = Cast<ACharacter>(OutHit.GetActor());
		if (HitActor)
		{
			UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(HitActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
			if (AttributeComp)
			{
				AttributeComp->ApplyHealthChange(-1.f);
			}
		}
	}
}