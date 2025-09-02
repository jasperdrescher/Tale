// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TaleGameModeBase.h"

#include "TaleMainGameMode.generated.h"

UCLASS()
class TALE_API ATaleMainGameMode : public ATaleGameModeBase
{
	GENERATED_BODY()

public:
	ATaleMainGameMode();

protected:
	virtual void BeginPlay() override;
};
