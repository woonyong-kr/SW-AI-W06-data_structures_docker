//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 자료구조
랩 테스트: 섹션 A - 연결 리스트 문제
목적: 문제 3에 필요한 함수를 구현하기 */

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
void moveOddItemsToBack(LinkedList* ll);

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
  printf("2: 모든 홀수를 연결 리스트 뒤로 이동:\n");
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
        moveOddItemsToBack(&ll);  // 이 함수는 직접 구현해야 합니다
        printf("홀수를 뒤로 이동한 뒤의 연결 리스트: ");
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

//////////////////////////////////////////////////////////////////////////////////
void moveOddItemsToBack(LinkedList* ll) {
  // Todo: 홀수 노드를 리스트 뒤쪽으로 이동시키되, 기존 상대 순서는 가능한 한 유지하고 노드의 연결이 끊기지 않도록 재배치하세요.
  // head와 size가 일관되게 유지되어야 합니다.
  if (ll == NULL || ll->head == NULL) return;

  ListNode* curr = ll->head;
  ListNode* next = NULL;
  ListNode* oddHead = NULL;
  ListNode* oddTail = NULL;
  ListNode* evenHead = NULL;
  ListNode* evenTail = NULL;

  while (curr != NULL) {
    // 현재 리스트 예시: [1|*2] -> [2|*3] -> [3|*4] -> [4|NULL]
    next = curr->next;
    curr->next = NULL;

    if (curr->item % 2 == 0) {
      // 짝수 노드는 even 리스트 뒤에 붙입니다.
      // 예: evenHead -> [2|*4], evenTail -> [4|NULL]
      if (evenHead == NULL) {
        evenHead = curr;
        evenTail = curr;
      } else {
        evenTail->next = curr;
        evenTail = curr;
      }
    } else {
      // 홀수 노드는 odd 리스트 뒤에 붙입니다.
      // 예: oddHead -> [1|*3], oddTail -> [3|NULL]
      if (oddHead == NULL) {
        oddHead = curr;
        oddTail = curr;
      } else {
        oddTail->next = curr;
        oddTail = curr;
      }
    }
    curr = next;
  }

  // 분리 후 예시:
  // evenHead -> [2|*4] -> [4|NULL]
  // oddHead  -> [1|*3] -> [3|NULL]
  if (evenHead == NULL) {
    ll->head = oddHead;
  } else {
    evenTail->next = oddHead;
    ll->head = evenHead;
  }
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
