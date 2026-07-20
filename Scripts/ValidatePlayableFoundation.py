"""Headless structural validation for the playable TechnicalSandbox scene."""

from __future__ import annotations

import unreal


LEVEL_PACKAGE = "/Game/RA/Dev/Maps/TechnicalSandbox"
PROTOTYPE_TAG = "RA_TechnicalStreet"


def validate() -> None:
    level_editor = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    actors = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    if not level_editor.load_level(LEVEL_PACKAGE):
        raise RuntimeError(f"Unable to load {LEVEL_PACKAGE}")

    tagged = [
        actor
        for actor in actors.get_all_level_actors()
        if PROTOTYPE_TAG in [str(tag) for tag in actor.tags]
    ]
    labels = {actor.get_actor_label() for actor in tagged}
    required_labels = {
        "RA_Ground_SafetyFloor",
        "RA_Road_West",
        "RA_Road_Centre",
        "RA_Road_EastBend",
        "RA_LowObstacle",
        "RA_TestRamp",
        "RA_PlayerStart_TechnicalStreet",
        "RA_DirectionalLight_Prototype",
        "RA_SkyLight_Prototype",
        "RA_SkyAtmosphere_Prototype",
        "RA_PrototypeTitle",
    }
    missing = sorted(required_labels - labels)
    if missing:
        raise RuntimeError(f"TechnicalSandbox is missing required actors: {missing}")

    class_names = [actor.get_class().get_name() for actor in tagged]
    if class_names.count("PlayerStart") != 1:
        raise RuntimeError("TechnicalSandbox must contain exactly one tagged PlayerStart")
    if len(tagged) < 20:
        raise RuntimeError(f"Prototype actor count is unexpectedly low: {len(tagged)}")

    unreal.log(f"PLAYABLE_FOUNDATION_SCENE_VALID: {len(tagged)} tagged actors")


validate()
