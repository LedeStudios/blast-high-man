// Copyright Lede Studios. All Rights Reserved.


#include "ScreenFadeSubsystem.h"

#include "Animation/UMGSequencePlayer.h"
#include "Widgets/FadeWidget.h"

void UScreenFadeSubsystem::FadeIn()
{
	Fade(false);
}

void UScreenFadeSubsystem::FadeOut()
{
	Fade(true);
}

void UScreenFadeSubsystem::Fade(const bool bIsFadeOut)
{
	if (WidgetClass)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
			Widget = nullptr;
		}
		
		Widget = CreateWidget<UFadeWidget>(GetWorld(), WidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();

			if (UWidgetAnimation* Anim = bIsFadeOut ? FadeOutAnim : FadeInAnim)
			{
				if (UUMGSequencePlayer* AnimPlayer = Widget->PlayAnimation(Anim))
				{
					if (!AnimPlayer->OnSequenceFinishedPlaying().IsBoundToObject(this))
					{
						AnimPlayer->OnSequenceFinishedPlaying().AddLambda([this](UUMGSequencePlayer& Player)
						{
							Widget->RemoveFromParent();
							Widget = nullptr;
						});
					}
				}
			}
		}
	}
}
