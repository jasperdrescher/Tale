// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TaleNPCSpawnPoint.h"
#include "TaleMainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TALE_API ATaleMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATaleMainGameMode();

	void PlayerDied(AController* Controller);

protected:
	virtual void BeginPlay() override;

	void RespawnPlayer(AController* Controller);

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ATalePlayerCharacter> PlayerClass;
	TArray<ATaleNPCSpawnPoint*> NPCSpawnPoints;
	float RespawnDelaySeconds;
};
