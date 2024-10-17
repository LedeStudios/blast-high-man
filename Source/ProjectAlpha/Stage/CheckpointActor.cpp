// Copyright Lede Studios. All Rights Reserved.


#include "CheckpointActor.h"

#include "Checkpoint.h"
#include "Stage.h"
#include "Game/StageGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PA_Character.h"


ACheckpointActor::ACheckpointActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(GetRootComponent());
}

void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();

	GameMode = CastChecked<AStageGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}


void ACheckpointActor::OnBeginOverlap(AActor* OtherActor)
{
	if (APA_Character* Character = Cast<APA_Character>(OtherActor))
	{
		if (UStage* Stage = GameMode->GetCurrentStage())
		{
			if (UCheckpoint* Checkpoint = Stage->GetCheckpointById(CheckpointId))
			{
				Character->SetCheckpoint(Checkpoint);
				Character->SetLastCheckpoint(Checkpoint);
				Character->SetLastCheckpointActor(this);
			}
		}
	}
}

void ACheckpointActor::OnEndOverlap(AActor* OtherActor)
{
	if (APA_Character* Character = Cast<APA_Character>(OtherActor))
	{
		Character->SetCheckpoint(nullptr);
	}
}

