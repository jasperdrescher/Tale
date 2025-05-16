// Fill out your copyright notice in the Description page of Project Settings.


#include "TaleEnemyCharacter.h"
#include "TaleAbilityComponent.h"
#include "TaleAttributeSet.h"

ATaleEnemyCharacter::ATaleEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilityComponent = CreateDefaultSubobject<UTaleAbilityComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UTaleAttributeSet>("AttributeSet");
}

void ATaleEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilityComponent->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
	InitDefaultAttributes();
}
