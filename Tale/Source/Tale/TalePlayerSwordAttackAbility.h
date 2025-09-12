// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "Abilities/GameplayAbility.h"
#include "CoreMinimal.h"

#include "TalePlayerSwordAttackAbility.generated.h"

UCLASS()
class TALE_API UTalePlayerSwordAttackAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
    UTalePlayerSwordAttackAbility();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    UFUNCTION()
    void OnCompletedCallback();

    UFUNCTION()
    void OnInterruptedCallback();

    UFUNCTION()
    void OnCancelledCallback();

    UFUNCTION()
    void OnDamageEvent(FGameplayEventData Payload);

    UPROPERTY(EditDefaultsOnly, Category = "Ability|Animation")
    UAnimMontage* AttackMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Ability|Animation")
    TArray<FName> AttackAnimSectionNames;

    UPROPERTY(EditDefaultsOnly, Category = "Ability|Effects")
    TSubclassOf<UGameplayEffect> DamageEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Ability|Effects")
    TSubclassOf<UGameplayEffect> StaminaRecoverEffect;
};
