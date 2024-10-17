// Copyright Lede Studios. All Rights Reserved.


#include "BombBase.h"

#include "BombComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Platform/PA_FloatingPlatform.h"
#include "Platform/PlatformBase.h"
#include "Platform/PlatformComponent.h"
#include "Player/PA_Character.h"

ABombBase::ABombBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->bSweepCollision = true;
	ProjectileMovementComponent->bShouldBounce = true;

	BombCollision = CreateDefaultSubobject<USphereComponent>("BombCollision");
	SetRootComponent(BombCollision);
	
	Property = FBombProperty();
}

void ABombBase::BeginPlay()
{
	Super::BeginPlay();

	BombCollision->OnComponentHit.AddDynamic(this, &ABombBase::OnPlatformHit);
}

void ABombBase::SetLaunchVelocity(const FVector& InVelocity) const
{
	ProjectileMovementComponent->Velocity = InVelocity;
}

void ABombBase::SetBombType(const EBombType Type)
{
	BombType = Type;
}

void ABombBase::Explode(const FVector& Pos)
{
	TArray<FOverlapResult> Results;
	if (GetWorld()->OverlapMultiByChannel(
		Results, Pos, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(Property.Radius),
		FCollisionQueryParams::DefaultQueryParam, FCollisionResponseParams::DefaultResponseParam))
	{
		for (FOverlapResult& Result : Results)
		{
			AActor* OverlappedActor = Result.GetActor();
			if (OverlappedActor == nullptr || OverlappedActor == this)
			{
				continue;
			}
			
			if (const APA_Character* Character = Cast<APA_Character>(OverlappedActor))
			{
				FVector Direction = (Character->GetActorLocation() - Pos).GetSafeNormal();
				if (BombType == EBombType::Attraction)
				{
					Direction *= -1;
				}
				
				Character->GetCharacterMovement()->AddImpulse(Direction * Property.Power, true);
				UE_LOG(LogTemp, Warning, TEXT("Push Character %s"), *Character->GetName());
				continue;
			}

			if (APA_FloatingPlatform* Platform = Cast<APA_FloatingPlatform>(OverlappedActor))
			{
				FVector Direction = (Platform->GetActorLocation() - Pos).GetSafeNormal();
				if (BombType == EBombType::Attraction)
				{
					Direction *= -1;
				}

				Platform->Push(Direction, Property.Power, 1.f);
				UE_LOG(LogTemp, Warning, TEXT("Push Platform %s"), *Platform->GetName());
			}
		}
	}

	this->Destroy();
}

void ABombBase::Remove()
{
	this->Destroy();
}

void ABombBase::OnPlatformHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit Other Actor"))
	
	if (APlatformBase* Platform = Cast<APlatformBase>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Other Platform"))
		
		UPlatformComponent* Component = Platform->GetPlatformComponent();
		Component->OnBombHit(this, Hit);
	}
}

FVector ABombBase::GetExplodeLocation()
{
	return GetActorLocation();
}

int32 ABombBase::GetChargeLevel()
{
	return ChargeLevel;
}

void ABombBase::SetChargeLevel(const int32 Level)
{
	ChargeLevel = FMath::Clamp(Level, 0, 2);
}


