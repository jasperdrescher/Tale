// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TalePlayerState.h"

#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TalePowerUpAttributeSet.h"

ATalePlayerState::ATalePlayerState()
{
	CharacterASC = CreateDefaultSubobject<UTaleCharacterASC>("CharacterASC");
	CharacterBaseAttributeSet = CreateDefaultSubobject<UTaleCharacterBaseAttributeSet>("CharacterBaseAttributeSet");
	PowerUpAttributeSet = CreateDefaultSubobject<UTalePowerUpAttributeSet>("PowerUpAttributeSet");
}

UAbilitySystemComponent* ATalePlayerState::GetAbilitySystemComponent() const
{
	return CharacterASC;
}

UTaleCharacterBaseAttributeSet* ATalePlayerState::GetCharacterBaseAttributeSet() const
{
	return CharacterBaseAttributeSet;
}

UTalePowerUpAttributeSet* ATalePlayerState::GetPowerUpAttributeSet() const
{
	return PowerUpAttributeSet;
}
