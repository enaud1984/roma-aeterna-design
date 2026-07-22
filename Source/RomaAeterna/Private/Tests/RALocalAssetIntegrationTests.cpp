#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#include "EngineUtils.h"
#include "Tests/AutomationCommon.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "World/Modular/RARomanVisualCatalog.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FRALocalAssetIntegrationTest,
	"RomaAeterna.Prompt27.LocalAssetIntegration",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRALocalAssetIntegrationTest::RunTest(const FString& Parameters)
{
	TestTrue(TEXT("Soft path locale relativo al progetto"), URARomanVisualCatalog::GetLocalCatalogPath().ToString().StartsWith(TEXT("/Game/LocalAssets/")));
	TestTrue(TEXT("Fallback mesh disponibile"), URARomanVisualCatalog::GetFallbackMeshPath(ERARomanModuleCategory::Wall).IsValid());
	TestTrue(TEXT("Fallback materiale disponibile"), URARomanVisualCatalog::GetTechnicalMaterialPath(ERARomanModuleCategory::Wall).IsValid());

	URARomanVisualCatalog::SetLocalAssetsEnabled(false);
	TestNull(TEXT("Catalogo disattivato usa fallback"), URARomanVisualCatalog::LoadLocalCatalog(false));

	URARomanVisualCatalog::SetLocalAssetsEnabled(true);
	URARomanVisualCatalog* Catalog = URARomanVisualCatalog::LoadLocalCatalog(true);
	if (URARomanVisualCatalog::IsLocalCatalogAvailable())
	{
		TestNotNull(TEXT("Catalogo locale installato caricato"), Catalog);
		if (Catalog)
		{
			FRARomanVisualCatalogEntry Entry;
			TestTrue(TEXT("Mapping locale Wall presente"), Catalog->FindEntry(ERARomanModuleCategory::Wall, Entry));
			TestTrue(TEXT("Materiale locale risolvibile"), !Entry.Material.IsNull() && Entry.Material.LoadSynchronous() != nullptr);
			TestTrue(TEXT("Registro licenza associato"), !Entry.LicenseRegistryId.IsNone());
		}
	}
	else
	{
		TestNull(TEXT("Assenza intenzionale non impedisce il fallback"), Catalog);
	}

	if (!AutomationOpenMap(TEXT("/Game/Maps/RomaAeternaVerticalSlice"), true))
	{
		AddError(TEXT("Impossibile aprire la vertical slice per il test di regressione."));
		return false;
	}
	int32 BuildingCount = 0;
	for (TActorIterator<ARARomanProceduralBuildingActor> It(GWorld); It; ++It)
	{
		++BuildingCount;
		It->RefreshVisualCatalogFromLocalAssets();
		TestTrue(TEXT("Generazione valida con catalogo locale o fallback"), It->RebuildBuilding());
		TestTrue(TEXT("Moduli generati"), It->GetGeneratedInstanceCount() > 0);
	}
	TestTrue(TEXT("Archetipi Prompt 22-24 preservati"), BuildingCount >= 9);
	return true;
}

#endif
