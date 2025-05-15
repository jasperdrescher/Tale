// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaleCharacterBase.h"
#include "TalePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TALE_API ATalePlayerCharacter : public ATaleCharacterBase
{
	GENERATED_BODY()

public:
	ATalePlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;

private:
	void InitAbilitySystemComponent();
	void InitHUD() const;
};
