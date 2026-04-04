#!/usr/bin/env python3
import argparse
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]


def main() -> int:
    parser = argparse.ArgumentParser(description='Build a C source file into bin/debug or bin/release')
    parser.add_argument('source', help='Path to the .c source file')
    parser.add_argument('--config', choices=['debug', 'release'], default='debug')
    args = parser.parse_args()

    source = (REPO / args.source).resolve() if not Path(args.source).is_absolute() else Path(args.source)
    if not source.exists():
        print(f'소스 파일을 찾을 수 없습니다: {source}', file=sys.stderr)
        return 1

    topic = source.parent.name
    out_dir = REPO / 'bin' / args.config / topic
    out_dir.mkdir(parents=True, exist_ok=True)
    binary = out_dir / source.stem

    cmd = ['gcc', str(source), '-o', str(binary)]
    if args.config == 'debug':
        cmd[1:1] = ['-g', '-O0']
    else:
        cmd[1:1] = ['-O2']

    proc = subprocess.run(cmd, text=True)
    return proc.returncode


if __name__ == '__main__':
    raise SystemExit(main())
