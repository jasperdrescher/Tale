// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "TalePlayerState.generated.h"

class UTaleAbilityComponent;
class UTaleAttributeSet;

/**
 * 
 */
UCLASS()
class TALE_API ATalePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ATalePlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UTaleAttributeSet* GetAttributeSet() const;

protected:
	UPROPERTY()
	TObjectPtr<UTaleAbilityComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UTaleAttributeSet> AttributeSet;
};
