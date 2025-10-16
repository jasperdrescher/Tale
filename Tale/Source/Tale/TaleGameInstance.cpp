// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TaleGameInstance.h"

#include "MoviePlayer.h"
#include "TaleLoadingScreenWidget.h"

void UTaleGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UTaleGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UTaleGameInstance::EndLoadingScreen);
}

void UTaleGameInstance::BeginLoadingScreen(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.0f;
	LoadingScreenAttributes.WidgetLoadingScreen = SNew(STaleLoadingScreenWidget).BackgroundTexture(LoadingScreenBackgroundTexture);

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void UTaleGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
	UE_LOG(LogTemp, Verbose, TEXT("EndLoadingScreen delegate triggered"));
}
