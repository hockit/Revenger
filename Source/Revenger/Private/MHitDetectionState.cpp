
#include "MHitDetectionState.h"
#include "DrawDebugHelpers.h"
#include "MCharacter.h"
#include "AI/MAICharacter_Base.h"


void UMHitDetectionState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AMCharacter* MyCharacter = Cast<AMCharacter>(MeshComp->GetOwner());
	if (MyCharacter)
	{
		MyCharacter->HitDetection();
	}

	AMAICharacter_Base* MyAICharacter = Cast<AMAICharacter_Base>(MeshComp->GetOwner());
	if (MyAICharacter)
	{
		MyAICharacter->HitDetection();
	}
}