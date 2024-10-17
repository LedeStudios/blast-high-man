// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Stage/CheckpointActor.h"
#include "StageGameMode.generated.h"

class APA_Character;
class UStage;
class USoundCue;
/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTALPHA_API AStageGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStageGameMode();
	
protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category="Stage")
	TArray<UStage*> Stages;

	UPROPERTY()
	TWeakObjectPtr<UStage> CurrentStage;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UStage* GetCurrentStage() const { return CurrentStage.Get(); }

	UStage* NextStage();

	UStage* PrevStage();

protected:
	UPROPERTY()
	TWeakObjectPtr<ACheckpointActor> LastCheckpointActor;

public:
	void SetLastCheckpointActor(ACheckpointActor* InActor) { this->LastCheckpointActor = InActor; }

	ACheckpointActor* GetLastCheckpointActor() const { return LastCheckpointActor.Get(); }

public:
	UFUNCTION(BlueprintCallable, Category="Stage")
	void Restart() const;

	UFUNCTION(BlueprintCallable, Category="Stage")
	void MoveNextStage();

	UFUNCTION(BlueprintCallable, Category="Stage")
	void Respawn(APA_Character* InCharacter);

public:
	void OnStageLoaded(const FName& InLevel);

	void OnStageUnloaded(const FName& InLevel);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnStageLoadedBP(const FName& InLevel);

	UFUNCTION(BlueprintImplementableEvent)
	void OnStageUnloadedBP(const FName& InLevel);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bomb|Sound")
	TObjectPtr<USoundCue> BombImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bomb|Sound")
	TObjectPtr<USoundCue> BombShootSound;

public:
	USoundCue* GetBombImpactSound() { return BombImpactSound; }

	USoundCue* GetBombShootSound() { return BombShootSound; }

protected:
	TWeakObjectPtr<APostProcessVolume> PostProcessVolume;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> GlitchDynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glitch")
	TObjectPtr<UMaterialInstance> GlitchMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glitch")
	float GlitchDuration = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glitch")
	TObjectPtr<USoundCue> GlitchSound;
	
private:
	UPROPERTY()
	bool bIsGlitching = false;
	
	UPROPERTY()
	float GlitchElapsedTime = 0.f;
	
public:
	UFUNCTION(BlueprintCallable, Category="Glitch")
	void PlayGlitch();

	UFUNCTION(BlueprintCallable, Category="Glitch")
	void PlayGlitchWithSound(const FVector& SoundLoc);

	UFUNCTION(BlueprintCallable, Category="Glitch")
	void PlayGlitchWithSound2D();
	
	USoundCue* GetGlitchSound() { return GlitchSound; }
	
private:
	void InitGlitchEffect();
	
	void UpdateGlitchEffect(const float DeltaSeconds);
	
};
