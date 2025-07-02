// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TaleNPCSpawnPoint.h"

#include "TaleGameModeBase.generated.h"

UCLASS()
class TALE_API ATaleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATaleGameModeBase();

	UFUNCTION(BlueprintCallable)
	void PlayerDied(AController* Controller);

protected:
	virtual void BeginPlay() override;

	void RespawnPlayer(AController* Controller);

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ATalePlayerCharacter> PlayerClass;

	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	TArray<ATaleNPCSpawnPoint*> NPCSpawnPoints;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float RespawnDelaySeconds;
};
