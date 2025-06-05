// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleEnemyCharacter.h"
#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TaleEnemyAttributesWidget.h"

ATaleEnemyCharacter::ATaleEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterASC = CreateDefaultSubobject<UTaleCharacterASC>("CharacterASC");
	CharacterBaseAttributeSet = CreateDefaultSubobject<UTaleCharacterBaseAttributeSet>("CharacterBaseAttributeSet");

    EnemyAttributesWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyAttributesWidgetComponent"));
    EnemyAttributesWidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	EnemyAttributesWidgetComponent->SetBlendMode(EWidgetBlendMode::Transparent);
}

void ATaleEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterASC->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
	GiveDefaultEffects();

	if (UTaleEnemyAttributesWidget* EnemyAttributesWidget = Cast<UTaleEnemyAttributesWidget>(EnemyAttributesWidgetComponent->GetWidget()))
	{
		EnemyAttributesWidget->BindToAttributes(CharacterASC, CharacterBaseAttributeSet);
	}
}
