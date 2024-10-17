// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"

class AStageGameMode;

UCLASS()
class PROJECTALPHA_API ACheckpointActor : public AActor
{
	GENERATED_BODY()

public:
	ACheckpointActor();

public:
	virtual void BeginPlay() override;

protected:
	TWeakObjectPtr<AStageGameMode> GameMode;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Checkpoint")
	FName CheckpointId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Checkpoint")
	TObjectPtr<USceneComponent> SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Checkpoint")
	TObjectPtr<USceneComponent> SpawnPoint;
	
public:
	FName GetCheckpointId() const { return CheckpointId; }

	FTransform GetSpawnPoint() const { return SpawnPoint->GetComponentTransform(); }

protected:
	UFUNCTION(BlueprintCallable, Category="Checkpoint")
	void OnBeginOverlap(AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category="Checkpoint")
	void OnEndOverlap(AActor* OtherActor);
	
	
};
