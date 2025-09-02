// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TaleCharacterBase.h"

#include "TalePlayerCharacter.generated.h"

class UStaticMeshComponent;
class USphereComponent;

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

	UStaticMeshComponent* GetSwordMeshComponent() const;
	UStaticMeshComponent* GetShieldMeshComponent() const;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<USphereComponent> MeleeHitbox;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<USphereComponent> SwordHitbox;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UStaticMeshComponent> SwordMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UStaticMeshComponent> ShieldMeshComponent;

private:
	void InitAbilitySystemComponent();
	void InitHUD() const;

	UFUNCTION()
	void OnMeleeHitBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSwordHitBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
