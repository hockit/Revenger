#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MHitDetectionState.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UMHitDetectionState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
};
