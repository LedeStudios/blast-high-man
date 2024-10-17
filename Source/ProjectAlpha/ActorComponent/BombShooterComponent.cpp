// Copyright Lede Studios. All Rights Reserved.


#include "BombShooterComponent.h"

#include "Actor/BombActor.h"
#include "Game/StageGameMode.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

UBombShooterComponent::UBombShooterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBombShooterComponent::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AStageGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UBombShooterComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bFireAutomatic)
	{
		if (AutomaticFireInitTick < AutomaticFireInitDelay)
		{
			AutomaticFireInitTick += DeltaTime;
			return;
		}
		
		AutomaticFireTick += DeltaTime;
		if (AutomaticFireTick >= AutomaticFirePeriod)
		{
			AutomaticFireTick = 0.f;
			Fire();
		}
	}
	else
	{
		AutomaticFireInitTick = 0.f;
		AutomaticFireTick = 0.f;
	}
}

void UBombShooterComponent::Fire()
{
	if (BombActorClass)
	{
		ABombActor* Bomb = GetWorld()->SpawnActor<ABombActor>(BombActorClass, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
		if (UProjectileMovementComponent* Component = Bomb->GetProjectileMovementComponent())
		{
			Component->bShouldBounce = false;
			Component->bRotationFollowsVelocity = true;
			Component->Velocity = GetOwner()->GetActorForwardVector() * FireSpeed;
			Component->MaxSpeed = MaxSpeed;
		}

		if (GameMode.IsValid())
		{
			if (USoundCue* Sound = GameMode->GetBombShootSound())
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetOwner()->GetActorLocation());
			}
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Fire Bomb %s"), *GetOwner()->GetActorForwardVector().ToString())
	}
}

