// Copyright Lede Studios. All Rights Reserved.


#include "Widgets/Slate/SOptionSelector.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SOptionSelector::Construct(const FArguments& InArgs)
{
	Options = InArgs._Options;
	OnOptionChanged = InArgs._OnOptionChanged;
	SelectedOptionIndex = 0;

	HighlightColor = FLinearColor::White;

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("NoBorder"))
		[
			SNew(SHorizontalBox)

			// Left Arrow
			+ SHorizontalBox::Slot()
			.FillWidth(InArgs._LeftButtonFill)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Fill)
			[
				SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				.OnClicked(this, &SOptionSelector::OnLeftArrowClicked)
				[
					SNew(STextBlock)
					.Text(FText::FromString("<"))
				]
			]

			// Selected Option
			+ SHorizontalBox::Slot()
			.FillWidth(InArgs._ContentFill)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(this, &SOptionSelector::GetSelectedOptionText)
				.ColorAndOpacity(this, &SOptionSelector::GetHighlightColor)
			]

			// Right Arrow
			+ SHorizontalBox::Slot()
			.FillWidth(InArgs._RightButtonFill)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				.OnClicked(this, &SOptionSelector::OnRightArrowClicked)
				[
					SNew(STextBlock)
					.Text(FText::FromString(">"))
				]
			]
		]
	];
}

FReply SOptionSelector::OnLeftArrowClicked()
{
	if (Options.Num() > 0)
	{
		SelectedOptionIndex = (SelectedOptionIndex - 1 + Options.Num()) % Options.Num();
		OnOptionChanged.ExecuteIfBound(SelectedOptionIndex);
		
		UE_LOG(LogTemp, Warning, TEXT("OptionSelector Left Arrow Clicked."));
	}
	return FReply::Handled();
}

FReply SOptionSelector::OnRightArrowClicked()
{
	if (Options.Num() > 0)
	{
		SelectedOptionIndex = (SelectedOptionIndex + 1) % Options.Num();
		OnOptionChanged.ExecuteIfBound(SelectedOptionIndex);
		
		UE_LOG(LogTemp, Warning, TEXT("OptionSelector Right Arrow Clicked."));
	}
	return FReply::Handled();
}

FText SOptionSelector::GetSelectedOptionText() const
{
	if (Options.Num() > 0 && Options.IsValidIndex(SelectedOptionIndex))
	{
		return Options[SelectedOptionIndex];
	}
	return FText::FromString("No Options");
}

FSlateColor SOptionSelector::GetHighlightColor() const
{
	return HighlightColor;
}

void SOptionSelector::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	HighlightColor = FLinearColor::Yellow;
	SCompoundWidget::OnMouseEnter(MyGeometry, MouseEvent);
}

void SOptionSelector::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	HighlightColor = FLinearColor::White;
	SCompoundWidget::OnMouseLeave(MouseEvent);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
