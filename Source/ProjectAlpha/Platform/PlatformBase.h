// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformBase.generated.h"

class UPlatformComponent;

UCLASS()
class PROJECTALPHA_API APlatformBase : public AActor
{
	GENERATED_BODY()

public:
	APlatformBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Platform")
	TObjectPtr<UPlatformComponent> PlatformComponent;

public:
	UPlatformComponent* GetPlatformComponent() { return PlatformComponent; }
	
};
