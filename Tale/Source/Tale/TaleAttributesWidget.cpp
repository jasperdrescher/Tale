// Fill out your copyright notice in the Description page of Project Settings.


#include "TaleAttributesWidget.h"
#include "TaleAttributeSet.h"
#include "TalePlayerState.h"

void UTaleAttributesWidget::BindToAttributes()
{
	const ATalePlayerState* TalePlayerState = Cast<ATalePlayerState>(GetOwningPlayerState());
	if (!TalePlayerState)
		return;

	UAbilitySystemComponent* AbilitySystemComponent = TalePlayerState->GetAbilitySystemComponent();
	const UTaleAttributeSet* AttributeSet = TalePlayerState->GetAttributeSet();

	// Initial Attributes
	HealthPercent = NUMERIC_VALUE(AttributeSet, Health) / NUMERIC_VALUE(AttributeSet, MaxHealth);
	StaminaPercent = NUMERIC_VALUE(AttributeSet, Stamina) / NUMERIC_VALUE(AttributeSet, MaxStamina);

	// Attribute Changes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddLambda(
		[this, AttributeSet](const FOnAttributeChangeData& Data)
		{
			HealthPercent = Data.NewValue / NUMERIC_VALUE(AttributeSet, MaxHealth);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddLambda(
		[this, AttributeSet](const FOnAttributeChangeData& Data)
		{
			StaminaPercent = Data.NewValue / NUMERIC_VALUE(AttributeSet, MaxStamina);;
		});
}
