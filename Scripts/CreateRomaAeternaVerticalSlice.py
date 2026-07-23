"""Rigenera la vertical slice romana consolidata usando solo primitive e materiali procedurali."""

from __future__ import annotations

import unreal


LEVEL_PACKAGE = "/Game/Maps/RomaAeternaVerticalSlice"
MATERIAL_FOLDER = "/Game/Technical/Materials"
CUBE = "/Engine/BasicShapes/Cube.Cube"
CYLINDER = "/Engine/BasicShapes/Cylinder.Cylinder"
SPHERE = "/Engine/BasicShapes/Sphere.Sphere"
SLICE_TAG = "RA_VERTICAL_SLICE"

PALETTE = {
    "Stone": ((0.28, 0.27, 0.24, 1.0), 0.82, 0.0),
    "RoadStone": ((0.20, 0.21, 0.20, 1.0), 0.90, 0.0),
    "Sidewalk": ((0.47, 0.43, 0.35, 1.0), 0.88, 0.0),
    "PlasterLight": ((0.78, 0.68, 0.50, 1.0), 0.76, 0.0),
    "PlasterColor": ((0.52, 0.20, 0.12, 1.0), 0.80, 0.0),
    "RoughMasonry": ((0.34, 0.27, 0.20, 1.0), 0.92, 0.0),
    "Brick": ((0.45, 0.16, 0.09, 1.0), 0.86, 0.0),
    "Wood": ((0.24, 0.11, 0.045, 1.0), 0.78, 0.0),
    "RoofTile": ((0.48, 0.13, 0.065, 1.0), 0.86, 0.0),
    "Water": ((0.055, 0.25, 0.32, 1.0), 0.18, 0.05),
    "Metal": ((0.18, 0.17, 0.15, 1.0), 0.34, 0.72),
    "Ground": ((0.25, 0.18, 0.10, 1.0), 0.96, 0.0),
    "Vegetation": ((0.12, 0.28, 0.08, 1.0), 0.92, 0.0),
    "Technical": ((0.20, 0.31, 0.38, 1.0), 0.68, 0.0),
    "Hazard": ((0.48, 0.20, 0.035, 1.0), 0.72, 0.0),
}


def require_asset(path: str):
    asset = unreal.load_asset(path)
    if not asset:
        raise RuntimeError(f"Asset richiesto non trovato: {path}")
    return asset


def create_technical_materials():
    tools = unreal.AssetToolsHelpers.get_asset_tools()
    base_path = f"{MATERIAL_FOLDER}/M_RA_TechnicalBase"
    base = unreal.load_asset(base_path) if unreal.EditorAssetLibrary.does_asset_exist(base_path) else None
    if not base:
        base = tools.create_asset("M_RA_TechnicalBase", MATERIAL_FOLDER, unreal.Material, unreal.MaterialFactoryNew())
        color = unreal.MaterialEditingLibrary.create_material_expression(base, unreal.MaterialExpressionVectorParameter, -400, -80)
        color.set_editor_property("parameter_name", "BaseColor")
        color.set_editor_property("default_value", unreal.LinearColor(0.5, 0.5, 0.5, 1.0))
        roughness = unreal.MaterialEditingLibrary.create_material_expression(base, unreal.MaterialExpressionScalarParameter, -400, 20)
        roughness.set_editor_property("parameter_name", "Roughness")
        roughness.set_editor_property("default_value", 0.8)
        metallic = unreal.MaterialEditingLibrary.create_material_expression(base, unreal.MaterialExpressionScalarParameter, -400, 120)
        metallic.set_editor_property("parameter_name", "Metallic")
        metallic.set_editor_property("default_value", 0.0)
        unreal.MaterialEditingLibrary.connect_material_property(color, "", unreal.MaterialProperty.MP_BASE_COLOR)
        unreal.MaterialEditingLibrary.connect_material_property(roughness, "", unreal.MaterialProperty.MP_ROUGHNESS)
        unreal.MaterialEditingLibrary.connect_material_property(metallic, "", unreal.MaterialProperty.MP_METALLIC)
    # Il fallback tecnico è applicato anche agli InstancedStaticMeshComponent.
    base.set_editor_property("used_with_instanced_static_meshes", True)
    unreal.MaterialEditingLibrary.recompile_material(base)
    unreal.EditorAssetLibrary.save_loaded_asset(base)

    materials = {}
    for name, (rgba, roughness, metallic) in PALETTE.items():
        asset_name = f"MI_RA_{name}"
        path = f"{MATERIAL_FOLDER}/{asset_name}"
        instance = unreal.load_asset(path) if unreal.EditorAssetLibrary.does_asset_exist(path) else None
        if not instance:
            instance = tools.create_asset(asset_name, MATERIAL_FOLDER, unreal.MaterialInstanceConstant, unreal.MaterialInstanceConstantFactoryNew())
        instance.set_editor_property("parent", base)
        unreal.MaterialEditingLibrary.set_material_instance_vector_parameter_value(instance, "BaseColor", unreal.LinearColor(*rgba))
        unreal.MaterialEditingLibrary.set_material_instance_scalar_parameter_value(instance, "Roughness", roughness)
        unreal.MaterialEditingLibrary.set_material_instance_scalar_parameter_value(instance, "Metallic", metallic)
        unreal.EditorAssetLibrary.save_loaded_asset(instance)
        materials[name] = instance
    return materials


def spawn_block(actor_subsystem, mesh, label, location, scale, material, rotation=(0.0, 0.0, 0.0), tags=(), collision=True):
    actor = actor_subsystem.spawn_actor_from_class(
        unreal.StaticMeshActor,
        unreal.Vector(*location),
        unreal.Rotator(pitch=rotation[0], yaw=rotation[1], roll=rotation[2]),
    )
    if not actor:
        raise RuntimeError(f"Impossibile creare il modulo tecnico: {label}")
    actor.set_actor_label(label)
    actor.tags = [unreal.Name(SLICE_TAG), unreal.Name(label), *[unreal.Name(tag) for tag in tags]]
    actor.set_actor_scale3d(unreal.Vector(*scale))
    actor.set_actor_enable_collision(collision)
    component = actor.static_mesh_component
    component.set_static_mesh(mesh)
    component.set_mobility(unreal.ComponentMobility.MOVABLE)
    component.set_collision_enabled(unreal.CollisionEnabled.QUERY_AND_PHYSICS if collision else unreal.CollisionEnabled.NO_COLLISION)
    component.set_material(0, material)
    return actor


def spawn_label(actor_subsystem, text, location, rotation=(0.0, 90.0, 0.0)):
    actor = actor_subsystem.spawn_actor_from_class(
        unreal.TextRenderActor,
        unreal.Vector(*location),
        unreal.Rotator(pitch=rotation[0], yaw=rotation[1], roll=rotation[2]),
    )
    actor.set_actor_label(f"RA_Label_{text}")
    actor.tags = [unreal.Name(SLICE_TAG), unreal.Name("RA_TECHNICAL_LABEL")]
    actor.text_render.set_editor_property("text", text)
    actor.text_render.set_editor_property("world_size", 42.0)
    return actor


def spawn_generated_building(
    actor_subsystem,
    label,
    role_tag,
    front_tag,
    generator_name,
    seed,
    location,
    rotation=(0.0, 0.0, 0.0),
    floors=1,
    width_cm=None,
    depth_cm=None,
):
    actor = actor_subsystem.spawn_actor_from_class(
        unreal.RARomanProceduralBuildingActor,
        unreal.Vector(*location),
        unreal.Rotator(pitch=rotation[0], yaw=rotation[1], roll=rotation[2]),
    )
    if not actor:
        raise RuntimeError(f"Impossibile creare il generatore: {label}")
    actor.set_actor_label(label)
    storey_tag = "RA_TWO_STOREY" if floors > 1 else "RA_ONE_STOREY"
    actor.tags = [
        unreal.Name(SLICE_TAG),
        unreal.Name(role_tag),
        unreal.Name(front_tag),
        unreal.Name(storey_tag),
        unreal.Name("RA_CONTINUOUS_FACADE"),
        unreal.Name(label),
    ]
    actor.set_editor_property("generate_on_begin_play", True)
    actor.set_editor_property("auto_rebuild_in_editor", False)
    actor.set_editor_property("show_debug_labels", False)
    parameters = actor.get_editor_property("building_parameters")
    parameters.set_editor_property("random_seed", seed)
    parameters.set_editor_property("maximum_module_count", 768)
    parameters.set_editor_property("floor_count", floors)
    if width_cm is not None:
        parameters.set_editor_property("width_cm", width_cm)
    if depth_cm is not None:
        parameters.set_editor_property("depth_cm", depth_cm)
    actor.set_editor_property("building_parameters", parameters)
    actor.set_editor_property("decoration_variant", seed % 7)
    generation_succeeded = getattr(actor, generator_name)()
    if not generation_succeeded or actor.get_generated_instance_count() <= 0:
        result = actor.get_editor_property("last_generation_result")
        errors = result.get_editor_property("errors")
        details = "; ".join(
            f"{item.get_editor_property('code')}: {item.get_editor_property('message')}"
            for item in errors
        )
        components = ", ".join(
            f"{component.get_name()}={component.get_instance_count()}"
            for component in actor.get_editor_property("generated_instance_components")
            if component
        )
        raise RuntimeError(
            f"Generazione fallita per {label}; success={generation_succeeded}; "
            f"instances={actor.get_generated_instance_count()}; "
            f"rooms={actor.get_accessible_room_count()}; "
            f"rejected={actor.get_rejected_transform_count()}; errors={details}; "
            f"components={components}"
        )
    actor.clear_generated_building()
    label_y = location[1] - 520 if location[1] > 0 else location[1] + 520
    spawn_label(actor_subsystem, label.removeprefix("RA_"), (location[0] + 260, label_y, 265), (0.0, 90.0 if location[1] < 0 else -90.0, 0.0))
    return actor


def remove_previous_slice(actor_subsystem):
    for actor in actor_subsystem.get_all_level_actors():
        if SLICE_TAG in [str(tag) for tag in actor.tags]:
            actor_subsystem.destroy_actor(actor)


def build_roman_street(actor_subsystem, cube, materials):
    spawn_block(actor_subsystem, cube, "RA_SafetyFloor", (0, 0, -90), (170, 70, 1), materials["Ground"], tags=("RA_SAFETY_FLOOR",))
    # Basoli modulari: due corsie, giunti sfalsati e leggere irregolarità deterministiche.
    for index, x in enumerate(range(-8000, 8001, 400)):
        offset = 12 if index % 3 == 0 else -8 if index % 3 == 1 else 0
        for lane, y in enumerate((-205, 205)):
            spawn_block(actor_subsystem, cube, f"RA_RoadStone_{index}_{lane}", (x + (lane * 18), y + offset, 0), (3.8, 3.7, 0.18), materials["RoadStone"], rotation=(0.0, (index % 5 - 2) * 0.45, 0.0), tags=("RA_ROMAN_ROAD", "RA_RomanRoad"))
    for y, suffix in ((-475, "South"), (475, "North")):
        spawn_block(actor_subsystem, cube, f"RA_Curb_{suffix}", (0, y, 28), (165, 0.45, 0.55), materials["Stone"], tags=("RA_CURB",))
        sidewalk_y = -620 if y < 0 else 620
        spawn_block(actor_subsystem, cube, f"RA_Sidewalk_{suffix}", (0, sidewalk_y, 40), (165, 2.4, 0.42), materials["Sidewalk"], tags=("RA_SIDEWALK",))
        channel_y = -430 if y < 0 else 430
        spawn_block(actor_subsystem, cube, f"RA_DrainageChannel_{suffix}", (0, channel_y, 5), (165, 0.32, 0.12), materials["Water"], tags=("RA_DRAINAGE",), collision=False)

    for index, y in enumerate(range(-420, 421, 210)):
        spawn_block(actor_subsystem, cube, f"RA_CrossingStone_{index}", (-2650, y, 42), (1.35, 1.1, 0.42), materials["Sidewalk"], tags=("RA_CROSSING_STONE",))

    # Vicolo laterale e slargo riconoscibile.
    spawn_block(actor_subsystem, cube, "RA_Alley", (250, 2200, 2), (4.5, 28, 0.16), materials["RoadStone"], tags=("RA_ALLEY",))
    spawn_block(actor_subsystem, cube, "RA_AlleySidewalk_West", (-105, 2200, 35), (1.6, 28, 0.35), materials["Sidewalk"], tags=("RA_SIDEWALK", "RA_ALLEY"))
    spawn_block(actor_subsystem, cube, "RA_AlleySidewalk_East", (605, 2200, 35), (1.6, 28, 0.35), materials["Sidewalk"], tags=("RA_SIDEWALK", "RA_ALLEY"))
    spawn_block(actor_subsystem, cube, "RA_SmallPlaza", (250, -1500, 5), (15, 11, 0.18), materials["Stone"], tags=("RA_PLAZA",))
    spawn_block(actor_subsystem, cube, "RA_SewerEntrance", (3150, 500, 18), (1.6, 1.1, 0.22), materials["Metal"], tags=("RA_SEWER_VISIBLE",))


def build_environment(actor_subsystem, cube, cylinder, sphere, materials):
    for index, (x, y) in enumerate(((5100, 1850), (5700, 2050), (6250, 1750))):
        spawn_block(actor_subsystem, cylinder, f"RA_TreeTrunk_{index}", (x, y, 155), (0.32, 0.32, 3.1), materials["Wood"], tags=("RA_VEGETATION",), collision=False)
        spawn_block(actor_subsystem, sphere, f"RA_TreeCrown_{index}", (x, y, 390), (1.45, 1.45, 1.6), materials["Vegetation"], tags=("RA_VEGETATION",), collision=False)
    for index, x in enumerate((4800, 5450, 6100, 6750)):
        spawn_block(actor_subsystem, cube, f"RA_Planter_{index}", (x, 1250, 55), (2.2, 1.0, 0.55), materials["Brick"], tags=("RA_URBAN_GARDEN",))


def build_scene():
    level_editor = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    actor_subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    if unreal.EditorAssetLibrary.does_asset_exist(LEVEL_PACKAGE):
        if not level_editor.load_level(LEVEL_PACKAGE):
            raise RuntimeError(f"Impossibile caricare la mappa: {LEVEL_PACKAGE}")
    elif not level_editor.new_level(LEVEL_PACKAGE):
        raise RuntimeError(f"Impossibile creare la mappa: {LEVEL_PACKAGE}")
    remove_previous_slice(actor_subsystem)
    materials = create_technical_materials()
    cube, cylinder, sphere = require_asset(CUBE), require_asset(CYLINDER), require_asset(SPHERE)
    build_roman_street(actor_subsystem, cube, materials)

    player_start = actor_subsystem.spawn_actor_from_class(unreal.PlayerStart, unreal.Vector(-7350, 0, 125), unreal.Rotator())
    player_start.set_actor_label("RA_PlayerStart_VerticalSlice")
    player_start.tags = [unreal.Name(SLICE_TAG), unreal.Name("RA_PLAYER_START")]

    # Due fronti urbani addossati, con una sola interruzione intenzionale
    # in corrispondenza del vicolo e dello slargo della fontana.
    north = (0.0, 0.0, 0.0)
    south = (0.0, 180.0, 0.0)
    north_buildings = (
        ("PopularHouse_N1", "RA_RESIDENTIAL", "generate_popular_house", 30001, -6900, 2),
        ("DomusMedia_N1", "RA_RESIDENTIAL", "generate_domus_media", 30002, -5800, 2),
        ("Taberna_N1", "RA_COMMERCIAL", "generate_taberna", 30003, -4700, 2),
        ("Pistrinum", "RA_PRODUCTIVE", "generate_pistrinum", 30004, -3600, 1),
        ("PopularHouse_N2", "RA_RESIDENTIAL", "generate_popular_house", 30005, -2500, 1),
        ("DomusMedia_N2", "RA_RESIDENTIAL", "generate_domus_media", 30006, -1400, 2),
        ("Taberna_N2", "RA_COMMERCIAL", "generate_taberna", 30007, 1350, 1),
        ("PopularHouse_N3", "RA_RESIDENTIAL", "generate_popular_house", 30008, 2450, 2),
        ("BathComplex", "RA_BATH", "generate_bath_complex", 30009, 3550, 1),
        ("DomusMedia_N3", "RA_RESIDENTIAL", "generate_domus_media", 30010, 4650, 2),
        ("UrbanGarden", "RA_GARDEN", "generate_urban_garden", 30011, 5900, 1),
    )
    south_buildings = (
        ("Taberna_S1", "RA_COMMERCIAL", "generate_taberna", 30101, -6900, 1),
        ("Thermopolium", "RA_COMMERCIAL", "generate_thermopolium", 30102, -5800, 2),
        ("PopularHouse_S1", "RA_RESIDENTIAL", "generate_popular_house", 30103, -4700, 2),
        ("DomusMedia_S1", "RA_RESIDENTIAL", "generate_domus_media", 30104, -3600, 1),
        ("Taberna_S2", "RA_COMMERCIAL", "generate_taberna", 30105, -2500, 2),
        ("PopularHouse_S2", "RA_RESIDENTIAL", "generate_popular_house", 30106, -1400, 1),
        ("DomusMedia_S2", "RA_RESIDENTIAL", "generate_domus_media", 30107, 1900, 2),
        ("Taberna_S3", "RA_COMMERCIAL", "generate_taberna", 30108, 3000, 1),
        ("PopularHouse_S3", "RA_RESIDENTIAL", "generate_popular_house", 30109, 4100, 2),
        ("MetalWorkshop", "RA_PRODUCTIVE", "generate_metal_workshop", 30110, 5200, 1),
        ("ServiceYard", "RA_SERVICE", "generate_service_yard", 30111, 6400, 1),
    )
    for name, role, generator, seed, x, floors in north_buildings:
        spawn_generated_building(actor_subsystem, f"RA_{name}", role, "RA_URBAN_FRONT_NORTH", generator, seed, (x, 1110, 45), north, floors)
    for name, role, generator, seed, x, floors in south_buildings:
        spawn_generated_building(actor_subsystem, f"RA_{name}", role, "RA_URBAN_FRONT_SOUTH", generator, seed, (x, -1110, 45), south, floors)
    fountain = spawn_generated_building(
        actor_subsystem, "RA_PublicFountain", "RA_WATER", "RA_URBAN_PLAZA",
        "generate_public_fountain", 30200, (250, -1450, 45), south, 1
    )
    fountain.tags = [*fountain.tags, unreal.Name("RA_PLAZA_FOCAL_POINT")]
    spawn_generated_building(
        actor_subsystem, "RA_AqueductSection", "RA_UTILITY", "RA_INFRASTRUCTURE_EDGE",
        "generate_aqueduct_section", 30201, (7050, 2350, 45), north, 1
    )

    for side, y in ((1, 690), (-1, -690)):
        for index, x in enumerate((-6900, -5800, -4700, -3600, -2500, -1400, 1350, 2450, 3550, 4650)):
            spawn_block(actor_subsystem, cube, f"RA_Threshold_{side}_{index}", (x, y, 48), (1.55, 0.75, 0.18), materials["Stone"], tags=("RA_BUILDING_ENTRANCE",))

    build_environment(actor_subsystem, cube, cylinder, sphere, materials)
    directional = actor_subsystem.spawn_actor_from_class(
        unreal.DirectionalLight,
        unreal.Vector(0, 0, 1800),
        unreal.Rotator(pitch=-42.0, yaw=-32.0, roll=0.0),
    )
    directional.set_actor_label("RA_DirectionalLight_Dynamic")
    directional.tags = [unreal.Name(SLICE_TAG), unreal.Name("RA_DYNAMIC_LIGHT")]
    directional.light_component.set_mobility(unreal.ComponentMobility.MOVABLE)
    directional.light_component.set_editor_property("intensity", 5.5)
    directional.light_component.set_editor_property("atmosphere_sun_light", True)
    skylight = actor_subsystem.spawn_actor_from_class(unreal.SkyLight, unreal.Vector(0, 0, 1200))
    skylight.set_actor_label("RA_SkyLight_Dynamic")
    skylight.tags = [unreal.Name(SLICE_TAG), unreal.Name("RA_DYNAMIC_LIGHT")]
    skylight.light_component.set_mobility(unreal.ComponentMobility.MOVABLE)
    skylight.light_component.set_editor_property("intensity", 0.85)
    atmosphere = actor_subsystem.spawn_actor_from_class(unreal.SkyAtmosphere, unreal.Vector())
    atmosphere.set_actor_label("RA_SkyAtmosphere")
    atmosphere.tags = [unreal.Name(SLICE_TAG)]
    fog = actor_subsystem.spawn_actor_from_class(unreal.ExponentialHeightFog, unreal.Vector(0, 0, -150))
    fog.set_actor_label("RA_ExponentialHeightFog")
    fog.tags = [unreal.Name(SLICE_TAG), unreal.Name("RA_DYNAMIC_LIGHTING")]
    fog.component.set_editor_property("fog_density", 0.006)
    post = actor_subsystem.spawn_actor_from_class(unreal.PostProcessVolume, unreal.Vector())
    post.set_actor_label("RA_PostProcess_AutoExposure")
    post.tags = [unreal.Name(SLICE_TAG), unreal.Name("RA_DYNAMIC_LIGHTING")]
    post.set_editor_property("unbound", True)
    title = spawn_label(actor_subsystem, "ROMA AETERNA - STRADA POMPEIANA COMPATTA", (-7200, -520, 360))
    title.text_render.set_editor_property("world_size", 64.0)

    world = level_editor.get_current_level().get_outer()
    world.get_world_settings().set_editor_property("default_game_mode", unreal.RAVerticalSliceGameMode)
    if not level_editor.save_current_level():
        raise RuntimeError(f"Impossibile salvare la mappa: {LEVEL_PACKAGE}")
    unreal.log("VISUAL_CONSOLIDATION_MAP_CREATED: RomaAeternaVerticalSlice")


build_scene()
