// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TalePlayerInventoryWidget.h"
#include "TaleItemData.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"

#include "TalePlayerInventoryComponent.generated.h"

class UInputAction;
class USoundBase;
class ATalePlayerCharacter;

USTRUCT(BlueprintType)
struct FItemSearchResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bFound = false;

	UPROPERTY(BlueprintReadOnly)
	FTaleItemData Item;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALE_API UTalePlayerInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTalePlayerInventoryComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TryEquipSword();

	UFUNCTION(BlueprintCallable)
	void TryEquipShield();

	UFUNCTION(BlueprintCallable)
	void TryPickUpItem();

	void OnToggleInventoryAction();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* EquipSwordInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* EquipShieldInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* PickUpInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ToggleInventoryInputAction;

protected:
	UFUNCTION(BlueprintCallable)
	void RemoveItem(const FTaleItemData& ItemData);

	UFUNCTION(BlueprintCallable)
	FItemSearchResult GetHealthPotion() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UTalePlayerInventoryWidget> PlayerInventoryWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FTaleItemData> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bHasShield = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bHasSword = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundBase* PickupSoundEffect = nullptr;

private:
	ATalePlayerCharacter* PlayerCharacter = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTalePlayerInventoryWidget> PlayerInventoryWidget;
};
