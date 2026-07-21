using System.IO;
using UnrealBuildTool;

public class RomaAeterna : ModuleRules
{
	public RomaAeterna(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../RomaAeternaCore/include"));

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"EnhancedInput",
				"Engine",
				"InputCore"
			});
	}
}
