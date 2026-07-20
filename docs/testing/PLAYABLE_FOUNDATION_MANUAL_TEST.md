# Playable foundation — manual PIE test

- **Status:** `MANUAL_VERIFICATION_REQUIRED`
- **Build target:** `RomaAeternaEditor Win64 Development`
- **Map:** `/Game/RA/Dev/Maps/TechnicalSandbox`

## Objective

Verify physical input, visual presentation and uninterrupted traversal that cannot be honestly established by the headless automation used in this milestone.

## Preconditions

- Final Development Editor build reports `Result: Succeeded`.
- Four `RomaAeterna.PlayableFoundation` tests pass.
- No second Unreal Editor instance is holding stale modules.

## Procedure

| # | Check | Expected result | Status |
|---:|---|---|---|
| 1 | Open `RomaAeterna.uproject` | Editor opens without critical dialog | MANUAL_VERIFICATION_REQUIRED |
| 2 | Open `TechnicalSandbox` | labeled street, sky and lit geometry are visible | MANUAL_VERIFICATION_REQUIRED |
| 3 | Start Play In Editor | one placeholder Character spawns at PlayerStart | MANUAL_VERIFICATION_REQUIRED |
| 4 | Hold W, then S | forward/back movement follows camera yaw | MANUAL_VERIFICATION_REQUIRED |
| 5 | Press A and D | lateral movement works without loss of control | MANUAL_VERIFICATION_REQUIRED |
| 6 | Move mouse | pitch/yaw respond and remain controllable | MANUAL_VERIFICATION_REQUIRED |
| 7 | Hold left Shift while moving | speed increases, then returns on release | MANUAL_VERIFICATION_REQUIRED |
| 8 | Press Space | Character jumps and lands with collision | MANUAL_VERIFICATION_REQUIRED |
| 9 | Press F9 | first-person camera activates and body does not obstruct view | MANUAL_VERIFICATION_REQUIRED |
| 10 | Move, sprint and jump in first person | same pawn and locomotion state remain active | MANUAL_VERIFICATION_REQUIRED |
| 11 | Press F9 repeatedly | third/first alternation remains stable with one active camera | MANUAL_VERIFICATION_REQUIRED |
| 12 | Approach side walls and narrowing | spring arm retracts; camera does not enter geometry | MANUAL_VERIFICATION_REQUIRED |
| 13 | Cross obstacle/ramp and reach route end | collision and boundaries prevent falling into void | MANUAL_VERIFICATION_REQUIRED |
| 14 | Stop PIE | session ends without crash or critical error | MANUAL_VERIFICATION_REQUIRED |

## Evidence to record

Record tester, date, UE build, pass/fail per row, relevant log lines, screenshots for visual defects and a reproduction sequence for every failure. Do not replace `MANUAL_VERIFICATION_REQUIRED` with `PASS` without executing the row.

## Related documents

- [Player Character](../technical/PLAYER_CHARACTER.md)
- [Camera system](../technical/CAMERA_SYSTEM.md)
- [TechnicalSandbox](../technical/TECHNICAL_SANDBOX.md)
- [Build report](../audits/PLAYABLE_FOUNDATION_BUILD_REPORT.md)
