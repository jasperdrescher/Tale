// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleLoadingScreenWidget.h"

#include "SlateExtras.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STaleLoadingScreenWidget::Construct(const FArguments& InArgs)
{
	BackgroundTexture = InArgs._BackgroundTexture;
	BackgroundBrush = MakeShareable(new FSlateBrush());
	BackgroundBrush->SetResourceObject(BackgroundTexture);

	ChildSlot
	[
		SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
					.Image(BackgroundTexture ? BackgroundBrush.Get() : nullptr)
					.ColorAndOpacity(FLinearColor::White)
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(10.0f)
			[
				SNew(SThrobber)
					.Visibility(EVisibility::SelfHitTestInvisible)
					.NumPieces(10)
			]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
