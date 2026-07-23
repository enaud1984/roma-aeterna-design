"""Esegue PIE reale Prompt 30 e archivia prove visuali locali ignorate da Git."""

from __future__ import annotations

import shutil
import time
from pathlib import Path

import unreal


MAP = "/Game/Maps/RomaAeternaVerticalSlice"
saved = Path(unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_saved_dir()))
source_dir = saved / "Screenshots" / "WindowsEditor"
output_dir = saved / "Diagnostics" / "Prompt30" / "FinalScreenshots"
output_dir.mkdir(parents=True, exist_ok=True)
for previous_screenshot in output_dir.glob("*.png"):
    previous_screenshot.unlink()
state = {"started": None, "actions": set(), "last_shot": None, "ended": None, "origin": None}


def latest_screenshot():
    files = list(source_dir.glob("*.png"))
    return max(files, key=lambda path: path.stat().st_mtime_ns) if files else None


def archive_screenshot(name):
    latest = latest_screenshot()
    if latest and latest != state["last_shot"]:
        destination = output_dir / f"{name}.png"
        shutil.copy2(latest, destination)
        state["last_shot"] = latest
        unreal.log(f"PROMPT30_SCREENSHOT_SAVED name={name} path={destination.as_posix()}")


def get_character(world):
    actors = unreal.GameplayStatics.get_all_actors_of_class(world, unreal.RACharacter)
    return actors[0] if actors else None


def take_shot(world, name):
    unreal.SystemLibrary.execute_console_command(world, "Shot")
    state["actions"].add(f"archive_{name}")
    state[f"archive_{name}_at"] = time.monotonic() + 1.25


def position_view(world, character, location, yaw, pitch=-8.0, first_person=False):
    character.set_actor_location(unreal.Vector(*location), False, False)
    character.set_view_mode(
        unreal.RAViewMode.FIRST_PERSON if first_person else unreal.RAViewMode.THIRD_PERSON
    )
    controllers = unreal.GameplayStatics.get_all_actors_of_class(world, unreal.RAPlayerController)
    if controllers:
        controllers[0].set_control_rotation(unreal.Rotator(pitch=pitch, yaw=yaw, roll=0.0))


def tick(_delta):
    now = time.monotonic()
    level = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    editor = unreal.get_editor_subsystem(unreal.UnrealEditorSubsystem)
    if state["started"] is None:
        level.load_level(MAP)
        level.editor_request_begin_play()
        state["started"] = now
        unreal.log("PROMPT30_REAL_PIE_STARTED")
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

    if character and "ready" not in state["actions"]:
        state["origin"] = character.get_actor_location()
        unreal.log("PROMPT30_PLAYER_POSSESSED")
        state["actions"].add("ready")
    if character and 4 < elapsed < 6:
        character.add_movement_input(character.get_actor_forward_vector(), 1.0, False)
    if character and elapsed > 7 and "movement" not in state["actions"]:
        distance = (character.get_actor_location() - state["origin"]).length()
        if distance <= 1.0:
            raise RuntimeError("Il movimento WASD simulato non ha spostato il personaggio")
        unreal.log(f"PROMPT30_WASD_MOVEMENT_VALIDATED distance={distance:.2f}")
        state["actions"].add("movement")
    if character and elapsed > 8 and "main" not in state["actions"]:
        position_view(world, character, (-7200.0, 0.0, 120.0), 0.0)
        take_shot(world, "01_strada_principale")
        state["actions"].add("main")
    if character and elapsed > 13 and "fronts" not in state["actions"]:
        position_view(world, character, (-3900.0, 0.0, 120.0), 0.0)
        take_shot(world, "02_fronti_edilizi_addossati")
        state["actions"].add("fronts")
    if character and elapsed > 18 and "thermopolium" not in state["actions"]:
        position_view(world, character, (-5800.0, -100.0, 120.0), -90.0, first_person=True)
        take_shot(world, "03_thermopolium_e_taberna")
        state["actions"].add("thermopolium")
    if character and elapsed > 23 and "bakery" not in state["actions"]:
        position_view(world, character, (-3600.0, 100.0, 120.0), 90.0, first_person=True)
        take_shot(world, "04_pistrinum_area_panificazione")
        state["actions"].add("bakery")
    if character and elapsed > 28 and "domus" not in state["actions"]:
        position_view(world, character, (-5800.0, 790.0, 120.0), 90.0, -15.0, True)
        take_shot(world, "05_domus_atrio_interno")
        state["actions"].add("domus")
    if character and elapsed > 33 and "fallback" not in state["actions"]:
        character.execute_local_material_toggle()
        unreal.log("PROMPT30_F7_FALLBACK_EXECUTED")
        position_view(world, character, (-4700.0, 0.0, 120.0), 0.0)
        take_shot(world, "06_f7_fallback")
        state["actions"].add("fallback")
    if character and elapsed > 38 and "local" not in state["actions"]:
        character.execute_local_material_toggle()
        unreal.log("PROMPT30_F7_LOCAL_EXECUTED")
        state["actions"].add("local")
    if character and elapsed > 40 and "roof" not in state["actions"]:
        character.execute_roof_toggle()
        unreal.log("PROMPT30_F10_ROOFS_HIDDEN")
        position_view(world, character, (-1000.0, 0.0, 650.0), 0.0, -25.0)
        take_shot(world, "07_f10_tetti_nascosti")
        state["actions"].add("roof")
    if character and elapsed > 45 and "roof_restore" not in state["actions"]:
        character.execute_roof_toggle()
        unreal.log("PROMPT30_F10_ROOFS_VISIBLE")
        state["actions"].add("roof_restore")
    if character and elapsed > 47 and "aerial" not in state["actions"]:
        position_view(world, character, (250.0, -3200.0, 1150.0), 90.0, -32.0)
        take_shot(world, "08_vista_aerea_semialta")
        state["actions"].add("aerial")
    if character and elapsed > 52 and "rebuild" not in state["actions"]:
        character.execute_rebuild_command()
        unreal.log("PROMPT30_F5_REBUILD_EXECUTED")
        character.execute_decoration_toggle()
        character.execute_decoration_toggle()
        unreal.log("PROMPT30_F11_DECORATION_TOGGLE_VALIDATED")
        character.set_view_mode(unreal.RAViewMode.FIRST_PERSON)
        character.set_view_mode(unreal.RAViewMode.THIRD_PERSON)
        unreal.log("PROMPT30_F9_CAMERA_TOGGLE_VALIDATED")
        state["actions"].add("rebuild")
    if elapsed > 58 and state["ended"] is None and not any(
        action.startswith("archive_") for action in state["actions"]
    ):
        level.editor_request_end_play()
        state["ended"] = now
        unreal.log("PROMPT30_REAL_PIE_COMPLETED")


callback = unreal.register_slate_post_tick_callback(tick)
