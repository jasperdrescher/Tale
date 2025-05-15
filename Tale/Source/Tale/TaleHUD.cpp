// Fill out your copyright notice in the Description page of Project Settings.

#include "TaleHUD.h"
#include "TaleAttributesWidget.h"

void ATaleHUD::Init()
{
	AttributesWidget = CreateWidget<UTaleAttributesWidget>(GetOwningPlayerController(), AttributesWidgetClass);
	AttributesWidget->BindToAttributes();
	AttributesWidget->AddToViewport();
}
