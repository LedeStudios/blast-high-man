// Copyright Lede Studios. All Rights Reserved.


#include "PaperWidget.h"

void UPaperWidget::SetPaperTexture(UTexture2D* InTexture)
{
	PaperTexture = InTexture;
	OnPaperTextureUpdate(PaperTexture.Get());
}
