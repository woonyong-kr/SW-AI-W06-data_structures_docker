#!/usr/bin/env python3
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / 'scripts'))
from q_runner_common import parse_args, run_cases

CASES = {'Data-Structures/Binary_Tree/Q1_E_BT.c': {'input': '1\n1\na\na\n2\n1\na\na\n3\n0\n', 'expected': ['두 트리는 구조적으로 동일합니다.']}, 'Data-Structures/Binary_Tree/Q2_E_BT.c': {'input': '1\n1\n2\na\n3\na\na\na\n2\n0\n', 'expected': ['이진 트리의 최대 높이는 3입니다.']}, 'Data-Structures/Binary_Tree/Q3_E_BT.c': {'input': '1\n1\n2\na\n3\na\na\na\n2\n0\n', 'expected': ['자식 노드가 정확히 하나인 노드의 개수는 2입니다.']}, 'Data-Structures/Binary_Tree/Q4_E_BT.c': {'input': '1\n2\n3\n5\na\na\na\na\n2\n0\n', 'expected': ['이진 트리의 모든 홀수 합은 8입니다.']}, 'Data-Structures/Binary_Tree/Q5_E_BT.c': {'input': '1\n1\n2\n3\na\na\na\na\n2\n0\n', 'expected': ['대칭 변환된 이진 트리: 3 1 2']}, 'Data-Structures/Binary_Tree/Q6_E_BT.c': {'input': '1\n5\n3\n7\na\na\na\na\n2\n6\n0\n', 'expected': ['6보다 작은 값들은 다음과 같습니다: 3 5']}, 'Data-Structures/Binary_Tree/Q7_E_BT.c': {'input': '1\n5\n3\n7\na\na\na\na\n2\n0\n', 'expected': ['이진 트리의 최솟값은 3입니다.']}, 'Data-Structures/Binary_Tree/Q8_E_BT.c': {'input': '1\n1\n2\na\n3\na\n4\na\na\na\n2\n0\n', 'expected': ['증손자가 하나 이상 있는 모든 노드의 값은 다음과 같습니다: 1']}}

if __name__ == '__main__':
    args = parse_args('Binary_Tree 샘플 실행 및 기본 채점')
    raise SystemExit(run_cases(CASES, target=args.target, config=args.config))
