// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TaleCharacterBase.h"

#include "TalePlayerCharacter.generated.h"

UCLASS()
class TALE_API ATalePlayerCharacter : public ATaleCharacterBase
{
	GENERATED_BODY()

public:
	ATalePlayerCharacter();

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	UTalePowerUpAttributeSet* GetPowerUpAttributeSet() const;

	UFUNCTION(BlueprintCallable)
	void StartAdventure();

	UFUNCTION(BlueprintCallable)
	void EnableMeleeHitBox();

	UFUNCTION(BlueprintCallable)
	void DisableMeleeHitBox();

	UFUNCTION(BlueprintCallable)
	void EnableSwordHitBox();

	UFUNCTION(BlueprintCallable)
	void DisableSwordHitBox();

	class UStaticMeshComponent* GetSwordMeshComponent() const;
	class UStaticMeshComponent* GetShieldMeshComponent() const;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class USphereComponent* MeleeHitbox;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class USphereComponent* SwordHitbox;

private:
	void InitAbilitySystemComponent();
	void InitHUD() const;
	void OnMeleeHitBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnSwordHitBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	class UStaticMeshComponent* SwordMeshComponent;
	class UStaticMeshComponent* ShieldMeshComponent;
};
