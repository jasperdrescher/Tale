// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TalePlayerSwordAttackAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystemComponent.h"

UTalePlayerSwordAttackAbility::UTalePlayerSwordAttackAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UTalePlayerSwordAttackAbility::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    if (AttackMontage)
    {
        const int32 RandomSectionIndex = FMath::RandRange(0, AttackAnimSectionNames.Num() - 1);
        const FName RandomSection = AttackAnimSectionNames[RandomSectionIndex];
        UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackMontage, 1.0f, RandomSection);
        MontageTask->OnCompleted.AddDynamic(this, &UTalePlayerSwordAttackAbility::OnCompletedCallback);
        MontageTask->OnInterrupted.AddDynamic(this, &UTalePlayerSwordAttackAbility::OnInterruptedCallback);
        MontageTask->OnCancelled.AddDynamic(this, &UTalePlayerSwordAttackAbility::OnCancelledCallback);
        MontageTask->Activate();
    }

    if (StaminaRecoverEffect)
    {
        UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
        if (!SourceASC)
            return;

        FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
        EffectContext.AddSourceObject(this);

        FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
            StaminaRecoverEffect,
            1.0f,
            EffectContext
        );

        if (SpecHandle.IsValid())
        {
            FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
            if (Spec)
            {
                const float DurationValue = 3.0f;
                Spec->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Gameplay.Magnitude.Duration"), DurationValue);
            }

            SourceASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
        }
    }

    // Listen for the damage trigger event (from anim notify or overlap)
    const FGameplayTag DamageEventTag = FGameplayTag::RequestGameplayTag("Event.Player.Sword.DamageTrigger");
    UAbilityTask_WaitGameplayEvent* WaitForEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
        this, DamageEventTag, nullptr, false, false);
    WaitForEvent->EventReceived.AddDynamic(this, &UTalePlayerSwordAttackAbility::OnDamageEvent);
    WaitForEvent->Activate();
}

void UTalePlayerSwordAttackAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UTalePlayerSwordAttackAbility::OnCompletedCallback()
{
    bool bReplicatedEndAbility = false;
    bool bWasCancelled = false;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UTalePlayerSwordAttackAbility::OnInterruptedCallback()
{
    bool bReplicatedEndAbility = false;
    bool bWasCancelled = true;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UTalePlayerSwordAttackAbility::OnCancelledCallback()
{
    bool bReplicatedEndAbility = false;
    bool bWasCancelled = true;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UTalePlayerSwordAttackAbility::OnDamageEvent(FGameplayEventData Payload)
{
    if (!DamageEffect)
        return;

    const AActor* TargetActor = Payload.Target;
    if (!TargetActor)
        return;

    GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectToTarget(DamageEffect->GetDefaultObject<UGameplayEffect>(), GetAbilitySystemComponentFromActorInfo(), 1.0f);
}
