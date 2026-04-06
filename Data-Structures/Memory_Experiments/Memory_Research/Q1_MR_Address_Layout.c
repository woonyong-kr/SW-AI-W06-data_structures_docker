#include <stdio.h>
#include <stdlib.h>

/*
실험 목표
- 전역 변수, static 변수, 지역 변수, 힙 메모리, 문자열 리터럴이 보통 서로 다른 메모리 영역에 놓인다는 점을 관찰합니다.
- C 코드에서 보는 주소는 가상 주소이며, 각 영역이 대략 어떻게 분리되어 보이는지 확인합니다.

관찰 포인트
- global/static 주소는 보통 실행 파일의 데이터 영역 근처에 모입니다.
- local 변수와 포인터 변수는 스택에 놓여 서로 가까운 주소로 보이는 경우가 많습니다.
- malloc으로 얻은 주소는 힙 영역 주소입니다.
- 문자열 리터럴은 읽기 전용 데이터 영역 근처 주소로 보일 수 있습니다.
*/

int global_var = 100;
static int static_var = 200;

int main(void) {
  int local_var = 300;
  int* heap_var = (int*)malloc(sizeof(int));
  const char* literal = "hello";

  if (heap_var == NULL) return 1;
  *heap_var = 400;

  printf("global_var 주소: %p\n", (void*)&global_var);
  printf("static_var 주소: %p\n", (void*)&static_var);
  printf("local_var 주소: %p\n", (void*)&local_var);
  printf("heap_var 주소(포인터 변수): %p\n", (void*)&heap_var);
  printf("heap_var가 가리키는 힙 주소: %p\n", (void*)heap_var);
  printf("literal 주소: %p\n", (void*)literal);

  free(heap_var);
  return 0;
}
