// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleEnemyCharacter.h"

#include "AIController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "GenericTeamAgentInterface.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TaleCharacterASC.h"
#include "TaleCharacterBaseAttributeSet.h"
#include "TaleEnemyAttributesWidget.h"

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

	CloseRangeHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("CloseRangeHitbox"));
	CloseRangeHitbox->SetupAttachment(RootComponent);
	CloseRangeHitbox->SetCollisionProfileName("OverlapAllDynamic");
	CloseRangeHitbox->SetGenerateOverlapEvents(true);
	CloseRangeHitbox->SetSphereRadius(CloseRangeHitboxRadius);
	CloseRangeHitbox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	CloseRangeHitbox->OnComponentBeginOverlap.AddDynamic(this, &ATaleEnemyCharacter::OnCloseRangeHitboxOverlap);
	CloseRangeHitbox->OnComponentEndOverlap.AddDynamic(this, &ATaleEnemyCharacter::OnCloseRangeHitboxEndOverlap);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = LossSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;
	SightConfig->SetMaxAge(MaxStimuliAge);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATaleEnemyCharacter::OnTargetPerceptionUpdated);

	Tags.Add(FName("Enemy"));

	CharacterTeamId = 2;
}

void ATaleEnemyCharacter::EnableMeleeHitBox()
{
	MeleeHitbox->SetGenerateOverlapEvents(true);
}

void ATaleEnemyCharacter::DisableMeleeHitBox()
{
	MeleeHitbox->SetGenerateOverlapEvents(false);
}

void ATaleEnemyCharacter::HandleGetHitResponse()
{
	bHasSensedPlayer = true;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && AIController->GetBlackboardComponent())
	{
		AIController->GetBlackboardComponent()->SetValueAsBool(FName("HasSeenPlayer"), bHasSensedPlayer);
	}
}

void ATaleEnemyCharacter::HandleDieResponse()
{
	bHasSensedPlayer = false;
	bIsDying = true;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && AIController->GetBlackboardComponent())
	{
		AIController->GetBlackboardComponent()->SetValueAsBool(FName("HasSeenPlayer"), bHasSensedPlayer);
		AIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDying"), bIsDying);
	}

	GetController()->UnPossess();
}

void ATaleEnemyCharacter::PlayGetHitAnimMontage()
{
	if (!GetHitAnimMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("No Anim Montage found"));
		return;
	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No Anim Montage found"));
		return;
	}

	const float Duration = AnimInstance->Montage_Play(GetHitAnimMontage, 1.0f);
	if (Duration == 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to play Anim Montage"));
	}
}

void ATaleEnemyCharacter::PlayDieAnimMontage()
{
	if (!DieAnimMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("No Anim Montage found"));
		return;
	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No Anim Montage found"));
		return;
	}

	const float Duration = AnimInstance->Montage_Play(DieAnimMontage, 1.0f);
	if (Duration == 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to play Anim Montage"));
	}

	SetLifeSpan(Duration);
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

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->SetGenericTeamId(GetGenericTeamId());
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

void ATaleEnemyCharacter::OnCloseRangeHitboxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;

	if (!OtherActor->ActorHasTag(FName("Player")))
		return;

	if (!OtherComp->ComponentHasTag("PlayerCollider"))
		return;

	bIsPlayerCloseRange = true;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && AIController->GetBlackboardComponent())
	{
		AIController->GetBlackboardComponent()->SetValueAsBool(FName("IsInRangeOfPlayer"), bIsPlayerCloseRange);
	}
}

void ATaleEnemyCharacter::OnCloseRangeHitboxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this)
		return;

	if (!OtherActor->ActorHasTag(FName("Player")))
		return;

	if (!OtherComp->ComponentHasTag("PlayerCollider"))
		return;

	bIsPlayerCloseRange = false;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && AIController->GetBlackboardComponent())
	{
		AIController->GetBlackboardComponent()->SetValueAsBool(FName("IsInRangeOfPlayer"), bIsPlayerCloseRange);
	}
}

void ATaleEnemyCharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (Actor->ActorHasTag("Player"))
		{
			bHasSensedPlayer = true;

			AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController && AIController->GetBlackboardComponent())
			{
				AIController->GetBlackboardComponent()->SetValueAsBool(FName("HasSeenPlayer"), bHasSensedPlayer);
			}

			OnStartedSensingPlayer();
		}
	}
	else
	{
		if (Actor->ActorHasTag("Player"))
		{
			bHasSensedPlayer = false;

			AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController && AIController->GetBlackboardComponent())
			{
				AIController->GetBlackboardComponent()->SetValueAsBool(FName("HasSeenPlayer"), bHasSensedPlayer);
			}

			OnStoppedSensingPlayer();
		}
	}
}
