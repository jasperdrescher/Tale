// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleItemPickup.h"

#include "TaleItemData.h"

#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/MaterialBillboardComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystemInstance.h"

ATaleItemPickup::ATaleItemPickup()
	: SceneRootComponent(nullptr)
	, MeshComponent(nullptr)
	, ItemType(ETaleItemType::None)
	, DataTable(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRootComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBoxComponent"));
	TriggerBoxComponent->SetupAttachment(RootComponent);
	TriggerBoxComponent->SetBoxExtent(FVector(64.f, 64.f, 64.f));
	static FName CollisionProfileName(TEXT("OverlapAllDynamic"));
	TriggerBoxComponent->SetCollisionProfileName(CollisionProfileName);

	BillBoardComponent = CreateDefaultSubobject<UBillboardComponent>(FName("BillBoardComponent"));
	BillBoardComponent->SetupAttachment(RootComponent);
	UTexture2D* EditorIconTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Engine/EditorResources/S_Actor.S_Actor")));
	if (EditorIconTexture)
		BillBoardComponent->SetSprite(EditorIconTexture);
}

void ATaleItemPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ATaleItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!NiagaraComponent && SparklesNiagaraSystem)
	{
		NiagaraComponent = NewObject<UNiagaraComponent>(this, UNiagaraComponent::StaticClass(), TEXT("NiagaraComponent"));
		NiagaraComponent->SetupAttachment(RootComponent);
		NiagaraComponent->RegisterComponent();
		NiagaraComponent->SetAsset(SparklesNiagaraSystem);
		NiagaraComponent->Activate(true);
	}

	FindDataTable();

	switch (ItemData.Type)
	{
		case ETaleItemType::Sword:
			MeshComponent->SetStaticMesh(ItemData.Mesh);
			break;
		case ETaleItemType::Shield:
			MeshComponent->SetStaticMesh(ItemData.Mesh);
			break;
		case ETaleItemType::HealthPotion:
			MeshComponent->SetStaticMesh(ItemData.Mesh);
			break;
		case ETaleItemType::None:
			break;
	}
}

void ATaleItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATaleItemPickup::PickUp()
{
	Destroy();
}

void ATaleItemPickup::FindDataTable()
{
	if (DataTable)
	{
		const FString Context = TEXT("Type");
		FTaleItemData* Row = DataTable->FindRow<FTaleItemData>(FName(UEnum::GetDisplayValueAsText(ItemType).ToString()), Context);
		if (Row)
		{
			UE_LOG(LogTemp, Log, TEXT("Found Item: %s"), *UEnum::GetValueAsString(Row->Type));
			ItemData = *Row;
		}
	}
}
