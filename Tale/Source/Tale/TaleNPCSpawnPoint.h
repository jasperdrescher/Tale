// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaleNPCType.h"

#include "TaleNPCSpawnPoint.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TALE_API ATaleNPCSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ATaleNPCSpawnPoint();

	void FindDataTable();
	void SpawnNPC();

protected:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETaleNPCType NPCType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> NPCBlueprint;
};
