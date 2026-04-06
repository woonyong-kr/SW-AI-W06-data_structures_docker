#include <stddef.h>
#include <stdio.h>

/*
실험 목표
- 구조체 멤버 순서에 따라 패딩과 전체 크기가 달라질 수 있음을 확인합니다.

관찰 포인트
- struct A는 char 뒤에 int가 와서 정렬을 맞추기 위한 패딩이 들어갈 수 있습니다.
- struct B는 int를 먼저 두어 패딩을 줄여 더 작은 크기가 될 수 있습니다.
- offsetof를 보면 각 멤버가 실제로 몇 바이트 위치에 놓였는지 확인할 수 있습니다.
*/

struct A {
  char c;
  int i;
  char d;
};

struct B {
  int i;
  char c;
  char d;
};

int main(void) {
  printf("struct A sizeof: %zu\n", sizeof(struct A));
  printf("A.c offset: %zu\n", offsetof(struct A, c));
  printf("A.i offset: %zu\n", offsetof(struct A, i));
  printf("A.d offset: %zu\n", offsetof(struct A, d));
  printf("\n");
  printf("struct B sizeof: %zu\n", sizeof(struct B));
  printf("B.i offset: %zu\n", offsetof(struct B, i));
  printf("B.c offset: %zu\n", offsetof(struct B, c));
  printf("B.d offset: %zu\n", offsetof(struct B, d));
  return 0;
}
