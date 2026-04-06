#include <stdio.h>

/*
실험 목표
- const가 포인터 왼쪽/오른쪽 어디에 붙느냐에 따라 의미가 달라진다는 점을 확인합니다.

관찰 포인트
- const int* p1 : 가리키는 값 변경 불가, 다른 주소 가리키기 가능
- int* const p2 : 가리키는 값 변경 가능, 다른 주소 가리키기 불가
- const int* const p3 : 값 변경 불가, 다른 주소 가리키기 불가
*/

int main(void) {
  int a = 10;
  int b = 20;
  const int* p1 = &a;
  int* const p2 = &a;
  const int* const p3 = &a;

  printf("const int* p1: 가리키는 값 변경 불가, 다른 주소 가리키기 가능\n");
  p1 = &b;
  printf("p1 -> %d\n", *p1);

  printf("int* const p2: 가리키는 값 변경 가능, 다른 주소 가리키기 불가\n");
  *p2 = 99;
  printf("p2 -> %d\n", *p2);

  printf("const int* const p3: 값 변경 불가, 다른 주소 가리키기 불가\n");
  printf("p3 -> %d\n", *p3);
  return 0;
}
