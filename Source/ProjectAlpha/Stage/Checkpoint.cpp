// Copyright Lede Studios. All Rights Reserved.


#include "Checkpoint.h"

#include "Kismet/GameplayStatics.h"
#include "Player/PA_Character.h"

void UCheckpoint::LoadCheckpoints()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 0;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnCheckpointsLoaded");
	
	UGameplayStatics::LoadStreamLevel(
		this, Level, true, false, LatentInfo);
		
	UE_LOG(LogTemp, Warning, TEXT("Load Checkpoints."))
}

void UCheckpoint::UnloadCheckpoints()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.UUID = 2;
	LatentInfo.Linkage = 0;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnCheckpointsUnloaded");
	
	UGameplayStatics::UnloadStreamLevel(this, Level, LatentInfo, false);
	
	UE_LOG(LogTemp, Warning, TEXT("Unload Checkpoints."))
}

void UCheckpoint::OnCheckpointsLoaded()
{
	bIsLoaded = true;
	UE_LOG(LogTemp, Warning, TEXT("Checkpoints Load Finished."))
}

void UCheckpoint::OnCheckpointsUnloaded()
{
	bIsLoaded = false;
	UE_LOG(LogTemp, Warning, TEXT("Checkpoints Unload Finished."))
}