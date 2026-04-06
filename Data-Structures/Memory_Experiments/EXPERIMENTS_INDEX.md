# 메모리 실험 모음

이 폴더는 포인터, 가상 메모리, 힙/스택, 공유 메모리, 패딩 같은 주제를 실험형으로 익히기 위한 예제를 한곳에 모아둔 공간입니다.

## 현재 포함된 실험 묶음

### 1. Virtual_Memory
- `01_proc_self_maps.c`: 현재 프로세스의 가상 메모리 매핑 확인
- `02_shm_open_shared_mapping.c`: 서로 다른 가상 주소가 같은 내용을 공유하는지 확인

### 2. Memory_Research
- `Q1_MR_Address_Layout.c`: 전역/정적/스택/힙/리터럴 주소 비교
- `Q2_MR_Array_Pointer_Arithmetic.c`: 배열과 포인터 산술 관계 관찰
- `Q3_MR_Double_Pointer_Map.c`: `int`, `int*`, `int**` 관계 추적
- `Q4_MR_Realloc_Observe.c`: `realloc` 후 주소 변화 관찰
- `Q5_MR_Shared_Mapping.c`: 공유 매핑의 동작 확인
- `Q6_MR_Free_Dangling_Warning.c`: `free` 후 dangling pointer 경고 실험
- `Q7_MR_Use_After_Free_Unsafe.c`: use-after-free가 왜 위험한지 시연
- `Q8_MR_Struct_Padding.c`: 구조체 패딩과 정렬 관찰
- `Q9_MR_Endianness.c`: 엔디언 확인
- `Q10_MR_String_Literal_vs_Array.c`: 문자열 리터럴과 문자 배열 비교
- `Q11_MR_Const_Pointer.c`: `const int*`, `int* const`, `const int* const` 비교
- `Q12_MR_Fork_Copy_On_Write.c`: `fork()` 후 copy-on-write 관찰

## 추가 예제로 넣기 좋은 주제

아래 주제들은 아직 별도 파일로 만들지 않았지만, 지금 구조에 자연스럽게 확장할 수 있습니다.

- `Q13_MR_Volatile.c`: 최적화와 `volatile`의 차이 관찰
- `Q14_MR_Mprotect_Readonly.c`: 읽기 전용 페이지와 접근 보호 실험
- `Q15_MR_Struct_Bitfield.c`: 비트필드와 실제 메모리 배치 비교
- `Q16_MR_Function_Pointer.c`: 함수 포인터와 콜백 구조 실험
- `Q17_MR_Void_Pointer.c`: `void*` 캐스팅과 범용 포인터 사용법
- `Q18_MR_Alignment.c`: 자료형별 정렬 경계와 주소 배치 확인

## 정리 기준

- `Pointer`, `Dynamic_Memory_Allocation` 폴더는 문제 풀이용 세트라서 그대로 둡니다.
- 이 폴더는 개념 실험용 예제만 모읍니다.
- 안전한 실험과 위험한 실험은 파일명과 주석으로 구분합니다.
