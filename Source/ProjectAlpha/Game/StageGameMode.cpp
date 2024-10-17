// Copyright Lede Studios. All Rights Reserved.


#include "StageGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PA_Character.h"
#include "Sound/SoundCue.h"
#include "Stage/Stage.h"

AStageGameMode::AStageGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Init Stages
	UStage* Prev = nullptr;
	for (UStage* Stage : Stages)
	{
		if (Prev != nullptr && Prev != Stage)
		{
			Prev->SetNextStage(Stage);	
		}
		
		Stage->SetPrevStage(Prev);
		Prev = Stage;
	}

	UE_LOG(LogTemp, Warning, TEXT("Init Stages."))

	// Load Start Stage
	if (UStage* StartStage = Stages[0])
	{
		CurrentStage = StartStage;
		CurrentStage->LoadStage();
		CurrentStage->LoadCheckpoints();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Init Start Stage."))

	InitGlitchEffect();
	UE_LOG(LogTemp, Warning, TEXT("Init Glitch Effect."))
}

void AStageGameMode::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateGlitchEffect(DeltaSeconds);
}

UStage* AStageGameMode::NextStage()
{
	if (UStage* Next = CurrentStage->GetNextStage())
	{
		CurrentStage = Next;
		return Next;
	}
	return nullptr;
}

UStage* AStageGameMode::PrevStage()
{
	if (UStage* Prev = CurrentStage->GetPrevStage())
	{
		CurrentStage = Prev;
		return Prev;
	}
	return nullptr;
}

void AStageGameMode::Restart() const
{
	if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

		if (PlayerStarts.Num() > 0)
		{
			Character->SetActorTransform(PlayerStarts[0]->GetActorTransform());
			Character->GetController()->SetControlRotation(Character->GetActorRotation());
		}
	}
}

void AStageGameMode::MoveNextStage()
{
	// 다음 스테이지 로드
	UStage* Next = NextStage();
	if (Next == nullptr)
	{
		return;
	}
	
	Next->LoadStage();
	Next->LoadCheckpoints();

	// 이전 스테이지 언로드
	if (UStage* Prev = Next->GetPrevStage())
	{
		Prev->UnloadStage();

		// 이전 스테이지의 이전 스테이지 체크포인트 언로드
		if (UStage* PrevPrev = Prev->GetPrevStage())
		{
			PrevPrev->UnloadCheckpoints();
		}
	}

	TArray<AActor*> CheckpointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckpointActor::StaticClass(), CheckpointActors);

	ACheckpointActor* StartCheckpoint = nullptr;
	for (AActor* Actor : CheckpointActors)
	{
		if (ACheckpointActor* CheckpointActor = Cast<ACheckpointActor>(Actor))
		{
			if (StartCheckpoint == nullptr)
			{
				StartCheckpoint = CheckpointActor;
			}
			else
			{
				FName ID = StartCheckpoint->GetCheckpointId();
				FName OtherId = CheckpointActor->GetCheckpointId();

				if (OtherId.Compare(ID) > 0)
				{
					StartCheckpoint = CheckpointActor;
				}
			}
		}
	}

	SetLastCheckpointActor(StartCheckpoint);

	if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		Character->SetActorTransform(StartCheckpoint->GetSpawnPoint());
		Character->GetController()->SetControlRotation(Character->GetActorRotation());
	}
}

void AStageGameMode::Respawn(APA_Character* InCharacter)
{
	// PlayGlitchWithSound2D();
		
	if (const ACheckpointActor* Checkpoint = GetLastCheckpointActor())
	{
		InCharacter->SetActorTransform(Checkpoint->GetSpawnPoint());
		InCharacter->GetController()->SetControlRotation(InCharacter->GetActorRotation());
			
		UE_LOG(LogTemp, Warning, TEXT("Teleport to Last Spawn Point"));
		return;
	}

	Restart();
	UE_LOG(LogTemp, Warning, TEXT("Restart Initial Point"));
}

void AStageGameMode::OnStageLoaded(const FName& InLevel)
{
	OnStageLoadedBP(InLevel);
}

void AStageGameMode::OnStageUnloaded(const FName& InLevel)
{
	OnStageUnloadedBP(InLevel);
}

void AStageGameMode::PlayGlitch()
{
	bIsGlitching = true;

	UE_LOG(LogTemp, Warning, TEXT("Play Glitch"))
}

void AStageGameMode::PlayGlitchWithSound(const FVector& SoundLoc)
{
	PlayGlitch();
	if (GlitchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GlitchSound, SoundLoc);
	}
}

void AStageGameMode::PlayGlitchWithSound2D()
{
	PlayGlitch();
	UGameplayStatics::PlaySound2D(GetWorld(), GlitchSound);
}

void AStageGameMode::InitGlitchEffect()
{
	for (TActorIterator<APostProcessVolume> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->IsValidLowLevel())
		{
			PostProcessVolume = *ActorItr;
			UE_LOG(LogTemp, Warning, TEXT("Find PostProcessVolume"))
			break;
		}
	}
	
	if (GlitchMaterial)
	{
		GlitchDynamicMaterial = UMaterialInstanceDynamic::Create(GlitchMaterial, this);

		if (PostProcessVolume.IsValid())
		{
			PostProcessVolume->AddOrUpdateBlendable(GlitchDynamicMaterial);
			UE_LOG(LogTemp, Warning, TEXT("Create DynamicMaterial"))
		}
	}
}

void AStageGameMode::UpdateGlitchEffect(const float DeltaSeconds)
{
	if (!bIsGlitching)
	{
		return;
	}
	
	if (GlitchElapsedTime < GlitchDuration)
	{
		GlitchElapsedTime += DeltaSeconds;

		const float GlitchIntensity = FMath::Sin(GlitchElapsedTime / GlitchDuration * PI);

		if (GlitchDynamicMaterial)
		{
			GlitchDynamicMaterial->SetScalarParameterValue(FName("PostProcessBlend"), GlitchIntensity);
			UE_LOG(LogTemp, Warning, TEXT("Update Glitch %f"), GlitchIntensity);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Update Glitch but Material is Nullptr"));
		}
	}
	else
	{
		bIsGlitching = false;
		GlitchElapsedTime = 0.f;
		if (GlitchDynamicMaterial)
		{
			GlitchDynamicMaterial->SetScalarParameterValue(FName("PostProcessBlend"), 0.f);
		}

		UE_LOG(LogTemp, Warning, TEXT("Stop Glitch"));
	}
}
