// Copyright Lede Studios. All Rights Reserved.


#include "OptionSelectorWidget.h"

#include "Widgets/Slate/SOptionSelector.h"

void UOptionSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

TSharedRef<SWidget> UOptionSelectorWidget::RebuildWidget()
{
	OptionSelector = SNew(SOptionSelector)
		.Options(Options)
		.LeftButtonFill(LeftButtonFill)
		.ContentFill(ContentFill)
		.RightButtonFill(RightButtonFill)
		.OnOptionChanged(FOnOptionChanged_Slate::CreateUObject(this, &UOptionSelectorWidget::HandleOptionChanged));
	
	return OptionSelector.ToSharedRef();
}

void UOptionSelectorWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	
	OptionSelector.Reset();
}

void UOptionSelectorWidget::HandleOptionChanged(const int32 SelectedOptionIndex)
{
	OnOptionChanged.Broadcast(SelectedOptionIndex);
}
