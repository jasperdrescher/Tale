// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TaleItemType.generated.h"

UENUM(BlueprintType)
enum class ETaleItemType : uint8
{
	None UMETA(DisplayName = "None"),
	Sword UMETA(DisplayName = "Sword"),
	Shield UMETA(DisplayName = "Shield"),
	HealthPotion UMETA(DisplayName = "HealthPotion"),
};
