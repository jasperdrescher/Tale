// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TaleCharacterBase.h"

#include "TalePlayerCharacter.generated.h"

UCLASS()
class TALE_API ATalePlayerCharacter : public ATaleCharacterBase
{
	GENERATED_BODY()

public:
	ATalePlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;

	UTalePowerUpAttributeSet* GetPowerUpAttributeSet() const;

	UFUNCTION(BlueprintCallable)
	void StartAdventure();

private:
	void InitAbilitySystemComponent();
	void InitHUD() const;
};
