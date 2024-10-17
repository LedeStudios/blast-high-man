// Copyright Lede Studios. All Rights Reserved.


#include "ActorActivationComponent.h"

#include "BombShooterComponent.h"
#include "PushPlayerComponent.h"

UActorActivationComponent::UActorActivationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UActorActivationComponent::OnActorActivate()
{
	UActorComponent* Comp = GetOwner()->GetComponentByClass(UBombShooterComponent::StaticClass());
	if (UBombShooterComponent* ShooterComp = Cast<UBombShooterComponent>(Comp))
	{
		ShooterComp->Fire();
	}

	Comp = GetOwner()->GetComponentByClass(UPushPlayerComponent::StaticClass());
	if (UPushPlayerComponent* PushComp = Cast<UPushPlayerComponent>(Comp))
	{
		PushComp->bIsAutomatic = true;
	}
}

void UActorActivationComponent::OnActorDeactivate()
{

}

