// Fill out your copyright notice in the Description page of Project Settings.

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
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* LeftHandBox;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* RightHandBox;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* LeftLegBox;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* RightLegBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UMInteractionComponent* InteractionComp;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage | Combat")
	UAnimMontage* CombatMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage | Dodge")
	UAnimMontage* DodgeMontage;

	// FUNCTION

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Dodge();
	void PrimaryAttack();
	void Interact();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	void DodgeEnd();


	UFUNCTION(BlueprintCallable)
	void Hand_L_ActivateCollision();

	UFUNCTION(BlueprintCallable)
	void Hand_R_ActivateCollision();

	UFUNCTION(BlueprintCallable)
	void Leg_L_ActivateCollision();

	UFUNCTION(BlueprintCallable)
	void Leg_R_ActivateCollision();

	UFUNCTION(BlueprintCallable)
	void DeactivateCollision();

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// VARIABLES
	UPROPERTY(BlueprintReadOnly)
	bool IsDodging;

	// Attack variables
	bool IsAttacking;
	int AttackCount;
public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
