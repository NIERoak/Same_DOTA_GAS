// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Same_DOTA_GAS_Runtime : ModuleRules
{
	public Same_DOTA_GAS_Runtime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",				
				"InputCore",                
                "NavigationSystem", 
				"AIModule", 
				"Niagara",
                "NavigationSystem",
                "GameplayAbilities", 
				"GameplayTags", 
				"GameplayTasks",
				"UMG",
                "Engine",                
				"EnhancedInput",
                "NetCore",
                
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",                
                "Slate",
				"SlateCore",}
				// ... add private dependencies that you statically link with here ...					
            );
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
