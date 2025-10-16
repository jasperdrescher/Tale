// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class TALE_API STaleLoadingScreenWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STaleLoadingScreenWidget)
		: _BackgroundTexture(nullptr)
	{}
	SLATE_ARGUMENT(UTexture2D*, BackgroundTexture)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	UTexture2D* BackgroundTexture;
	TSharedPtr<FSlateBrush> BackgroundBrush;
};
