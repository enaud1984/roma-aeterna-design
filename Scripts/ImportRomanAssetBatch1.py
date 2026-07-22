"""Importa localmente il Batch 1 CC0, crea catalogo e preview senza toccare mappe versionate."""

from __future__ import annotations

import json
from pathlib import Path

import unreal


LOCAL_ROOT = "/Game/LocalAssets/RomaAeterna"
TEXTURE_ROOT = f"{LOCAL_ROOT}/Materials/Batch1/Textures"
MATERIAL_ROOT = f"{LOCAL_ROOT}/Materials/Batch1"
CATALOG_PATH = f"{LOCAL_ROOT}/Data/DA_RA_VisualCatalog_Batch1"
PREVIEW_MAP = f"{LOCAL_ROOT}/Maps/RomaAeternaAssetBatch1Preview"
CUBE_PATH = "/Engine/BasicShapes/Cube.Cube"
LOCAL_TAG = "RA_LOCAL_ASSET_BATCH_1"

SOURCES = {
    "PlasteredWall03": {
        "root": "ThirdParty/External/PolyHaven/PlasteredWall03/textures",
        "maps": {
            "Color": "plastered_wall_03_diff_2k.jpg",
            "Normal": "plastered_wall_03_nor_dx_2k.jpg",
            "Roughness": "plastered_wall_03_rough_2k.exr",
            "AO": "plastered_wall_03_ao_2k.jpg",
        },
        "license": "RA-CC0-PH-PLASTERED-WALL-03",
        "grade": "B",
        "tiling": 1.5,
    },
    "Bricks066": {
        "root": "ThirdParty/External/AmbientCG/Bricks066",
        "maps": {
            "Color": "Bricks066_2K-JPG_Color.jpg",
            "Normal": "Bricks066_2K-JPG_NormalDX.jpg",
            "Roughness": "Bricks066_2K-JPG_Roughness.jpg",
            "AO": "Bricks066_2K-JPG_AmbientOcclusion.jpg",
        },
        "license": "RA-CC0-ACG-BRICKS-066",
        "grade": "B",
        "tiling": 1.0,
    },
    "Cobblestone05": {
        "root": "ThirdParty/External/PolyHaven/Cobblestone05/textures",
        "maps": {
            "Color": "cobblestone_05_diff_2k.jpg",
            "Normal": "cobblestone_05_nor_dx_2k.jpg",
            "Roughness": "cobblestone_05_rough_2k.exr",
            "AO": "cobblestone_05_ao_2k.jpg",
        },
        "license": "RA-CC0-PH-COBBLESTONE-05",
        "grade": "C",
        "tiling": 1.0,
    },
    "RoofingTiles013A": {
        "root": "ThirdParty/External/AmbientCG/RoofingTiles013A",
        "maps": {
            "Color": "RoofingTiles013A_2K-JPG_Color.jpg",
            "Normal": "RoofingTiles013A_2K-JPG_NormalDX.jpg",
            "Roughness": "RoofingTiles013A_2K-JPG_Roughness.jpg",
            "AO": "RoofingTiles013A_2K-JPG_AmbientOcclusion.jpg",
        },
        "license": "RA-CC0-ACG-ROOFING-TILES-013A",
        "grade": "C",
        "tiling": 1.0,
    },
    "Bricks042": {
        "root": "ThirdParty/External/AmbientCG/Bricks042",
        "maps": {
            "Color": "Bricks042_2K-JPG_Color.jpg",
            "Normal": "Bricks042_2K-JPG_NormalDX.jpg",
            "Roughness": "Bricks042_2K-JPG_Roughness.jpg",
            "AO": "Bricks042_2K-JPG_AmbientOcclusion.jpg",
        },
        "license": "RA-CC0-ACG-BRICKS-042",
        "grade": "B",
        "tiling": 1.0,
    },
    "WoodPlanksGrey": {
        "root": "ThirdParty/External/PolyHaven/WoodPlanksGrey/textures",
        "maps": {
            "Color": "wood_planks_grey_diff_2k.jpg",
            "Normal": "wood_planks_grey_nor_dx_2k.jpg",
            "Roughness": "wood_planks_grey_rough_2k.exr",
            "AO": "wood_planks_grey_ao_2k.jpg",
        },
        "license": "RA-CC0-PH-WOOD-PLANKS-GREY",
        "grade": "B",
        "tiling": 1.0,
    },
    "Ground039": {
        "root": "ThirdParty/External/AmbientCG/Ground039",
        "maps": {
            "Color": "Ground039_2K-JPG_Color.jpg",
            "Normal": "Ground039_2K-JPG_NormalDX.jpg",
            "Roughness": "Ground039_2K-JPG_Roughness.jpg",
            "AO": "Ground039_2K-JPG_AmbientOcclusion.jpg",
        },
        "license": "RA-CC0-ACG-GROUND-039",
        "grade": "C",
        "tiling": 1.0,
    },
}

CATALOG_MAPPINGS = (
    ("WALL", "PlasteredWall03", "AllUrban", ("POOR", "MODEST", "COMFORTABLE", "WEALTHY"), 5.0),
    ("CORNER", "Bricks066", "PopularProductive", ("POOR", "MODEST"), 3.0),
    ("FLOOR", "Cobblestone05", "RoadsCourtyards", ("POOR", "MODEST", "COMFORTABLE"), 4.0),
    ("ROOF", "RoofingTiles013A", "AllUrban", ("POOR", "MODEST", "COMFORTABLE", "WEALTHY"), 5.0),
    ("DOLIUM", "Bricks042", "CommercialProductive", ("POOR", "MODEST", "COMFORTABLE"), 2.0),
    ("DOOR", "WoodPlanksGrey", "AllUrban", ("POOR", "MODEST", "COMFORTABLE", "WEALTHY"), 4.0),
    ("BEAM", "WoodPlanksGrey", "AllUrban", ("POOR", "MODEST", "COMFORTABLE"), 4.0),
    ("GARDEN_FEATURE", "Ground039", "CourtyardSuburb", ("POOR", "MODEST", "COMFORTABLE", "WEALTHY"), 3.0),
)


def require_file(path: Path) -> Path:
    if not path.is_file():
        raise RuntimeError(f"File sorgente Batch 1 mancante: {path}")
    return path


def import_texture(source: Path, destination_name: str):
    task = unreal.AssetImportTask()
    task.set_editor_property("filename", str(source))
    task.set_editor_property("destination_path", TEXTURE_ROOT)
    task.set_editor_property("destination_name", destination_name)
    task.set_editor_property("automated", True)
    task.set_editor_property("replace_existing", True)
    task.set_editor_property("replace_existing_settings", True)
    task.set_editor_property("save", True)
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
    if not task.get_editor_property("imported_object_paths"):
        raise RuntimeError(f"Import texture fallito: {source}")
    texture = unreal.load_asset(task.get_editor_property("imported_object_paths")[0])
    if not texture:
        raise RuntimeError(f"Texture importata non risolvibile: {source}")
    return texture


def configure_texture(texture, map_kind: str):
    if map_kind != "Color":
        texture.set_editor_property("srgb", False)
    if map_kind == "Normal":
        texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_NORMALMAP)
    texture.set_editor_property("virtual_texture_streaming", False)
    texture.modify()
    unreal.EditorAssetLibrary.save_loaded_asset(texture)


def create_material(name: str, textures: dict[str, object], tiling: float):
    asset_name = f"M_RA_Local_{name}"
    asset_path = f"{MATERIAL_ROOT}/{asset_name}"
    material = unreal.load_asset(asset_path) if unreal.EditorAssetLibrary.does_asset_exist(asset_path) else None
    if material:
        unreal.MaterialEditingLibrary.delete_all_material_expressions(material)
    else:
        material = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
            asset_name, MATERIAL_ROOT, unreal.Material, unreal.MaterialFactoryNew()
        )
    if not material:
        raise RuntimeError(f"Creazione materiale fallita: {asset_path}")

    coordinates = unreal.MaterialEditingLibrary.create_material_expression(
        material, unreal.MaterialExpressionTextureCoordinate, -650, 0
    )
    coordinates.set_editor_property("u_tiling", tiling)
    coordinates.set_editor_property("v_tiling", tiling)
    properties = {
        "Color": (unreal.MaterialProperty.MP_BASE_COLOR, "RGB", -350, -180),
        "Normal": (unreal.MaterialProperty.MP_NORMAL, "RGB", -350, -20),
        "Roughness": (unreal.MaterialProperty.MP_ROUGHNESS, "R", -350, 140),
        "AO": (unreal.MaterialProperty.MP_AMBIENT_OCCLUSION, "R", -350, 300),
    }
    for map_kind, texture in textures.items():
        target_property, output_name, x, y = properties[map_kind]
        sample = unreal.MaterialEditingLibrary.create_material_expression(
            material, unreal.MaterialExpressionTextureSample, x, y
        )
        sample.set_editor_property("texture", texture)
        if map_kind == "Normal":
            sample.set_editor_property("sampler_type", unreal.MaterialSamplerType.SAMPLERTYPE_NORMAL)
        unreal.MaterialEditingLibrary.connect_material_expressions(coordinates, "", sample, "UVs")
        unreal.MaterialEditingLibrary.connect_material_property(sample, output_name, target_property)
    unreal.MaterialEditingLibrary.recompile_material(material)
    unreal.EditorAssetLibrary.save_loaded_asset(material)
    return material


def import_materials(content_root: Path) -> dict[str, object]:
    materials = {}
    for source_name, spec in SOURCES.items():
        textures = {}
        source_root = content_root / spec["root"]
        for map_kind, filename in spec["maps"].items():
            source = require_file(source_root / filename)
            texture = import_texture(source, f"T_RA_Local_{source_name}_{map_kind}")
            configure_texture(texture, map_kind)
            textures[map_kind] = texture
        materials[source_name] = create_material(source_name, textures, spec["tiling"])
    return materials


def create_catalog(materials: dict[str, object]):
    catalog = unreal.load_asset(CATALOG_PATH) if unreal.EditorAssetLibrary.does_asset_exist(CATALOG_PATH) else None
    if not catalog:
        factory = unreal.DataAssetFactory()
        factory.set_editor_property("data_asset_class", unreal.RARomanVisualCatalog)
        catalog = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
            "DA_RA_VisualCatalog_Batch1", f"{LOCAL_ROOT}/Data", unreal.RARomanVisualCatalog, factory
        )
    if not catalog:
        raise RuntimeError("Creazione del catalogo locale fallita")
    cube = unreal.load_asset(CUBE_PATH)
    entries = []
    for category_name, source_name, district, wealth_names, weight in CATALOG_MAPPINGS:
        entry = unreal.RARomanVisualCatalogEntry()
        entry.set_editor_property("category", getattr(unreal.RARomanModuleCategory, category_name))
        entry.set_editor_property("mesh", cube)
        entry.set_editor_property("material", materials[source_name])
        entry.set_editor_property("replacement_asset_id", unreal.Name(f"LOCAL-B1-{source_name}"))
        entry.set_editor_property("historical_grade", SOURCES[source_name]["grade"])
        entry.set_editor_property("district_compatibility", [unreal.Name(district)])
        entry.set_editor_property("wealth_tiers", [getattr(unreal.RARomanWealthLevel, name) for name in wealth_names])
        entry.set_editor_property("variation_weight", weight)
        entry.set_editor_property("scale_correction", unreal.Vector(1.0, 1.0, 1.0))
        entry.set_editor_property("rotation_correction", unreal.Rotator())
        entry.set_editor_property("collision_profile", unreal.Name("BlockAll"))
        entry.set_editor_property("prefer_nanite", False)
        entry.set_editor_property("material_overrides", [materials[source_name]])
        entry.set_editor_property("source_package", unreal.Name(source_name))
        entry.set_editor_property("license_registry_id", unreal.Name(SOURCES[source_name]["license"]))
        entries.append(entry)
    catalog.set_editor_property("entries", entries)
    unreal.EditorAssetLibrary.save_loaded_asset(catalog)
    return catalog


def spawn_block(actor_subsystem, cube, label: str, location, scale, material, rotation=(0.0, 0.0, 0.0)):
    actor = actor_subsystem.spawn_actor_from_class(unreal.StaticMeshActor, unreal.Vector(*location), unreal.Rotator(*rotation))
    if not actor:
        raise RuntimeError(f"Creazione preview fallita: {label}")
    actor.set_actor_label(label)
    actor.tags = [unreal.Name(LOCAL_TAG), unreal.Name(label)]
    actor.set_actor_scale3d(unreal.Vector(*scale))
    actor.set_actor_enable_collision(True)
    component = actor.static_mesh_component
    component.set_static_mesh(cube)
    component.set_mobility(unreal.ComponentMobility.MOVABLE)
    component.set_collision_enabled(unreal.CollisionEnabled.QUERY_AND_PHYSICS)
    component.set_material(0, material)
    return actor


def spawn_label(actor_subsystem, text: str, location):
    actor = actor_subsystem.spawn_actor_from_class(unreal.TextRenderActor, unreal.Vector(*location), unreal.Rotator(0.0, 90.0, 0.0))
    actor.set_actor_label(f"RA_Local_Label_{text}")
    actor.tags = [unreal.Name(LOCAL_TAG), unreal.Name("RA_TECHNICAL_LABEL")]
    actor.text_render.set_editor_property("text", text)
    actor.text_render.set_editor_property("world_size", 36.0)
    return actor


def create_preview(materials: dict[str, object]):
    level_editor = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    actor_subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    if unreal.EditorAssetLibrary.does_asset_exist(PREVIEW_MAP):
        if not level_editor.load_level(PREVIEW_MAP):
            raise RuntimeError(f"Caricamento preview fallito: {PREVIEW_MAP}")
    elif not level_editor.new_level(PREVIEW_MAP):
        raise RuntimeError(f"Creazione preview fallita: {PREVIEW_MAP}")
    for actor in actor_subsystem.get_all_level_actors():
        if LOCAL_TAG in [str(tag) for tag in actor.tags]:
            actor_subsystem.destroy_actor(actor)

    cube = unreal.load_asset(CUBE_PATH)
    placeholder = unreal.load_asset("/Game/Technical/Materials/MI_RA_Technical.MI_RA_Technical")
    if not placeholder:
        placeholder = unreal.load_asset("/Game/Technical/Materials/MI_RA_Stone.MI_RA_Stone")
    spawn_block(actor_subsystem, cube, "RA_Local_PreviewFloor", (0, 0, -55), (90, 55, 1), materials["Ground039"])
    rows = (
        ("INTONACO", "PlasteredWall03", (5.0, 0.5, 3.2)),
        ("MURATURA PIETRA", "Bricks066", (5.0, 0.5, 3.2)),
        ("BASOLATO", "Cobblestone05", (5.0, 5.0, 0.25)),
        ("TEGOLE", "RoofingTiles013A", (5.0, 4.0, 0.3)),
        ("LATERIZIO", "Bricks042", (5.0, 0.5, 3.2)),
        ("LEGNO", "WoodPlanksGrey", (5.0, 0.5, 3.2)),
        ("TERRENO", "Ground039", (5.0, 5.0, 0.25)),
    )
    for index, (label, source_name, scale) in enumerate(rows):
        x = -3600 + index * 1200
        z = 160 if scale[2] < 1.0 else 320
        rotation = (0.0, 8.0, 0.0) if source_name == "RoofingTiles013A" else (0.0, 0.0, 0.0)
        spawn_block(actor_subsystem, cube, f"RA_Placeholder_{source_name}", (x, -650, z), scale, placeholder, rotation)
        spawn_block(actor_subsystem, cube, f"RA_Local_{source_name}", (x, 650, z), scale, materials[source_name], rotation)
        spawn_label(actor_subsystem, f"{label} - PLACEHOLDER", (x - 250, -950, 690))
        spawn_label(actor_subsystem, f"{label} - ASSET LOCALE", (x - 250, 350, 690))

    player = actor_subsystem.spawn_actor_from_class(unreal.PlayerStart, unreal.Vector(-4300, 0, 130), unreal.Rotator())
    player.set_actor_label("RA_Local_PlayerStart")
    player.tags = [unreal.Name(LOCAL_TAG), unreal.Name("RA_PLAYER_START")]
    light = actor_subsystem.spawn_actor_from_class(unreal.DirectionalLight, unreal.Vector(0, 0, 1200), unreal.Rotator(-35.0, -25.0, 0.0))
    light.set_actor_label("RA_Local_DirectionalLight")
    light.tags = [unreal.Name(LOCAL_TAG), unreal.Name("RA_DYNAMIC_LIGHTING")]
    light.light_component.set_mobility(unreal.ComponentMobility.MOVABLE)
    sky = actor_subsystem.spawn_actor_from_class(unreal.SkyLight, unreal.Vector(0, 0, 1000))
    sky.set_actor_label("RA_Local_SkyLight")
    sky.tags = [unreal.Name(LOCAL_TAG), unreal.Name("RA_DYNAMIC_LIGHTING")]
    sky.light_component.set_mobility(unreal.ComponentMobility.MOVABLE)
    spawn_label(actor_subsystem, "BATCH 1 CC0 - CONFRONTO PLACEHOLDER / MATERIALE LOCALE", (-4300, 0, 950))
    world = level_editor.get_current_level().get_outer()
    world.get_world_settings().set_editor_property("default_game_mode", unreal.RAVerticalSliceGameMode)
    if not level_editor.save_current_level():
        raise RuntimeError(f"Salvataggio preview fallito: {PREVIEW_MAP}")


def write_local_mapping(project_root: Path, materials: dict[str, object]):
    output = project_root / "Saved" / "LocalAssetConfig" / "roman_asset_batch_1.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    payload = {
        "schema_version": 1,
        "batch": 1,
        "catalog": f"{CATALOG_PATH}.DA_RA_VisualCatalog_Batch1",
        "preview_map": PREVIEW_MAP,
        "assets": [
            {
                "asset_id": f"LOCAL-B1-{name}",
                "material": material.get_path_name(),
                "historical_grade": SOURCES[name]["grade"],
                "license_registry_id": SOURCES[name]["license"],
            }
            for name, material in sorted(materials.items())
        ],
    }
    output.write_text(json.dumps(payload, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")


def main():
    content_root = Path(unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_content_dir()))
    project_root = content_root.parent
    materials = import_materials(content_root)
    create_catalog(materials)
    create_preview(materials)
    write_local_mapping(project_root, materials)
    unreal.log("ASSET_BATCH_1_LOCAL_IMPORT_PASSED")
    unreal.log("LOCAL_ASSET_CATALOG_LOADED")
    unreal.log("LOCAL_ASSET_PREVIEW_CREATED")


main()
