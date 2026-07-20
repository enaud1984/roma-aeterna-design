"""Build the lightweight Technical Roman Street Prototype in TechnicalSandbox."""

from __future__ import annotations

import unreal


LEVEL_PACKAGE = "/Game/RA/Dev/Maps/TechnicalSandbox"
CUBE = "/Engine/BasicShapes/Cube.Cube"
WORLD_GRID_MATERIAL = "/Engine/BasicShapes/BasicShapeMaterial_Inst"
BASIC_MATERIAL = "/Engine/BasicShapes/BasicShapeMaterial"
PROTOTYPE_TAG = "RA_TechnicalStreet"


def require_asset(path: str):
    asset = unreal.load_asset(path)
    if not asset:
        raise RuntimeError(f"Required engine asset is missing: {path}")
    return asset


def spawn_block(
    actor_subsystem,
    mesh,
    label: str,
    location: tuple[float, float, float],
    scale: tuple[float, float, float],
    rotation: tuple[float, float, float] = (0.0, 0.0, 0.0),
    material=None,
):
    actor = actor_subsystem.spawn_actor_from_class(
        unreal.StaticMeshActor,
        unreal.Vector(*location),
        unreal.Rotator(*rotation),
    )
    if not actor:
        raise RuntimeError(f"Unable to spawn prototype block: {label}")

    actor.set_actor_label(label)
    actor.tags = [unreal.Name(PROTOTYPE_TAG)]
    actor.set_actor_scale3d(unreal.Vector(*scale))
    actor.set_actor_enable_collision(True)

    component = actor.static_mesh_component
    component.set_static_mesh(mesh)
    component.set_mobility(unreal.ComponentMobility.STATIC)
    component.set_collision_enabled(unreal.CollisionEnabled.QUERY_AND_PHYSICS)
    if material:
        component.set_material(0, material)
    return actor


def remove_previous_prototype(actor_subsystem) -> None:
    for actor in actor_subsystem.get_all_level_actors():
        if PROTOTYPE_TAG in [str(tag) for tag in actor.tags]:
            actor_subsystem.destroy_actor(actor)


def build_scene() -> None:
    level_editor = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    actor_subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)

    if unreal.EditorAssetLibrary.does_asset_exist(LEVEL_PACKAGE):
        if not level_editor.load_level(LEVEL_PACKAGE):
            raise RuntimeError(f"Unable to load existing level: {LEVEL_PACKAGE}")
    elif not level_editor.new_level(LEVEL_PACKAGE):
        raise RuntimeError(f"Unable to create level: {LEVEL_PACKAGE}")

    remove_previous_prototype(actor_subsystem)

    cube = require_asset(CUBE)
    grid = require_asset(WORLD_GRID_MATERIAL)
    basic = require_asset(BASIC_MATERIAL)

    # A broad safety floor prevents the prototype player from falling into the void.
    spawn_block(actor_subsystem, cube, "RA_Ground_SafetyFloor", (0, 0, -35), (58, 20, 0.5), material=basic)

    # Three joined pieces provide a straight test section and a gentle camera-test bend.
    spawn_block(actor_subsystem, cube, "RA_Road_West", (-1500, 0, 0), (25, 6, 0.2), material=grid)
    spawn_block(actor_subsystem, cube, "RA_Road_Centre", (700, 0, 0), (19, 6, 0.2), material=grid)
    spawn_block(actor_subsystem, cube, "RA_Road_EastBend", (2250, 155, 0), (13, 6, 0.2), rotation=(0, 7, 0), material=grid)

    # Sidewalks and enclosing masses make camera collision and spatial legibility testable.
    for y, suffix in ((390, "North"), (-390, "South")):
        spawn_block(actor_subsystem, cube, f"RA_Sidewalk_{suffix}", (0, y, 18), (55, 1.5, 0.36), material=basic)
    for y, suffix in ((850, "North"), (-850, "South")):
        spawn_block(actor_subsystem, cube, f"RA_Wall_{suffix}_West", (-1450, y, 210), (26, 0.6, 4.2), material=basic)
        spawn_block(actor_subsystem, cube, f"RA_Wall_{suffix}_East", (1500, y, 210), (22, 0.6, 4.2), rotation=(0, 4 if y > 0 else -4, 0), material=basic)

    # Narrowing, low obstacle and ramp validate capsule clearance, jump and slope movement.
    spawn_block(actor_subsystem, cube, "RA_Narrowing_North", (350, 500, 90), (4.0, 3.0, 1.8), material=basic)
    spawn_block(actor_subsystem, cube, "RA_Narrowing_South", (350, -500, 90), (4.0, 3.0, 1.8), material=basic)
    spawn_block(actor_subsystem, cube, "RA_LowObstacle", (-450, 150, 28), (1.7, 2.0, 0.55), material=basic)
    spawn_block(actor_subsystem, cube, "RA_TestRamp", (1350, -130, 22), (5.0, 2.3, 0.28), rotation=(0, -7, 0), material=basic)

    # Terminal barriers keep the playable test route bounded.
    spawn_block(actor_subsystem, cube, "RA_TerminalBarrier_West", (-2950, 0, 150), (0.6, 18, 3.0), material=basic)
    spawn_block(actor_subsystem, cube, "RA_TerminalBarrier_East", (3300, 350, 150), (0.6, 18, 3.0), rotation=(0, 7, 0), material=basic)

    player_start = actor_subsystem.spawn_actor_from_class(
        unreal.PlayerStart,
        unreal.Vector(-2450, 0, 125),
        unreal.Rotator(0, 0, 0),
    )
    player_start.set_actor_label("RA_PlayerStart_TechnicalStreet")
    player_start.tags = [unreal.Name(PROTOTYPE_TAG)]

    directional = actor_subsystem.spawn_actor_from_class(
        unreal.DirectionalLight,
        unreal.Vector(0, 0, 900),
        unreal.Rotator(-38, -28, 0),
    )
    directional.set_actor_label("RA_DirectionalLight_Prototype")
    directional.tags = [unreal.Name(PROTOTYPE_TAG)]
    directional.light_component.set_editor_property("intensity", 7.0)
    directional.light_component.set_editor_property("atmosphere_sun_light", True)

    skylight = actor_subsystem.spawn_actor_from_class(unreal.SkyLight, unreal.Vector(0, 0, 600))
    skylight.set_actor_label("RA_SkyLight_Prototype")
    skylight.tags = [unreal.Name(PROTOTYPE_TAG)]
    skylight.light_component.set_editor_property("intensity", 1.0)

    atmosphere = actor_subsystem.spawn_actor_from_class(unreal.SkyAtmosphere, unreal.Vector(0, 0, 0))
    atmosphere.set_actor_label("RA_SkyAtmosphere_Prototype")
    atmosphere.tags = [unreal.Name(PROTOTYPE_TAG)]

    title = actor_subsystem.spawn_actor_from_class(
        unreal.TextRenderActor,
        unreal.Vector(-2300, -720, 240),
        unreal.Rotator(0, 90, 0),
    )
    title.set_actor_label("RA_PrototypeTitle")
    title.tags = [unreal.Name(PROTOTYPE_TAG)]
    title.text_render.set_editor_property("text", "Technical Roman Street Prototype")
    title.text_render.set_editor_property("world_size", 48.0)

    if not level_editor.save_current_level():
        raise RuntimeError(f"Unable to save level: {LEVEL_PACKAGE}")

    unreal.log("Built Technical Roman Street Prototype in TechnicalSandbox")


build_scene()
