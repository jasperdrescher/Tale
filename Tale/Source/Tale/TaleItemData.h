// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "TaleItemType.h"

#include "TaleItemData.generated.h"

USTRUCT(BlueprintType)
struct FTaleItemData : public FTableRowBase
{
	GENERATED_BODY()

	bool operator==(const FTaleItemData& Other) const
	{
		return (Name.ToString() == Other.Name.ToString());
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	bool bIsStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UTexture2D* Thumbnail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	ETaleItemType Type = ETaleItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FVector MeshScale = FVector(1.0f, 1.0f, 1.0f);
};
