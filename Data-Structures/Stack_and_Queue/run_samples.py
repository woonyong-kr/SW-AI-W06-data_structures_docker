#!/usr/bin/env python3
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / 'scripts'))
from q_runner_common import parse_args, run_cases

CASES = {'Data-Structures/Stack_and_Queue/Q1_C_SQ.c': {'input': '1\n1\n1\n2\n1\n3\n1\n4\n2\n3\n0\n', 'expected': ['홀수를 제거한 뒤의 큐: 2 4']}, 'Data-Structures/Stack_and_Queue/Q2_C_SQ.c': {'input': '1\n1\n1\n2\n1\n3\n1\n4\n2\n3\n0\n', 'expected': ['짝수를 제거한 뒤의 스택: 3 1']}, 'Data-Structures/Stack_and_Queue/Q3_C_SQ.c': {'input': '1\n4\n1\n5\n1\n6\n1\n7\n2\n0\n', 'expected': ['스택은 쌍별로 연속적입니다.']}, 'Data-Structures/Stack_and_Queue/Q4_C_SQ.c': {'input': '1\n1\n1\n2\n1\n3\n2\n0\n', 'expected': ['원소를 뒤집은 뒤의 큐: 3 2 1']}, 'Data-Structures/Stack_and_Queue/Q5_C_SQ.c': {'input': '1\n1\n1\n2\n1\n3\n2\n0\n', 'expected': ['뒤집힌 결과 큐: 3 2 1']}, 'Data-Structures/Stack_and_Queue/Q6_C_SQ.c': {'input': '1\n1\n1\n2\n1\n3\n1\n4\n3\n2\n0\n', 'expected': ['지정한 값이 나올 때까지 제거한 뒤의 스택: 2 1']}, 'Data-Structures/Stack_and_Queue/Q7_C_SQ.c': {'input': '1\n([])\n2\n0\n', 'expected': ['균형이 맞습니다!']}}

if __name__ == '__main__':
    args = parse_args('Stack_and_Queue 샘플 실행 및 기본 채점')
    raise SystemExit(run_cases(CASES, target=args.target, config=args.config))
