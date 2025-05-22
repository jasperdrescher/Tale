// Fill out your copyright notice in the Description page of Project Settings.


#include "TaleCharacterBase.h"
#include "TaleAbilityComponent.h"

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
	return AbilityComponent;
}

UTaleAttributeSet* ATaleCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ATaleCharacterBase::GiveDefaultAbilities()
{
	check(AbilityComponent);

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		AbilityComponent->GiveAbility(AbilitySpec);
	}
}

void ATaleCharacterBase::InitDefaultAttributes() const
{
	if (!AbilityComponent || !DefaultAttributeEffect)
		return;

	FGameplayEffectContextHandle EffectContext = AbilityComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1.f, EffectContext);

	if (SpecHandle.IsValid())
	{
		AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
