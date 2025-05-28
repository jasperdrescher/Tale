// Fill out your copyright notice in the Description page of Project Settings.


#include "TalePowerUpAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

UTalePowerUpAttributeSet::UTalePowerUpAttributeSet()
{
}

void UTalePowerUpAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UTalePowerUpAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
