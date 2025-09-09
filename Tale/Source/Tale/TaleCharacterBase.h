// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"

#include "TaleCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UTaleCharacterASC;
class UTaleCharacterBaseAttributeSet;
class UTalePowerUpAttributeSet;

UCLASS()
class TALE_API ATaleCharacterBase : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ATaleCharacterBase();

	virtual UTaleCharacterBaseAttributeSet* GetCharacterBaseAttributeSet() const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual FGenericTeamId GetGenericTeamId() const override;

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

	UPROPERTY()
	int32 CharacterTeamId = 0;

private:
	UPROPERTY()
	FGenericTeamId GenericTeamId;
};
