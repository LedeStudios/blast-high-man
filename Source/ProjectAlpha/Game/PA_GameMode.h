// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PA_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTALPHA_API APA_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category="SaveLoad")
	void SaveDataCompleted();
	
	UFUNCTION(BlueprintImplementableEvent, Category="SaveLoad")
	void LoadDataCompleted();
	
};

