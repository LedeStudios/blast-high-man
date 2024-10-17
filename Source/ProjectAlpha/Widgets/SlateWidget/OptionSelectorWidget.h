// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionSelectorWidget.generated.h"

class SOptionSelector;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOptionChanged, int32, SelectedOptionIndex);

UCLASS()
class PROJECTALPHA_API UOptionSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	TSharedPtr<SOptionSelector> OptionSelector;

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

private:
	void HandleOptionChanged(int32 SelectedOptionIndex);

protected:
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnOptionChanged OnOptionChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Option Selector")
	TArray<FText> Options;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Option Selector")
	float LeftButtonFill = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Option Selector")
	float ContentFill = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Option Selector")
	float RightButtonFill = 0.1f;
};
