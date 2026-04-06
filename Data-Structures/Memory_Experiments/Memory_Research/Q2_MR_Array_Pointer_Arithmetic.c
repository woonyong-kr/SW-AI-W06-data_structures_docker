#include <stdio.h>

/*
실험 목표
- 배열 인덱스 접근과 포인터 산술이 사실상 같은 의미라는 점을 확인합니다.

관찰 포인트
- &arr[i] 와 arr + i 는 같은 주소를 나타냅니다.
- arr[i] 와 *(arr + i) 는 같은 값을 읽습니다.
- int 배열이라면 주소가 자료형 크기만큼 증가해 보입니다.
*/

int main(void) {
  int arr[5] = {10, 20, 30, 40, 50};
  int i;

  for (i = 0; i < 5; i++) {
    printf("i=%d | &arr[i]=%p | arr+i=%p | arr[i]=%d | *(arr+i)=%d\n",
           i,
           (void*)&arr[i],
           (void*)(arr + i),
           arr[i],
           *(arr + i));
  }

  return 0;
}
