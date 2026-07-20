# Enhanced Input — playable foundation

## Objective and scope

Define event-driven keyboard and mouse controls for the first controllable prototype using UE 5.8 Enhanced Input.

## Input contract

| Action | Type | Mapping | Trigger behavior |
|---|---|---|---|
| `IA_Move` | Axis2D | W, A, S, D | Triggered |
| `IA_Look` | Axis2D | Mouse 2D | Triggered |
| `IA_Jump` | Boolean | Space | Started / Completed |
| `IA_Sprint` | Boolean | Left Shift | Started / Completed |
| `IA_ToggleView` | Boolean | F9 | Started |

All mappings live in `IMC_Player`. Axis modifiers place W/S on the Y axis and negate A/S. `PawnClientRestart` removes and re-adds the context to the owning local-player subsystem, preventing duplicate active contexts after possession restarts.

## Architecture decision

Actions and context are named UObject default subobjects owned by `ARACharacter`, not separately authored Content assets. This makes the foundation deterministic and asset-free while preserving Enhanced Input semantics. Migrating them to reviewed Input Action assets before production rebinding is tracked as [TD-001](../../10-technical/architecture/technical-debt-register.md).

`Config/DefaultInput.ini` selects `EnhancedPlayerInput` and `EnhancedInputComponent`; the module and plugin dependencies are explicit in `RomaAeterna.Build.cs` and `RomaAeterna.uproject`.

## Error handling and performance

- An incompatible input component emits an `ensureMsgf` and no bindings are attempted.
- No per-frame polling is used.
- Mapping installation occurs on local pawn restart, not every frame.
- Toggle, sprint and jump are discrete Enhanced Input events.

## Validation

Automation checks that `IMC_Player` and all five actions exist and that the context exposes exactly eight key mappings. Physical input remains covered by the [manual protocol](../testing/PLAYABLE_FOUNDATION_MANUAL_TEST.md).

## Related documents

- [Player Character](PLAYER_CHARACTER.md)
- [Camera system](CAMERA_SYSTEM.md)
- [Build report](../audits/PLAYABLE_FOUNDATION_BUILD_REPORT.md)
