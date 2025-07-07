// Copyright (c) 2025 Jasper Drescher. All rights reserved.

using UnrealBuildTool;

public class Tale : ModuleRules
{
	public Tale(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
            "Niagara"
        });
	}
}
