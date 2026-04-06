#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
실험 목표
- fork 직후 부모/자식이 같은 내용을 복사해 시작하지만, 쓰기 시점에는 copy-on-write로 분리된다는 점을 확인합니다.

관찰 포인트
- 자식은 global/local 값을 바꿉니다.
- 부모는 wait 후에도 자기 값이 그대로 유지됩니다.
- 즉 fork 직후 같은 내용을 가졌더라도, 한쪽 쓰기가 시작되면 독립된 메모리처럼 동작합니다.
*/

int global_value = 100;

int main(void) {
  pid_t pid;
  int local_value = 200;

  printf("fork 전: global=%d, local=%d\n", global_value, local_value);
  fflush(stdout);

  pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    global_value = 999;
    local_value = 888;
    printf("자식: global=%d, local=%d\n", global_value, local_value);
    fflush(stdout);
    _exit(0);
  }

  wait(NULL);
  printf("부모: global=%d, local=%d\n", global_value, local_value);
  printf("설명: fork 직후에는 같은 내용을 복사해 시작하지만, 쓰기가 일어나면 copy-on-write로 분리됩니다.\n");
  return 0;
}
