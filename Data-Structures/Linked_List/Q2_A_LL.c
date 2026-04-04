//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 자료구조
랩 테스트: 섹션 A - 연결 리스트 문제
목적: 문제 2에 필요한 함수를 구현하기 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode {
  int item;
  struct _listnode* next;
} ListNode;  // ListNode의 정의는 변경하면 안 됩니다

typedef struct _linkedlist {
  int size;
  ListNode* head;
} LinkedList;  // LinkedList의 정의는 변경하면 안 됩니다

//////////////////////// 함수 원형 /////////////////////////////////////

// 이 함수의 원형은 변경하면 안 됩니다
void alternateMergeLinkedList(LinkedList* ll1, LinkedList* ll2);

void printList(LinkedList* ll);
void removeAllItems(LinkedList* ll);
ListNode* findNode(LinkedList* ll, int index);
int insertNode(LinkedList* ll, int index, int value);
int removeNode(LinkedList* ll, int index);

//////////////////////////// main()
/////////////////////////////////////////////////

int main() {
  LinkedList ll1, ll2;
  int c, i, j;
  c = 1;
  // 연결 리스트 1을 빈 연결 리스트로 초기화
  ll1.head = NULL;
  ll1.size = 0;

  // 연결 리스트 2를 빈 연결 리스트로 초기화
  ll2.head = NULL;
  ll2.size = 0;

  printf("1: 연결 리스트 1에 정수를 삽입:\n");
  printf("2: 연결 리스트 2에 정수를 삽입:\n");
  printf("3: 번갈아 병합된 연결 리스트 생성:\n");
  printf("0: 종료:\n");

  while (c != 0) {
    printf("원하는 작업을 입력하세요(1/2/3/0): ");
    scanf("%d", &c);

    switch (c) {
      case 1:
        printf("연결 리스트 1에 추가할 정수를 입력하세요: ");
        scanf("%d", &i);
        j = insertNode(&ll1, ll1.size, i);
        printf("연결 리스트 1: ");
        printList(&ll1);
        break;
      case 2:
        printf("연결 리스트 2에 추가할 정수를 입력하세요: ");
        scanf("%d", &i);
        j = insertNode(&ll2, ll2.size, i);
        printf("연결 리스트 2: ");
        printList(&ll2);
        break;
      case 3:
        printf("주어진 연결 리스트들을 병합한 결과는 다음과 같습니다:\n");
        alternateMergeLinkedList(&ll1, &ll2);  // 이 함수는 직접 구현해야 합니다
        printf("결과 연결 리스트 1: ");
        printList(&ll1);
        printf("결과 연결 리스트 2: ");
        printList(&ll2);
        removeAllItems(&ll1);
        removeAllItems(&ll2);
        break;
      case 0:
        removeAllItems(&ll1);
        removeAllItems(&ll2);
        break;
      default:
        printf("알 수 없는 선택입니다.\n");
        break;
    }
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////
void alternateMergeLinkedList(LinkedList* ll1, LinkedList* ll2) {
  // Todo: ll1의 각 노드 뒤에 ll2의 노드를 하나씩 번갈아 끼워 넣으세요.
  // 연결을 바꾸기 전에 next 포인터를 미리 저장하고, 병합 후 ll2에는 사용하고 남은 노드만 남도록 head와 size를 갱신하세요.
  ListNode *curr1, *curr2, *next1, *next2;
  int count = 0;

  if (ll1 == NULL || ll2 == NULL) return;

  if (ll1->head == NULL) return;

  curr1 = ll1->head;
  curr2 = ll2->head;

  while (curr1 != NULL && curr2 != NULL) {
    next1 = curr1->next;
    next2 = curr2->next;

    curr1->next = curr2;
    curr2->next = next1;

    curr1 = next1;
    curr2 = next2;
    count++;
  }

  ll2->head = curr2;
  ll1->size += count;
  ll2->size -= count;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList* ll) {
  ListNode* cur;
  if (ll == NULL) return;
  cur = ll->head;

  if (cur == NULL) printf("비어 있음");
  while (cur != NULL) {
    printf("%d ", cur->item);
    cur = cur->next;
  }
  printf("\n");
}

void removeAllItems(LinkedList* ll) {
  ListNode* cur = ll->head;
  ListNode* tmp;

  while (cur != NULL) {
    tmp = cur->next;
    free(cur);
    cur = tmp;
  }
  ll->head = NULL;
  ll->size = 0;
}

ListNode* findNode(LinkedList* ll, int index) {
  ListNode* temp;

  if (ll == NULL || index < 0 || index >= ll->size) return NULL;

  temp = ll->head;

  if (temp == NULL || index < 0) return NULL;

  while (index > 0) {
    temp = temp->next;
    if (temp == NULL) return NULL;
    index--;
  }

  return temp;
}

int insertNode(LinkedList* ll, int index, int value) {
  ListNode *pre, *cur;

  if (ll == NULL || index < 0 || index > ll->size + 1) return -1;

  // 빈 리스트이거나 첫 번째 노드를 삽입하는 경우 head 포인터를 갱신해야 함
  if (ll->head == NULL || index == 0) {
    cur = ll->head;
    ll->head = malloc(sizeof(ListNode));
    ll->head->item = value;
    ll->head->next = cur;
    ll->size++;
    return 0;
  }

  // 목표 위치의 이전 노드와 해당 위치의 노드를 찾기
  // 새 노드를 만들고 링크를 다시 연결하기
  if ((pre = findNode(ll, index - 1)) != NULL) {
    cur = pre->next;
    pre->next = malloc(sizeof(ListNode));
    pre->next->item = value;
    pre->next->next = cur;
    ll->size++;
    return 0;
  }

  return -1;
}

int removeNode(LinkedList* ll, int index) {
  ListNode *pre, *cur;

  // 제거할 수 있는 가장 큰 인덱스는 size-1임
  if (ll == NULL || index < 0 || index >= ll->size) return -1;

  // 첫 번째 노드를 제거하는 경우 head 포인터를 갱신해야 함
  if (index == 0) {
    cur = ll->head->next;
    free(ll->head);
    ll->head = cur;
    ll->size--;

    return 0;
  }

  // 목표 위치의 이전 노드와 다음 노드를 찾기
  // 대상 노드를 해제하고 링크를 다시 연결하기
  if ((pre = findNode(ll, index - 1)) != NULL) {
    if (pre->next == NULL) return -1;

    cur = pre->next;
    pre->next = cur->next;
    free(cur);
    ll->size--;
    return 0;
  }

  return -1;
}
