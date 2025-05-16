// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaleCharacterBase.h"
#include "TaleEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TALE_API ATaleEnemyCharacter : public ATaleCharacterBase
{
	GENERATED_BODY()
	
public:	
	ATaleEnemyCharacter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
