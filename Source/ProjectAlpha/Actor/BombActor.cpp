// Copyright Lede Studios. All Rights Reserved.


#include "BombActor.h"

#include "ActorComponent/BombPlatformComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ABombActor::ABombActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->SetUpdatedComponent(GetRootComponent());
	ProjectileMovementComponent->bAutoActivate = true;
}

void ABombActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABombActor::OnHit(AActor* Other, const FVector HitLocation)
{
	if (UActorComponent* Component = Other->GetComponentByClass(UBombPlatformComponent::StaticClass()))
	{
		if (UBombPlatformComponent* Platform = Cast<UBombPlatformComponent>(Component))
		{
			Platform->OnHit(HitLocation);
		}
	}
	this->Destroy();
}

