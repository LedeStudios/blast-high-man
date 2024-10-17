// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Save/SettingsSaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveLoadSubsystem.generated.h"

class USettingsSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoaded);

UCLASS()
class PROJECTALPHA_API USaveLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	FOnSaved OnSettingsSaved;
	FOnLoaded OnSettingsLoaded;
	
public:
	UFUNCTION(BlueprintCallable, Category="SaveLoad")
	void SaveSettings();

	UFUNCTION(BlueprintCallable, Category="SaveLoad")
	void LoadSettings();
	
};
