// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TaleHUD.generated.h"

class UTaleAttributesWidget;

/**
 * 
 */
UCLASS()
class TALE_API ATaleHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void Init();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTaleAttributesWidget> AttributesWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UTaleAttributesWidget> AttributesWidget;
};
