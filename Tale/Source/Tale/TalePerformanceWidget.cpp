// Copyright (c) 2025 Jasper Drescher. All rights reserved.

#include "TalePerformanceWidget.h"

#include "GenericPlatform/GenericPlatformDriver.h"
#include "GenericPlatform/GenericPlatformMemory.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "RHIGlobals.h"

void UTalePerformanceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DeltaTimeHistory.Reserve(MaxDeltaTimeSamples + 1);

	const FGPUDriverInfo GPUDriverInfo = FPlatformMisc::GetGPUDriverInfo(GRHIAdapterName);
	GPUName = GPUDriverInfo.DeviceDescription;
}

void UTalePerformanceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	DeltaTimeHistory.Add(InDeltaTime);

	if (DeltaTimeHistory.Num() > MaxDeltaTimeSamples)
		DeltaTimeHistory.RemoveAt(0);

	const float SmoothedDeltaTime = GetAverageDeltaTime();
	FrameTime = FString::Printf(TEXT("Frametime %.1f (%.1f) ms"), SmoothedDeltaTime * 1000.f, InDeltaTime * 1000.f);

	CalculateAverageFPS(InDeltaTime);
	FramesPerSecond = FString::Printf(TEXT("FPS %.0f (%.0f)"), AverageFPS, 1.0f / InDeltaTime);

	const FPlatformMemoryStats MemoryStats = FPlatformMemory::GetStats();
	PhysicalMB = FString::Printf(TEXT("Physical %s / %s"), *FGenericPlatformMemory::PrettyMemory(MemoryStats.UsedPhysical), *FGenericPlatformMemory::PrettyMemory(MemoryStats.AvailablePhysical));
	VirtualMB = FString::Printf(TEXT("Virtual %s / %s"), *FGenericPlatformMemory::PrettyMemory(MemoryStats.UsedVirtual), *FGenericPlatformMemory::PrettyMemory(MemoryStats.AvailableVirtual));
}

void UTalePerformanceWidget::CalculateAverageFPS(float InDeltaTime)
{
	TotalDeltaTime += InDeltaTime;
	FrameCount++;

	AverageFPS = FrameCount / TotalDeltaTime;

	AccumulatedTime += InDeltaTime;
	if (AccumulatedTime >= AccumulatedTimeThreshold)
	{
		TotalDeltaTime = 0.0f;
		FrameCount = 0;
		AccumulatedTime = 0.0f;
	}
}

float UTalePerformanceWidget::BytesToMegabytes(float Bytes) const
{
	return Bytes / (1024.0f * 1024.0f);
}

float UTalePerformanceWidget::GetAverageDeltaTime() const
{
	if (DeltaTimeHistory.IsEmpty())
		return 0.0f;

	float Sum = 0.0f;
	for (const float DeltaTime : DeltaTimeHistory)
		Sum += DeltaTime;

	return Sum / DeltaTimeHistory.Num();
}
