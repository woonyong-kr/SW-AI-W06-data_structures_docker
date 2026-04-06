#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  const char* shm_name = "/vm_shared_mapping_demo_openai";
  const size_t map_size = 4096;
  int fd;
  int* p1;
  int* p2;

  fd = shm_open(shm_name, O_CREAT | O_RDWR, 0600);
  if (fd == -1) {
    perror("shm_open");
    return 1;
  }

  if (ftruncate(fd, (off_t)map_size) == -1) {
    perror("ftruncate");
    close(fd);
    shm_unlink(shm_name);
    return 1;
  }

  p1 = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (p1 == MAP_FAILED) {
    perror("mmap p1");
    close(fd);
    shm_unlink(shm_name);
    return 1;
  }

  p2 = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (p2 == MAP_FAILED) {
    perror("mmap p2");
    munmap(p1, map_size);
    close(fd);
    shm_unlink(shm_name);
    return 1;
  }

  close(fd);

  printf("서로 다른 가상 주소에 같은 공유 메모리 객체를 매핑한 실험\n");
  printf("-------------------------------------------------------\n");
  printf("p1 virtual addr = %p\n", (void*)p1);
  printf("p2 virtual addr = %p\n", (void*)p2);
  printf("초기값: *p1 = %d, *p2 = %d\n", p1[0], p2[0]);

  p1[0] = 12345;
  printf("p1[0] = 12345 저장 후: *p1 = %d, *p2 = %d\n", p1[0], p2[0]);

  p2[0] = 777;
  printf("p2[0] = 777 저장 후:   *p1 = %d, *p2 = %d\n", p1[0], p2[0]);

  strcpy((char*)(p1 + 1), "shared-memory-string");
  printf("문자열도 공유됨: p2에서 읽은 문자열 = %s\n", (char*)(p2 + 1));

  if (munmap(p1, map_size) == -1) {
    perror("munmap p1");
  }
  if (munmap(p2, map_size) == -1) {
    perror("munmap p2");
  }
  if (shm_unlink(shm_name) == -1) {
    perror("shm_unlink");
  }

  return 0;
}
