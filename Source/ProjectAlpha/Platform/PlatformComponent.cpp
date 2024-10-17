// Copyright Lede Studios. All Rights Reserved.


#include "PlatformComponent.h"

#include "PlatformBase.h"
#include "Bomb/BombBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


UPlatformComponent::UPlatformComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPlatformComponent::BeginPlay()
{
	Super::BeginPlay();

	PlatformActor = CastChecked<APlatformBase>(GetOwner());
}


void UPlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UPlatformComponent::GetPlatformTypeBitmask() const
{
	return PlatformType;
}

bool UPlatformComponent::IsTypeMatch(const uint8 InFlags) const
{
	return PlatformType & InFlags;
}

bool UPlatformComponent::IsTypeMatch(const EPlatformFlag InFlag) const
{
	return PlatformType & static_cast<uint8>(InFlag);
}

void UPlatformComponent::OnBombHit(ABombBase* InBomb, const FHitResult& InHitResult)
{
	// 아무런 동작도 하지 않음
	if (IsTypeMatch(EPlatformFlag::None))
	{
		return;
	}

	// 폭탄 부착
	if (IsTypeMatch(EPlatformFlag::Attachable))
	{
		UProjectileMovementComponent* Component = InBomb->GetProjectileMovementComponent();
		Component->Velocity = FVector::ZeroVector;
		InBomb->GetBombCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InBomb->AttachToActor(PlatformActor.Get(), FAttachmentTransformRules::KeepWorldTransform);

		UE_LOG(LogTemp, Warning, TEXT("Attachable"));
	}
}

