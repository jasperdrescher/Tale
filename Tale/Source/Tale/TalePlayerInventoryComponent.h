// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TalePlayerInventoryWidget.h"
#include "TaleItemData.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"

#include "TalePlayerInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemSearchResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bFound;

	UPROPERTY(BlueprintReadOnly)
	FTaleItemData Item;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TALE_API UTalePlayerInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTalePlayerInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TryEquipSword();

	UFUNCTION(BlueprintCallable)
	void TryEquipShield();

	UFUNCTION(BlueprintCallable)
	void TryPickUpItem();

	UFUNCTION(BlueprintCallable)
	void RemoveItem(const FTaleItemData& ItemData);

	UFUNCTION(BlueprintCallable)
	FItemSearchResult GetHealthPotion();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UTalePlayerInventoryWidget> PlayerInventoryWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FTaleItemData> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bHasShield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bHasSword;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	class USoundBase* PickupSoundEffect;

private:
	class ATalePlayerCharacter* PlayerCharacter;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTalePlayerInventoryWidget> PlayerInventoryWidget;
};
