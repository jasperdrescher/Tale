// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TaleEnemyCharacter.h"
#include "TaleItemPickup.h"

#include "TaleEnemyMushroomCharacter.generated.h"

UCLASS()
class TALE_API ATaleEnemyMushroomCharacter : public ATaleEnemyCharacter
{
	GENERATED_BODY()

public:
	ATaleEnemyMushroomCharacter();

	UFUNCTION(BlueprintCallable)
	void LookAtPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnStartedSensingPlayer() override;
	virtual void OnStoppedSensingPlayer() override;

	UFUNCTION(BlueprintImplementableEvent)
	void WakeUp();

	UFUNCTION(BlueprintImplementableEvent)
	void Sleep();

	UPROPERTY(EditAnywhere, Category = "Pickup")
	TSubclassOf<ATaleItemPickup> PickupClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	float StoppedSensingTimer = 4.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	float TargetRotationSpeed = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	float MaxPitchAngle = 26.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	bool bIsAwake = false;

private:
	UFUNCTION()
	void OnStoppedSensingTimerExpired();

	UFUNCTION()
	void OnActorDestroyed(AActor* DestroyedActor);

	UPROPERTY()
	FTimerHandle StoppedSensingTimerHandle;
};
