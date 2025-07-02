// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
#include "TaleCharacterBase.h"

#include "TaleEnemyCharacter.generated.h"

UCLASS()
class TALE_API ATaleEnemyCharacter : public ATaleCharacterBase
{
	GENERATED_BODY()
	
public:	
	ATaleEnemyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> EnemyAttributesWidgetComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
