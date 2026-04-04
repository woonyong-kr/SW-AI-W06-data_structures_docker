#!/usr/bin/env python3
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / 'scripts'))
from q_runner_common import parse_args, run_cases

CASES = {'Data-Structures/Linked_List/Q1_A_LL.c': {'input': '1\n5\n1\n3\n1\n7\n3\n0\n', 'expected': ['정렬된 연결 리스트 결과: 3 5 7']}, 'Data-Structures/Linked_List/Q2_A_LL.c': {'input': '1\n1\n1\n3\n1\n5\n2\n2\n2\n4\n2\n6\n3\n0\n', 'expected': ['결과 연결 리스트 1: 1 2 3 4 5 6', '결과 연결 리스트 2: 비어 있음']}, 'Data-Structures/Linked_List/Q3_A_LL.c': {'input': '1\n1\n1\n2\n1\n3\n1\n4\n2\n0\n', 'expected': ['홀수를 뒤로 이동한 뒤의 연결 리스트: 2 4 1 3']}, 'Data-Structures/Linked_List/Q4_A_LL.c': {'input': '1\n1\n1\n2\n1\n3\n1\n4\n2\n0\n', 'expected': ['짝수를 뒤로 이동한 뒤의 연결 리스트: 1 3 2 4']}, 'Data-Structures/Linked_List/Q5_A_LL.c': {'input': '1\n1\n1\n2\n1\n3\n1\n4\n1\n5\n2\n0\n', 'expected': ['앞쪽 연결 리스트: 1 2 3', '뒤쪽 연결 리스트: 4 5']}, 'Data-Structures/Linked_List/Q6_A_LL.c': {'input': '1\n1\n1\n5\n1\n3\n2\n0\n', 'expected': ['최댓값을 맨 앞으로 이동한 뒤의 연결 리스트: 5 1 3']}, 'Data-Structures/Linked_List/Q7_A_LL.c': {'input': '1\n1\n1\n2\n1\n3\n2\n0\n', 'expected': ['주어진 연결 리스트를 뒤집은 결과: 3 2 1']}}

if __name__ == '__main__':
    args = parse_args('Linked_List 샘플 실행 및 기본 채점')
    raise SystemExit(run_cases(CASES, target=args.target, config=args.config))
