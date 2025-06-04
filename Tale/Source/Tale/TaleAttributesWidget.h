// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "TaleAttributesWidget.generated.h"

/**
 * 
 */
UCLASS()
class TALE_API UTaleAttributesWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTaleAttributesWidget(const FObjectInitializer& ObjectInitializer);

	void BindToAttributes();

protected:
	UPROPERTY(BlueprintReadOnly)
	float HealthPercent;

	UPROPERTY(BlueprintReadOnly)
	float StaminaPercent;
};
