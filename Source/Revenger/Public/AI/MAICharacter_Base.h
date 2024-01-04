
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
	void UpdateWalkSpeed(float NewSpeed);
	void Attack();
	void HitDetection();

protected:

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMAttributeComponent* AttributeComp;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage | Combat")
	TArray<UAnimMontage*> CombatArrayMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage | Combat")
	UAnimMontage* HitReaction;

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta);

	bool IsAttacking;
	int AttackCount;
	FName SocketName;
};
