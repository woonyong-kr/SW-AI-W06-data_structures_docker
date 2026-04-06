#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

/*
실험 목표
- 서로 다른 두 가상 주소가 같은 공유 메모리 내용을 볼 수 있음을 확인합니다.

관찰 포인트
- p1과 p2의 가상 주소는 다릅니다.
- 하지만 같은 shm 객체를 MAP_SHARED로 매핑했기 때문에 한쪽에서 값이나 문자열을 바꾸면 다른 쪽에서도 바로 보입니다.
- 이 실험은 "서로 다른 가상 주소가 같은 실제 내용을 공유할 수 있다"는 점을 간접적으로 보여줍니다.
*/

int main(void) {
  const char* name = "/memory_research_shared_demo";
  const size_t size = 4096;
  int fd = shm_open(name, O_CREAT | O_RDWR, 0600);
  int* p1;
  int* p2;

  if (fd == -1) return 1;
  if (ftruncate(fd, (off_t)size) == -1) return 1;

  p1 = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  p2 = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);

  if (p1 == MAP_FAILED || p2 == MAP_FAILED) return 1;

  printf("p1 가상 주소: %p\n", (void*)p1);
  printf("p2 가상 주소: %p\n", (void*)p2);

  p1[0] = 1234;
  printf("p1[0]=1234 후: p1=%d, p2=%d\n", p1[0], p2[0]);

  p2[0] = 7777;
  printf("p2[0]=7777 후: p1=%d, p2=%d\n", p1[0], p2[0]);

  strcpy((char*)(p1 + 1), "shared-text");
  printf("문자열 공유 확인: %s\n", (char*)(p2 + 1));

  munmap(p1, size);
  munmap(p2, size);
  shm_unlink(name);
  return 0;
}
