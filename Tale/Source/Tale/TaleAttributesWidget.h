// Fill out your copyright notice in the Description page of Project Settings.

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
	void BindToAttributes();

protected:
	UPROPERTY(BlueprintReadOnly)
	float HealthPercent;

	UPROPERTY(BlueprintReadOnly)
	float StaminaPercent;
};
