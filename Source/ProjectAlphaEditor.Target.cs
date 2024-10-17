// Copyright Lede Studios. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectAlphaEditorTarget : TargetRules
{
	public ProjectAlphaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("ProjectAlpha");
	}
}
