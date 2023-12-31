
#include "MHitDetectionState.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "MCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MAttributeComponent.h"


void UMHitDetectionState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AMCharacter* MyCharacter = Cast<AMCharacter>(MeshComp->GetOwner());
	if (MyCharacter)
	{
		MyCharacter->HitDetection();
	}
}