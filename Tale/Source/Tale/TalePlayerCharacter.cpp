// Fill out your copyright notice in the Description page of Project Settings.

#include "TalePlayerCharacter.h"
#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TalePowerUpAttributeSet.h"
#include "TalePlayerState.h"
#include "TaleHUD.h"

ATalePlayerCharacter::ATalePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATalePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
	GiveDefaultEffects();
	InitHUD();
}

void ATalePlayerCharacter::InitAbilitySystemComponent()
{
	ATalePlayerState* TalePlayerState = GetPlayerState<ATalePlayerState>();
	check(TalePlayerState);
	CharacterASC = CastChecked<UTaleCharacterASC>(TalePlayerState->GetAbilitySystemComponent());
	CharacterASC->InitAbilityActorInfo(TalePlayerState, this);
	CharacterBaseAttributeSet = TalePlayerState->GetCharacterBaseAttributeSet();
}

void ATalePlayerCharacter::InitHUD() const
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ATaleHUD* TaleHUD = Cast<ATaleHUD>(PlayerController->GetHUD()))
		{
			TaleHUD->Init();
		}
	}
}

UTalePowerUpAttributeSet* ATalePlayerCharacter::GetPowerUpAttributeSet() const
{
	const ATalePlayerState* TalePlayerState = GetPlayerState<ATalePlayerState>();
	return CastChecked<UTalePowerUpAttributeSet>(TalePlayerState->GetPowerUpAttributeSet());
}
