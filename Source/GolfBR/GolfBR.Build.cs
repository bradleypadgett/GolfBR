// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GolfBR : ModuleRules
{
	public GolfBR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameLiftServerSDK", "UMG", "SlateCore", "Http", "Json", "JsonUtilities", "WebBrowserWidget" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
