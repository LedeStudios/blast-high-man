// Copyright Lede Studios. All Rights Reserved.


#include "PA_FloatingPlatform.h"

APA_FloatingPlatform::APA_FloatingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APA_FloatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Bind Transforms
	InitialTransform = GetActorTransform();
	OriginTransform = GetActorTransform();
	FloatingTransform = GetActorTransform();
	PushOriginTransform = GetActorTransform();
	MoveOriginTransform = GetActorTransform();

	// Play Floating Animation
	if (PlayOnStart)
	{
		PlayFloating();
	}
}

void APA_FloatingPlatform::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Play Timelines for Calculate Transform
	FloatingTimeline.TickTimeline(DeltaSeconds);
	PushTimeline.TickTimeline(DeltaSeconds);
	MoveTimeline.TickTimeline(DeltaSeconds);

	// Update Actor Transform
	UpdateActorTransform();
}

void APA_FloatingPlatform::UpdateActorTransform()
{
	if (FloatingTimeline.IsPlaying())
	{
		SetActorTransform(FloatingTransform);
		return;
	}

	if (PushTimeline.IsPlaying() || MoveTimeline.IsPlaying())
	{
		SetActorTransform(OriginTransform);
		return;
	}
}

void APA_FloatingPlatform::PlayFloating()
{
	if (FloatingOffsetCurve && FloatingRotCurve)
	{
		FOnTimelineVector OffsetCallback;
		OffsetCallback.BindDynamic(this, &APA_FloatingPlatform::UpdateFloatingOffset);
		FloatingTimeline.AddInterpVector(FloatingOffsetCurve, OffsetCallback);

		FOnTimelineVector RotCallback;
		RotCallback.BindDynamic(this, &APA_FloatingPlatform::UpdateFloatingRot);
		FloatingTimeline.AddInterpVector(FloatingRotCurve, RotCallback);

		FloatingTimeline.SetTimelineLength(1.f);
		FloatingTimeline.SetPlayRate(1.f / FloatingPlayLength);
		FloatingTimeline.SetLooping(true);
		FloatingTimeline.PlayFromStart();

		UE_LOG(LogTemp, Warning, TEXT("Play Floating"));
	}
}

void APA_FloatingPlatform::StopFloating()
{
	FloatingTimeline.Stop();
	SetActorTransform(OriginTransform);

	UE_LOG(LogTemp, Warning, TEXT("Stop Floating"));
}

void APA_FloatingPlatform::MoveToTarget(const FVector& TargetLoc, const float PlayLength)
{
	MoveTimeline.Stop();

	if (MoveSpeedCurve)
	{
		CurrentMoveTargetLoc = TargetLoc;
		MoveOriginTransform = OriginTransform;

		
		
		FOnTimelineFloat Callback;
		Callback.BindDynamic(this, &APA_FloatingPlatform::UpdateMoveLoc);
		MoveTimeline.AddInterpFloat(MoveSpeedCurve, Callback);

		MoveTimeline.SetTimelineLength(1.f);
		MoveTimeline.SetPlayRate(1.f / PlayLength);
		MoveTimeline.SetLooping(false);
		MoveTimeline.PlayFromStart();

		UE_LOG(LogTemp, Warning, TEXT("Play Move"));
	}
}

void APA_FloatingPlatform::Push(const FVector& PushDirection, const float PushDistance, const float PlayLength)
{
	if (PushTimeline.IsPlaying())
	{
		return;
	}

	if (PushSpeedCurve)
	{
		CurrentPushDirection = PushDirection;
		CurrentPushDistance = PushDistance;
		CurrentPushTimelineLength = PlayLength;
		PushOriginTransform = OriginTransform;

		FOnTimelineFloat Callback;
		Callback.BindDynamic(this, &APA_FloatingPlatform::UpdatePushLoc);
		PushTimeline.AddInterpFloat(PushSpeedCurve, Callback);

		PushTimeline.SetTimelineLength(1.f);
		PushTimeline.SetPlayRate(1.f / PlayLength);
		PushTimeline.SetLooping(false);
		PushTimeline.PlayFromStart();

		UE_LOG(LogTemp, Warning, TEXT("Play Push"));
	}
}

void APA_FloatingPlatform::ReturnToInitial()
{
	//TODO: 액터 사라지는 -> 등장하는 애니메이션 추가
	SetActorTransform(InitialTransform);
}

void APA_FloatingPlatform::ReturnToOrigin()
{
	//TODO: 액터 사라지는 -> 등장하는 애니메이션 추가
	SetActorTransform(OriginTransform);
}



void APA_FloatingPlatform::UpdateFloatingOffset(FVector InVector)
{
	const FVector NewLocation = OriginTransform.GetLocation() + (InVector * 100);
	
	FloatingTransform = OriginTransform;
	FloatingTransform.SetLocation(NewLocation);
}

void APA_FloatingPlatform::UpdateFloatingRot(FVector InVector)
{
	const FQuat NewRot = OriginTransform.GetRotation() + FQuat::MakeFromEuler(InVector * 360);

	FloatingTransform = OriginTransform;
	FloatingTransform.SetRotation(NewRot);
}

void APA_FloatingPlatform::UpdatePushLoc(float InFloat)
{
	const FVector Loc = PushOriginTransform.GetLocation();
	const FVector Dir = CurrentPushDirection.GetSafeNormal();
	const FVector NewLoc = Loc + (Dir * InFloat * CurrentPushDistance);

	OriginTransform.SetLocation(NewLoc);
}

void APA_FloatingPlatform::UpdateMoveLoc(float InFloat)
{
	const FVector Diff = CurrentMoveTargetLoc - MoveOriginTransform.GetLocation();
	const FVector NewLoc = MoveOriginTransform.GetLocation() + (Diff * InFloat);
	
	if (PushTimeline.IsPlaying())
	{
		PushOriginTransform.SetLocation(NewLoc);
	} else
	{
		OriginTransform.SetLocation(NewLoc);
	}
}

