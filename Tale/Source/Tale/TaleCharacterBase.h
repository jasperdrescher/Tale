// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TaleCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UTaleCharacterASC;
class UTaleCharacterBaseAttributeSet;
class UTalePowerUpAttributeSet;

UCLASS()
class TALE_API ATaleCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATaleCharacterBase();

	virtual UTaleCharacterBaseAttributeSet* GetCharacterBaseAttributeSet() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	void GiveDefaultAbilities();
	void GiveDefaultEffects();

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

	UPROPERTY()
	TObjectPtr<UTaleCharacterASC> CharacterASC;

	UPROPERTY()
	TObjectPtr<UTaleCharacterBaseAttributeSet> CharacterBaseAttributeSet;
};
