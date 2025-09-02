// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleGameModeBase.h"

#include "TalePlayerCharacter.h"
#include "TalePlayerController.h"
#include "TalePerformanceWidget.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Class.h"

ATaleGameModeBase::ATaleGameModeBase()
	: RespawnDelaySeconds(1.0f)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATaleGameModeBase::PlayerDied(AController* Controller)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ASpectatorPawn* SpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(SpectatorClass, Controller->GetPawn()->GetActorTransform(), SpawnParameters);

	Controller->UnPossess();
	Controller->Possess(SpectatorPawn);

	FTimerHandle RespawnTimerHandle;
	FTimerDelegate RespawnDelegate;

	RespawnDelegate = FTimerDelegate::CreateUObject(this, &ATaleGameModeBase::RespawnPlayer, Controller);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDelegate, RespawnDelaySeconds, false);

	ATalePlayerController* PlayerController = Cast<ATalePlayerController>(Controller);
	if (PlayerController)
	{
		PlayerController->SetRespawnCountdown(RespawnDelaySeconds);
	}
}

void ATaleGameModeBase::BeginPlay()
{
	if (PerformanceWidgetClass)
	{
		PerformanceWidget = CreateWidget<UTalePerformanceWidget>(GetWorld(), PerformanceWidgetClass);
		if (PerformanceWidget)
		{
			if (!PerformanceWidget->AddToPlayerScreen())
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to add PerformanceWidget"));
				}
			}
		}
	}

	TArray<AActor*> FoundNPCSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATaleNPCSpawnPoint::StaticClass(), FoundNPCSpawnPoints);
	for (AActor* Actor : FoundNPCSpawnPoints)
	{
		if (ATaleNPCSpawnPoint* NPCSpawnPoint = Cast<ATaleNPCSpawnPoint>(Actor))
		{
			NPCSpawnPoint->FindDataTable();
			NPCSpawnPoint->SpawnNPC();
			NPCSpawnPoints.Emplace(NPCSpawnPoint);
		}
	}

	if (NPCSpawnPoints.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No NPC Spawn Points found."), *FString(__FUNCTION__));
	}
}

void ATaleGameModeBase::RespawnPlayer(AController* Controller)
{
	if (!IsValid(Controller))
	{
		return;
	}

	if (!PlayerClass)
	{
		UE_LOG(LogTemp, Error, TEXT("No player class found."), *FString(__FUNCTION__));
		return;
	}

	if (Controller->IsPlayerController())
	{
		AActor* PlayerStart = FindPlayerStart(Controller);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ATalePlayerCharacter* PlayerCharacter = GetWorld()->SpawnActor<ATalePlayerCharacter>(PlayerClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParameters);

		APawn* OldSpectatorPawn = Controller->GetPawn();
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(PlayerCharacter);

		ATalePlayerController* PC = Cast<ATalePlayerController>(Controller);
		if (PC)
		{
			PC->SetControlRotation(PlayerStart->GetActorRotation());
		}
	}
}
