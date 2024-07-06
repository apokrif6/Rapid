// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Rapid : ModuleRules
{
	public Rapid(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "GameplayTasks",
			"GameplayTags", "AIModule", "UMG", "ComponentVisualizers"
		});
	}
}