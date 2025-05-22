// Fill out your copyright notice in the Description page of Project Settings.

#include "TalePlayerCharacter.h"
#include "TaleAbilityComponent.h"
#include "TaleAttributeSet.h"
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
	InitDefaultAttributes();
	InitHUD();
}

void ATalePlayerCharacter::InitAbilitySystemComponent()
{
	ATalePlayerState* TalePlayerState = GetPlayerState<ATalePlayerState>();
	check(TalePlayerState);
	AbilityComponent = CastChecked<UTaleAbilityComponent>(TalePlayerState->GetAbilitySystemComponent());
	AbilityComponent->InitAbilityActorInfo(TalePlayerState, this);
	AttributeSet = TalePlayerState->GetAttributeSet();
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
