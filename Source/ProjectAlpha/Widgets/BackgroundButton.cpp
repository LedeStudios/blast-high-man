// Copyright Lede Studios. All Rights Reserved.


#include "BackgroundButton.h"

#include "Kismet/GameplayStatics.h"

UBackgroundButton::UBackgroundButton()
{
	FButtonStyle Style = GetStyle();
	Style.Normal.DrawAs = ESlateBrushDrawType::Box;
	Style.Normal.TintColor = FColor::White;
	
	Style.Hovered.DrawAs = ESlateBrushDrawType::Box;
	Style.Hovered.TintColor = FColor::White;
	
	Style.Pressed.DrawAs = ESlateBrushDrawType::Box;
	Style.Pressed.TintColor = FColor::White;
	
	SetStyle(Style);
}

void UBackgroundButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!OnClicked.IsAlreadyBound(this, &UBackgroundButton::Click))
	{
		OnClicked.AddDynamic(this, &UBackgroundButton::Click);
	}
	
	if (!OnHovered.IsAlreadyBound(this, &UBackgroundButton::Hover))
	{
		OnHovered.AddDynamic(this, &UBackgroundButton::Hover);
	}

	if (!OnUnhovered.IsAlreadyBound(this, &UBackgroundButton::Unhover))
	{
		OnUnhovered.AddDynamic(this, &UBackgroundButton::Unhover);
	}

	UpdateBackgroundAlphaToUnhovered();
}

void UBackgroundButton::Select(const bool InSelected)
{
	bIsSelected = InSelected;
	bIsSelected ? UpdateBackgroundAlphaToHovered() : UpdateBackgroundAlphaToUnhovered();
}

bool UBackgroundButton::IsSelected()
{
	return bIsSelected;
}

void UBackgroundButton::Click()
{
	if (ClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound);
	}
}

void UBackgroundButton::Hover()
{
	if (HoverSound)
	{
		UGameplayStatics::PlaySound2D(this, HoverSound);
	}

	if (!bIsSelected)
	{
		UpdateBackgroundAlphaToHovered();
	}
}

void UBackgroundButton::Unhover()
{
	if (!bIsSelected)
	{
		UpdateBackgroundAlphaToUnhovered();
	}
}

void UBackgroundButton::UpdateBackgroundAlphaToHovered()
{
	SetBackgroundColor(HoveredBackgroundColor.WithAlpha(255 * HoveredBackgroundAlpha));
}

void UBackgroundButton::UpdateBackgroundAlphaToUnhovered()
{
	SetBackgroundColor(HoveredBackgroundColor.WithAlpha(255 * UnhoveredBackgroundAlpha));
}
