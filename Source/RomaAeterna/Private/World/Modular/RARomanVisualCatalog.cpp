#include "World/Modular/RARomanVisualCatalog.h"

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
