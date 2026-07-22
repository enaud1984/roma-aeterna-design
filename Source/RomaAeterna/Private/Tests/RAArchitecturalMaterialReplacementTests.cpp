#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#include "Tests/AutomationCommon.h"
#include "UI/RATechnicalHUD.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "World/Modular/RARomanVisualCatalog.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRAArchitecturalMaterialReplacementTest,
	"RomaAeterna.Prompt28.ArchitecturalMaterialReplacement",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

namespace
{
FRARomanBuildingParameters MakePrompt28Parameters(const ERARomanBuildingType Type, const int32 Seed)
{
	FRARomanBuildingParameters Parameters;
	Parameters.BuildingType = Type;
	Parameters.RandomSeed = Seed;
	Parameters.MaximumModuleCount = 512;
	Parameters.DegradationLevel = ERARomanDegradationLevel::Weathered;
	Parameters.WealthLevel = ERARomanWealthLevel::Modest;
	if (Type == ERARomanBuildingType::DomusMedia || Type == ERARomanBuildingType::BathComplex
		|| Type == ERARomanBuildingType::PublicFountain || Type == ERARomanBuildingType::UrbanGarden)
	{
		Parameters.WealthLevel = ERARomanWealthLevel::Comfortable;
	}
	if (Type == ERARomanBuildingType::DomusMedia || Type == ERARomanBuildingType::BathComplex
		|| Type == ERARomanBuildingType::UrbanGarden)
	{
		Parameters.DegradationLevel = ERARomanDegradationLevel::Maintained;
	}
	return Parameters;
}
}

bool FRAArchitecturalMaterialReplacementTest::RunTest(const FString& Parameters)
{
	TestNotEqual(TEXT("Ruoli superficie distinti"), ERARomanSurfaceRole::ExteriorWall, ERARomanSurfaceRole::Roof);
	TestNotEqual(TEXT("Livelli usura distinti"), ERARomanWeatheringLevel::New, ERARomanWeatheringLevel::Ruined);
	TestNotEqual(TEXT("Livelli ricchezza esistenti riutilizzati"), ERARomanWealthLevel::Poor, ERARomanWealthLevel::Wealthy);
	TestEqual(TEXT("Conversione usura mantenuta"),
		URARomanVisualCatalog::ConvertDegradationLevel(ERARomanDegradationLevel::Weathered),
		ERARomanWeatheringLevel::Medium);
	TestNotNull(TEXT("HUD tecnico disponibile"), GetDefault<ARATechnicalHUD>());

	URARomanVisualCatalog* SyntheticCatalog = NewObject<URARomanVisualCatalog>();
	for (int32 Index = 0; Index < 2; ++Index)
	{
		FRARomanVisualCatalogEntry Entry;
		Entry.Category = ERARomanModuleCategory::Wall;
		Entry.BuildingArchetypes = {ERARomanBuildingType::PopularHouse};
		Entry.WealthTiers = {ERARomanWealthLevel::Modest};
		Entry.WeatheringLevels = {ERARomanWeatheringLevel::Medium};
		Entry.DistrictCompatibility = {TEXT("PopularResidential")};
		Entry.MaterialVariant = Index == 0 ? TEXT("TestA") : TEXT("TestB");
		Entry.VariationWeight = 1.0f;
		Entry.Material = TSoftObjectPtr<UMaterialInterface>(
			URARomanVisualCatalog::GetTechnicalMaterialPath(ERARomanModuleCategory::Wall));
		SyntheticCatalog->Entries.Add(Entry);
	}
	FRARomanVisualCatalogEntry First;
	FRARomanVisualCatalogEntry Second;
	int32 FirstVariant = INDEX_NONE;
	int32 SecondVariant = INDEX_NONE;
	TestTrue(TEXT("Mapping sintetico risolto"), SyntheticCatalog->ResolveEntry(
		ERARomanModuleCategory::Wall, ERARomanBuildingType::PopularHouse, ERARomanWealthLevel::Modest,
		ERARomanWeatheringLevel::Medium, TEXT("PopularResidential"), 2801, First, FirstVariant));
	TestTrue(TEXT("Cache risolve lo stesso seed"), SyntheticCatalog->ResolveEntry(
		ERARomanModuleCategory::Wall, ERARomanBuildingType::PopularHouse, ERARomanWealthLevel::Modest,
		ERARomanWeatheringLevel::Medium, TEXT("PopularResidential"), 2801, Second, SecondVariant));
	TestEqual(TEXT("Variante deterministica"), First.MaterialVariant, Second.MaterialVariant);
	TSet<FName> SeedVariants;
	for (int32 Seed = 0; Seed < 32; ++Seed)
	{
		FRARomanVisualCatalogEntry Resolved;
		int32 Variant = INDEX_NONE;
		if (SyntheticCatalog->ResolveEntry(ERARomanModuleCategory::Wall, ERARomanBuildingType::PopularHouse,
			ERARomanWealthLevel::Modest, ERARomanWeatheringLevel::Medium, TEXT("PopularResidential"),
			Seed, Resolved, Variant))
		{
			SeedVariants.Add(Resolved.MaterialVariant);
		}
	}
	TestEqual(TEXT("Numero varianti limitato"), SeedVariants.Num(), 2);
	SyntheticCatalog->ClearResolutionCache();

	URARomanVisualCatalog::SetLocalAssetsEnabled(false);
	TestNull(TEXT("Catalogo assente/disattivato usa fallback"), URARomanVisualCatalog::LoadLocalCatalog(false));
	URARomanVisualCatalog::SetLocalAssetsEnabled(true);
	URARomanVisualCatalog* LocalCatalog = URARomanVisualCatalog::LoadLocalCatalog(true);
	const bool bLocalInstalled = URARomanVisualCatalog::IsLocalCatalogAvailable();
	if (bLocalInstalled)
	{
		TestNotNull(TEXT("Catalogo locale presente"), LocalCatalog);
		if (LocalCatalog)
		{
			TestTrue(TEXT("Almeno sette categorie locali"), LocalCatalog->CountResolvedCategories() >= 7);
			TestTrue(TEXT("Varianti locali condivise"), LocalCatalog->CountMaterialVariants() >= 11);
		}
	}

	if (!AutomationOpenMap(TEXT("/Game/Maps/RomaAeternaVerticalSlice"), true))
	{
		AddError(TEXT("Impossibile aprire RomaAeternaVerticalSlice."));
		return false;
	}
	const ERARomanBuildingType Archetypes[] = {
		ERARomanBuildingType::PopularHouse, ERARomanBuildingType::DomusMedia,
		ERARomanBuildingType::Taberna, ERARomanBuildingType::Thermopolium,
		ERARomanBuildingType::BathComplex, ERARomanBuildingType::PublicFountain,
		ERARomanBuildingType::MetalWorkshop, ERARomanBuildingType::AqueductSection,
		ERARomanBuildingType::UrbanGarden, ERARomanBuildingType::ServiceYard,
	};
	for (int32 Index = 0; Index < UE_ARRAY_COUNT(Archetypes); ++Index)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.ObjectFlags |= RF_Transient;
		ARARomanProceduralBuildingActor* Actor = GWorld->SpawnActor<ARARomanProceduralBuildingActor>(
			FVector(Index * 5000.0f, 15000.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		TestNotNull(TEXT("Actor procedurale creato"), Actor);
		if (!Actor)
		{
			continue;
		}
		Actor->BuildingParameters = MakePrompt28Parameters(Archetypes[Index], 2800 + Index);
		URARomanVisualCatalog::SetLocalAssetsEnabled(false);
		Actor->RefreshVisualCatalogFromLocalAssets();
		TestTrue(TEXT("Generazione fallback"), Actor->GenerateBuildingByType(Archetypes[Index]));
		TestEqual(TEXT("Nessuna categoria locale in fallback"), Actor->GetLocallyResolvedCategoryCount(), 0);
		TestTrue(TEXT("Fallback selettivo disponibile"), Actor->GetFallbackCategoryCount() > 0);
		const int32 FallbackInstanceCount = Actor->GetGeneratedInstanceCount();

		URARomanVisualCatalog::SetLocalAssetsEnabled(true);
		Actor->RefreshVisualCatalogFromLocalAssets();
		TestTrue(TEXT("Rigenerazione con catalogo locale o fallback"), Actor->RebuildBuilding());
		const int32 FirstCount = Actor->GetGeneratedInstanceCount();
		const FString FirstSummary = Actor->GetActiveMaterialSummary();
		TestEqual(TEXT("Geometria invariata dal catalogo"), FirstCount, FallbackInstanceCount);
		if (bLocalInstalled)
		{
			TestTrue(TEXT("Almeno una categoria locale applicata"), Actor->GetLocallyResolvedCategoryCount() > 0);
			TestTrue(TEXT("Fallback resta selettivo"), Actor->GetFallbackCategoryCount() > 0);
		}
		AddInfo(FString::Printf(TEXT("PROMPT28_METRICS type=%d seed=%d instances=%d local=%d fallback=%d variants=%d"),
			static_cast<int32>(Archetypes[Index]), Actor->BuildingParameters.RandomSeed,
			Actor->GetGeneratedInstanceCount(), Actor->GetLocallyResolvedCategoryCount(),
			Actor->GetFallbackCategoryCount(), Actor->GetActiveMaterialVariantCount()));
		TestTrue(TEXT("Clear/rebuild senza accumulo"), Actor->RebuildBuilding());
		TestEqual(TEXT("Conteggio deterministico"), Actor->GetGeneratedInstanceCount(), FirstCount);
		TestEqual(TEXT("Materiali deterministici"), Actor->GetActiveMaterialSummary(), FirstSummary);
		Actor->Destroy();
	}
	URARomanVisualCatalog::SetLocalAssetsEnabled(true);
	return true;
}

#endif
