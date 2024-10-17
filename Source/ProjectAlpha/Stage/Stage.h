// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Stage.generated.h"

class UCheckpoint;
/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Blueprintable)
class PROJECTALPHA_API UStage : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stage")
	FName Level;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="Stage")
	TObjectPtr<UStage> Next;
	
	UPROPERTY(BlueprintReadOnly, Category="Stage")
	TObjectPtr<UStage> Prev;

public:
	UStage* GetNextStage() { return Next; }

	void SetNextStage(UStage* InStage) { Next = InStage; }

	UStage* GetPrevStage() const { return Prev.Get(); }

	void SetPrevStage(UStage* InStage) { Prev = InStage; }

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category="Stage")
	TArray<UCheckpoint*> Checkpoints;

public:
	TArray<UCheckpoint*> GetCheckpoints() { return Checkpoints; }

	UCheckpoint* GetCheckpointById(FName InCheckpointId);

	bool IsStageCheckpoint(const UCheckpoint* Checkpoint);

	bool IsCheckpointsAchieved();

protected:
	bool bIsStageLoaded = false;

	bool bIsInLoading = false;
	bool bIsInUnloading = false;
	
public:
	void LoadStage();

	void UnloadStage();
	
	void LoadCheckpoints();

	void UnloadCheckpoints();

	bool IsStageLoaded() const;
	
private:
	UFUNCTION()
	void OnStageLoaded();

	UFUNCTION()
	void OnStageUnloaded();

};
