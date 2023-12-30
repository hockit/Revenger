
#include "MCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MAttributeComponent.h"
#include "MInteractionComponent.h"
#include "Animation/AnimMontage.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AMCharacter::AMCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");
	InteractionComp = CreateDefaultSubobject<UMInteractionComponent>("InteractionComp");

	IsDodging = false;
	IsAttacking = false;
	IsSprinting = false;
	AttackCount = 0;
}


void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMCharacter::Interact);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AMCharacter::Dodge);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMCharacter::SprintStop);
}

void AMCharacter::Dodge()
{
	if (!IsAttacking && !IsDodging)
	{
		IsDodging = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && DodgeMontage)
		{
			AnimInstance->Montage_Play(DodgeMontage);
		}
	}
}

void AMCharacter::DodgeEnd()
{
	IsDodging = false;
}

void AMCharacter::PrimaryAttack()
{
	if (!IsAttacking)
	{
		IsAttacking = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (ensure(AnimInstance))
		{
			if (AttackCount == CombatArrayMontage.Num())
			{
				AttackCount = 0;
			}
			AnimInstance->Montage_Play(CombatArrayMontage[AttackCount]);
			AttackCount++;
		}
		IsDodging = false;
	}
}

void AMCharacter::AttackEnd()
{
	IsAttacking = false;
}

void AMCharacter::ResetCombo()
{
	AttackCount = 0;
}

void AMCharacter::Interact()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void AMCharacter::SprintStart()
{
	IsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = 1200.f;
}

void AMCharacter::SprintStop()
{
	IsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AMCharacter::MoveForward(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	AddMovementInput(ControlRotation.Vector(), Value);
}

void AMCharacter::MoveRight(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}