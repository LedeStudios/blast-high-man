// Copyright Lede Studios. All Rights Reserved.


#include "PaperActor.h"

#include "Kismet/GameplayStatics.h"
#include "Player/PA_Character.h"
#include "Widgets/PaperWidget.h"
#include "Sound/SoundCue.h"


APaperActor::APaperActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APaperActor::OpenPaperUI(APlayerController* Controller)
{
	if (IsPaperUIOpened())
	{
		return;
	}

	if (PaperWidgetClass)
	{
		Controller->SetInputMode(FInputModeGameAndUI());
		Controller->bShowMouseCursor = true;
		
		PaperWidget = CreateWidget<UPaperWidget>(Controller, PaperWidgetClass);
		PaperWidget->AddToViewport();

		if (PaperTexture)
		{
			PaperWidget->SetPaperTexture(PaperTexture);
		}

		if (OpenSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
		}
	}
}

void APaperActor::ClosePaperUI(APlayerController* Controller)
{
	if (IsPaperUIOpened())
	{
		Controller->SetInputMode(FInputModeGameOnly());
		Controller->bShowMouseCursor = false;
		
		PaperWidget->RemoveFromParent();
		PaperWidget = nullptr;

		if (CloseSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), CloseSound);
		}
	}
}

bool APaperActor::IsPaperUIOpened()
{
	return PaperWidget != nullptr;
}

void APaperActor::OnBeginOverlap(AActor* Other)
{
	if (APA_Character* Character = Cast<APA_Character>(Other))
	{
		Character->SetPaperActor(this);

		UE_LOG(LogTemp, Warning, TEXT("Begin Overlap Paper"))
	}
}

void APaperActor::OnEndOverlap(AActor* Other)
{
	if (APA_Character* Character = Cast<APA_Character>(Other))
	{
		Character->SetPaperActor(nullptr);

		UE_LOG(LogTemp, Warning, TEXT("End Overlap Paper"))
	}
}

