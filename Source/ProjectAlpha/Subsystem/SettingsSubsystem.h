// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SettingsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTALPHA_API USettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float AudioMaster = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float AudioBGM = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float AudioSFX = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float AudioUI = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	bool bIsScreenShake = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float MouseX = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float MouseY = 100.f;
	
};
