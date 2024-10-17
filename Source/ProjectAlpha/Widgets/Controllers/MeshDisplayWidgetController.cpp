// Copyright Lede Studios. All Rights Reserved.


#include "MeshDisplayWidgetController.h"

#include "Player/PA_HUD.h"
#include "Widgets/MeshDisplayWidget.h"

void UMeshDisplayWidgetController::Init(const APA_HUD* HUD)
{
	Widget = CreateWidget<UMeshDisplayWidget>(GetWorld(), WidgetClass);
}
