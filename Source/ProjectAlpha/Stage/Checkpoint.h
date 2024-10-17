// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Checkpoint.generated.h"

class ACheckpointActor;
/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Blueprintable)
class PROJECTALPHA_API UCheckpoint : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Checkpoint")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Checkpoint")
	FName Level;

	UPROPERTY(BlueprintReadOnly, Category="Checkpoint")
	bool bIsAchieved;

	UPROPERTY(BlueprintReadOnly, Category="Checkpoint")
	bool bIsLoaded = false;

public:
	FName GetId() const { return Id; }
	
	void SetAchieved(const bool IsAchieved) { bIsAchieved = IsAchieved; }
	
	bool IsAchieved() const { return bIsAchieved; }

	void LoadCheckpoints();

	void UnloadCheckpoints();

private:
	UFUNCTION()
	void OnCheckpointsLoaded();

	UFUNCTION()
	void OnCheckpointsUnloaded();

};
