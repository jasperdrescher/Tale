// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleGameInstance.h"

void UTaleGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UTaleGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UTaleGameInstance::EndLoadingScreen);
}

void UTaleGameInstance::BeginLoadingScreen(const FString& MapName)
{
	UE_LOG(LogTemp, Warning, TEXT("PreLoadMap delegate triggered for map: %s"), *MapName);
}

void UTaleGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
	UE_LOG(LogTemp, Warning, TEXT("EndLoadingScreen delegate triggered"));
}
