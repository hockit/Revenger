// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMAttributeComponent;
class UMInteractionComponent;
class UAnimMontage;

UCLASS()
class REVENGER_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AMCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UMInteractionComponent* InteractionComp;

	FTimerHandle TimerHandle_Dodge;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage | Combat")
	UAnimMontage* CombatMontage;

	// FUNCTION

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Dodge();
	void Dodge_TimeElapsed();
	void PrimaryAttack();
	void Interact();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	// VARIABLES
	bool IsDodging;

	// Attack variables
	bool IsAttacking;
	int AttackCount;
public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};