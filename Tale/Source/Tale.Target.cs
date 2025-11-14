// Copyright (c) 2025 Jasper Drescher. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TaleTarget : TargetRules
{
	public TaleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.AddRange( new string[] { "Tale" } );
	}
}
