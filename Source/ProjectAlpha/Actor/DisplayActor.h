// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DisplayActor.generated.h"

class UBoxComponent;
class UMeshDisplayWidget;

UCLASS()
class PROJECTALPHA_API ADisplayActor : public AActor
{
	GENERATED_BODY()

public:
	ADisplayActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="DisplayActor")
	TObjectPtr<UBoxComponent> Box;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="DisplayActor")
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent2D;

	UPROPERTY()
	TObjectPtr<UTextureRenderTarget2D> RenderTarget;
	
private:
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
