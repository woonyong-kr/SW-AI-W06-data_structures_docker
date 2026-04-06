#include <stdio.h>
#include <stdlib.h>

/*
실험 목표
- realloc 후 주소가 유지될 수도 있고 바뀔 수도 있다는 점을 관찰합니다.

관찰 포인트
- realloc은 기존 블록을 그대로 늘릴 수 있으면 같은 주소를 유지합니다.
- 여유 공간이 없으면 새 블록으로 옮기고 기존 데이터를 복사할 수 있습니다.
- 즉 realloc 후에는 반드시 반환된 새 주소를 기준으로 계속 사용해야 합니다.
*/

int main(void) {
  int i;
  int* arr = (int*)malloc(sizeof(int) * 3);
  if (arr == NULL) return 1;

  for (i = 0; i < 3; i++) arr[i] = i + 1;

  printf("초기 주소: %p\n", (void*)arr);
  printf("초기 값: %d %d %d\n", arr[0], arr[1], arr[2]);

  arr = (int*)realloc(arr, sizeof(int) * 6);
  if (arr == NULL) return 1;

  for (i = 3; i < 6; i++) arr[i] = i + 1;

  printf("realloc 후 주소: %p\n", (void*)arr);
  printf("확장 후 값: %d %d %d %d %d %d\n",
         arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);

  free(arr);
  return 0;
}
