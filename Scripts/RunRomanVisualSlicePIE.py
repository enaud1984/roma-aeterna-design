"""Esegue una prova PIE reale e salva screenshot diagnostici locali ignorati da Git."""

from __future__ import annotations

import shutil
import time
from pathlib import Path

import unreal


MAP = "/Game/Maps/RomaAeternaVerticalSlice"
saved = Path(unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_saved_dir()))
source_dir = saved / "Screenshots" / "WindowsEditor"
output_dir = saved / "Diagnostics" / "Prompt29Bis" / "FinalScreenshots"
output_dir.mkdir(parents=True, exist_ok=True)
state = {
    "started": None,
    "actions": set(),
    "last_shot": None,
    "ended": None,
}


def latest_screenshot():
    files = list(source_dir.glob("*.png"))
    return max(files, key=lambda path: path.stat().st_mtime_ns) if files else None


def archive_screenshot(name):
    latest = latest_screenshot()
    if latest and latest != state["last_shot"]:
        destination = output_dir / f"{name}.png"
        shutil.copy2(latest, destination)
        state["last_shot"] = latest
        unreal.log(f"PROMPT29BIS_SCREENSHOT_SAVED name={name} path={destination.as_posix()}")


def get_character(world):
    actors = unreal.GameplayStatics.get_all_actors_of_class(world, unreal.RACharacter)
    return actors[0] if actors else None


def take_shot(world, name):
    unreal.SystemLibrary.execute_console_command(world, "Shot")
    state["actions"].add(f"archive_{name}")
    state[f"archive_{name}_at"] = time.monotonic() + 1.5


def tick(_delta):
    now = time.monotonic()
    level = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    editor = unreal.get_editor_subsystem(unreal.UnrealEditorSubsystem)
    if state["started"] is None:
        level.load_level(MAP)
        level.editor_request_begin_play()
        state["started"] = now
        unreal.log("PROMPT29BIS_REAL_PIE_STARTED")
        return
    elapsed = now - state["started"]
    if state["ended"] is not None:
        if now - state["ended"] > 3:
            unreal.unregister_slate_post_tick_callback(callback)
            unreal.SystemLibrary.quit_editor()
        return
    world = editor.get_game_world()
    if not world:
        return
    character = get_character(world)

    for action in tuple(state["actions"]):
        if action.startswith("archive_") and now >= state.get(f"{action}_at", now + 1):
            archive_screenshot(action.removeprefix("archive_"))
            state["actions"].remove(action)

    if character and "character_ready" not in state["actions"]:
        unreal.log("PROMPT29BIS_PLAYER_POSSESSED")
        state["actions"].add("character_ready")
    if elapsed > 8 and character and "general" not in state["actions"]:
        take_shot(world, "vista_generale_materiali_locali")
        state["actions"].add("general")
    if elapsed > 12 and "fallback_toggle" not in state["actions"] and character:
        character.execute_local_material_toggle()
        unreal.log("PROMPT29BIS_F7_FALLBACK_EXECUTED")
        state["actions"].add("fallback_toggle")
    if elapsed > 15 and "fallback_toggle" in state["actions"] and "fallback_shot" not in state["actions"]:
        take_shot(world, "f7_materiali_fallback")
        state["actions"].add("fallback_shot")
    if elapsed > 19 and "local_toggle" not in state["actions"] and character:
        character.execute_local_material_toggle()
        unreal.log("PROMPT29BIS_F7_LOCAL_EXECUTED")
        state["actions"].add("local_toggle")
    if elapsed > 22 and "local_toggle" in state["actions"] and "local_shot" not in state["actions"]:
        take_shot(world, "f7_materiali_locali")
        state["actions"].add("local_shot")
    if elapsed > 26 and "roof_hide" not in state["actions"] and character:
        character.execute_roof_toggle()
        unreal.log("PROMPT29BIS_F10_HIDE_EXECUTED")
        state["actions"].add("roof_hide")
    if elapsed > 29 and "roof_hide" in state["actions"] and "roof_hidden_shot" not in state["actions"]:
        take_shot(world, "f10_tetti_nascosti")
        state["actions"].add("roof_hidden_shot")
    if elapsed > 33 and "roof_show" not in state["actions"] and character:
        character.execute_roof_toggle()
        unreal.log("PROMPT29BIS_F10_SHOW_EXECUTED")
        state["actions"].add("roof_show")
    if elapsed > 36 and "roof_show" in state["actions"] and "roof_visible_shot" not in state["actions"]:
        take_shot(world, "f10_tetti_visibili")
        state["actions"].add("roof_visible_shot")
    if elapsed > 40 and "rebuild" not in state["actions"] and character:
        character.execute_rebuild_command()
        unreal.log("PROMPT29BIS_F5_REBUILD_EXECUTED")
        state["actions"].add("rebuild")
    if elapsed > 43 and "rebuild" in state["actions"] and "rebuild_shot" not in state["actions"]:
        take_shot(world, "dopo_f5_rebuild")
        state["actions"].add("rebuild_shot")
    if elapsed > 47 and "decoration_fallback" not in state["actions"] and character:
        character.execute_decoration_toggle()
        unreal.log("PROMPT29BIS_F11_FALLBACK_EXECUTED")
        state["actions"].add("decoration_fallback")
    if elapsed > 50 and "decoration_fallback_shot" not in state["actions"]:
        take_shot(world, "f11_decorazioni_fallback")
        state["actions"].add("decoration_fallback_shot")
    if elapsed > 54 and "decoration_local" not in state["actions"] and character:
        character.execute_decoration_toggle()
        unreal.log("PROMPT29BIS_F11_DECORATIONS_EXECUTED")
        state["actions"].add("decoration_local")
    if elapsed > 57 and "decoration_local_shot" not in state["actions"]:
        take_shot(world, "f11_decorazioni_attive")
        state["actions"].add("decoration_local_shot")
    if elapsed > 61 and "interior" not in state["actions"] and character:
        buildings = unreal.GameplayStatics.get_all_actors_of_class(
            world, unreal.RARomanProceduralBuildingActor
        )
        target = min(
            buildings,
            key=lambda actor: (
                actor.get_actor_location() - unreal.Vector(-5000.0, 1050.0, 45.0)
            ).length(),
            default=None,
        )
        if target:
            interior = target.get_actor_transform().transform_location(
                unreal.Vector(-220.0, -260.0, 96.0)
            )
            character.set_actor_location(interior, False, False)
            character.set_view_mode(unreal.RAViewMode.FIRST_PERSON)
            unreal.log("PROMPT29BIS_F9_FIRST_PERSON_EXECUTED")
            controllers = unreal.GameplayStatics.get_all_actors_of_class(
                world, unreal.RAPlayerController
            )
            if controllers:
                controllers[0].set_control_rotation(
                    unreal.Rotator(pitch=-18.0, yaw=62.0, roll=0.0)
                )
            unreal.log("PROMPT29BIS_INTERIOR_CAMERA_POSITIONED")
        state["actions"].add("interior")
    if elapsed > 64 and "interior_shot" not in state["actions"]:
        take_shot(world, "interno_domus_affresco_pavimento")
        state["actions"].add("interior_shot")
    if elapsed > 69 and state["ended"] is None and not any(
        action.startswith("archive_") for action in state["actions"]
    ):
        level.editor_request_end_play()
        state["ended"] = now
        unreal.log("PROMPT29BIS_REAL_PIE_COMPLETED")
callback = unreal.register_slate_post_tick_callback(tick)
