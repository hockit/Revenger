
#include "MInteractionComponent.h"
#include "MGameplayInterface.h"
#include "DrawDebugHelpers.h"


UMInteractionComponent::UMInteractionComponent()
{

}

void UMInteractionComponent::PrimaryInteract()
{
	TArray<FHitResult> Hits;

	AActor* MyActor = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyActor->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 300);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	float Radius = 20.f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool bBlockHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockHit ? FColor::Blue : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements< UMGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyActor);
				IMGameplayInterface::Execute_Interact(HitActor, MyPawn);			
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 24, LineColor, false, 2.f);
		break;
	}
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 2.f);
}