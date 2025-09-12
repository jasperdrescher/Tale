// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleEnemyMushroomCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ATaleEnemyMushroomCharacter::ATaleEnemyMushroomCharacter()
	: ATaleEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATaleEnemyMushroomCharacter::LookAtPlayer()
{
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn)
		return;

	const FVector CurrentLocation = GetActorLocation();
	const FVector TargetLocation = PlayerPawn->GetActorLocation();
	const FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);
	TargetRotation.Pitch = FMath::Clamp(TargetRotation.Pitch, 0.0f, MaxPitchAngle);
	TargetRotation.Roll = 0.0f;

	SetActorRotation(TargetRotation);
}

void ATaleEnemyMushroomCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnDestroyed.AddDynamic(this, &ATaleEnemyMushroomCharacter::OnActorDestroyed);
}

void ATaleEnemyMushroomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATaleEnemyMushroomCharacter::OnStartedSensingPlayer()
{
	GetWorld()->GetTimerManager().ClearTimer(StoppedSensingTimerHandle);

	if (!bIsAwake)
	{
		bIsAwake = true;
		WakeUp();
	}
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

void ATaleEnemyMushroomCharacter::OnActorDestroyed(AActor* DestroyedActor)
{
	const FVector SpawnLocation = GetActorLocation();
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.Instigator = GetInstigator();

	GetWorld()->SpawnActor<AActor>(
		PickupClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);
}
