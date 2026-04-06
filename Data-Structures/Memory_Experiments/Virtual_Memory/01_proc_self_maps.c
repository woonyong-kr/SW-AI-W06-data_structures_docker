#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE* fp;
  char line[512];

  printf("현재 프로세스의 가상 메모리 매핑(/proc/self/maps)\n");
  printf("----------------------------------------------\n");

  fp = fopen("/proc/self/maps", "r");
  if (fp == NULL) {
    perror("fopen");
    return 1;
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    fputs(line, stdout);
  }

  fclose(fp);
  return 0;
}
