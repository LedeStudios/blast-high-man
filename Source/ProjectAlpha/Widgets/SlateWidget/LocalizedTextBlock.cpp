// Copyright Lede Studios. All Rights Reserved.


#include "LocalizedTextBlock.h"

void ULocalizedTextBlock::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();


}

void ULocalizedTextBlock::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	switch (Type)
	{
	case ETextType::Title:
		{
			UpdateFont(FontTable.TitleFont);
			break;
		}
	case ETextType::Description:
		{
			UpdateFont(FontTable.DescriptionFont);
			break;
		}
	case ETextType::Paper:
		{
			UpdateFont(FontTable.PaperFont);
			break;
		}
	}
}

void ULocalizedTextBlock::UpdateFont(const FFontTableContent& Content)
{
	FSlateFontInfo Copy = GetFont();
	
	FSlateFontInfo NewFont = FSlateFontInfo(FontTable.TitleFont.Font, Copy.Size, Copy.TypefaceFontName, Copy.OutlineSettings);
	NewFont.FontMaterial = FontTable.TitleFont.FontMaterial;
	
	NewFont.bForceMonospaced = Copy.bForceMonospaced;
	NewFont.CompositeFont = Copy.CompositeFont;
	NewFont.FontFallback = Copy.FontFallback;
	NewFont.LetterSpacing = Copy.LetterSpacing;
	NewFont.MonospacedWidth = Copy.MonospacedWidth;
	NewFont.SkewAmount = Copy.SkewAmount;

	SetFont(NewFont);
}
