// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CPPTutoial : ModuleRules
{
	public CPPTutoial(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CPPTutoial",
			"CPPTutoial/Variant_Platforming",
			"CPPTutoial/Variant_Platforming/Animation",
			"CPPTutoial/Variant_Combat",
			"CPPTutoial/Variant_Combat/AI",
			"CPPTutoial/Variant_Combat/Animation",
			"CPPTutoial/Variant_Combat/Gameplay",
			"CPPTutoial/Variant_Combat/Interfaces",
			"CPPTutoial/Variant_Combat/UI",
			"CPPTutoial/Variant_SideScrolling",
			"CPPTutoial/Variant_SideScrolling/AI",
			"CPPTutoial/Variant_SideScrolling/Gameplay",
			"CPPTutoial/Variant_SideScrolling/Interfaces",
			"CPPTutoial/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
