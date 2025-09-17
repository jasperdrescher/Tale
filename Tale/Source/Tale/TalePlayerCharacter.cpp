// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TalePlayerCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TaleCharacterASC.h"
#include "TaleHUD.h"
#include "TalePlayerState.h"
#include "TalePowerUpAttributeSet.h"
#include "TalePlayerInventoryComponent.h"

ATalePlayerCharacter::ATalePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SwordMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMeshComponent"));
	SwordMeshComponent->SetupAttachment(GetMesh(), WeaponRSocketName);
	SwordMeshComponent->SetRelativeRotation(SwordMeshRotation);
	SwordMeshComponent->SetCollisionProfileName("OverlapAllDynamic");
	SwordMeshComponent->SetGenerateOverlapEvents(false);
	SwordMeshComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	ShieldMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMeshComponent"));
	ShieldMeshComponent->SetupAttachment(GetMesh(), WeaponLSocketName);
	ShieldMeshComponent->SetRelativeLocation(ShieldMeshLocation);
	ShieldMeshComponent->SetRelativeRotation(ShieldMeshRotation);
	ShieldMeshComponent->SetCollisionProfileName("OverlapAllDynamic");
	ShieldMeshComponent->SetGenerateOverlapEvents(false);
	ShieldMeshComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	MeleeHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("MeleeHitbox"));
	MeleeHitbox->SetupAttachment(GetMesh(), WeaponRSocketName);
	MeleeHitbox->SetCollisionProfileName("OverlapAllDynamic");
	MeleeHitbox->SetGenerateOverlapEvents(false);
	MeleeHitbox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	MeleeHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATalePlayerCharacter::OnMeleeHitboxOverlap);

	SwordHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SwordHitbox"));
	SwordHitbox->SetupAttachment(GetMesh(), WeaponRSocketName);
	SwordHitbox->SetCollisionProfileName("OverlapAllDynamic");
	SwordHitbox->SetGenerateOverlapEvents(false);
	SwordHitbox->SetRelativeLocation(SwordHitboxLocation);
	SwordHitbox->SetRelativeRotation(SwordHitboxRotation);
	SwordHitbox->SetCapsuleRadius(SwordHitboxRadius);
	SwordHitbox->SetCapsuleHalfHeight(SwordHitboxHalfHeight);
	SwordHitbox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	SwordHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATalePlayerCharacter::OnSwordHitboxOverlap);

	ShieldHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("ShieldHitbox"));
	ShieldHitbox->SetupAttachment(GetMesh(), WeaponLSocketName);
	ShieldHitbox->SetCollisionProfileName("OverlapAllDynamic");
	ShieldHitbox->SetGenerateOverlapEvents(false);
	ShieldHitbox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	ShieldHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATalePlayerCharacter::OnShieldHitboxOverlap);

	PlayerInventoryComponent = CreateDefaultSubobject<UTalePlayerInventoryComponent>(TEXT("PlayerInventoryComponent"));

	Tags.Add(FName("Player"));
	GetCapsuleComponent()->ComponentTags.Add("PlayerCollider");

	CharacterTeamId = 1;
}

void ATalePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	FText GameplayTagError;
	if (!FGameplayTag::IsValidGameplayTagString(SwordHitGameplayTagName.ToString(), &GameplayTagError))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Gameplay Tag: %s"), *GameplayTagError.ToString());
	}

	if (!FGameplayTag::IsValidGameplayTagString(MeleeHitGameplayTagName.ToString(), &GameplayTagError))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Gameplay Tag: %s"), *GameplayTagError.ToString());
	}

	if (!FGameplayTag::IsValidGameplayTagString(ShieldHitGameplayTagName.ToString(), &GameplayTagError))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Gameplay Tag: %s"), *GameplayTagError.ToString());
	}
}

void ATalePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
	GiveDefaultEffects();
}

void ATalePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(PlayerInventoryComponent->EquipSwordInputAction, ETriggerEvent::Triggered, PlayerInventoryComponent, &UTalePlayerInventoryComponent::TryEquipSword);
		EnhancedInput->BindAction(PlayerInventoryComponent->EquipShieldInputAction, ETriggerEvent::Triggered, PlayerInventoryComponent, &UTalePlayerInventoryComponent::TryEquipShield);
		EnhancedInput->BindAction(PlayerInventoryComponent->PickUpInputAction, ETriggerEvent::Triggered, PlayerInventoryComponent, &UTalePlayerInventoryComponent::TryPickUpItem);
		EnhancedInput->BindAction(PlayerInventoryComponent->ToggleInventoryInputAction, ETriggerEvent::Triggered, PlayerInventoryComponent, &UTalePlayerInventoryComponent::OnToggleInventoryAction);
	}
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

	FGameplayAbilityTargetData_ActorArray* TargetDataActorArray = new FGameplayAbilityTargetData_ActorArray();
	TargetDataActorArray->TargetActorArray.Add(OtherActor);
	FGameplayAbilityTargetDataHandle TargetDataHandle(TargetDataActorArray);

	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = OtherActor;
	EventData.TargetData = TargetDataHandle;

	const FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag(MeleeHitGameplayTagName, true);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GameplayTag, EventData);
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

	FGameplayAbilityTargetData_ActorArray* TargetDataActorArray = new FGameplayAbilityTargetData_ActorArray();
	TargetDataActorArray->TargetActorArray.Add(OtherActor);
	FGameplayAbilityTargetDataHandle TargetDataHandle(TargetDataActorArray);

	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = OtherActor;
	EventData.TargetData = TargetDataHandle;

	const FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag(SwordHitGameplayTagName, true);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GameplayTag, EventData);
}

void ATalePlayerCharacter::OnShieldHitboxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;

	if (!OtherActor->ActorHasTag(FName("Enemy")))
		return;

	FGameplayAbilityTargetData_ActorArray* TargetDataActorArray = new FGameplayAbilityTargetData_ActorArray();
	TargetDataActorArray->TargetActorArray.Add(OtherActor);
	FGameplayAbilityTargetDataHandle TargetDataHandle(TargetDataActorArray);

	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = OtherActor;
	EventData.TargetData = TargetDataHandle;

	const FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag(ShieldHitGameplayTagName, true);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GameplayTag, EventData);
}
