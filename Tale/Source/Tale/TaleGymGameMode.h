// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TaleGameModeBase.h"

#include "TaleGymGameMode.generated.h"

UCLASS()
class TALE_API ATaleGymGameMode : public ATaleGameModeBase
{
	GENERATED_BODY()
	
public:
	ATaleGymGameMode();

protected:
	virtual void BeginPlay() override;

};
