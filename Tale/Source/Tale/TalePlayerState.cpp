// Fill out your copyright notice in the Description page of Project Settings.


#include "TalePlayerState.h"
#include "TaleAbilityComponent.h"
#include "TaleAttributeSet.h"

ATalePlayerState::ATalePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTaleAbilityComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UTaleAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ATalePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UTaleAttributeSet* ATalePlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
