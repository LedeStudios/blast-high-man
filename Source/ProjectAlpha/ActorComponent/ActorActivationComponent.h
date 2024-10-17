// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorActivationComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class PROJECTALPHA_API UActorActivationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActorActivationComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	FName ActivationID;

public:
	FName GetActivationID() const { return ActivationID; }

public:
	void OnActorActivate();

	void OnActorDeactivate();
	
};
