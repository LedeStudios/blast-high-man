// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnOptionChanged_Slate, int32 /* SelectedOptionIndex */);

class PROJECTALPHA_API SOptionSelector : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SOptionSelector) {}
		SLATE_ARGUMENT(TArray<FText>, Options)
		SLATE_ARGUMENT(float, LeftButtonFill)
		SLATE_ARGUMENT(float, ContentFill)
		SLATE_ARGUMENT(float, RightButtonFill)
		SLATE_EVENT(FOnOptionChanged_Slate, OnOptionChanged)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TArray<FText> Options;
	int32 SelectedOptionIndex = 0;

private:
	FOnOptionChanged_Slate OnOptionChanged;

private:
	FReply OnLeftArrowClicked();
	FReply OnRightArrowClicked();

	FText GetSelectedOptionText() const;


private:
	FSlateColor HighlightColor;
	FSlateColor GetHighlightColor() const;

private:
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;
	
};
