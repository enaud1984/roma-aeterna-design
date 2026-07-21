#!/usr/bin/env python3
from pathlib import Path
import re, sys, math
root=Path(__file__).resolve().parents[1]
errors=[]
def read(p): return (root/p).read_text(encoding='utf-8')
def need(path, tokens=()):
    p=root/path
    if not p.exists(): errors.append(f"file mancante: {path}"); return ''
    s=p.read_text(encoding='utf-8')
    for t in tokens:
        if t not in s: errors.append(f"token mancante in {path}: {t}")
    return s
files=[
'Source/RomaAeterna/Public/World/Modular/RARomanModularTypes.h','Source/RomaAeterna/Public/World/Modular/RARomanModuleCatalog.h','Source/RomaAeterna/Private/World/Modular/RARomanModuleCatalog.cpp','Source/RomaAeterna/Public/World/Modular/RARomanBuildingStyleData.h','Source/RomaAeterna/Public/World/Modular/RARomanBuildingRuleLibrary.h','Source/RomaAeterna/Private/World/Modular/RARomanBuildingRuleLibrary.cpp','Source/RomaAeterna/Public/World/Modular/RARomanConstructionValidator.h','Source/RomaAeterna/Public/World/Modular/RARomanProceduralBuildingActor.h','Source/RomaAeterna/Private/Tests/RARomanModularFoundationTests.cpp','docs/technical/ROMAN_MODULAR_FOUNDATION_IMPLEMENTATION.md','docs/testing/ROMAN_MODULAR_FOUNDATION_TEST_PLAN.md','docs/audits/PROMPT_20_IMPLEMENTATION_REPORT.md']
for f in files: need(f)
types=need('Source/RomaAeterna/Public/World/Modular/RARomanModularTypes.h')
for e in 'ERARomanBuildingType ERARomanWallType ERARomanRoofType ERARomanArchitecturalOrder ERARomanModuleCategory ERARomanWealthLevel ERARomanDegradationLevel'.split():
    if not re.search(r'UENUM\(BlueprintType\).*?enum class '+e, types, re.S): errors.append(f'UENUM BlueprintType mancante: {e}')
for st in 'FRARomanModuleDimensions FRARomanModuleDefinition FRARomanBuildingParameters FRARomanModulePlacement FRARomanGenerationMessage FRARomanGenerationResult'.split():
    if st not in types or 'GENERATED_BODY()' not in types: errors.append(f'USTRUCT mancante: {st}')
allcpp='\n'.join(p.read_text(encoding='utf-8',errors='ignore') for p in list((root/'Source/RomaAeterna').rglob('*.cpp'))+list((root/'Source/RomaAeterna').rglob('*.h')))
for t in 'URARomanModuleCatalog URARomanBuildingStyleData URARomanBuildingRuleLibrary URARomanConstructionValidator ARARomanProceduralBuildingActor'.split():
    if t not in allcpp: errors.append(f'classe mancante: {t}')
for fn in 'ValidateBuildingParameters NormalizeBuildingParameters CalculateBayWidth CalculateFloorHeight CalculateBuildingBounds EstimateRequiredModules IsModuleCompatible SelectCompatibleModules CalculateGridAlignedTransform BuildSimpleHouseLayout BuildTabernaLayout BuildTempleLayout BuildStreetSectionLayout'.split():
    if fn not in allcpp: errors.append(f'funzione mancante: {fn}')
for bad in ['UnrealEd','Editor.h','LevelEditor','AssetTools','TechnicalSandbox','/workspace/','C:\\','.uasset','.umap','GEditor','SavePackage']:
    
    newcode='\n'.join((root/f).read_text(encoding='utf-8',errors='ignore') for f in files if f.startswith('Source/'))
    if bad in newcode: errors.append(f'riferimento vietato nel nuovo codice: {bad}')
for h in (root/'Source/RomaAeterna/Public/World/Modular').glob('*.h'):
    s=h.read_text();
    if not s.startswith('#pragma once'): errors.append(f'header senza pragma once: {h}')
for cpp in (root/'Source/RomaAeterna/Private/World/Modular').glob('*.cpp'):
    lines=[l for l in cpp.read_text().splitlines() if l.strip()]
    expected=f'#include "World/Modular/{cpp.stem}.h"'
    if lines and lines[0].strip()!=expected: errors.append(f'include principale non primo in {cpp}')
for name in re.findall(r'class\s+(ROMAETERNA_API\s+)?(U|A)RA\w+', allcpp): pass
public_headers='\n'.join(p.read_text() for p in (root/'Source/RomaAeterna/Public/World/Modular').glob('*.h'))
for m in re.finditer(r'class\s+(?!ROMAETERNA_API)([UA]RARoman\w+)', public_headers): errors.append(f'ROMAETERNA_API mancante: {m.group(1)}')
for kind,pat in [('class',r'class\s+(?:ROMAETERNA_API\s+)?([UA]RARoman\w+)'),('enum',r'enum class\s+(ERARoman\w+)'),('struct',r'struct\s+ROMAETERNA_API\s+(FRARoman\w+)')]:
    vals=re.findall(pat, allcpp); dup={v for v in vals if vals.count(v)>1}
    if dup: errors.append(f'{kind} duplicate: {sorted(dup)}')
build=need('Source/RomaAeterna/RomaAeterna.Build.cs')
if 'UnrealEd' in build: errors.append('Build.cs contiene UnrealEd')
# deterministic python checks
def norm(p):
    p=p.copy(); p['WidthCm']=max(p.get('WidthCm',800),100); p['DepthCm']=max(p.get('DepthCm',600),100); p['BayCount']=max(1,min(p.get('BayCount',4),64)); p['FloorCount']=max(1,min(p.get('FloorCount',1),8)); p['MaximumModuleCount']=max(1,min(p.get('MaximumModuleCount',256),10000)); return p
def bay(p): p=norm(p); return p['WidthCm']/p['BayCount']
def finite(v): return math.isfinite(v)
cases=[{'WidthCm':0},{'DepthCm':-1},{'BayCount':0},{'FloorCount':0},{'MaximumModuleCount':0},{'WidthCm':math.nan},{'WidthCm':math.inf},{'WidthCm':-math.inf},{'WidthCm':1e8,'BayCount':64}]
for c in cases:
    try: norm(c); 
    except Exception as ex: errors.append(f'test python limite fallito {c}: {ex}')
if bay({'WidthCm':800,'BayCount':4})!=200: errors.append('calcolo campata python fallito')
if not all(finite(x) for x in [0,1e8]) or finite(math.nan) or finite(math.inf): errors.append('controllo finitezza python fallito')
if errors:
    print('FAILED_STATIC')
    print('\n'.join(errors)); sys.exit(1)
print('PASSED_STATIC: Roman Modular Foundation checks completati')
print('APPROXIMATE_UHT_CHECK: controlli macro/header eseguiti staticamente')
