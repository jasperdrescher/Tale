// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "TaleHUD.generated.h"

class UTaleAttributesWidget;

UCLASS()
class TALE_API ATaleHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void Init();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetRespawnCountdown(float RespawnTimeRemaining);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTaleAttributesWidget> AttributesWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ControlsWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UTaleAttributesWidget> AttributesWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> ControlsWidget;
};
