// Copyright Lede Studios. All Rights Reserved.


#include "PA_HUD.h"

#include "Widgets/Controllers/MeshDisplayWidgetController.h"

void APA_HUD::BeginPlay()
{
	Super::BeginPlay();

	MeshDisplayWidgetController = NewObject<UMeshDisplayWidgetController>(this);
	MeshDisplayWidgetController->Init(this);
}
