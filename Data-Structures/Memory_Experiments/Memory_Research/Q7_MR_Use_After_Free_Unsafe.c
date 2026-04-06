#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
경고
- 이 파일은 의도적으로 use-after-free를 시연하는 위험 예제입니다.
- 어떤 환경에서는 예전 문자열처럼 보일 수 있지만, 그것은 "동작이 보장되기 때문"이 아니라 우연입니다.
- 다른 환경에서는 쓰레기 값이 나오거나 즉시 크래시가 날 수 있습니다.
*/

int main(void) {
  char* p = (char*)malloc(32);
  if (p == NULL) return 1;

  strcpy(p, "danger-zone");
  printf("free 전 주소: %p\n", (void*)p);
  printf("free 전 값: %s\n", p);

  free(p);

  printf("아래 줄은 정의되지 않은 동작(UB) 시연용입니다.\n");
  printf("환경에 따라 예전 값, 쓰레기 값, 크래시 중 아무거나 나올 수 있습니다.\n");
  printf("free 후 읽기 결과(위험): %s\n", p);

  return 0;
}
