// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleCharacterBase.h"
#include "TaleCharacterASC.h"

// Sets default values
ATaleCharacterBase::ATaleCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void ATaleCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATaleCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ATaleCharacterBase::GetAbilitySystemComponent() const
{
	return CharacterASC;
}

UTaleCharacterBaseAttributeSet* ATaleCharacterBase::GetCharacterBaseAttributeSet() const
{
	return CharacterBaseAttributeSet;
}

void ATaleCharacterBase::GiveDefaultAbilities()
{
	check(CharacterASC);

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		CharacterASC->GiveAbility(AbilitySpec);
	}
}

void ATaleCharacterBase::GiveDefaultEffects()
{
	check(CharacterASC);

	FGameplayEffectContextHandle EffectContext = CharacterASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : DefaultEffects)
	{
		const FGameplayEffectSpecHandle SpecHandle = CharacterASC->MakeOutgoingSpec(GameplayEffect, 1.f, EffectContext);
		if (SpecHandle.IsValid())
		{
			CharacterASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}
