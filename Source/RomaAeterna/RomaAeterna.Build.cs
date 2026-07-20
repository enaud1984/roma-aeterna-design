using UnrealBuildTool;

public class RomaAeterna : ModuleRules
{
	public RomaAeterna(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore"
			});
	}
}
