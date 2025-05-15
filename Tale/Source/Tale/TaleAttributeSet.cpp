// Fill out your copyright notice in the Description page of Project Settings.

#include "TaleAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

UTaleAttributeSet::UTaleAttributeSet()
{
	InitHealth(80.f);
}

void UTaleAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UTaleAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}
