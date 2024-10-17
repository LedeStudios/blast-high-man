// Copyright Lede Studios. All Rights Reserved.


#include "Stage.h"

#include "Checkpoint.h"
#include "Game/StageGameMode.h"
#include "Kismet/GameplayStatics.h"

UCheckpoint* UStage::GetCheckpointById(const FName InCheckpointId)
{
	for (UCheckpoint* Checkpoint : Checkpoints)
	{
		if (Checkpoint->GetId() == InCheckpointId)
		{
			return Checkpoint;
		}
	}
	return nullptr;
}

bool UStage::IsStageCheckpoint(const UCheckpoint* Checkpoint)
{
	if (Checkpoint)
	{
		return GetCheckpointById(Checkpoint->GetId()) != nullptr;
	}
	return false;
}

bool UStage::IsCheckpointsAchieved()
{
	for (const UCheckpoint* Checkpoint : Checkpoints)
	{
		if (!Checkpoint->IsAchieved())
		{
			return false;
		}
	}
	return true;
}

void UStage::LoadStage()
{
	if (!bIsInLoading && !bIsStageLoaded)
	{
		bIsInLoading = true;
		
		FLatentActionInfo LatentInfo;
		LatentInfo.UUID = 1;
		LatentInfo.Linkage = 0;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = FName("OnStageLoaded");
	
		UGameplayStatics::LoadStreamLevel(
				this, Level, true, false, LatentInfo);
		
		UE_LOG(LogTemp, Warning, TEXT("Load Stage."))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Stage is on loading or already loaded."))
	}
}

void UStage::UnloadStage()
{
	if (!bIsInUnloading)
	{
		FLatentActionInfo LatentInfo;
		LatentInfo.UUID = 2;
		LatentInfo.Linkage = 0;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = FName("OnStageUnloaded");
	
		UGameplayStatics::UnloadStreamLevel(this, Level, LatentInfo, false);
	
		UE_LOG(LogTemp, Warning, TEXT("Unload Stage."))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Stage is on unloading."))
	}
}

bool UStage::IsStageLoaded() const
{
	return bIsStageLoaded;
}

void UStage::LoadCheckpoints()
{
	for (UCheckpoint* Checkpoint : Checkpoints)
	{
		Checkpoint->LoadCheckpoints();
	}
}

void UStage::UnloadCheckpoints()
{
	for (UCheckpoint* Checkpoint : Checkpoints)
	{
		Checkpoint->UnloadCheckpoints();
	}
}

void UStage::OnStageLoaded()
{
	bIsStageLoaded = true;
	bIsInLoading = false;
	UE_LOG(LogTemp, Warning, TEXT("Load Stage Finished."))

	if (AStageGameMode* GameMode = Cast<AStageGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->OnStageLoaded(Level);
	}
}

void UStage::OnStageUnloaded()
{
	bIsStageLoaded = false;
	bIsInUnloading = false;
	UE_LOG(LogTemp, Warning, TEXT("Unload Stage Finished."))
	
	if (AStageGameMode* GameMode = Cast<AStageGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->OnStageUnloaded(Level);
	}
}
