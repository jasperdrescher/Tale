// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleEnemyAIController.h"

#include "GenericTeamAgentInterface.h"

void ATaleEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type ATaleEnemyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (!OtherPawn)
		return ETeamAttitude::Neutral;

	const IGenericTeamAgentInterface* OtherGenericTeamAgentInterface = Cast<IGenericTeamAgentInterface>(&Other);
	if (!OtherGenericTeamAgentInterface)
		return ETeamAttitude::Neutral;

	return GetGenericTeamId() == OtherGenericTeamAgentInterface->GetGenericTeamId() ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}
