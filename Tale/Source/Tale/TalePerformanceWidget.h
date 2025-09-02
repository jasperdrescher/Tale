// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TalePerformanceWidget.generated.h"

UCLASS()
class TALE_API UTalePerformanceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	FString FramesPerSecond;

	UPROPERTY(BlueprintReadOnly)
	FString FrameTime;

	UPROPERTY(BlueprintReadOnly)
	FString PhysicalMB;

	UPROPERTY(BlueprintReadOnly)
	FString VirtualMB;

	UPROPERTY(BlueprintReadOnly)
	FString GPUName;

private:
	void CalculateAverageFPS(float InDeltaTime);

	float BytesToMegabytes(float Bytes) const;
	float GetAverageDeltaTime() const;

	TArray<float> DeltaTimeHistory;
	float TotalDeltaTime = 0.0f;
	float AverageFPS = 0.0f;
	float AccumulatedTime = 0.0f;
	float AccumulatedTimeThreshold = 5.0f;
	int32 MaxDeltaTimeSamples = 30;
	int32 FrameCount = 0;
};
