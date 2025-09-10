// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaleNPCType.h"

#include "TaleNPCSpawnPoint.generated.h"

class ATaleEnemyCharacter;

UCLASS(Blueprintable, BlueprintType)
class TALE_API ATaleNPCSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ATaleNPCSpawnPoint();

	void FindDataTable();
	ATaleEnemyCharacter* SpawnNPC();

protected:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETaleNPCType NPCType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> NPCBlueprint;
};
