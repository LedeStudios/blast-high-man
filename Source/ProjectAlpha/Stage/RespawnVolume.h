// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RespawnVolume.generated.h"

class AStageGameMode;

UCLASS()
class PROJECTALPHA_API ARespawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ARespawnVolume();

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TWeakObjectPtr<AStageGameMode> GameMode;
	
public:
	UFUNCTION(BlueprintCallable, Category="Respawn")
	void Respawn(AActor* Other);
	
};
