
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MAICharacter_Base.generated.h"

class UMAttributeComponent;

UCLASS()
class REVENGER_API AMAICharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	
	AMAICharacter_Base();

protected:

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMAttributeComponent* AttributeComp;

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta);
};
