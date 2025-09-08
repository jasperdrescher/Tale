// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TaleEnemyCharacter.h"

#include "TaleEnemySlimeCharacter.generated.h"

UCLASS()
class TALE_API ATaleEnemySlimeCharacter : public ATaleEnemyCharacter
{
	GENERATED_BODY()

public:
	ATaleEnemySlimeCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnStartedSensingPlayer() override;
	virtual void OnStoppedSensingPlayer() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartedSensingPlayer();

	UFUNCTION(BlueprintImplementableEvent)
	void StoppedSensingPlayer();
};
