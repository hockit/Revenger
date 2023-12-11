
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGameplayInterface.h"
#include "MBaseItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class REVENGER_API AMBaseItem : public AActor, public IMGameplayInterface
{
	GENERATED_BODY()
	
public:	
	
	AMBaseItem();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

};
