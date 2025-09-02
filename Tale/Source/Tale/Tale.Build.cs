// Copyright (c) 2025 Jasper Drescher. All rights reserved.

using UnrealBuildTool;

public class Tale : ModuleRules
{
	public Tale(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IWYUSupport = IWYUSupport.Full;
        OptimizeCode = CodeOptimization.InShippingBuildsOnly;
        bUseUnity = true;

        PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"RHI",
		});

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "GameplayTasks",
            "GameplayTags",
            "GameplayAbilities",
            "Niagara",
        });
    }
}
