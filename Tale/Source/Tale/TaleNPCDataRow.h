// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TaleNPCType.h"

#include "TaleNPCDataRow.generated.h"

USTRUCT(BlueprintType)
struct TALE_API FTaleNPCDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETaleNPCType NPCType = ETaleNPCType::Slime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> NPCBlueprint;
};
