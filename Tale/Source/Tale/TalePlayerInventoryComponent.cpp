// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TalePlayerInventoryComponent.h"

#include "TaleItemPickup.h"
#include "TalePlayerCharacter.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

UTalePlayerInventoryComponent::UTalePlayerInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	const int minInventorySize = 10;
	Items.Reserve(minInventorySize);
}

void UTalePlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ATalePlayerCharacter>(GetOwner());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find TalePlayerCharacter!"));
		return;
	}

	PlayerInventoryWidget = CreateWidget<UTalePlayerInventoryWidget>(GetWorld()->GetFirstPlayerController(), PlayerInventoryWidgetClass);
	PlayerInventoryWidget->ReloadInventory(Items);
}

void UTalePlayerInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTalePlayerInventoryComponent::TryEquipSword()
{
	if (!bHasSword)
		return;

	if (!PlayerCharacter->GetSwordMeshComponent())
		return;

	for (const FTaleItemData& itemData : Items)
	{
		if (itemData.Type == ETaleItemType::Sword)
		{
			if (!itemData.Mesh)
				continue;

			if (PlayerCharacter->GetSwordMeshComponent()->SetStaticMesh(itemData.Mesh))
			{
				break;
			}
		}
	}
}

void UTalePlayerInventoryComponent::TryEquipShield()
{
	if (!bHasShield)
		return;

	if (!PlayerCharacter->GetShieldMeshComponent())
		return;

	for (const FTaleItemData& itemData : Items)
	{
		if (itemData.Type == ETaleItemType::Shield)
		{
			if (!itemData.Mesh)
				continue;

			if (PlayerCharacter->GetShieldMeshComponent()->SetStaticMesh(itemData.Mesh))
			{
				break;
			}
		}
	}
}

void UTalePlayerInventoryComponent::TryPickUpItem()
{
	TArray<AActor*> OutOverlappingActors;
	PlayerCharacter->GetOverlappingActors(OutOverlappingActors, ATaleItemPickup::StaticClass());
	
	if (OutOverlappingActors.IsEmpty())
		return;
	
	AActor* NearestActor = nullptr;
	float MinDistSquared = FLT_MAX;

	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	for (TActorIterator<AActor> It(GetWorld(), ATaleItemPickup::StaticClass()); It; ++It)
	{
		AActor* Actor = *It;
		const float DistSquared = FVector::DistSquared(Actor->GetActorLocation(), PlayerLocation);

		if (DistSquared < MinDistSquared)
		{
			MinDistSquared = DistSquared;
			NearestActor = Actor;
		}
	}

	ATaleItemPickup* ItemPickup = Cast<ATaleItemPickup>(NearestActor);
	if (ItemPickup->ItemType == ETaleItemType::Sword)
	{
		bHasSword = true;
	}

	if (ItemPickup->ItemType == ETaleItemType::Shield)
	{
		bHasShield = true;
	}

	bool bWasFound = false;
	for (FTaleItemData& itemData : Items)
	{
		if (itemData.Name.ToString() == ItemPickup->ItemData.Name.ToString())
		{
			if (itemData.bIsStackable)
			{
				itemData.Quantity++;
				bWasFound = true;

				UGameplayStatics::PlaySound2D(GetWorld(), PickupSoundEffect, 1.0f);

				ItemPickup->PickUp();
			}
		}
	}
	
	if (!bWasFound)
	{
		Items.Add(ItemPickup->ItemData);

		UGameplayStatics::PlaySound2D(GetWorld(), PickupSoundEffect, 1.0f);

		ItemPickup->PickUp();
	}

	PlayerInventoryWidget->ReloadInventory(Items);
}

void UTalePlayerInventoryComponent::RemoveItem(const FTaleItemData& ItemData)
{
	Items.Remove(ItemData);

	PlayerInventoryWidget->ReloadInventory(Items);
}

FItemSearchResult UTalePlayerInventoryComponent::GetHealthPotion() const
{
	FItemSearchResult SearchResult;
	for (const FTaleItemData& itemData : Items)
	{
		if (itemData.Type == ETaleItemType::HealthPotion)
		{
			SearchResult.bFound = true;
			SearchResult.Item = itemData;

			break;
		}
	}

	return SearchResult;
}
