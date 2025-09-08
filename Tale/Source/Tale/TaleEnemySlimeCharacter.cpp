// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleEnemySlimeCharacter.h"

ATaleEnemySlimeCharacter::ATaleEnemySlimeCharacter()
	: ATaleEnemyCharacter()
{
}

void ATaleEnemySlimeCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATaleEnemySlimeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATaleEnemySlimeCharacter::OnStartedSensingPlayer()
{
	StartedSensingPlayer();
}

void ATaleEnemySlimeCharacter::OnStoppedSensingPlayer()
{
	StoppedSensingPlayer();
}
