#!/usr/bin/env python3
import argparse
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]


def normalize(text: str) -> str:
    return ' '.join(text.split())


def build_binary(source: Path, config: str = 'debug') -> Path:
    topic = source.parent.name
    out_dir = REPO / 'bin' / config / topic
    out_dir.mkdir(parents=True, exist_ok=True)
    binary = out_dir / source.stem

    cmd = ['gcc']
    cmd.extend(['-g', '-O0'] if config == 'debug' else ['-O2'])
    cmd.extend(['-w', str(source), '-o', str(binary)])
    proc = subprocess.run(cmd, capture_output=True, text=True)
    if proc.returncode != 0:
        raise RuntimeError(f'컴파일 실패\n{proc.stderr}')
    return binary


def run_cases(cases: dict, target: str = 'all', config: str = 'debug') -> int:
    if target == 'all':
        targets = list(cases.keys())
    else:
        needle = target.lower()
        targets = [path for path in cases if needle in path.lower() or needle in Path(path).stem.lower()]
        if not targets:
            print(f'대상과 일치하는 테스트를 찾지 못했습니다: {target}')
            return 1

    passed = 0
    for rel_path in targets:
        case = cases[rel_path]
        source = REPO / rel_path
        print(f'== {rel_path} ==')
        try:
            binary = build_binary(source, config=config)
        except RuntimeError as exc:
            print(str(exc))
            print('결과: FAIL\n')
            continue

        run_proc = subprocess.run(
            [str(binary)],
            input=case['input'],
            capture_output=True,
            text=True,
            timeout=5,
        )
        output = run_proc.stdout + run_proc.stderr
        normalized_output = normalize(output)
        missing = [exp for exp in case['expected'] if normalize(exp) not in normalized_output]
        if missing:
            print('결과: FAIL')
            print('누락된 기대 문자열:')
            for item in missing:
                print(f'- {item}')
            print('실행 출력:')
            print(output)
            print()
        else:
            passed += 1
            print('결과: PASS')
            print('실행 출력:')
            print(output)
            print()

    print(f'요약: {passed}/{len(targets)} 통과')
    return 0 if passed == len(targets) else 1


def parse_args(description: str):
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('target', nargs='?', default='all', help='all 또는 특정 파일 이름')
    parser.add_argument('--config', choices=['debug', 'release'], default='debug')
    return parser.parse_args()
