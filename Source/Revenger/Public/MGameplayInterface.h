
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MGameplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class REVENGER_API IMGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
