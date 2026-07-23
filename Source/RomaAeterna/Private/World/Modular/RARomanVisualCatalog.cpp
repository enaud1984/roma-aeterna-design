#include "World/Modular/RARomanVisualCatalog.h"

#include "RARomanModularCore.h"
#include "Misc/PackageName.h"
#include "RomaAeterna.h"

namespace
{
const TCHAR* Cube = TEXT("/Engine/BasicShapes/Cube.Cube");
const TCHAR* Cylinder = TEXT("/Engine/BasicShapes/Cylinder.Cylinder");
const TCHAR* Sphere = TEXT("/Engine/BasicShapes/Sphere.Sphere");
const TCHAR* Cone = TEXT("/Engine/BasicShapes/Cone.Cone");

const TCHAR* Stone = TEXT("/Game/Technical/Materials/MI_RA_Stone.MI_RA_Stone");
const TCHAR* Plaster = TEXT("/Game/Technical/Materials/MI_RA_PlasterLight.MI_RA_PlasterLight");
const TCHAR* Brick = TEXT("/Game/Technical/Materials/MI_RA_Brick.MI_RA_Brick");
const TCHAR* Wood = TEXT("/Game/Technical/Materials/MI_RA_Wood.MI_RA_Wood");
const TCHAR* Tile = TEXT("/Game/Technical/Materials/MI_RA_RoofTile.MI_RA_RoofTile");
const TCHAR* Water = TEXT("/Game/Technical/Materials/MI_RA_Water.MI_RA_Water");
const TCHAR* Metal = TEXT("/Game/Technical/Materials/MI_RA_Metal.MI_RA_Metal");
const TCHAR* Vegetation = TEXT("/Game/Technical/Materials/MI_RA_Vegetation.MI_RA_Vegetation");
const TCHAR* Hazard = TEXT("/Game/Technical/Materials/MI_RA_Hazard.MI_RA_Hazard");
const TCHAR* LocalCatalogPackage = TEXT("/Game/LocalAssets/RomaAeterna/Data/DA_RA_VisualCatalog_Batch1");
const TCHAR* LocalCatalogObject = TEXT("/Game/LocalAssets/RomaAeterna/Data/DA_RA_VisualCatalog_Batch1.DA_RA_VisualCatalog_Batch1");
bool bLocalAssetsEnabled = true;
}

bool URARomanVisualCatalog::FindEntry(const ERARomanModuleCategory Category, FRARomanVisualCatalogEntry& OutEntry) const
{
	for (const FRARomanVisualCatalogEntry& Entry : Entries)
	{
		if (Entry.Category == Category)
		{
			OutEntry = Entry;
			return true;
		}
	}
	return false;
}

bool URARomanVisualCatalog::ResolveEntry(const ERARomanModuleCategory Category, const ERARomanBuildingType Archetype,
	const ERARomanWealthLevel Wealth, const ERARomanWeatheringLevel Weathering, const FName District,
	const int32 Seed, FRARomanVisualCatalogEntry& OutEntry, int32& OutVariantIndex) const
{
	TArray<int32> Candidates;
	for (int32 Index = 0; Index < Entries.Num(); ++Index)
	{
		const FRARomanVisualCatalogEntry& Entry = Entries[Index];
		if (Entry.Category != Category
			|| (Entry.BuildingArchetypes.Num() > 0 && !Entry.BuildingArchetypes.Contains(Archetype))
			|| (Entry.WealthTiers.Num() > 0 && !Entry.WealthTiers.Contains(Wealth))
			|| (Entry.WeatheringLevels.Num() > 0 && !Entry.WeatheringLevels.Contains(Weathering))
			|| (!District.IsNone() && Entry.DistrictCompatibility.Num() > 0
				&& !Entry.DistrictCompatibility.Contains(District)
				&& !Entry.DistrictCompatibility.Contains(TEXT("AllUrban"))))
		{
			continue;
		}
		Candidates.Add(Index);
	}
	if (Candidates.IsEmpty())
	{
		++UnresolvedCount;
		return false;
	}

	uint32 CacheKey = HashCombine(GetTypeHash(Seed), GetTypeHash(Category));
	CacheKey = HashCombine(CacheKey, GetTypeHash(Archetype));
	CacheKey = HashCombine(CacheKey, GetTypeHash(Wealth));
	CacheKey = HashCombine(CacheKey, GetTypeHash(Weathering));
	CacheKey = HashCombine(CacheKey, GetTypeHash(District));
	int32 SelectedIndex = INDEX_NONE;
	if (const int32* CachedIndex = ResolutionCache.Find(CacheKey); CachedIndex && Entries.IsValidIndex(*CachedIndex))
	{
		++CacheHitCount;
		SelectedIndex = *CachedIndex;
	}
	else
	{
		++CacheMissCount;
		std::vector<double> Weights;
		Weights.reserve(Candidates.Num());
		for (const int32 Candidate : Candidates) Weights.push_back(Entries[Candidate].VariationWeight);
		const std::size_t RelativeIndex = RomaAeternaCore::SelectDeterministicWeightedIndex(
			Weights, Seed, CacheKey ^ 0x52414D41u);
		SelectedIndex = Candidates[FMath::Min(static_cast<int32>(RelativeIndex), Candidates.Num() - 1)];
		ResolutionCache.Add(CacheKey, SelectedIndex);
	}

	OutEntry = Entries[SelectedIndex];
	OutVariantIndex = 0;
	if (OutEntry.MaterialOverrides.Num() > 0)
	{
		const std::vector<double> OverrideWeights(OutEntry.MaterialOverrides.Num(), 1.0);
		OutVariantIndex = static_cast<int32>(RomaAeternaCore::SelectDeterministicWeightedIndex(
			OverrideWeights, Seed, CacheKey ^ 0x52414D49u));
		if (!OutEntry.MaterialOverrides[OutVariantIndex].IsNull())
		{
			OutEntry.Material = OutEntry.MaterialOverrides[OutVariantIndex];
		}
	}
	if (OutEntry.Material.IsNull() && !OutEntry.FallbackMaterial.IsNull())
	{
		OutEntry.Material = OutEntry.FallbackMaterial;
	}
	if (OutEntry.Material.ToSoftObjectPath().ToString().StartsWith(TEXT("/Game/LocalAssets/")))
	{
		++LocalResolvedCount;
	}
	return !OutEntry.Material.IsNull();
}

int32 URARomanVisualCatalog::CountResolvedCategories() const
{
	TSet<ERARomanModuleCategory> Categories;
	for (const FRARomanVisualCatalogEntry& Entry : Entries)
	{
		if (!Entry.Material.IsNull() || Entry.MaterialOverrides.Num() > 0)
		{
			Categories.Add(Entry.Category);
		}
	}
	return Categories.Num();
}

int32 URARomanVisualCatalog::CountMaterialVariants() const
{
	int32 Count = 0;
	for (const FRARomanVisualCatalogEntry& Entry : Entries)
	{
		Count += FMath::Max(1, Entry.MaterialOverrides.Num());
	}
	return Count;
}

void URARomanVisualCatalog::ClearResolutionCache() const
{
	ResolutionCache.Reset();
	++InvalidationCount;
}

ERARomanSurfaceRole URARomanVisualCatalog::GetDefaultSurfaceRole(const ERARomanModuleCategory Category)
{
	switch (Category)
	{
	case ERARomanModuleCategory::Wall: return ERARomanSurfaceRole::ExteriorWall;
	case ERARomanModuleCategory::Corner: return ERARomanSurfaceRole::StructuralBrick;
	case ERARomanModuleCategory::Floor: return ERARomanSurfaceRole::SecondaryPaving;
	case ERARomanModuleCategory::Roof: return ERARomanSurfaceRole::Roof;
	case ERARomanModuleCategory::Door:
	case ERARomanModuleCategory::Beam:
	case ERARomanModuleCategory::Counter:
	case ERARomanModuleCategory::Shelf:
	case ERARomanModuleCategory::Table:
	case ERARomanModuleCategory::Bench:
	case ERARomanModuleCategory::ShopOpening:
		return ERARomanSurfaceRole::Timber;
	case ERARomanModuleCategory::GardenFeature:
	case ERARomanModuleCategory::IrrigationChannel:
		return ERARomanSurfaceRole::Ground;
	case ERARomanModuleCategory::Basin:
	case ERARomanModuleCategory::FountainBasin:
	case ERARomanModuleCategory::WaterChannel:
		return ERARomanSurfaceRole::WaterEdge;
	case ERARomanModuleCategory::Furnace:
	case ERARomanModuleCategory::Oven:
	case ERARomanModuleCategory::HypocaustPillar:
	case ERARomanModuleCategory::AqueductArch:
		return ERARomanSurfaceRole::UtilitySurface;
	default: return ERARomanSurfaceRole::ServiceArea;
	}
}

ERARomanWeatheringLevel URARomanVisualCatalog::ConvertDegradationLevel(const ERARomanDegradationLevel Level)
{
	switch (Level)
	{
	case ERARomanDegradationLevel::New: return ERARomanWeatheringLevel::New;
	case ERARomanDegradationLevel::Maintained: return ERARomanWeatheringLevel::Light;
	case ERARomanDegradationLevel::Weathered: return ERARomanWeatheringLevel::Medium;
	case ERARomanDegradationLevel::Damaged: return ERARomanWeatheringLevel::Heavy;
	case ERARomanDegradationLevel::Ruined: return ERARomanWeatheringLevel::Ruined;
	default: return ERARomanWeatheringLevel::Medium;
	}
}

FSoftObjectPath URARomanVisualCatalog::GetFallbackMeshPath(const ERARomanModuleCategory Category)
{
	switch (Category)
	{
	case ERARomanModuleCategory::Column:
	case ERARomanModuleCategory::Portico:
	case ERARomanModuleCategory::Dolium:
	case ERARomanModuleCategory::Millstone:
	case ERARomanModuleCategory::Oven:
	case ERARomanModuleCategory::StorageContainer:
	case ERARomanModuleCategory::ScrollStorage:
		return FSoftObjectPath(Cylinder);
	case ERARomanModuleCategory::Vegetation:
	case ERARomanModuleCategory::InteractionMarker:
		return FSoftObjectPath(Sphere);
	case ERARomanModuleCategory::Decoration:
	case ERARomanModuleCategory::StatueMarker:
		return FSoftObjectPath(Cone);
	default:
		return FSoftObjectPath(Cube);
	}
}

FSoftObjectPath URARomanVisualCatalog::GetTechnicalMaterialPath(const ERARomanModuleCategory Category)
{
	switch (Category)
	{
	case ERARomanModuleCategory::Wall:
	case ERARomanModuleCategory::Corner:
	case ERARomanModuleCategory::Column:
	case ERARomanModuleCategory::Capital:
	case ERARomanModuleCategory::Portico:
		return FSoftObjectPath(Plaster);
	case ERARomanModuleCategory::Roof:
		return FSoftObjectPath(Tile);
	case ERARomanModuleCategory::Door:
	case ERARomanModuleCategory::Beam:
	case ERARomanModuleCategory::Counter:
	case ERARomanModuleCategory::Shelf:
	case ERARomanModuleCategory::Table:
	case ERARomanModuleCategory::Bench:
	case ERARomanModuleCategory::WritingDesk:
	case ERARomanModuleCategory::ShopOpening:
		return FSoftObjectPath(Wood);
	case ERARomanModuleCategory::Furnace:
	case ERARomanModuleCategory::Oven:
	case ERARomanModuleCategory::FuelStorage:
	case ERARomanModuleCategory::WasteArea:
		return FSoftObjectPath(Hazard);
	case ERARomanModuleCategory::Basin:
	case ERARomanModuleCategory::ServiceBasin:
	case ERARomanModuleCategory::WaterChannel:
	case ERARomanModuleCategory::Drain:
	case ERARomanModuleCategory::WateringTrough:
	case ERARomanModuleCategory::FountainBasin:
	case ERARomanModuleCategory::AqueductChannel:
	case ERARomanModuleCategory::SewerChannel:
		return FSoftObjectPath(Water);
	case ERARomanModuleCategory::Anvil:
	case ERARomanModuleCategory::Press:
	case ERARomanModuleCategory::PotteryWheel:
		return FSoftObjectPath(Metal);
	case ERARomanModuleCategory::Vegetation:
	case ERARomanModuleCategory::IrrigationChannel:
		return FSoftObjectPath(Vegetation);
	case ERARomanModuleCategory::Dolium:
	case ERARomanModuleCategory::StorageContainer:
	case ERARomanModuleCategory::LatrineSeat:
		return FSoftObjectPath(Brick);
	default:
		return FSoftObjectPath(Stone);
	}
}

FSoftObjectPath URARomanVisualCatalog::GetLocalCatalogPath()
{
	return FSoftObjectPath(LocalCatalogObject);
}

URARomanVisualCatalog* URARomanVisualCatalog::LoadLocalCatalog(const bool bWriteLog)
{
	if (!bLocalAssetsEnabled)
	{
		if (bWriteLog)
		{
			UE_LOG(LogRomaAeterna, Display, TEXT("LOCAL_ASSET_CATALOG_NOT_FOUND_USING_FALLBACKS: integrazione locale disattivata"));
		}
		return nullptr;
	}

	FString PackageFilename;
	if (!FPackageName::DoesPackageExist(LocalCatalogPackage, &PackageFilename))
	{
		if (bWriteLog)
		{
			UE_LOG(LogRomaAeterna, Display, TEXT("LOCAL_ASSET_CATALOG_NOT_FOUND_USING_FALLBACKS"));
		}
		return nullptr;
	}

	URARomanVisualCatalog* Catalog = LoadObject<URARomanVisualCatalog>(nullptr, LocalCatalogObject);
	if (bWriteLog)
	{
		UE_LOG(LogRomaAeterna, Display, TEXT("%s"), Catalog
			? TEXT("LOCAL_ASSET_CATALOG_LOADED")
			: TEXT("LOCAL_ASSET_CATALOG_NOT_FOUND_USING_FALLBACKS"));
	}
	return Catalog;
}

bool URARomanVisualCatalog::IsLocalCatalogAvailable()
{
	FString PackageFilename;
	return FPackageName::DoesPackageExist(LocalCatalogPackage, &PackageFilename);
}

bool URARomanVisualCatalog::AreLocalAssetsEnabled()
{
	return bLocalAssetsEnabled;
}

void URARomanVisualCatalog::SetLocalAssetsEnabled(const bool bEnabled)
{
	bLocalAssetsEnabled = bEnabled;
	if (URARomanVisualCatalog* Catalog = LoadLocalCatalog(false))
	{
		Catalog->ClearResolutionCache();
	}
}
