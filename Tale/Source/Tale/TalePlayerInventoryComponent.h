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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* EquipSwordInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* EquipShieldInputAction;

	UFUNCTION(BlueprintCallable)
	void TryEquipSword();

	UFUNCTION(BlueprintCallable)
	void TryEquipShield();

	UFUNCTION(BlueprintCallable)
	void TryPickUpItem();

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
	class USoundBase* PickupSoundEffect = nullptr;

private:
	class ATalePlayerCharacter* PlayerCharacter = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTalePlayerInventoryWidget> PlayerInventoryWidget;
};
