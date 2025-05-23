// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TaleCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UTaleAbilityComponent;
class UTaleAttributeSet;

UCLASS()
class TALE_API ATaleCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATaleCharacterBase();

	virtual UTaleAttributeSet* GetAttributeSet() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	void GiveDefaultAbilities();
	void InitDefaultAttributes() const;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY()
	TObjectPtr<UTaleAbilityComponent> AbilityComponent;

	UPROPERTY()
	TObjectPtr<UTaleAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
};
