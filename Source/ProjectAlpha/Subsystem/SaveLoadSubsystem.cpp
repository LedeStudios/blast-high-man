// Copyright Lede Studios. All Rights Reserved.


#include "SaveLoadSubsystem.h"

#include "SettingsSubsystem.h"

void USaveLoadSubsystem::SaveSettings()
{
	if (USettingsSaveGame* SaveGame = Cast<USettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(USettingsSaveGame::StaticClass())))
	{
		const USettingsSubsystem* Settings = GetGameInstance()->GetSubsystem<USettingsSubsystem>();

		// Audio
		SaveGame->AudioMaster = Settings->AudioMaster;
		SaveGame->AudioBGM = Settings->AudioBGM;
		SaveGame->AudioSFX = Settings->AudioSFX;
		SaveGame->AudioUI = Settings->AudioUI;

		// Video
		SaveGame->bIsScreenShake = Settings->bIsScreenShake;

		// Control
		SaveGame->MouseX = Settings->MouseX;
		SaveGame->MouseY = Settings->MouseY;

		FAsyncSaveGameToSlotDelegate Saved;
		Saved.BindLambda([this](const FString& SlotName, const int32 UserIndex, bool bSuccess)
		{
			if (bSuccess)
			{
				UE_LOG(LogTemp, Warning, TEXT("Settings Data Save Completed."))
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Settings Data Save Failed."))
			}

			if (OnSettingsSaved.IsBound())
			{
				OnSettingsSaved.Broadcast();
			}
		});

		UE_LOG(LogTemp, Warning, TEXT("Settings Save Started."))
		UGameplayStatics::AsyncSaveGameToSlot(SaveGame, USettingsSaveGame::SaveSlotName, USettingsSaveGame::UserIndex, Saved);
	}
}

void USaveLoadSubsystem::LoadSettings()
{
	FAsyncLoadGameFromSlotDelegate Loaded;
	Loaded.BindLambda([this](const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Settings Load Completed."))

		if (LoadedGameData == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot Load Settings Data, Save New Data."))
			SaveSettings();
			return;
		}
		
		if (const USettingsSaveGame* SaveGame = Cast<USettingsSaveGame>(LoadedGameData))
		{
			USettingsSubsystem* Settings = GetGameInstance()->GetSubsystem<USettingsSubsystem>();

			// Audio
			Settings->AudioMaster = SaveGame->AudioMaster;
			Settings->AudioBGM = SaveGame->AudioBGM;
			Settings->AudioSFX = SaveGame->AudioSFX;
			Settings->AudioUI = SaveGame->AudioUI;

			// Video
			Settings->bIsScreenShake = SaveGame->bIsScreenShake;

			// Control
			Settings->MouseX = SaveGame->MouseX;
			Settings->MouseY = SaveGame->MouseY;
			
			UE_LOG(LogTemp, Warning, TEXT("BGM: %f, SFX: %f, UI: %f"), Settings->AudioBGM, Settings->AudioSFX, Settings->AudioUI)
		}

		if (OnSettingsLoaded.IsBound())
		{
			OnSettingsLoaded.Broadcast();
		}
	});

	UE_LOG(LogTemp, Warning, TEXT("Settings Load Started."))
	UGameplayStatics::AsyncLoadGameFromSlot(USettingsSaveGame::SaveSlotName, USettingsSaveGame::UserIndex, Loaded);
}
