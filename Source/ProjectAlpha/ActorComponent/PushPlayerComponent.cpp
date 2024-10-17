// Copyright Lede Studios. All Rights Reserved.


#include "PushPlayerComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PA_Character.h"


UPushPlayerComponent::UPushPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPushPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsAutomatic) {
		if (AutomaticPushTick > AutomaticPushPeriod)
		{
			AutomaticPushTick = 0.f;
			if (Player.IsValid())
			{
				Push(Player.Get());
			}
		}
		AutomaticPushTick += DeltaTime;
	}
}

void UPushPlayerComponent::Push(const ACharacter* Character) const
{
	Character->GetCharacterMovement()->AddImpulse(GetForwardVector() * PushPower, true);
}

void UPushPlayerComponent::OnBeginOverlap(AActor* InActor)
{
	if (APA_Character* ApaChar = Cast<APA_Character>(InActor))
	{
		Player = ApaChar;
	}
}

void UPushPlayerComponent::OnEndOverlap(AActor* InActor)
{
	Player.Reset();
}
