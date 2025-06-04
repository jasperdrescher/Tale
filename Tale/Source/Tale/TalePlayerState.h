// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "TalePlayerState.generated.h"

class UTaleCharacterASC;
class UTaleCharacterBaseAttributeSet;
class UTalePowerUpAttributeSet;

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

	UTaleCharacterBaseAttributeSet* GetCharacterBaseAttributeSet() const;
	UTalePowerUpAttributeSet* GetPowerUpAttributeSet() const;

protected:
	UPROPERTY()
	TObjectPtr<UTaleCharacterASC> CharacterASC;

	UPROPERTY()
	TObjectPtr<UTaleCharacterBaseAttributeSet> CharacterBaseAttributeSet;

	UPROPERTY()
	TObjectPtr<UTalePowerUpAttributeSet> PowerUpAttributeSet;
};
