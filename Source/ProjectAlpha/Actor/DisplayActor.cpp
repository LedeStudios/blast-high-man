// Copyright Lede Studios. All Rights Reserved.


#include "DisplayActor.h"

#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

ADisplayActor::ADisplayActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Scene"));

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(GetRootComponent());

	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent2D");
	SceneCaptureComponent2D->SetupAttachment(GetRootComponent());
	SceneCaptureComponent2D->CaptureSource = SCS_FinalColorLDR;
	SceneCaptureComponent2D->bCaptureEveryFrame = true;
	SceneCaptureComponent2D->bCaptureOnMovement = true;
}

void ADisplayActor::BeginPlay()
{
	Super::BeginPlay();

	// Box->OnComponentBeginOverlap.AddDynamic(this, &ADisplayActor::OnBeginOverlap);
}

void ADisplayActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: 디스플레이 할 위젯에 액터 바인딩
}
