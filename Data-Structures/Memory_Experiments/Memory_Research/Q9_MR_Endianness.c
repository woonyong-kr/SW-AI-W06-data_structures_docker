#include <stdio.h>

/*
실험 목표
- 하나의 정수를 바이트 단위로 읽었을 때 메모리에 어떤 순서로 저장되는지 확인합니다.

관찰 포인트
- unsigned char*로 정수의 메모리를 보면 각 바이트를 직접 읽을 수 있습니다.
- 0x12345678이 메모리에서 78 56 34 12로 보이면 little-endian입니다.
- 반대로 12 34 56 78로 보이면 big-endian입니다.
*/

int main(void) {
  unsigned int value = 0x12345678;
  unsigned char* p = (unsigned char*)&value;
  int i;

  printf("value = 0x%x\n", value);
  printf("바이트 순서:");
  for (i = 0; i < (int)sizeof(value); i++) {
    printf(" %02x", p[i]);
  }
  printf("\n");

  if (p[0] == 0x78) {
    printf("판정: little-endian\n");
  } else if (p[0] == 0x12) {
    printf("판정: big-endian\n");
  } else {
    printf("판정: 알 수 없음\n");
  }
  return 0;
}
