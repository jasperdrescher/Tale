// Fill out your copyright notice in the Description page of Project Settings.


#include "TalePlayerState.h"
#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"

ATalePlayerState::ATalePlayerState()
{
	CharacterASC = CreateDefaultSubobject<UTaleCharacterASC>("CharacterASC");
	CharacterBaseAttributeSet = CreateDefaultSubobject<UTaleCharacterBaseAttributeSet>("CharacterBaseAttributeSet");
}

UAbilitySystemComponent* ATalePlayerState::GetAbilitySystemComponent() const
{
	return CharacterASC;
}

UTaleCharacterBaseAttributeSet* ATalePlayerState::GetCharacterBaseAttributeSet() const
{
	return CharacterBaseAttributeSet;
}
