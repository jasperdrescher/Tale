// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TalePlayerInventoryComponent.h"

#include "TaleItemPickup.h"
#include "TalePlayerCharacter.h"

#include "Components/SphereComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

UTalePlayerInventoryComponent::UTalePlayerInventoryComponent()
	: bHasSword(false)
	, bHasShield(false)
	, PlayerCharacter(nullptr)
	, SwordMeshComponent(nullptr)
	, ShieldMeshComponent(nullptr)
	, WeaponSphereComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;

	const int minInventorySize = 10;
	Items.Reserve(minInventorySize);
	for (size_t i = 0; i < minInventorySize; i++)
	{
		Items.Add(FTaleItemData());
	}
}

void UTalePlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerCharacter = Cast<ATalePlayerCharacter>(Character);
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find TalePlayerCharacter!"));
		return;
	}

	TArray<UActorComponent*> FoundWeaponComponents = PlayerCharacter->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("WeaponR"));
	if (FoundWeaponComponents.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find Weapon R Component!"));
		return;
	}

	SwordMeshComponent = Cast<UStaticMeshComponent>(FoundWeaponComponents[0]);
	WeaponSphereComponent = PlayerCharacter->GetComponentByClass<USphereComponent>();

	TArray<UActorComponent*> FoundShieldComponents = PlayerCharacter->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("WeaponL"));
	if (FoundShieldComponents.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find Weapon L Component!"));
		return;
	}

	ShieldMeshComponent = Cast<UStaticMeshComponent>(FoundShieldComponents[0]);

	PlayerInventoryWidget = CreateWidget<UTalePlayerInventoryWidget>(GetWorld()->GetFirstPlayerController(), PlayerInventoryWidgetClass);

	ReloadInventory();
}

void UTalePlayerInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTalePlayerInventoryComponent::TryEquipSword()
{
	if (!bHasSword)
		return;

	for (const FTaleItemData& itemData : Items)
	{
		if (itemData.Type == ETaleItemType::Sword)
		{
			if (SwordMeshComponent->SetStaticMesh(itemData.Mesh))
			{
				WeaponSphereComponent->SetRelativeLocation(FVector(-1.69f, 1.17f, 110.69f));
				break;
			}
		}
	}
}

void UTalePlayerInventoryComponent::TryEquipShield()
{
	if (!bHasShield)
		return;

	for (const FTaleItemData& itemData : Items)
	{
		if (itemData.Type == ETaleItemType::Shield)
		{
			if (ShieldMeshComponent->SetStaticMesh(itemData.Mesh))
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
		bHasSword = true;
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

				// TODO: Play Sound

				ItemPickup->PickUp();
			}
		}
	}
	
	if (!bWasFound)
	{
		Items.Add(ItemPickup->ItemData);

		// TODO: Play Sound

		ItemPickup->PickUp();
	}

	ReloadInventory();
}

void UTalePlayerInventoryComponent::RemoveItem(const FTaleItemData& ItemData)
{
	Items.Remove(ItemData);

	ReloadInventory();
}

FItemSearchResult UTalePlayerInventoryComponent::GetHealthPotion()
{
	FItemSearchResult SearchResult;
	for (FTaleItemData& itemData : Items)
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
