// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "TaleItemType.h"

#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"

#include "TaleItemData.generated.h"

USTRUCT(BlueprintType)
struct FTaleItemData : public FTableRowBase
{
	GENERATED_BODY()

	FTaleItemData();

	bool operator==(const FTaleItemData& Other) const
	{
		return (Name.ToString() == Other.Name.ToString());
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	ETaleItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMesh* Mesh;
};
