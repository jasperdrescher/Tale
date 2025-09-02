// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "TaleNPCSpawnPoint.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "TaleGameModeBase.generated.h"

class UTalePerformanceWidget;

UCLASS()
class TALE_API ATaleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATaleGameModeBase();

	void RespawnPlayer(AController* Controller);

	UFUNCTION(BlueprintCallable)
	void PlayerDied(AController* Controller);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTalePerformanceWidget> PerformanceWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ATalePlayerCharacter> PlayerClass;

	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	TArray<ATaleNPCSpawnPoint*> NPCSpawnPoints;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float RespawnDelaySeconds;

private:
	UPROPERTY()
	TObjectPtr<UTalePerformanceWidget> PerformanceWidget;
};
