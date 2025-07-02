// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NPCType.h"

#include "NPCDataRow.generated.h"

USTRUCT(BlueprintType)
struct TALE_API FNPCDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENPCType NPCType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> NPCBlueprint;
};
