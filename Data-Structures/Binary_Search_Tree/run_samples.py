#!/usr/bin/env python3
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / 'scripts'))
from q_runner_common import parse_args, run_cases

CASES = {'Data-Structures/Binary_Search_Tree/Q1_F_BST.c': {'input': '1\n5\n1\n3\n1\n7\n2\n0\n', 'expected': ['이진 탐색 트리의 레벨 순회 결과: 5 3 7']}, 'Data-Structures/Binary_Search_Tree/Q2_F_BST.c': {'input': '1\n5\n1\n3\n1\n7\n2\n0\n', 'expected': ['이진 탐색 트리의 중위 순회 결과: 3 5 7']}, 'Data-Structures/Binary_Search_Tree/Q3_F_BST.c': {'input': '1\n5\n1\n3\n1\n7\n2\n0\n', 'expected': ['이진 탐색 트리의 전위 순회 결과: 5 3 7']}, 'Data-Structures/Binary_Search_Tree/Q4_F_BST.c': {'input': '1\n5\n1\n3\n1\n7\n2\n0\n', 'expected': ['이진 탐색 트리의 후위 순회 결과: 3 7 5']}, 'Data-Structures/Binary_Search_Tree/Q5_F_BST.c': {'input': '1\n5\n1\n3\n1\n7\n2\n0\n', 'expected': ['이진 탐색 트리의 후위 순회 결과: 3 7 5']}}

if __name__ == '__main__':
    args = parse_args('Binary_Search_Tree 샘플 실행 및 기본 채점')
    raise SystemExit(run_cases(CASES, target=args.target, config=args.config))
