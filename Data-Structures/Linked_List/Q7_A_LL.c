//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 자료구조
랩 테스트: 섹션 A - 연결 리스트 문제
목적: 문제 7에 필요한 함수를 구현하기 */

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
void RecursiveReverse(ListNode** ptrHead);

void printList(LinkedList* ll);
void removeAllItems(LinkedList* ll);
ListNode* findNode(LinkedList* ll, int index);
int insertNode(LinkedList* ll, int index, int value);
int removeNode(LinkedList* ll, int index);

//////////////////////////// main()
/////////////////////////////////////////////////

int main() {
  LinkedList ll;
  int c, i, j;
  c = 1;
  // 연결 리스트 1을 빈 연결 리스트로 초기화
  ll.head = NULL;
  ll.size = 0;

  printf("1: 연결 리스트에 정수를 삽입:\n");
  printf("2: 연결 리스트 뒤집기:\n");
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
        RecursiveReverse(&(ll.head));  // 이 함수는 직접 구현해야 합니다
        printf("주어진 연결 리스트를 뒤집은 결과: ");
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
void RecursiveReverse(ListNode** ptrHead) {
  // Todo: 재귀를 사용해 단일 연결 리스트를 제자리에서 뒤집으세요.
  // 먼저 리스트가 비어 있거나 노드가 1개뿐인 경우는 그대로 반환하는 기저 조건을
  // 처리하세요. 그 다음 현재 head의 다음 노드를 기준으로 나머지 리스트를 먼저
  // 재귀적으로 뒤집고, 재귀 호출이 끝나면 원래 두 번째 노드의 next가 현재
  // head를 가리키도록 연결을 반대로 바꾸세요. 현재 head의 next는 NULL로 끊어
  // 사이클이 생기지 않게 해야 하며, 마지막에는 ptrHead가 새 head(원래 마지막
  // 노드)를 가리키도록 갱신해야 합니다.

  if (ptrHead == NULL || *ptrHead == NULL || (*ptrHead)->next == NULL) return;
  // 현재 리스트: [1|*2] -> [2|*3] -> [3|*4] -> [4|*5] -> [5|NULL]

  // first는 첫 번째 노드를 가리킴
  ListNode* first = *ptrHead;  // first -> [1|*2]

  // rest는 first 다음 노드부터 시작하는 부분 리스트를 가리킴
  ListNode* rest = first->next;  // rest -> [2|*3] -> [3|*4] -> [4|*5] -> [5|NULL]

  // rest가 가리키는 부분 리스트를 먼저 재귀적으로 뒤집음
  RecursiveReverse(&rest);

  // 재귀 호출 후:
  // rest  -> [5|*4] -> [4|*3] -> [3|*2] -> [2|NULL]
  // first -> [1|*2]

  // 현재 2의 next가 first(1)를 가리키도록 연결
  first->next->next = first;
  // 연결 후 일부 구조: [2|*1] -> [1|*2]

  // first의 next를 NULL로 바꿔 기존 연결을 끊고 사이클을 방지
  first->next = NULL;
  // 연결 후 일부 구조: [2|*1] -> [1|NULL]

  // 뒤집힌 부분 리스트의 head를 전체 리스트의 새 head로 갱신
  *ptrHead = rest;
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
