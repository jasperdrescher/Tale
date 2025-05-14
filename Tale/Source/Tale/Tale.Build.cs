// Fill out your copyright notice in the Description page of Project Settings.

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
			"GameplayTasks"
		});
	}
}
