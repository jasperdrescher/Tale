// Fill out your copyright notice in the Description page of Project Settings.

#include "TalePlayerCharacter.h"
#include "TaleAbilityComponent.h"
#include "TaleAttributeSet.h"
#include "TaleHUD.h"

ATalePlayerCharacter::ATalePlayerCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UTaleAbilityComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UTaleAttributeSet>("AttributeSet");
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
	AbilityComponent->InitAbilityActorInfo(this, this);
	AttributeSet = GetAttributeSet();
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
