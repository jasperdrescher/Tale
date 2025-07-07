// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TalePlayerInventoryWidget.generated.h"

UCLASS()
class TALE_API UTalePlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Inventory")
	void ReloadInventory(class UTalePlayerInventoryComponent* PlayerInventoryComponent);
};
