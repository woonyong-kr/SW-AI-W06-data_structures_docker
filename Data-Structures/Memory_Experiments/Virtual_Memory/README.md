# Virtual Memory Experiments

가상 주소와 공유 매핑을 직접 확인해 보는 예제입니다.

파일 목록
- `01_proc_self_maps.c`: 현재 프로세스의 가상 메모리 매핑(`/proc/self/maps`)을 출력합니다.
- `02_shm_open_shared_mapping.c`: 같은 공유 메모리 객체를 두 개의 서로 다른 가상 주소에 매핑하고, 한쪽 수정이 다른 쪽에서도 보이는지 확인합니다.

실행 예시
```bash
gcc -g -O0 Data-Structures/Virtual_Memory_Experiments/01_proc_self_maps.c -o bin/debug/Virtual_Memory_Experiments/01_proc_self_maps
gcc -g -O0 Data-Structures/Virtual_Memory_Experiments/02_shm_open_shared_mapping.c -o bin/debug/Virtual_Memory_Experiments/02_shm_open_shared_mapping

./bin/debug/Virtual_Memory_Experiments/01_proc_self_maps
./bin/debug/Virtual_Memory_Experiments/02_shm_open_shared_mapping
```
