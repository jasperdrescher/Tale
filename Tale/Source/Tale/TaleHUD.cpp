// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleHUD.h"
#include "TaleAttributesWidget.h"

void ATaleHUD::Init()
{
	AttributesWidget = CreateWidget<UTaleAttributesWidget>(GetOwningPlayerController(), AttributesWidgetClass);
	AttributesWidget->BindToAttributes();
	AttributesWidget->AddToViewport();
}
