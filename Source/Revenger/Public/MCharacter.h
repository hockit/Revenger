#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UMAttributeComponent;
class UMInteractionComponent;
class UAnimMontage;

UCLASS()
class REVENGER_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AMCharacter();
	void HitDetection();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UMInteractionComponent* InteractionComp;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage | Combat")
	TArray<UAnimMontage*> CombatArrayMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage | Combat")
	UAnimMontage* SprintAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage | Combat")
	UAnimMontage* HitReaction;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage | Dodge")
	UAnimMontage* DodgeMontage;

	// FUNCTION

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Dodge();
	void PrimaryAttack();
	void Interact();
	void SprintStart();
	void SprintStop();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	void DodgeEnd();

	// VARIABLES
	UPROPERTY(BlueprintReadOnly)
	bool IsDodging;

	UPROPERTY(BlueprintReadOnly)
	bool IsSprinting;

	// Attack variables
	bool IsAttacking;
	int AttackCount;
	FName SocketName;

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
