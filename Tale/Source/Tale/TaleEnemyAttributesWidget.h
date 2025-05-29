// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "TaleEnemyAttributesWidget.generated.h"

class ATaleEnemyCharacter;

/**
 * 
 */
UCLASS()
class TALE_API UTaleEnemyAttributesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void BindToAttributes();

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TObjectPtr<ATaleEnemyCharacter> EnemyCharacter;

protected:
	UPROPERTY(BlueprintReadOnly)
	float HealthPercent;

	UPROPERTY(BlueprintReadOnly)
	float StaminaPercent;
};
