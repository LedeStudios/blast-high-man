// Copyright Lede Studios. All Rights Reserved.


#include "BombPlatformComponent.h"

#include "Game/StageGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PA_Character.h"
#include "Sound/SoundCue.h"


UBombPlatformComponent::UBombPlatformComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBombPlatformComponent::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AStageGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UBombPlatformComponent::OnHit(const FVector& HitLocation) const
{
	if (HitVfx)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitVfx, HitLocation, FRotator::ZeroRotator);

		UE_LOG(LogTemp, Warning, TEXT("Spawn VFX"))
	}

	switch (Type)
	{
	case EBombPlatformType::Impact:
		Impact(HitLocation);
		break;
	case EBombPlatformType::Destruct:
		Destruct(HitLocation);
		break;
	default: ;
	}
}

void UBombPlatformComponent::Impact(const FVector& HitLocation) const
{
	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	Params.bReturnPhysicalMaterial = true;

	TArray<FHitResult> Result;
	GetWorld()->SweepMultiByChannel(
		Result, HitLocation, HitLocation,
		FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(ImpactRadius),
		Params);

	for (FHitResult Hit : Result)
	{
		if (const APA_Character * Character = Cast<APA_Character>(Hit.GetActor()))
		{
			FVector Adjustment = GetForwardVector() * ImpactAdjustmentFactor;
			FVector Direction = (Character->GetActorLocation() - HitLocation).GetSafeNormal();
			FVector FinalDirection = (Direction + Adjustment).GetSafeNormal();
			Character->GetCharacterMovement()->AddImpulse(FinalDirection * ImpactPower, true);

			UE_LOG(LogTemp, Warning, TEXT("Impact Player"));
		}
	}
	
	if (GameMode.IsValid())
	{
		if (USoundCue* Sound = GameMode->GetBombImpactSound())
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, HitLocation);
			UE_LOG(LogTemp, Warning, TEXT("Play Impact Sound"))
		}
	}
}

void UBombPlatformComponent::Destruct(const FVector& HitLocation) const
{
	GetOwner()->Destroy();
}