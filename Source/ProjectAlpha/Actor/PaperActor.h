// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperActor.generated.h"

class UPaperWidget;
class APA_Character;
class USoundCue;

UCLASS()
class PROJECTALPHA_API APaperActor : public AActor
{
	GENERATED_BODY()

public:
	APaperActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Paper")
	TObjectPtr<UTexture2D> PaperTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Paper")
	TSubclassOf<UPaperWidget> PaperWidgetClass;

	UPROPERTY()
	TObjectPtr<UPaperWidget> PaperWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Paper")
	TObjectPtr<USoundCue> OpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Paper")
	TObjectPtr<USoundCue> CloseSound;
	
	
public:
	UFUNCTION(BlueprintCallable, Category="Paper")
	void OpenPaperUI(APlayerController* Controller);

	UFUNCTION(BlueprintCallable, Category="Paper")
	void ClosePaperUI(APlayerController* Controller);

	UFUNCTION(BlueprintCallable, Category="Paper")
	bool IsPaperUIOpened();

public:
	UFUNCTION(BlueprintCallable, Category="Paper")
	void OnBeginOverlap(AActor* Other);

	UFUNCTION(BlueprintCallable, Category="Paper")
	void OnEndOverlap(AActor* Other);
	
};
