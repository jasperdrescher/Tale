// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"

#include "TaleEnemyAIController.generated.h"

UCLASS()
class TALE_API ATaleEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
