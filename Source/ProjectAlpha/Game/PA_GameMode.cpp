// Copyright Lede Studios. All Rights Reserved.


#include "Game/PA_GameMode.h"

#include "Subsystem/SaveLoadSubsystem.h"

void APA_GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (USaveLoadSubsystem* SaveLoad = GetGameInstance()->GetSubsystem<USaveLoadSubsystem>())
	{
		SaveLoad->OnSettingsLoaded.AddDynamic(this, &APA_GameMode::LoadDataCompleted);
		SaveLoad->OnSettingsSaved.AddDynamic(this, &APA_GameMode::SaveDataCompleted);
		SaveLoad->LoadSettings();
	}
}


