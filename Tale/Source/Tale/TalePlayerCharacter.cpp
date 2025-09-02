// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TalePlayerCharacter.h"

#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TaleHUD.h"
#include "TalePlayerState.h"
#include "TalePowerUpAttributeSet.h"

#include "Components/SphereComponent.h"

ATalePlayerCharacter::ATalePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SwordMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMeshComponent"));
	SwordMeshComponent->SetupAttachment(GetMesh(), WeaponRSocketName);
	SwordMeshComponent->SetRelativeRotation(SwordMeshRotation);

	ShieldMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMeshComponent"));
	ShieldMeshComponent->SetupAttachment(GetMesh(), WeaponLSocketName);
	ShieldMeshComponent->SetRelativeLocation(ShieldMeshLocation);
	ShieldMeshComponent->SetRelativeRotation(ShieldMeshRotation);

	MeleeHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("MeleeHitbox"));
	MeleeHitbox->SetupAttachment(GetMesh(), WeaponRSocketName);
	MeleeHitbox->SetCollisionProfileName("OverlapAllDynamic");
	MeleeHitbox->SetGenerateOverlapEvents(true);
	MeleeHitbox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	MeleeHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATalePlayerCharacter::OnMeleeHitboxOverlap);

	SwordHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("SwordHitbox"));
	SwordHitbox->SetupAttachment(GetMesh(), WeaponRSocketName);
	SwordHitbox->SetCollisionProfileName("OverlapAllDynamic");
	SwordHitbox->SetGenerateOverlapEvents(true);
	SwordHitbox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	SwordHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATalePlayerCharacter::OnSwordHitboxOverlap);

	ShieldHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("ShieldHitbox"));
	ShieldHitbox->SetupAttachment(GetMesh(), WeaponLSocketName);
	ShieldHitbox->SetCollisionProfileName("OverlapAllDynamic");
	ShieldHitbox->SetGenerateOverlapEvents(true);
	ShieldHitbox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	ShieldHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATalePlayerCharacter::OnShieldHitboxOverlap);
}

void ATalePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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

void ATalePlayerCharacter::OnMeleeHitboxOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;

	if (!OtherActor->ActorHasTag(FName("Enemy")))
		return;

	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = OtherActor;
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (AbilitySystemComponent)
	{
		const FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag("Event.Player.Melee.DamageTrigger", true);
		if (GameplayTag.IsValid())
		{
			AbilitySystemComponent->HandleGameplayEvent(GameplayTag, &EventData);
		}
	}
}

void ATalePlayerCharacter::OnSwordHitboxOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;

	if (!OtherActor->ActorHasTag(FName("Enemy")))
		return;

	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = OtherActor;
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (AbilitySystemComponent)
	{
		const FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag("Event.Player.Sword.DamageTrigger", true);
		if (GameplayTag.IsValid())
		{
			AbilitySystemComponent->HandleGameplayEvent(GameplayTag, &EventData);
		}
	}
}

void ATalePlayerCharacter::OnShieldHitboxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;

	if (!OtherActor->ActorHasTag(FName("Enemy")))
		return;

	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = OtherActor;
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (AbilitySystemComponent)
	{
		const FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag("Event.Player.Shield.Hitbox", true);
		if (GameplayTag.IsValid())
		{
			AbilitySystemComponent->HandleGameplayEvent(GameplayTag, &EventData);
		}
	}
}
