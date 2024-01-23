// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Schmoove : ModuleRules
{
	public Schmoove(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
