// Copyright Lede Studios. All Rights Reserved.


#include "PA_Controller.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PA_Character.h"
#include "Actor/PaperActor.h"
#include "ActorComponent/ActorTriggerComponent.h"
#include "Blueprint/UserWidget.h"
#include "Bomb/BombComponent.h"
#include "Bomb/PA_BombGaugeArea.h"
#include "Game/StageGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Stage/Checkpoint.h"
#include "Stage/Stage.h"
#include "Subsystem/SaveLoadSubsystem.h"
#include "Subsystem/SettingsSubsystem.h"

APA_Controller::APA_Controller()
{
	bReplicates = true;
}

void APA_Controller::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	PlayerCharacter =  CastChecked<APA_Character>(GetCharacter());
	GameMode = CastChecked<AStageGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Settings = GetGameInstance()->GetSubsystem<USettingsSubsystem>();
}

void APA_Controller::OpenEscMenu()
{
	if (EscWidget)
	{
		Widget = CreateWidget<UUserWidget>(this, EscWidget);
		Widget->AddToViewport();

		FInputModeGameAndUI Mode = FInputModeGameAndUI();
		Mode.SetWidgetToFocus(Widget->TakeWidget());
		SetInputMode(Mode);
		bShowMouseCursor = true;

		UE_LOG(LogTemp, Warning, TEXT("Open Esc Menu"))
	}
}

void APA_Controller::CloseEscMenu()
{
	Widget->RemoveFromParent();
	Widget = nullptr;
		
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	// 메뉴 종료 시 설정 저장
	GetGameInstance()->GetSubsystem<USaveLoadSubsystem>()->SaveSettings();
	
	UE_LOG(LogTemp, Warning, TEXT("Close Esc Menu"))
}

bool APA_Controller::IsEscMenuOpened() const
{
	return Widget != nullptr;
}

void APA_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APA_Controller::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APA_Controller::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APA_Controller::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APA_Controller::Look);

		// Bomb - 2스테이지 개방 후 언락
		// EnhancedInputComponent->BindAction(RepulsionBombAction, ETriggerEvent::Started, this, &APA_Controller::ChargeRepulsionBomb);
		// EnhancedInputComponent->BindAction(RepulsionBombAction, ETriggerEvent::Completed, this, &APA_Controller::ShootRepulsionBomb);
		// EnhancedInputComponent->BindAction(AttractionBombAction, ETriggerEvent::Started, this, &APA_Controller::ChargeAttractionBomb);
		// EnhancedInputComponent->BindAction(AttractionBombAction, ETriggerEvent::Completed, this, &APA_Controller::ShootAttractionBomb);

		// Regen - 2스테이지 개방 후 언락
		// EnhancedInputComponent->BindAction(RegenAction, ETriggerEvent::Started, this, &APA_Controller::Regen);

		// Interaction
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &APA_Controller::Interaction);

		// Esc
		EnhancedInputComponent->BindAction(EscAction, ETriggerEvent::Started, this, &APA_Controller::Esc);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APA_Controller::Jump()
{
	if (IsEscMenuOpened())
	{
		return;
	}

	if (APaperActor* PaperActor = PlayerCharacter->GetPaperActor())
	{
		if (PaperActor->IsPaperUIOpened())
		{
			return;
		}
	}
	
	if (PlayerCharacter.IsValid())
	{
		if (bUseLadder)
		{
			// Reset Ladder State
			bUseLadder = false;
			PlayerCharacter->GetCharacterMovement()->MovementMode = MOVE_Walking;
		}
		
		PlayerCharacter->Jump();
	}
}

void APA_Controller::StopJumping()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->StopJumping();
	}
}

void APA_Controller::Move(const FInputActionValue& Value)
{
	if (IsEscMenuOpened())
	{
		return;
	}

	if (APaperActor* PaperActor = PlayerCharacter->GetPaperActor())
	{
		if (PaperActor->IsPaperUIOpened())
		{
			return;
		}
	}
	
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	// get forward vector
	FVector ForwardDirection;
	if (bUseLadder)
	{
		const float CurrentPitch = PlayerCharacter->GetControlRotation().Pitch;
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, TEXT("Pitch: " + FString::SanitizeFloat(CurrentPitch)));
		ForwardDirection = PlayerCharacter->GetActorUpVector() * (CurrentPitch > 90 || CurrentPitch < 0 ? -1 : 1);
	}
	else
	{
		ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	}
	
	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
		PlayerCharacter->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APA_Controller::Look(const FInputActionValue& Value)
{
	if (IsEscMenuOpened())
	{
		return;
	}
	
	if (APaperActor* PaperActor = PlayerCharacter->GetPaperActor())
	{
		if (PaperActor->IsPaperUIOpened())
		{
			return;
		}
	}
	
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (PlayerCharacter.IsValid())
	{
		
		LookAxisVector.X = LookAxisVector.X / 100 * Settings->MouseX;
		LookAxisVector.Y = LookAxisVector.Y / 100 * Settings->MouseY;
		
		// add yaw input to controller
		PlayerCharacter->AddControllerYawInput(LookAxisVector.X);
		
		// limit pitch angle
		const float CurrentPitch = PlayerCharacter->GetControlRotation().Pitch;
		const float PitchToUpdate = (CurrentPitch > 180 ? CurrentPitch - 360 : CurrentPitch) - LookAxisVector.Y;
		const float Pitch = FMath::Clamp(PitchToUpdate, MinPitchAngle, MaxPitchAngle);

		// set controller pitch
		FRotator Rotator = PlayerCharacter->GetControlRotation();
		Rotator.Pitch = Pitch;
		if (PlayerCharacter->GetController())
		{
			PlayerCharacter->GetController()->SetControlRotation(Rotator);
		}
	}
}

void APA_Controller::ChargeRepulsionBomb()
{
	if (IsEscMenuOpened())
	{
		return;
	}

	if (APaperActor* PaperActor = PlayerCharacter->GetPaperActor())
	{
		if (PaperActor->IsPaperUIOpened())
		{
			return;
		}
	}
	
	if (PlayerCharacter.IsValid())
	{
		UBombComponent* Component = PlayerCharacter->GetBombComponent();
		if (!Component->IsAnyBombCharging())
		{
			Component->Charge(EBombType::Repulsion);
		}
	}
}

void APA_Controller::ShootRepulsionBomb()
{
	if (PlayerCharacter.IsValid())
	{
		UBombComponent* Component = PlayerCharacter->GetBombComponent();
		if (Component->IsBombCharging(EBombType::Repulsion))
		{
			Component->EndCharge();
		}
	}
}

void APA_Controller::ChargeAttractionBomb()
{
	if (IsEscMenuOpened())
	{
		return;
	}

	if (APaperActor* PaperActor = PlayerCharacter->GetPaperActor())
	{
		if (PaperActor->IsPaperUIOpened())
		{
			return;
		}
	}
	
	if (PlayerCharacter.IsValid())
	{
		UBombComponent* Component = PlayerCharacter->GetBombComponent();
		if (!Component->IsAnyBombCharging())
		{
			Component->Charge(EBombType::Attraction);
		}
	}
}

void APA_Controller::ShootAttractionBomb()
{
	if (PlayerCharacter.IsValid())
	{
		UBombComponent* Component = PlayerCharacter->GetBombComponent();
		if (Component->IsBombCharging(EBombType::Attraction))
		{
			Component->EndCharge();
		}
	}
}

void APA_Controller::Regen()
{
	if (IsEscMenuOpened())
	{
		return;
	}

	if (APaperActor* PaperActor = PlayerCharacter->GetPaperActor())
	{
		if (PaperActor->IsPaperUIOpened())
		{
			return;
		}
	}
	
	if (PlayerCharacter.IsValid())
	{
		if (PlayerCharacter->GetBombGaugeRegenArea() == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Yellow, "Not Regen Area");
			return;
		}

		PlayerCharacter->GetBombGaugeRegenArea()->RegenBombGauge(PlayerCharacter.Get());
	}
}

void APA_Controller::Interaction()
{
	if (IsEscMenuOpened())
	{
		return;
	}

	if (APaperActor* PaperActor = PlayerCharacter->GetPaperActor())
	{
		if (PaperActor->IsPaperUIOpened())
		{
			return;
		}
	}
	
	if (PlayerCharacter.IsValid())
	{
		// 체크포인트 안에 위치했다면 체크포인트와 상호작용
		if (UStage* Stage = GameMode->GetCurrentStage())
		{
			if (UCheckpoint* Checkpoint = PlayerCharacter->GetCheckpoint())
			{
				if (Stage->IsStageCheckpoint(Checkpoint))
				{
					Checkpoint->SetAchieved(true);
					GameMode->SetLastCheckpointActor(PlayerCharacter->GetLastCheckpointActor());
					
					if (Stage->IsCheckpointsAchieved())
					{
						UStage* Next = GameMode->NextStage();
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
						
						GameMode->PlayGlitchWithSound2D();
					}
				}
			}
		}

		// 쪽지 구역 안에 위치했다면 쪽지와 상호작용
		if (APaperActor* PaperActor = PlayerCharacter->GetPaperActor())
		{
			if (!PaperActor->IsPaperUIOpened())
			{
				PaperActor->OpenPaperUI(this);
				UE_LOG(LogTemp, Warning, TEXT("Open Paper UI"))
			}
		}

		// 트리거 액터 구역 안에 위치했다면 트리거 발동
		if (const AActor* TriggerActor = PlayerCharacter->GetActorTriggerActor())
		{
			UActorComponent* ActorComp = TriggerActor->GetComponentByClass(UActorTriggerComponent::StaticClass());
			if (UActorTriggerComponent* TriggerComp = Cast<UActorTriggerComponent>(ActorComp))
			{
				TriggerComp->IsActorActivated() ? TriggerComp->DeactiveActor() : TriggerComp->ActiveActor();
			}
		}
	}
}

void APA_Controller::Esc()
{
	// 쪽지 메뉴가 열려있다면 쪽지 메뉴만 종료
	if (APaperActor* PaperActor = PlayerCharacter->GetPaperActor())
	{
		if (PaperActor->IsPaperUIOpened())
		{
			PaperActor->ClosePaperUI(this);
			UE_LOG(LogTemp, Warning, TEXT("Close Paper UI"))

			return;
		}
	}

	// 다른 메뉴가 열려있지 않을 때만 ESC 메뉴 작동
	IsEscMenuOpened() ? CloseEscMenu() : OpenEscMenu();
}
