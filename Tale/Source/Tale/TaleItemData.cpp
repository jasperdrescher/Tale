// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleItemData.h"

FTaleItemData::FTaleItemData()
	: bIsStackable(false)
	, Quantity(1)
	, Type(ETaleItemType::None)
	, Mesh(nullptr)
	, Thumbnail(nullptr)
{
}
