#include <stdio.h>

/*
실험 목표
- int, int*, int**가 각각 무엇을 저장하는지 한 번에 확인합니다.

관찰 포인트
- p는 x의 주소를 저장합니다.
- pp는 p의 주소를 저장합니다.
- *p 는 실제 x의 값이고, **pp도 결국 같은 x의 값입니다.
*/

int main(void) {
  int x = 42;
  int* p = &x;
  int** pp = &p;

  printf("x 값: %d\n", x);
  printf("&x: %p\n", (void*)&x);
  printf("p 값(&x): %p\n", (void*)p);
  printf("&p: %p\n", (void*)&p);
  printf("*p: %d\n", *p);
  printf("pp 값(&p): %p\n", (void*)pp);
  printf("&pp: %p\n", (void*)&pp);
  printf("*pp(=p): %p\n", (void*)*pp);
  printf("**pp(=x): %d\n", **pp);

  return 0;
}
