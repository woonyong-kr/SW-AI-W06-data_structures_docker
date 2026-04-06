#include <stdio.h>

/*
실험 목표
- 문자열 리터럴과 문자 배열이 메모리 관점에서 다르게 취급된다는 점을 확인합니다.

관찰 포인트
- char array_str[] = "hello" 는 배열 안에 문자열이 복사되므로 수정이 가능합니다.
- const char* literal_str = "hello" 는 리터럴 위치를 가리키므로 읽기 전용 영역일 수 있습니다.
- 그래서 literal_str[0] 수정은 정의되지 않은 동작(UB)입니다.
*/

int main(void) {
  char array_str[] = "hello";
  const char* literal_str = "hello";

  printf("array_str 주소: %p\n", (void*)array_str);
  printf("literal_str 주소: %p\n", (void*)literal_str);

  array_str[0] = 'H';
  printf("배열 수정 후: %s\n", array_str);

  printf("문자열 리터럴은 읽기 전용 영역에 있을 수 있어 수정하면 위험합니다.\n");
  printf("literal_str[0] = 'H' 같은 코드는 정의되지 않은 동작(UB)입니다.\n");
  return 0;
}
