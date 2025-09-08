// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
#include "TaleCharacterBase.h"

#include "TaleEnemyCharacter.generated.h"

class USphereComponent;

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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<USphereComponent> MeleeHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> EnemyAttributesWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName MeleeHitGameplayTagName = "Gameplay.Event.Montage.Enemy.Attack";

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FVector MeleeHitboxOffset = FVector(50.0f, 0.0f, 20.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MeleeHitboxRadius = 100.0f;

private:
	UFUNCTION()
	void OnMeleeHitboxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
