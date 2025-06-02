// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "TaleEnemyAttributesWidget.generated.h"

class UAbilitySystemComponent;
class UTaleCharacterBaseAttributeSet;

/**
 * 
 */
UCLASS()
class TALE_API UTaleEnemyAttributesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTaleEnemyAttributesWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void BindToAttributes(UAbilitySystemComponent* CharacterASC, const UTaleCharacterBaseAttributeSet* CharacterBaseAttributeSet);

protected:
	UPROPERTY(BlueprintReadOnly)
	float HealthPercent;

	UPROPERTY(BlueprintReadOnly)
	float StaminaPercent;
};
