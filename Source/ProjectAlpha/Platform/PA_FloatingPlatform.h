// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "PA_FloatingPlatform.generated.h"

UCLASS()
class PROJECTALPHA_API APA_FloatingPlatform : public AActor
{
	GENERATED_BODY()

public:
	APA_FloatingPlatform();
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform")
	TObjectPtr<UCurveVector> FloatingOffsetCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform")
	TObjectPtr<UCurveVector> FloatingRotCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform")
	TObjectPtr<UCurveFloat> MoveSpeedCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform")
	TObjectPtr<UCurveFloat> PushSpeedCurve;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform")
	float FloatingPlayLength = 5.f;
	
	FTimeline FloatingTimeline;
	
	FTimeline MoveTimeline;

	FTimeline PushTimeline;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform")
	bool PlayOnStart = false;

private:
	FTransform InitialTransform;
	FTransform OriginTransform;
	FTransform FloatingTransform;
	FTransform PushOriginTransform;
	FTransform MoveOriginTransform;

private:
	FVector CurrentPushDirection;
	float CurrentPushTimelineLength;
	float CurrentPushDistance;

private:
	FVector CurrentMoveTargetLoc;
	

public:
	UFUNCTION(BlueprintCallable, Category="Platform")
	void PlayFloating();

	UFUNCTION(BlueprintCallable, Category="Platform")
	void StopFloating();

	UFUNCTION(BlueprintCallable, Category="Platform")
	void ReturnToInitial();

	UFUNCTION(BlueprintCallable, Category="Platform")
	void ReturnToOrigin();

	UFUNCTION(BlueprintCallable, Category="Platform")
	void MoveToTarget(const FVector& TargetLoc, const float PlayLength);

	UFUNCTION(BlueprintCallable, Category="Platform")
	void Push(const FVector& PushDirection, const float PushDistance, const float PlayLength);

private:
	void UpdateActorTransform();
	
	UFUNCTION()
	void UpdateFloatingOffset(FVector InVector);

	UFUNCTION()
	void UpdateFloatingRot(FVector InVector);

	UFUNCTION()
	void UpdatePushLoc(float InFloat);

	UFUNCTION()
	void UpdateMoveLoc(float InFloat);

};
