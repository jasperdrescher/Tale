// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "NPCType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ENPCType : uint8
{
	Slime UMETA(DisplayName = "Slime"),
	Mushroom UMETA(DisplayName = "Mushroom"),
	Cactus UMETA(DisplayName = "Cactus"),
};
