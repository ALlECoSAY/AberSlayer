// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

using UnrealBuildTool;

public class AberSlayer : ModuleRules
{
	public AberSlayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"UMG",
			"Slate",
		});
	}
}
