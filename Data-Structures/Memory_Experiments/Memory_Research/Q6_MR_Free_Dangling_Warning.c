#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
실험 목표
- free 후에도 포인터 변수 안의 주소값 자체는 남아 있을 수 있지만, 그 메모리는 더 이상 안전하게 접근할 수 없다는 점을 확인합니다.

관찰 포인트
- p를 free해도 q는 같은 숫자 주소를 계속 들고 있을 수 있습니다.
- 그러나 그 주소의 메모리는 이제 해제되었으므로 읽기/쓰기 모두 정의되지 않은 동작(UB)입니다.
- 즉 "주소가 남아 있음"과 "여전히 내 메모리임"은 전혀 다른 말입니다.
*/

int main(void) {
  char* p = (char*)malloc(32);
  char* q;

  if (p == NULL) return 1;

  strcpy(p, "hello-memory");
  q = p;

  printf("free 전 주소: %p\n", (void*)p);
  printf("free 전 값: %s\n", p);

  free(p);

  printf("q는 여전히 같은 주소를 들고 있음: %p\n", (void*)q);
  printf("주의: 여기서 q를 역참조하거나 출력하면 정의되지 않은 동작(UB)입니다.\n");
  printf("즉, 우연히 예전 값이 보일 수도 있고, 깨진 값이 보일 수도 있고, 바로 크래시 날 수도 있습니다.\n");
  printf("이 실험의 핵심은 '주소값은 남아 있어도, free 후 그 메모리는 더 이상 내 것이 아니다' 입니다.\n");

  return 0;
}
