// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TalePlayerController.h"

#include "TaleHUD.h"

void ATalePlayerController::SetRespawnCountdown(float RespawnTimeRemaining)
{
	ATaleHUD* HUD = Cast<ATaleHUD>(GetHUD());
	if (HUD)
	{
		HUD->SetRespawnCountdown(RespawnTimeRemaining);
	}
}
