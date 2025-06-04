// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleCharacterASC.h"

// Sets default values for this component's properties
UTaleCharacterASC::UTaleCharacterASC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTaleCharacterASC::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTaleCharacterASC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
