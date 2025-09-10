// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "TaleNPCSpawnPoint.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GenericTeamAgentInterface.h"

#include "TaleGameModeBase.generated.h"

class UTalePerformanceWidget;
class ATaleEnemyCharacter;

UCLASS()
class TALE_API ATaleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATaleGameModeBase();

	static ETeamAttitude::Type TeamAttitudeSolver(FGenericTeamId GenericTeamIdA, FGenericTeamId GenericTeamIdB);

	void RespawnPlayer(AController* Controller);

	UFUNCTION(BlueprintCallable)
	void PlayerDied(AController* Controller);

	UFUNCTION(BlueprintCallable)
	void LimitFPS();

	UFUNCTION(BlueprintCallable)
	void RemoveFPSLimit();

	UFUNCTION(BlueprintImplementableEvent)
	void LevelCleared();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTalePerformanceWidget> PerformanceWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ATalePlayerCharacter> PlayerClass;

	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	TArray<ATaleNPCSpawnPoint*> NPCSpawnPoints;

	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	TArray<ATaleEnemyCharacter*> SpawnedNPCs;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float RespawnDelaySeconds = 1.0f;

private:
	UFUNCTION()
	void OnSpawnedNPCDestroyed(AActor* DestroyedActor);

	UPROPERTY()
	TObjectPtr<UTalePerformanceWidget> PerformanceWidget;
};
