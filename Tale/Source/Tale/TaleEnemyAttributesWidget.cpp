// Fill out your copyright notice in the Description page of Project Settings.


#include "TaleEnemyAttributesWidget.h"
#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TaleEnemyCharacter.h"

void UTaleEnemyAttributesWidget::BindToAttributes()
{
	UAbilitySystemComponent* CharacterASC = EnemyCharacter->GetAbilitySystemComponent();
	if (!CharacterASC)
		return;

	const UTaleCharacterBaseAttributeSet* CharacterBaseAttributeSet = EnemyCharacter->GetCharacterBaseAttributeSet();

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
