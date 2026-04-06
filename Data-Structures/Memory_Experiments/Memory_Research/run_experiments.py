#!/usr/bin/env python3
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
REPO = ROOT.parents[1]
BIN = REPO / 'bin' / 'debug' / 'Memory_Research'

CASES = [
    'Q1_MR_Address_Layout.c',
    'Q2_MR_Array_Pointer_Arithmetic.c',
    'Q3_MR_Double_Pointer_Map.c',
    'Q4_MR_Realloc_Observe.c',
    'Q5_MR_Shared_Mapping.c',
    'Q6_MR_Free_Dangling_Warning.c',
    'Q8_MR_Struct_Padding.c',
    'Q9_MR_Endianness.c',
    'Q10_MR_String_Literal_vs_Array.c',
    'Q11_MR_Const_Pointer.c',
    'Q12_MR_Fork_Copy_On_Write.c',
]

OPTIONAL_UNSAFE = 'Q7_MR_Use_After_Free_Unsafe.c'


def build(source: Path) -> Path:
    BIN.mkdir(parents=True, exist_ok=True)
    out = BIN / source.stem
    cmd = ['gcc', '-g', '-O0', str(source), '-o', str(out)]
    proc = subprocess.run(cmd, capture_output=True, text=True)
    if proc.returncode != 0:
        raise RuntimeError(proc.stderr)
    return out


def run_one(name: str) -> int:
    source = ROOT / name
    exe = build(source)
    print(f'== {name} ==')
    proc = subprocess.run([str(exe)], capture_output=True, text=True)
    print(proc.stdout + proc.stderr)
    return proc.returncode


if __name__ == '__main__':
    target = sys.argv[1] if len(sys.argv) > 1 else 'safe'
    names = CASES if target == 'safe' else CASES + [OPTIONAL_UNSAFE] if target == 'all' else [target]
    code = 0
    for name in names:
        code |= run_one(name)
    raise SystemExit(code)
