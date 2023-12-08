
#include "MCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
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

	LeftHandBox = CreateDefaultSubobject<UBoxComponent>("LeftHandBox");
	LeftHandBox->OnComponentBeginOverlap.AddDynamic(this, &AMCharacter::OnActorOverlap);
	LeftHandBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_l"));

	RightHandBox = CreateDefaultSubobject<UBoxComponent>("RightHandBox");
	RightHandBox->OnComponentBeginOverlap.AddDynamic(this, &AMCharacter::OnActorOverlap);
	RightHandBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_r"));

	LeftLegBox = CreateDefaultSubobject<UBoxComponent>("LeftLegBox");
	LeftLegBox->OnComponentBeginOverlap.AddDynamic(this, &AMCharacter::OnActorOverlap);
	LeftLegBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("foot_l"));

	RightLegBox = CreateDefaultSubobject<UBoxComponent>("RightLegBox");
	RightLegBox->OnComponentBeginOverlap.AddDynamic(this, &AMCharacter::OnActorOverlap);
	RightLegBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("foot_r"));
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");
	InteractionComp = CreateDefaultSubobject<UMInteractionComponent>("InteractionComp");

	IsDodging = false;
	IsAttacking = false;
	AttackCount = 0;
}

void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	LeftHandBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftLegBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightLegBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

void AMCharacter::Hand_L_ActivateCollision()
{
	UE_LOG(LogTemp, Display, TEXT("Hand_L Active"));
	LeftHandBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMCharacter::Hand_R_ActivateCollision()
{
	UE_LOG(LogTemp, Display, TEXT("Hand_R Active"));
	RightHandBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMCharacter::Leg_L_ActivateCollision()
{
	UE_LOG(LogTemp, Display, TEXT("Leg_L Active"));
	LeftLegBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMCharacter::Leg_R_ActivateCollision()
{
	UE_LOG(LogTemp, Display, TEXT("Leg_R Active"));
	RightLegBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMCharacter::DeactivateCollision()
{
	LeftHandBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftLegBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightLegBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMCharacter::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UMAttributeComponent* AttributeComponent = Cast<UMAttributeComponent>(OtherActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
		if (AttributeComponent)
		{
			UE_LOG(LogTemp, Display, TEXT("Enemy Hit"));
			AttributeComponent->ApplyHealthChange(-5.f);
		}
	}
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
				AnimInstance->Montage_Play(CombatMontage, 1.5f);
				AnimInstance->Montage_JumpToSection(FName("Attack01"), CombatMontage);
				break;
			case 1:
				AttackCount++;
				AnimInstance->Montage_Play(CombatMontage, 1.5f);
				AnimInstance->Montage_JumpToSection(FName("Attack02"), CombatMontage);
				break;
			case 2:
				AttackCount++;
				AnimInstance->Montage_Play(CombatMontage, 1.5f);
				AnimInstance->Montage_JumpToSection(FName("Attack03"), CombatMontage);
				break;
			case 3:
				AttackCount = 0;
				AnimInstance->Montage_Play(CombatMontage, 0.9f);
				AnimInstance->Montage_JumpToSection(FName("Attack04"), CombatMontage);
				break;
			default:
				break;
			}
			
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