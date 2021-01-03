// Fill out your copyright notice in the Description page of Project Settings.
using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class GolfBRServerTarget : TargetRules
{
    public GolfBRServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange(new string[] { "GolfBR" });
    }
}