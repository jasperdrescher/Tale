// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TalePlayerCharacter.h"

#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TaleHUD.h"
#include "TalePlayerState.h"
#include "TalePowerUpAttributeSet.h"

#include "Components/SphereComponent.h"

ATalePlayerCharacter::ATalePlayerCharacter()
	: SwordMeshComponent(nullptr)
	, ShieldMeshComponent(nullptr)
	, MeleeHitbox(nullptr)
	, SwordHitbox(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	MeleeHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("MeleeHitbox"));
	MeleeHitbox->SetupAttachment(GetMesh());
	MeleeHitbox->SetCollisionProfileName("OverlapAllDynamic");
	MeleeHitbox->SetGenerateOverlapEvents(false);

	SwordHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("SwordHitbox"));
	SwordHitbox->SetupAttachment(GetMesh());
	SwordHitbox->SetCollisionProfileName("OverlapAllDynamic");
	SwordHitbox->SetGenerateOverlapEvents(false);
}

void ATalePlayerCharacter::BeginPlay()
{
	MeleeHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATalePlayerCharacter::OnMeleeHitBoxOverlap);
	SwordHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATalePlayerCharacter::OnSwordHitBoxOverlap);

	TArray<UActorComponent*> FoundWeaponComponents = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Weapon_R"));
	if (!FoundWeaponComponents.IsEmpty())
	{
		SwordMeshComponent = Cast<UStaticMeshComponent>(FoundWeaponComponents[0]);
		MeleeHitbox->AttachToComponent(SwordMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SwordHitbox->AttachToComponent(SwordMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}

	TArray<UActorComponent*> FoundShieldComponents = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Weapon_L"));
	if (!FoundShieldComponents.IsEmpty())
	{
		ShieldMeshComponent = Cast<UStaticMeshComponent>(FoundShieldComponents[0]);
	}
}

void ATalePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
	GiveDefaultEffects();
}

void ATalePlayerCharacter::InitAbilitySystemComponent()
{
	ATalePlayerState* TalePlayerState = GetPlayerState<ATalePlayerState>();
	check(TalePlayerState);
	CharacterASC = CastChecked<UTaleCharacterASC>(TalePlayerState->GetAbilitySystemComponent());
	CharacterASC->InitAbilityActorInfo(TalePlayerState, this);
	CharacterBaseAttributeSet = TalePlayerState->GetCharacterBaseAttributeSet();
}

void ATalePlayerCharacter::InitHUD() const
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ATaleHUD* TaleHUD = Cast<ATaleHUD>(PlayerController->GetHUD()))
		{
			TaleHUD->Init();
		}
	}
}

UTalePowerUpAttributeSet* ATalePlayerCharacter::GetPowerUpAttributeSet() const
{
	const ATalePlayerState* TalePlayerState = GetPlayerState<ATalePlayerState>();
	return CastChecked<UTalePowerUpAttributeSet>(TalePlayerState->GetPowerUpAttributeSet());
}

void ATalePlayerCharacter::StartAdventure()
{
	InitHUD();
}

void ATalePlayerCharacter::EnableMeleeHitBox()
{
	MeleeHitbox->SetGenerateOverlapEvents(true);
}

void ATalePlayerCharacter::DisableMeleeHitBox()
{
	MeleeHitbox->SetGenerateOverlapEvents(false);
}

void ATalePlayerCharacter::EnableSwordHitBox()
{
	SwordHitbox->SetGenerateOverlapEvents(true);
}

void ATalePlayerCharacter::DisableSwordHitBox()
{
	SwordHitbox->SetGenerateOverlapEvents(false);
}

UStaticMeshComponent* ATalePlayerCharacter::GetSwordMeshComponent() const
{
	return SwordMeshComponent;
}

UStaticMeshComponent* ATalePlayerCharacter::GetShieldMeshComponent() const
{
	return ShieldMeshComponent;
}

void ATalePlayerCharacter::OnMeleeHitBoxOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		FGameplayEventData EventData;
		EventData.Instigator = this;
		EventData.Target = OtherActor;
		UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
		ASC->HandleGameplayEvent(
			FGameplayTag::RequestGameplayTag("Event.Player.Melee.DamageTrigger"),
			&EventData
		);
	}
}

void ATalePlayerCharacter::OnSwordHitBoxOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		FGameplayEventData EventData;
		EventData.Instigator = this;
		EventData.Target = OtherActor;
		UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
		ASC->HandleGameplayEvent(
			FGameplayTag::RequestGameplayTag("Event.Player.Sword.DamageTrigger"),
			&EventData
		);
	}
}
