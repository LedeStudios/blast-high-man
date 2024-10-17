// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSaveGame.generated.h"

class UGameplayStatics;
/**
 * 
 */
UCLASS()
class PROJECTALPHA_API USettingsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	inline static FString SaveSlotName = FString("SettingsSlot");

	inline static uint32 UserIndex = 0;
	
public:
	USettingsSaveGame() {}

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
	bool bIsScreenShake = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float MouseX = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float MouseY = 100.f;
	
};
