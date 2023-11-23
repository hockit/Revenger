// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMAttributeComponent;

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

	// FUNCTION

	void MoveForward(float Value);
	void MoveRight(float Value);

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
