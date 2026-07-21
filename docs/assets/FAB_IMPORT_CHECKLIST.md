# Fab import checklist — Prompt 19

## Before acquisition

- [ ] Confirm asset URL and exact title.
- [ ] Confirm publisher.
- [ ] Confirm current price; do not assume free.
- [ ] Confirm license/tier and save evidence.
- [ ] Confirm Unreal Engine compatibility and whether UE 5.8 is explicitly listed.
- [ ] Confirm import route: Add to Project, Create Project, or manual download/migration.
- [ ] Confirm approximate download size and disk budget if visible.

## During import

- [ ] Use Unreal/Fab tooling, not Explorer file moves.
- [ ] Import into a temporary local branch or project copy first.
- [ ] Do not touch `Content/RA/Dev/Maps/TechnicalSandbox.umap`.
- [ ] Record created Content folders.
- [ ] Keep vendor folders intact until migration plan is approved.

## Immediate validation

- [ ] Open the project in UE 5.8.
- [ ] Check new Content folders.
- [ ] Place one representative mesh in a local test map.
- [ ] Check scale, pivot, materials, collision, Nanite, LODs and shader compile cost.
- [ ] Run Prompt 18 manual PIE checks separately; status remains `MANUAL_VERIFICATION_REQUIRED` until executed.
