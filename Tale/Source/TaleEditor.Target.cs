// Copyright (c) 2025 Jasper Drescher. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TaleEditorTarget : TargetRules
{
	public TaleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.AddRange( new string[] { "Tale" } );
	}
}
