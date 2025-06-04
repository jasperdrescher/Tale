// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleEnemyAttributesWidget.h"
#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TaleEnemyCharacter.h"

UTaleEnemyAttributesWidget::UTaleEnemyAttributesWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
	, HealthPercent(0.0f)
	, StaminaPercent(0.0f)
{
}

void UTaleEnemyAttributesWidget::BindToAttributes(UAbilitySystemComponent* CharacterASC, const UTaleCharacterBaseAttributeSet* CharacterBaseAttributeSet)
{
	// Initial Attributes
	HealthPercent = NUMERIC_VALUE(CharacterBaseAttributeSet, Health) / NUMERIC_VALUE(CharacterBaseAttributeSet, MaxHealth);
	StaminaPercent = NUMERIC_VALUE(CharacterBaseAttributeSet, Stamina) / NUMERIC_VALUE(CharacterBaseAttributeSet, MaxStamina);

	// Attribute Changes
	CharacterASC->GetGameplayAttributeValueChangeDelegate(CharacterBaseAttributeSet->GetHealthAttribute()).AddLambda(
		[this, CharacterBaseAttributeSet](const FOnAttributeChangeData& Data)
		{
			HealthPercent = Data.NewValue / NUMERIC_VALUE(CharacterBaseAttributeSet, MaxHealth);
		});

	CharacterASC->GetGameplayAttributeValueChangeDelegate(CharacterBaseAttributeSet->GetStaminaAttribute()).AddLambda(
		[this, CharacterBaseAttributeSet](const FOnAttributeChangeData& Data)
		{
			StaminaPercent = Data.NewValue / NUMERIC_VALUE(CharacterBaseAttributeSet, MaxStamina);;
		});
}
