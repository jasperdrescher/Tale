// Fill out your copyright notice in the Description page of Project Settings.


#include "TaleAttributesWidget.h"
#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TalePlayerState.h"

UTaleAttributesWidget::UTaleAttributesWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
	, HealthPercent(0.0f)
	, StaminaPercent(0.0f)
{
}

void UTaleAttributesWidget::BindToAttributes()
{
	const ATalePlayerState* TalePlayerState = Cast<ATalePlayerState>(GetOwningPlayerState());
	if (!TalePlayerState)
		return;

	UAbilitySystemComponent* CharacterASC = TalePlayerState->GetAbilitySystemComponent();
	if (!CharacterASC)
		return;

	const UTaleCharacterBaseAttributeSet* CharacterBaseAttributeSet = TalePlayerState->GetCharacterBaseAttributeSet();

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
