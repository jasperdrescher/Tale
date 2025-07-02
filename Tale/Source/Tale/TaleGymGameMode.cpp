// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleGymGameMode.h"

#include "TalePlayerCharacter.h"

#include <Kismet/GameplayStatics.h>

ATaleGymGameMode::ATaleGymGameMode()
	: ATaleGameModeBase()
{
}

void ATaleGymGameMode::BeginPlay()
{
	Super::BeginPlay();

	ATalePlayerCharacter* PlayerCharacter = Cast<ATalePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		PlayerCharacter->StartAdventure();
	}
}
