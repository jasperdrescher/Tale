// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TaleEnemyCharacter.h"

#include "TaleEnemyCactusCharacter.generated.h"

UCLASS()
class TALE_API ATaleEnemyCactusCharacter : public ATaleEnemyCharacter
{
	GENERATED_BODY()

public:
	ATaleEnemyCactusCharacter();

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
