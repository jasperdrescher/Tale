// Fill out your copyright notice in the Description page of Project Settings.


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
