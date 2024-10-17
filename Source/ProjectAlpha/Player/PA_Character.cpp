// Copyright Lede Studios. All Rights Reserved.


#include "PA_Character.h"

#include "FootstepComponent.h"
#include "Stage/Checkpoint.h"

#include "Bomb/BombComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Stage/CheckpointActor.h"


APA_Character::APA_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCamera->SetupAttachment(GetMesh());
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Mesh
	GetMesh()->SetVisibility(false);
	GetMesh()->SetCastHiddenShadow(true);

	// Footstep
	FootstepComponent = CreateDefaultSubobject<UFootstepComponent>("FootstepComponent");
	
	// Bomb Charger
	BombComponent = CreateDefaultSubobject<UBombComponent>("Bomb");
}

void APA_Character::BeginPlay()
{
	Super::BeginPlay();
}

void APA_Character::SetCheckpoint(UCheckpoint* Checkpoint)
{
	if (Checkpoint)
	{
		CurrentCheckpoint = Checkpoint;
		UE_LOG(LogTemp, Warning, TEXT("Set Checkpoint."))
	}
	else
	{
		CurrentCheckpoint.Reset();
		UE_LOG(LogTemp, Warning, TEXT("Clear Checkpoint."))
	}
}

void APA_Character::SetLastCheckpoint(UCheckpoint* Checkpoint)
{
	if (Checkpoint)
	{
		LastCheckpoint = Checkpoint;
	}
	else
	{
		LastCheckpoint.Reset();
	}
}

void APA_Character::SetLastCheckpointActor(ACheckpointActor* InActor)
{
	LastCheckpointActor = InActor;
}

void APA_Character::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	
	if (OnJump.IsBound())
	{
		OnJump.Broadcast();
	}
}

void APA_Character::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (OnLand.IsBound())
	{
		OnLand.Broadcast(Hit);
	}
}

