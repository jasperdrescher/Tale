// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleNPCSpawnPoint.h"

#include "TaleNPCDataRow.h"
#include "TaleEnemyCharacter.h"

ATaleNPCSpawnPoint::ATaleNPCSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATaleNPCSpawnPoint::FindDataTable()
{
    if (DataTable)
    {
        const FString Context = TEXT("NPCBlueprint");
        FTaleNPCDataRow* Row = DataTable->FindRow<FTaleNPCDataRow>(FName(UEnum::GetDisplayValueAsText(NPCType).ToString()), Context);
        if (Row)
        {
            UE_LOG(LogTemp, Log, TEXT("Found NPC: %s"), *UEnum::GetValueAsString(Row->NPCType));
            NPCBlueprint = Row->NPCBlueprint;
        }
    }
}

ATaleEnemyCharacter* ATaleNPCSpawnPoint::SpawnNPC()
{
    if (!NPCBlueprint)
        return nullptr;

    return GetWorld()->SpawnActor<ATaleEnemyCharacter>(NPCBlueprint, GetActorLocation(), GetActorRotation());
}
