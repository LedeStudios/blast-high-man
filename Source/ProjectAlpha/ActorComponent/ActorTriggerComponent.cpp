// Copyright Lede Studios. All Rights Reserved.


#include "ActorTriggerComponent.h"

#include "ActorActivationComponent.h"
#include "Kismet/GameplayStatics.h"

UActorTriggerComponent::UActorTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UActorTriggerComponent::ActiveActor()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);

	for (const AActor* Actor : Actors)
	{
		UActorComponent* Comp = Actor->GetComponentByClass(UActorActivationComponent::StaticClass());
		if (UActorActivationComponent* ActivationComp = Cast<UActorActivationComponent>(Comp))
		{
			if (ActivationID.IsEqual(ActivationComp->GetActivationID()))
			{
				ActivationComp->OnActorActivate();
				bIsActivated = true;

				UE_LOG(LogTemp, Warning, TEXT("Activate Actor: %s"), *ActivationID.ToString());
			}
		}
	}
}

void UActorTriggerComponent::DeactiveActor()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);

	for (const AActor* Actor : Actors)
	{
		UActorComponent* Comp = Actor->GetComponentByClass(UActorActivationComponent::StaticClass());
		if (UActorActivationComponent* ActivationComp = Cast<UActorActivationComponent>(Comp))
		{
			if (ActivationID.IsEqual(ActivationComp->GetActivationID()))
			{
				ActivationComp->OnActorDeactivate();
				bIsActivated = false;

				UE_LOG(LogTemp, Warning, TEXT("Deactived Actor: %s"), *ActivationID.ToString());
			}
		}
	}
}

bool UActorTriggerComponent::IsActorActivated()
{
	return bIsActivated;
}
