// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleEnemyCharacter.h"

#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TaleEnemyAttributesWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SphereComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ATaleEnemyCharacter::ATaleEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterASC = CreateDefaultSubobject<UTaleCharacterASC>("CharacterASC");
	CharacterBaseAttributeSet = CreateDefaultSubobject<UTaleCharacterBaseAttributeSet>("CharacterBaseAttributeSet");

    EnemyAttributesWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyAttributesWidgetComponent"));
    EnemyAttributesWidgetComponent->SetupAttachment(RootComponent);
	EnemyAttributesWidgetComponent->AddRelativeLocation(AttributesWidgetOffset);
	EnemyAttributesWidgetComponent->SetBlendMode(EWidgetBlendMode::Transparent);
	EnemyAttributesWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	EnemyAttributesWidgetComponent->SetDrawSize(AttributesWidgetSize);
	EnemyAttributesWidgetComponent->SetDrawAtDesiredSize(true);
	EnemyAttributesWidgetComponent->SetPivot(FVector2D(0.5f, 0.5f));

	MeleeHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("MeleeHitbox"));
	MeleeHitbox->SetupAttachment(RootComponent);
	MeleeHitbox->SetCollisionProfileName("OverlapAllDynamic");
	MeleeHitbox->SetGenerateOverlapEvents(false);
	MeleeHitbox->AddRelativeLocation(MeleeHitboxOffset);
	MeleeHitbox->SetSphereRadius(MeleeHitboxRadius);
	MeleeHitbox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	MeleeHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATaleEnemyCharacter::OnMeleeHitboxOverlap);

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 400.0f;
	SightConfig->LoseSightRadius = 500.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATaleEnemyCharacter::OnTargetPerceptionUpdated);

	Tags.Add(FName("Enemy"));
}

void ATaleEnemyCharacter::EnableMeleeHitBox()
{
	MeleeHitbox->SetGenerateOverlapEvents(true);
}

void ATaleEnemyCharacter::DisableMeleeHitBox()
{
	MeleeHitbox->SetGenerateOverlapEvents(false);
}

void ATaleEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterASC->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
	GiveDefaultEffects();

	if (UTaleEnemyAttributesWidget* EnemyAttributesWidget = Cast<UTaleEnemyAttributesWidget>(EnemyAttributesWidgetComponent->GetWidget()))
	{
		EnemyAttributesWidget->BindToAttributes(CharacterASC, CharacterBaseAttributeSet);
	}
}

void ATaleEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATaleEnemyCharacter::OnMeleeHitboxOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;

	if (!OtherActor->ActorHasTag(FName("Player")))
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

void ATaleEnemyCharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (Actor->ActorHasTag("Player"))
		{
			bHasSensedPlayer = true;
			OnStartedSensingPlayer();
		}
	}
	else
	{
		if (Actor->ActorHasTag("Player"))
		{
			bHasSensedPlayer = false;
			OnStoppedSensingPlayer();
		}
	}
}
