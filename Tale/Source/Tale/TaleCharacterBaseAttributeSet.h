// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "TaleCharacterBaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define NUMERIC_VALUE(AttributeSetName, PropertyName) \
	AttributeSetName->Get##PropertyName##Attribute().GetNumericValue(AttributeSetName)

/**
 * 
 */
UCLASS()
class TALE_API UTaleCharacterBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UTaleCharacterBaseAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTaleCharacterBaseAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTaleCharacterBaseAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UTaleCharacterBaseAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS(UTaleCharacterBaseAttributeSet, MaxArmor);

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UTaleCharacterBaseAttributeSet, Damage);

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UTaleCharacterBaseAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UTaleCharacterBaseAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UTaleCharacterBaseAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData MaxStrength;
	ATTRIBUTE_ACCESSORS(UTaleCharacterBaseAttributeSet, MaxStrength);
};
