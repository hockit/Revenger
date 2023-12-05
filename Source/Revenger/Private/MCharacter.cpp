
#include "MCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MAttributeComponent.h"
#include "MInteractionComponent.h"
#include "Animation/AnimMontage.h"

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
}
void AMCharacter::Dodge()
{
	IsDodging = true;
	GetWorldTimerManager().SetTimer(TimerHandle_Dodge, this, &AMCharacter::Dodge_TimeElapsed, 1.f);
}

void AMCharacter::Dodge_TimeElapsed()
{
	IsDodging = false;
}

void AMCharacter::PrimaryAttack()
{
	if (!IsAttacking)
	{
		IsAttacking = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CombatMontage)
		{
			switch (AttackCount)
			{
			case 0:
				AttackCount++;
				AnimInstance->Montage_Play(CombatMontage, 1.35f);
				AnimInstance->Montage_JumpToSection(FName("Attack01"), CombatMontage);
				break;
			case 1:
				AttackCount++;
				AnimInstance->Montage_Play(CombatMontage, 1.35f);
				AnimInstance->Montage_JumpToSection(FName("Attack02"), CombatMontage);
				break;
			case 2:
				AttackCount++;
				AnimInstance->Montage_Play(CombatMontage, 1.35f);
				AnimInstance->Montage_JumpToSection(FName("Attack03"), CombatMontage);
				break;
			case 3:
				AttackCount = 0;
				AnimInstance->Montage_Play(CombatMontage, 0.85f);
				AnimInstance->Montage_JumpToSection(FName("Attack04"), CombatMontage);
				break;
			default:
				break;
			}
			
		}
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