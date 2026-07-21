# Git LFS asset strategy — Prompt 19

## Current ignore status

`.gitignore` already ignores Unreal generated output and local IDE state: `Binaries/`, `DerivedDataCache/`, `Intermediate/`, `Saved/`, `.vs/`, `.idea/`, solution/database files and local editor settings. `.gitattributes` is currently absent, so no Git LFS rules are active.

## Recommendation

Do not enable Git LFS blindly in this branch. Enable it only after the team confirms storage/quota, local Git LFS installation, hosting support and migration policy.

Recommended candidate patterns when approved:

```gitattributes
*.uasset filter=lfs diff=lfs merge=lfs -text
*.umap filter=lfs diff=lfs merge=lfs -text
*.fbx filter=lfs diff=lfs merge=lfs -text
*.glb filter=lfs diff=lfs merge=lfs -text
*.gltf filter=lfs diff=lfs merge=lfs -text
*.obj filter=lfs diff=lfs merge=lfs -text
*.blend filter=lfs diff=lfs merge=lfs -text
*.wav filter=lfs diff=lfs merge=lfs -text
*.tga filter=lfs diff=lfs merge=lfs -text
*.exr filter=lfs diff=lfs merge=lfs -text
*.mp4 filter=lfs diff=lfs merge=lfs -text
*.psd filter=lfs diff=lfs merge=lfs -text
```

## PNG caution

`*.png` should not be globally moved to LFS without review. Pros: large textures and generated diagrams avoid repository bloat. Cons: documentation diagrams are diffable enough for normal Git workflows, LFS can complicate text-doc review, and small UI/reference PNG files do not justify LFS overhead. Prefer path- or size-based policy, for example only production texture folders or files above a documented threshold.

## Size guidance

- Maximum recommended single non-LFS asset: 25 MB.
- Maximum recommended single LFS asset without review: 250 MB.
- Maximum recommended asset commit: 500 MB total changed binary payload.
- Anything larger requires explicit approval and import notes.

## Risks

- LFS quota exhaustion.
- Contributors without Git LFS receiving pointer files only.
- Broken CI/editor workflows if LFS files are not fetched.
- History rewrite risk if retroactive migration is attempted.

## Verification procedure

```bash
git lfs version
git lfs track
git check-attr filter -- Content/RA/SomeAsset.uasset
git status --short
git lfs ls-files
```

## Rollback procedure for future LFS-rule-only change

1. Remove the uncommitted `.gitattributes` changes.
2. Run `git lfs untrack '<pattern>'` before commit if a pattern was added by mistake.
3. Re-check `git status --short` and `git lfs track`.
4. Do not rewrite history unless explicitly approved.

## Prerequisites

- Git LFS installed locally.
- Repository host supports LFS.
- Team storage/quota confirmed.
- CI/build machines run `git lfs pull` before Unreal validation.

## JPG caution

Like PNG, `*.jpg` should not be globally tracked by LFS without a path/size policy. Pros: large photographic reference sets and texture sources avoid Git bloat. Cons: small documentation screenshots and compressed references are easier to review when stored normally. Prefer production texture folders and file-size thresholds rather than a blanket rule.
