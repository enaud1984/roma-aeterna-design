"""Genera esclusivamente asset locali ignorati per la preview decorativa del Prompt 29."""

import unreal

ROOT = "/Game/LocalAssets/RomaAeterna/Decoration"
MATERIALS = f"{ROOT}/Materials"
PREVIEW_MAP = "/Game/LocalAssets/RomaAeterna/Maps/RomaAeternaDecorationPreview"
PREVIEW_TAG = "RA_PROMPT29_DECORATION_PREVIEW"

PALETTE = {
    "PompeianRed": ((0.50, 0.075, 0.035, 1.0), 0.88),
    "Ochre": ((0.64, 0.34, 0.07, 1.0), 0.90),
    "BlackPanel": ((0.035, 0.030, 0.025, 1.0), 0.82),
    "PlainPlaster": ((0.71, 0.62, 0.45, 1.0), 0.94),
    "ServicePlaster": ((0.45, 0.35, 0.25, 1.0), 0.98),
    "Frame": ((0.18, 0.09, 0.045, 1.0), 0.84),
    "OpusSigninum": ((0.42, 0.17, 0.11, 1.0), 0.93),
    "GeometricMosaic": ((0.70, 0.68, 0.60, 1.0), 0.76),
    "PolychromeMosaic": ((0.36, 0.28, 0.18, 1.0), 0.78),
    "OpusSectile": ((0.28, 0.38, 0.30, 1.0), 0.70),
    "ThermalFloor": ((0.56, 0.51, 0.40, 1.0), 0.80),
    "ProductiveFloor": ((0.20, 0.16, 0.12, 1.0), 0.98),
    "BrickFloor": ((0.46, 0.18, 0.09, 1.0), 0.94),
}


def create_materials():
    tools = unreal.AssetToolsHelpers.get_asset_tools()
    unreal.EditorAssetLibrary.make_directory(MATERIALS)
    base_path = f"{MATERIALS}/M_RA_DecorationBase"
    base = unreal.load_asset(base_path)
    if not base:
        base = tools.create_asset("M_RA_DecorationBase", MATERIALS, unreal.Material, unreal.MaterialFactoryNew())
        color = unreal.MaterialEditingLibrary.create_material_expression(
            base, unreal.MaterialExpressionVectorParameter, -420, -80
        )
        color.set_editor_property("parameter_name", "BaseColor")
        color.set_editor_property("default_value", unreal.LinearColor(0.5, 0.2, 0.1, 1.0))
        roughness = unreal.MaterialEditingLibrary.create_material_expression(
            base, unreal.MaterialExpressionScalarParameter, -420, 40
        )
        roughness.set_editor_property("parameter_name", "Roughness")
        roughness.set_editor_property("default_value", 0.9)
        unreal.MaterialEditingLibrary.connect_material_property(color, "", unreal.MaterialProperty.MP_BASE_COLOR)
        unreal.MaterialEditingLibrary.connect_material_property(roughness, "", unreal.MaterialProperty.MP_ROUGHNESS)
        unreal.MaterialEditingLibrary.recompile_material(base)
        unreal.EditorAssetLibrary.save_loaded_asset(base)

    instances = {}
    for name, (color, roughness) in PALETTE.items():
        asset_name = f"MI_RA_Decoration_{name}"
        instance = unreal.load_asset(f"{MATERIALS}/{asset_name}")
        if not instance:
            instance = tools.create_asset(
                asset_name, MATERIALS, unreal.MaterialInstanceConstant,
                unreal.MaterialInstanceConstantFactoryNew()
            )
        instance.set_editor_property("parent", base)
        unreal.MaterialEditingLibrary.set_material_instance_vector_parameter_value(
            instance, "BaseColor", unreal.LinearColor(*color)
        )
        unreal.MaterialEditingLibrary.set_material_instance_scalar_parameter_value(
            instance, "Roughness", roughness
        )
        unreal.EditorAssetLibrary.save_loaded_asset(instance)
        instances[name] = instance
    return instances


def spawn_sample(actor_subsystem, mesh, material, label, location, scale):
    actor = actor_subsystem.spawn_actor_from_class(
        unreal.StaticMeshActor, unreal.Vector(*location), unreal.Rotator()
    )
    actor.set_actor_label(label)
    actor.tags = [unreal.Name(PREVIEW_TAG), unreal.Name(label)]
    actor.set_actor_scale3d(unreal.Vector(*scale))
    actor.static_mesh_component.set_static_mesh(mesh)
    actor.static_mesh_component.set_material(0, material)
    actor.static_mesh_component.set_collision_enabled(unreal.CollisionEnabled.QUERY_AND_PHYSICS)


def create_preview(instances):
    level_editor = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    actor_subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    if unreal.EditorAssetLibrary.does_asset_exist(PREVIEW_MAP):
        if not level_editor.load_level(PREVIEW_MAP):
            raise RuntimeError("Preview decorazioni non caricabile")
    elif not level_editor.new_level(PREVIEW_MAP):
        raise RuntimeError("Preview decorazioni non creabile")
    for actor in actor_subsystem.get_all_level_actors():
        if PREVIEW_TAG in [str(tag) for tag in actor.tags]:
            actor_subsystem.destroy_actor(actor)
    cube = unreal.load_asset("/Engine/BasicShapes/Cube.Cube")
    if not cube:
        raise RuntimeError("Cube Engine mancante")
    wall_names = ["PompeianRed", "Ochre", "BlackPanel", "PlainPlaster", "ServicePlaster", "Frame"]
    for index, name in enumerate(wall_names):
        spawn_sample(actor_subsystem, cube, instances[name], f"RA_DecorWall_{name}",
                     (-1500 + index * 600, 350, 160), (5.0, 0.15, 3.2))
    floor_names = ["OpusSigninum", "GeometricMosaic", "PolychromeMosaic", "OpusSectile",
                   "ThermalFloor", "ProductiveFloor", "BrickFloor"]
    for index, name in enumerate(floor_names):
        spawn_sample(actor_subsystem, cube, instances[name], f"RA_DecorFloor_{name}",
                     (-1800 + index * 600, -450, 0), (5.0, 5.0, 0.12))
    light = actor_subsystem.spawn_actor_from_class(
        unreal.DirectionalLight, unreal.Vector(0, 0, 1800), unreal.Rotator(-45, -30, 0)
    )
    light.set_actor_label("RA_DecorationPreviewLight")
    light.tags = [unreal.Name(PREVIEW_TAG)]
    light.light_component.set_mobility(unreal.ComponentMobility.MOVABLE)
    light.light_component.set_editor_property("intensity", 5.0)
    if not level_editor.save_current_level():
        raise RuntimeError("Preview decorazioni non salvata")


instances = create_materials()
create_preview(instances)
unreal.log(f"ROMAN_DECORATION_LOCAL_ASSETS_CREATED materials={len(instances)} preview={PREVIEW_MAP}")
unreal.log("FIGURATIVE_FRESCO_ART_NOT_STARTED")
