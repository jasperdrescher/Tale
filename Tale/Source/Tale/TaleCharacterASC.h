// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "AbilitySystemComponent.h"
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "TaleCharacterASC.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TALE_API UTaleCharacterASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTaleCharacterASC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
