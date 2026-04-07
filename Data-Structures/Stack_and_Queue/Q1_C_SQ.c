//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 자료구조
랩 테스트: 섹션 C - 스택 및 큐 문제
목적: 문제 1에 필요한 함수를 구현하기 */

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

typedef struct _queue {
  LinkedList ll;
} Queue;  // Queue의 정의는 변경하면 안 됩니다

///////////////////////// 함수 원형 ////////////////////////////////////

// 이 함수들의 원형은 변경하면 안 됩니다
void createQueueFromLinkedList(LinkedList* ll, Queue* q);
void removeOddValues(Queue* q);

void enqueue(Queue* q, int item);
int dequeue(Queue* q);
int isEmptyQueue(Queue* q);
void removeAllItemsFromQueue(Queue* q);

void printList(LinkedList* ll);
ListNode* findNode(LinkedList* ll, int index);
int insertNode(LinkedList* ll, int index, int value);
int removeNode(LinkedList* ll, int index);
void removeAllItems(LinkedList* ll);

//////////////////////////// main()
/////////////////////////////////////////////////

int main() {
  int c, i;
  LinkedList ll;
  Queue q;

  c = 1;

  // 연결 리스트를 빈 연결 리스트로 초기화
  ll.head = NULL;
  ll.size = 0;

  // Queue를 빈 큐로 초기화
  q.ll.head = NULL;
  q.ll.size = 0;

  printf("1: 연결 리스트에 정수를 삽입:\n");
  printf("2: 연결 리스트로부터 큐를 생성:\n");
  printf("3: 큐에서 홀수를 제거:\n");
  printf("0: 종료:\n");

  while (c != 0) {
    printf("원하는 작업을 입력하세요(1/2/3/0): ");
    scanf("%d", &c);

    switch (c) {
      case 1:
        printf("리스트에 삽입할 정수를 입력하세요: ");
        scanf("%d", &i);
        insertNode(&ll, ll.size, i);
        printf("결과 연결 리스트: ");
        printList(&ll);
        break;
      case 2:
        createQueueFromLinkedList(&ll, &q);  // 이 함수는 직접 구현해야 합니다
        printf("결과 큐: ");
        printList(&(q.ll));
        break;
      case 3:
        removeOddValues(&q);  // 이 함수는 직접 구현해야 합니다
        printf("홀수를 제거한 뒤의 큐: ");
        printList(&(q.ll));
        removeAllItemsFromQueue(&q);
        removeAllItems(&ll);
        break;
      case 0:
        removeAllItemsFromQueue(&q);
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
void createQueueFromLinkedList(LinkedList* ll, Queue* q) {
  // Todo: 연결 리스트의 값을 앞에서부터 읽어 같은 순서의 큐를 만드세요.
  // 필요하면 enqueue를 사용하고, 기존 큐 상태가 남지 않도록 내부 리스트를
  // 올바르게 채우세요.
  if (ll == NULL || q == NULL) return;

  removeAllItemsFromQueue(q);

  ListNode* curr = ll->head;
  while (curr != NULL) {
    enqueue(q, curr->item);
    curr = curr->next;
  }
}
void removeOddValues(Queue* q) {
  // Todo: 큐를 순회하면서 홀수 값은 제거하고 짝수 값만 남기세요.
  // 남은 원소들의 큐 순서는 유지되어야 하며, size와 head 상태도 일관되어야
  // 합니다.

  if (q == NULL) return;

  while (q->ll.head != NULL && q->ll.head->item % 2 != 0) {
    ListNode* temp = q->ll.head;
    q->ll.head = q->ll.head->next;
    free(temp);
    q->ll.size--;
  }

  ListNode* prev = NULL;
  ListNode* curr = q->ll.head;

  while (curr != NULL) {
    if (curr->item % 2 != 0) {
      prev->next = curr->next;
      free(curr);
      curr = prev->next;
      q->ll.size--;
      continue;
    }
    prev = curr;
    curr = curr->next;
  }
}

//////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue* q, int item) { insertNode(&(q->ll), q->ll.size, item); }

int dequeue(Queue* q) {
  int item;

  if (!isEmptyQueue(q)) {
    item = ((q->ll).head)->item;
    removeNode(&(q->ll), 0);
    return item;
  }
  return -1;
}

int isEmptyQueue(Queue* q) {
  if ((q->ll).size == 0) return 1;
  return 0;
}

void removeAllItemsFromQueue(Queue* q) {
  int count, i;
  if (q == NULL) return;
  count = q->ll.size;

  for (i = 0; i < count; i++) dequeue(q);
}

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
    if (ll->head == NULL) {
      exit(0);
    }
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
    if (pre->next == NULL) {
      exit(0);
    }
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
