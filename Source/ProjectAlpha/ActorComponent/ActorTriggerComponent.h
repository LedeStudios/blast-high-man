// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorTriggerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTALPHA_API UActorTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActorTriggerComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Activation")
	FName ActivationID;

public:
	FName GetActivationID() const { return ActivationID; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Activation")
	bool bIsActivated;
	
public:
	UFUNCTION(BlueprintCallable, Category="Trigger")
	void ActiveActor();

	UFUNCTION(BlueprintCallable, Category="Trigger")
	void DeactiveActor();

	UFUNCTION(BlueprintCallable, Category="Trigger")
	bool IsActorActivated();
	
};
