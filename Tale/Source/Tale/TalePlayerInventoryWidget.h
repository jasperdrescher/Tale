// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "TaleItemData.h"

#include "TalePlayerInventoryWidget.generated.h"

UCLASS()
class TALE_API UTalePlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void ReloadInventory(const TArray<FTaleItemData>& ItemData);
};
