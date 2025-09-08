// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleEnemyMushroomCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ATaleEnemyMushroomCharacter::ATaleEnemyMushroomCharacter()
	: ATaleEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATaleEnemyMushroomCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATaleEnemyMushroomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHasSensedPlayer)
	{
		const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (!PlayerPawn)
			return;

		const FVector CurrentLocation = GetActorLocation();
		const FVector TargetLocation = PlayerPawn->GetActorLocation();
		const FRotator CurrentRotation = GetActorRotation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);
		TargetRotation.Pitch = 0.0f;
		TargetRotation.Roll = 0.0f;
		
		const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, TargetRotationSpeed);
		SetActorRotation(NewRotation);
	}
}

void ATaleEnemyMushroomCharacter::OnStartedSensingPlayer()
{
	GetWorld()->GetTimerManager().ClearTimer(StoppedSensingTimerHandle);

	bIsAwake = true;
	WakeUp();
}

void ATaleEnemyMushroomCharacter::OnStoppedSensingPlayer()
{
	GetWorld()->GetTimerManager().SetTimer(
		StoppedSensingTimerHandle,
		this,
		&ATaleEnemyMushroomCharacter::OnStoppedSensingTimerExpired,
		StoppedSensingTimer,
		false
	);
}

void ATaleEnemyMushroomCharacter::OnStoppedSensingTimerExpired()
{
	bIsAwake = false;
	Sleep();
}
