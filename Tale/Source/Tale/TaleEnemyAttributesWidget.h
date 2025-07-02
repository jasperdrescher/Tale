// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "TaleEnemyAttributesWidget.generated.h"

class UAbilitySystemComponent;
class UTaleCharacterBaseAttributeSet;

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
