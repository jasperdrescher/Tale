// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleEnemyCactusCharacter.h"

ATaleEnemyCactusCharacter::ATaleEnemyCactusCharacter()
	: ATaleEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATaleEnemyCactusCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATaleEnemyCactusCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATaleEnemyCactusCharacter::OnStartedSensingPlayer()
{
	StartedSensingPlayer();
}

void ATaleEnemyCactusCharacter::OnStoppedSensingPlayer()
{
	StoppedSensingPlayer();
}
