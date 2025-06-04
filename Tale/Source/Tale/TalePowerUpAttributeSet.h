// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "TalePowerUpAttributeSet.generated.h"

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
class TALE_API UTalePowerUpAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UTalePowerUpAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData PowerUpHeal;
	ATTRIBUTE_ACCESSORS(UTalePowerUpAttributeSet, PowerUpHeal);

	UPROPERTY(BlueprintReadOnly, Category = "Ability | Gameplay Attribute")
	FGameplayAttributeData PowerUpStamina;
	ATTRIBUTE_ACCESSORS(UTalePowerUpAttributeSet, PowerUpStamina);
};
