
#include "MHitDetectionState.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "MCharacter.h"

void UMHitDetectionState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	AMCharacter* MyCharacter = Cast<AMCharacter>(MeshComp->GetOwner());
	if (ensure(MyCharacter))
	{
		MyCharacter->HitDetection();
	}
}

