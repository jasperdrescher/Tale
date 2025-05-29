// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaleCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "TaleEnemyCharacter.generated.h"

class UTaleEnemyAttributesWidget;

/**
 * 
 */
UCLASS()
class TALE_API ATaleEnemyCharacter : public ATaleCharacterBase
{
	GENERATED_BODY()
	
public:	
	ATaleEnemyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyAttributesWidgetComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
