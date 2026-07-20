"""Create the TechnicalSandbox level through Unreal Editor's Python API."""

import unreal


LEVEL_PACKAGE = "/Game/RA/Dev/Maps/TechnicalSandbox"


def main() -> None:
    level_editor = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    if unreal.EditorAssetLibrary.does_asset_exist(LEVEL_PACKAGE):
        if not level_editor.load_level(LEVEL_PACKAGE):
            raise RuntimeError(f"Unable to load existing level: {LEVEL_PACKAGE}")
        unreal.log(f"Validated existing technical map: {LEVEL_PACKAGE}")
        return

    if not level_editor.new_level(LEVEL_PACKAGE):
        raise RuntimeError(f"Unable to create level: {LEVEL_PACKAGE}")

    if not unreal.EditorAssetLibrary.save_asset(LEVEL_PACKAGE, only_if_is_dirty=False):
        raise RuntimeError(f"Unable to save level: {LEVEL_PACKAGE}")

    unreal.log(f"Created technical map: {LEVEL_PACKAGE}")


main()
