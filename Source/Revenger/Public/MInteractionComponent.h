
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UMInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMInteractionComponent();

	void PrimaryInteract();
};
