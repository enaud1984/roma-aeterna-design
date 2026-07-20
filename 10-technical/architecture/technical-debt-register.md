# Registro del debito tecnico

## Scopo

Track deliberate shortcuts in the implemented UE foundation so they cannot silently become production architecture.

## Register

| ID | Debt | Reason accepted now | Exit criterion | Priority | Status |
|---|---|---|---|---:|---|
| TD-001 | Enhanced Input actions/context are Character subobjects rather than Content assets | deterministic asset-free prototype | approved asset/rebinding strategy, migrated mappings and regression tests | P1 | Open |
| TD-002 | third-person body is cylinder/sphere static-mesh placeholder | no approved character asset or animation stack | reviewed skeletal mesh, AnimBP and first-person visibility policy | P1 | Open |
| TD-003 | no automated physical PIE traversal or input injection | headless unit tests cannot prove hardware interaction | functional/Gauntlet test covers locomotion, view toggle and route traversal | P1 | Open |
| TD-004 | prototype HUD uses Canvas text | avoids premature production UI dependency | replace or remove after onboarding/debug UI contract is approved | P2 | Open |
| TD-005 | TechnicalSandbox uses Engine primitives and shared materials | scene exists only for systems validation | historically reviewed graybox supersedes it without reusing claims | P2 | Open |

## Rules

Debt entries require an owner and target milestone during production planning. Closing an entry requires evidence in tests and an ADR when the replacement changes a public contract.

## Dependencies

- [Technical ADR](technical-adr.md)
- [Playable foundation report](../../docs/audits/PLAYABLE_FOUNDATION_BUILD_REPORT.md)

## Related documents

- [Player Character](../../docs/technical/PLAYER_CHARACTER.md)
- [Camera system](../../docs/technical/CAMERA_SYSTEM.md)
- [Enhanced Input](../../docs/technical/ENHANCED_INPUT.md)

## Open decisions and TODO

- Assign owners and target milestones at the next production planning gate.
- Select the production input-asset and automated functional-test strategy.
