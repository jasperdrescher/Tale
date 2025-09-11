// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
#include "TaleCharacterBase.h"

#include "Perception/AIPerceptionTypes.h"

#include "TaleEnemyCharacter.generated.h"

class AActor;
class USphereComponent;
class UPawnSensingComponent;
class UPrimitiveComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class TALE_API ATaleEnemyCharacter : public ATaleCharacterBase
{
	GENERATED_BODY()
	
public:	
	ATaleEnemyCharacter();

	UFUNCTION(BlueprintCallable)
	void EnableMeleeHitBox();

	UFUNCTION(BlueprintCallable)
	void DisableMeleeHitBox();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void HandleGetHitResponse();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void HandleDieResponse();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayGetHitAnimMontage();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayDieAnimMontage();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnStartedSensingPlayer() {}
	virtual void OnStoppedSensingPlayer() {}

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<USphereComponent> MeleeHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> EnemyAttributesWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	FVector AttributesWidgetOffset = FVector(0.0f, 0.0, 200.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	FVector2D AttributesWidgetSize = FVector2D(400.0f, 400.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName MeleeHitGameplayTagName = "Gameplay.Event.Montage.Enemy.Attack";

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FVector MeleeHitboxOffset = FVector(50.0f, 0.0f, 20.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MeleeHitboxRadius = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SightRadius = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float LossSightRadius = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float PeripheralVisionAngleDegrees = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float MaxStimuliAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	bool bHasSensedPlayer = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	bool bIsDying = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* GetHitAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DieAnimMontage;

private:
	UFUNCTION()
	void OnMeleeHitboxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
