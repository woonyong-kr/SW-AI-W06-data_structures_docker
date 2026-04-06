#include <stdio.h>

/* 포인터 연습 문제 8
문제: int* 포인터 배열을 각 포인터가 가리키는 값 기준으로 오름차순 정렬하세요.
입력: n, 이어서 n개 정수
출력: 정렬된 포인터 값: ...
*/

void sortIntPointers(int* ptrs[], int n);
void qsorted(int* ptrs[], int left, int right);

int main(void) {
  int n;
  int values[100];
  int* ptrs[100];
  int i;

  // 정수 개수를 입력받습니다.
  if (scanf("%d", &n) != 1) return 0;

  // 실제 정수값은 values 배열에 저장합니다.
  // ptrs 배열에는 각 정수의 주소를 저장합니다.
  for (i = 0; i < n; i++) {
    scanf("%d", &values[i]);
    ptrs[i] = &values[i];
  }

  // ptrs 배열 안의 포인터 순서만 정렬합니다.
  sortIntPointers(ptrs, n);

  // *ptrs[i]는 ptrs[i]가 가리키는 실제 값입니다.
  printf("정렬된 포인터 값:");
  for (i = 0; i < n; i++) printf(" %d", *ptrs[i]);
  printf("\n");
  return 0;
}

void sortIntPointers(int* ptrs[], int n) {
  // Todo: 포인터 배열 자체를 정렬하되, 비교 기준은 각 포인터가 가리키는 값으로
  // 삼으세요.

  if (ptrs == NULL || n <= 1) return;
  qsorted(ptrs, 0, n - 1);
}

void qsorted(int* ptrs[], int left, int right) {
  if (ptrs == NULL || left >= right) return;

  int i = left;
  int j = right;
  int* pivot = ptrs[(left + right) / 2];

  while (i <= j) {
    while (*ptrs[i] < *pivot) i++;
    while (*ptrs[j] > *pivot) j--;

    if (i <= j) {
      int* temp = ptrs[i];
      ptrs[i] = ptrs[j];
      ptrs[j] = temp;
      i++;
      j--;
    }
  }
  if (left < j) qsorted(ptrs, left, j);
  if (i < right) qsorted(ptrs, i, right);
}
