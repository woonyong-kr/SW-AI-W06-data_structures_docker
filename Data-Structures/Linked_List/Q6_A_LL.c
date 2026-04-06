//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 자료구조
랩 테스트: 섹션 A - 연결 리스트 문제
목적: 문제 6에 필요한 함수를 구현하기 */

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
int moveMaxToFront(ListNode** ptrHead);

void printList(LinkedList* ll);
void removeAllItems(LinkedList* ll);
ListNode* findNode(LinkedList* ll, int index);
int insertNode(LinkedList* ll, int index, int value);
int removeNode(LinkedList* ll, int index);

//////////////////////////// main()
/////////////////////////////////////////////////

int main() {
  int c, i, j;
  c = 1;

  LinkedList ll;
  // 연결 리스트 1을 빈 연결 리스트로 초기화
  ll.head = NULL;
  ll.size = 0;

  printf("1: 연결 리스트에 정수를 삽입:\n");
  printf("2: 저장된 최댓값을 리스트 맨 앞으로 이동:\n");
  printf("0: 종료:\n");

  while (c != 0) {
    printf("원하는 작업을 입력하세요(1/2/0): ");
    scanf("%d", &c);

    switch (c) {
      case 1:
        printf("연결 리스트에 추가할 정수를 입력하세요: ");
        scanf("%d", &i);
        j = insertNode(&ll, ll.size, i);
        printf("결과 연결 리스트: ");
        printList(&ll);
        break;
      case 2:
        moveMaxToFront(&(ll.head));  // 이 함수는 직접 구현해야 합니다
        printf("최댓값을 맨 앞으로 이동한 뒤의 연결 리스트: ");
        printList(&ll);
        removeAllItems(&ll);
        break;
      case 0:
        removeAllItems(&ll);
        break;
      default:
        printf("알 수 없는 선택입니다.\n");
        break;
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////
int moveMaxToFront(ListNode** ptrHead) {
  // Todo: 최댓값을 가진 노드를 찾아 현재 위치에서 분리한 뒤 리스트 맨 앞으로 이동시키세요.
  // head 포인터를 올바르게 갱신하고, 필요하면 이동한 값 또는 실패 상태를 반환하세요.

  if (ptrHead == NULL || *ptrHead == NULL) return -1;

  ListNode* curr = *ptrHead;
  ListNode* prev = NULL;
  ListNode* maxNode = *ptrHead;
  ListNode* maxPrev = NULL;
  // 시작 예시: [1|*5] -> [5|*3] -> [3|NULL]
  // maxNode는 현재 가장 큰 값을 가진 노드, maxPrev는 그 이전 노드를 가리킵니다.

  while (curr != NULL) {
    // curr가 [1|*5], [5|*3], [3|NULL] 순서로 이동하면서 최댓값을 찾습니다.
    if (maxNode->item < curr->item) {
      maxNode = curr;
      maxPrev = prev;
    }
    prev = curr;
    curr = curr->next;
  }

  // 탐색 후 예시: maxNode -> [5|*3], maxPrev -> [1|*5]
  if ((*ptrHead) == maxNode) return -1;

  // 먼저 maxNode(5)를 원래 자리에서 분리해 [1|*3] -> [3|NULL]로 만듭니다.
  maxPrev->next = maxNode->next;
  // 그 다음 5의 next가 기존 head(1)를 가리키게 해 [5|*1]로 만듭니다.
  maxNode->next = *ptrHead;
  // 마지막으로 head를 5로 바꿔 [5|*1] -> [1|*3] -> [3|NULL]을 완성합니다.
  *ptrHead = maxNode;

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////

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
