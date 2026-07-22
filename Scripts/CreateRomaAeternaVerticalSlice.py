"""Crea in modo riproducibile la mappa tecnica giocabile del Prompt 24-BIS."""

from __future__ import annotations

import unreal


LEVEL_PACKAGE = "/Game/Maps/RomaAeternaVerticalSlice"
CUBE = "/Engine/BasicShapes/Cube.Cube"
GRID_MATERIAL = "/Engine/BasicShapes/BasicShapeMaterial_Inst"
BASIC_MATERIAL = "/Engine/BasicShapes/BasicShapeMaterial"
SLICE_TAG = "RA_VERTICAL_SLICE"


def require_asset(path: str):
    asset = unreal.load_asset(path)
    if not asset:
        raise RuntimeError(f"Asset Engine richiesto non trovato: {path}")
    return asset


def spawn_block(actor_subsystem, mesh, label, location, scale, material):
    actor = actor_subsystem.spawn_actor_from_class(
        unreal.StaticMeshActor, unreal.Vector(*location), unreal.Rotator()
    )
    if not actor:
        raise RuntimeError(f"Impossibile creare il blocco tecnico: {label}")
    actor.set_actor_label(label)
    actor.tags = [unreal.Name(SLICE_TAG), unreal.Name(label)]
    actor.set_actor_scale3d(unreal.Vector(*scale))
    actor.set_actor_enable_collision(True)
    component = actor.static_mesh_component
    component.set_static_mesh(mesh)
    component.set_mobility(unreal.ComponentMobility.STATIC)
    component.set_collision_enabled(unreal.CollisionEnabled.QUERY_AND_PHYSICS)
    component.set_material(0, material)
    return actor


def spawn_label(actor_subsystem, text, location):
    actor = actor_subsystem.spawn_actor_from_class(
        unreal.TextRenderActor, unreal.Vector(*location), unreal.Rotator(0.0, 90.0, 0.0)
    )
    if not actor:
        raise RuntimeError(f"Impossibile creare la label: {text}")
    actor.set_actor_label(f"RA_Label_{text}")
    actor.tags = [unreal.Name(SLICE_TAG), unreal.Name("RA_TECHNICAL_LABEL")]
    actor.text_render.set_editor_property("text", text)
    actor.text_render.set_editor_property("world_size", 54.0)
    return actor


def spawn_generated_building(actor_subsystem, label, role_tag, generator_name, seed, location):
    actor = actor_subsystem.spawn_actor_from_class(
        unreal.RARomanProceduralBuildingActor, unreal.Vector(*location), unreal.Rotator()
    )
    if not actor:
        raise RuntimeError(f"Impossibile creare il generatore: {label}")
    actor.set_actor_label(label)
    actor.tags = [unreal.Name(SLICE_TAG), unreal.Name(role_tag), unreal.Name(label)]
    actor.set_editor_property("generate_on_begin_play", True)
    actor.set_editor_property("auto_rebuild_in_editor", False)
    actor.set_editor_property("show_debug_labels", True)

    parameters = actor.get_editor_property("building_parameters")
    parameters.set_editor_property("random_seed", seed)
    parameters.set_editor_property("maximum_module_count", 512)
    actor.set_editor_property("building_parameters", parameters)

    generator = getattr(actor, generator_name)
    if not generator():
        raise RuntimeError(f"Generazione fallita per {label}")
    if actor.get_generated_instance_count() <= 0:
        raise RuntimeError(f"Il generatore {label} non ha prodotto moduli")
    actor.clear_generated_building()
    spawn_label(actor_subsystem, label.removeprefix("RA_"), (location[0] + 350, location[1], 420))
    return actor


def remove_previous_slice(actor_subsystem):
    for actor in actor_subsystem.get_all_level_actors():
        if SLICE_TAG in [str(tag) for tag in actor.tags]:
            actor_subsystem.destroy_actor(actor)


def build_scene():
    level_editor = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    actor_subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)

    if unreal.EditorAssetLibrary.does_asset_exist(LEVEL_PACKAGE):
        if not level_editor.load_level(LEVEL_PACKAGE):
            raise RuntimeError(f"Impossibile caricare la mappa: {LEVEL_PACKAGE}")
    elif not level_editor.new_level(LEVEL_PACKAGE):
        raise RuntimeError(f"Impossibile creare la mappa: {LEVEL_PACKAGE}")

    remove_previous_slice(actor_subsystem)
    cube = require_asset(CUBE)
    grid = require_asset(GRID_MATERIAL)
    basic = require_asset(BASIC_MATERIAL)

    # Piano di sicurezza e strada di 200 metri Unreal, entrambi con collisione.
    spawn_block(actor_subsystem, cube, "RA_SafetyFloor", (0, 0, -55), (220, 80, 1), basic)
    spawn_block(actor_subsystem, cube, "RA_RomanRoad", (0, 0, 0), (200, 12, 0.25), grid)
    for side_y, suffix in ((850, "North"), (-850, "South")):
        spawn_block(actor_subsystem, cube, f"RA_Sidewalk_{suffix}", (0, side_y, 22), (200, 4, 0.35), basic)
    for x in (-10000, 10000):
        spawn_block(actor_subsystem, cube, f"RA_RoadLimit_{x}", (x, 0, 160), (1, 35, 3.2), basic)

    player_start = actor_subsystem.spawn_actor_from_class(
        unreal.PlayerStart, unreal.Vector(-8800, 0, 130), unreal.Rotator()
    )
    player_start.set_actor_label("RA_PlayerStart_VerticalSlice")
    player_start.tags = [unreal.Name(SLICE_TAG), unreal.Name("RA_PLAYER_START")]

    # I sei actor seguenti usano realmente i generatori runtime dei Prompt 21-24.
    spawn_generated_building(actor_subsystem, "RA_PopularHouse", "RA_RESIDENTIAL", "generate_popular_house", 24001, (-7200, 1450, 25))
    spawn_generated_building(actor_subsystem, "RA_Taberna", "RA_COMMERCIAL", "generate_taberna", 24002, (-4300, -2050, 25))
    spawn_generated_building(actor_subsystem, "RA_BathComplex", "RA_BATH", "generate_bath_complex", 24003, (-900, 1450, 25))
    spawn_generated_building(actor_subsystem, "RA_PublicFountain", "RA_WATER", "generate_public_fountain", 24004, (2300, -1900, 25))
    spawn_generated_building(actor_subsystem, "RA_MetalWorkshop", "RA_PRODUCTIVE", "generate_metal_workshop", 24005, (5000, 1450, 25))
    spawn_generated_building(actor_subsystem, "RA_AqueductSection", "RA_UTILITY", "generate_aqueduct_section", 24006, (7600, -2050, 25))

    directional = actor_subsystem.spawn_actor_from_class(
        unreal.DirectionalLight, unreal.Vector(0, 0, 1400), unreal.Rotator(-40.0, -25.0, 0.0)
    )
    directional.set_actor_label("RA_DirectionalLight_VerticalSlice")
    directional.tags = [unreal.Name(SLICE_TAG)]
    directional.light_component.set_editor_property("intensity", 7.0)
    directional.light_component.set_editor_property("atmosphere_sun_light", True)

    skylight = actor_subsystem.spawn_actor_from_class(unreal.SkyLight, unreal.Vector(0, 0, 900))
    skylight.set_actor_label("RA_SkyLight_VerticalSlice")
    skylight.tags = [unreal.Name(SLICE_TAG)]
    skylight.light_component.set_editor_property("intensity", 1.0)

    atmosphere = actor_subsystem.spawn_actor_from_class(unreal.SkyAtmosphere, unreal.Vector())
    atmosphere.set_actor_label("RA_SkyAtmosphere_VerticalSlice")
    atmosphere.tags = [unreal.Name(SLICE_TAG)]

    title = spawn_label(actor_subsystem, "ROMA AETERNA - VERTICAL SLICE TECNICA", (-8200, -1050, 360))
    title.text_render.set_editor_property("world_size", 72.0)

    world = level_editor.get_current_level().get_outer()
    world.get_world_settings().set_editor_property("default_game_mode", unreal.RAVerticalSliceGameMode)
    if not level_editor.save_current_level():
        raise RuntimeError(f"Impossibile salvare la mappa: {LEVEL_PACKAGE}")
    unreal.log("VERTICAL_SLICE_MAP_CREATED: RomaAeternaVerticalSlice")


build_scene()
