// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ConsoleCommandTest : ModuleRules
{
	public ConsoleCommandTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"EngineSettings",
		});
	}
}
