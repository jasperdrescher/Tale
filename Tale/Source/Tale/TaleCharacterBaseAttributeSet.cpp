// Fill out your copyright notice in the Description page of Project Settings.


#include "TaleCharacterBaseAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

UTaleCharacterBaseAttributeSet::UTaleCharacterBaseAttributeSet()
{
}

void UTaleCharacterBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UTaleCharacterBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}

	if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		SetStrength(FMath::Clamp(GetStrength(), 0.f, GetMaxStrength()));
	}

	if (Data.EvaluatedData.Attribute == GetArmorAttribute())
	{
		SetArmor(FMath::Clamp(GetArmor(), 0.f, GetMaxArmor()));
	}
}
