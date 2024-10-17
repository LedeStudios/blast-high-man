// Copyright Lede Studios. All Rights Reserved.


#include "RespawnVolume.h"

#include "CheckpointActor.h"
#include "Game/StageGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PA_Character.h"


ARespawnVolume::ARespawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARespawnVolume::BeginPlay()
{
	Super::BeginPlay();

	GameMode = CastChecked<AStageGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ARespawnVolume::Respawn(AActor* Other)
{
	if (APA_Character* Character = Cast<APA_Character>(Other))
	{
		// GameMode->PlayGlitchWithSound2D();
		
		if (const ACheckpointActor* Checkpoint = GameMode->GetLastCheckpointActor())
		{
			Character->SetActorTransform(Checkpoint->GetSpawnPoint());
			Character->GetController()->SetControlRotation(Character->GetActorRotation());
			
			UE_LOG(LogTemp, Warning, TEXT("Teleport to Last Spawn Point"));
			return;
		}

		GameMode->Restart();
		UE_LOG(LogTemp, Warning, TEXT("Restart Initial Point"));
	}
}


