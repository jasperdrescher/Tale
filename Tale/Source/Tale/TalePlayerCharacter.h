// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "TaleCharacterBase.h"

#include "TalePlayerCharacter.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UCapsuleComponent;
class UInputComponent;
class UInputMappingContext;

UCLASS()
class TALE_API ATalePlayerCharacter : public ATaleCharacterBase
{
	GENERATED_BODY()

public:
	ATalePlayerCharacter();

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

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
	TObjectPtr<UCapsuleComponent> SwordHitbox;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<USphereComponent> ShieldHitbox;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UStaticMeshComponent> SwordMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UStaticMeshComponent> ShieldMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName WeaponRSocketName = "Weapon_R";

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName WeaponLSocketName = "Weapon_L";

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FRotator SwordMeshRotation = FRotator(0.0f, 0.0f, -90.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FRotator ShieldMeshRotation = FRotator(0.0f, 90.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FVector ShieldMeshLocation = FVector(14.0f, 0.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FVector SwordHitboxLocation = FVector(0.0f, -60.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FRotator SwordHitboxRotation = FRotator(0.0f, 0.0f, 90.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float SwordHitboxRadius = 22.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float SwordHitboxHalfHeight = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName SwordHitGameplayTagName = "Gameplay.Event.Montage.Player.SwordAttack";

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName MeleeHitGameplayTagName = "Gameplay.Event.Montage.Player.MeleeAttack";

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName ShieldHitGameplayTagName = "Gameplay.Event.Montage.Player.ShieldHit";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

private:
	void InitAbilitySystemComponent();
	void InitHUD() const;

	UFUNCTION()
	void OnMeleeHitboxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSwordHitboxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnShieldHitboxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
