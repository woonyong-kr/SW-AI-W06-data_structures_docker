//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 자료구조
랩 테스트: 섹션 C - 스택 및 큐 문제
목적: 문제 6에 필요한 함수를 구현하기 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// ListNode의 정의는 변경하면 안 됩니다

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// LinkedList의 정의는 변경하면 안 됩니다


typedef struct stack{
	LinkedList ll;
} Stack; // stack의 정의는 변경하면 안 됩니다

///////////////////////// 함수 원형 ////////////////////////////////////

// 이 함수들의 원형은 변경하면 안 됩니다
void removeUntil(Stack *s, int value);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	LinkedList ll;
	Stack s;

	// 연결 리스트를 빈 연결 리스트로 초기화
	ll.head = NULL;
	ll.size = 0;

	// 스택을 빈 스택으로 초기화
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: 스택에 정수를 삽입:\n");
	printf("3: 지정한 값이 나올 때까지 값을 제거;\n");
	printf("0: 종료:\n");


	while (c != 0)
	{
		printf("원하는 작업을 입력하세요(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("스택에 삽입할 정수를 입력하세요: ");
			scanf("%d", &i);
			push(&s, i);
			printf("결과 스택: ");
			printList(&(s.ll));
			break;
		case 2:
		    printf("해당 값이 나올 때까지 제거할 기준 정수를 스택에서 입력하세요: ");
			scanf("%d", &i);
			removeUntil(&s,i); // 이 함수는 직접 구현해야 합니다
			printf("지정한 값이 나올 때까지 제거한 뒤의 스택: ");
			printList(&(s.ll));
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		default:
			printf("알 수 없는 선택입니다.\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////

void removeUntil(Stack *s, int value)
{
/* 여기에 코드를 작성하세요 */
}

//////////////////////////////////////////////////////////////////////////////////

void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int peek(Stack *s){
    if(isEmptyStack(s))
        return MIN_INT;
    else
        return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;

	cur = ll->head;
	if (cur == NULL)
		printf("비어 있음");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 빈 리스트이거나 첫 번째 노드를 삽입하는 경우 head 포인터를 갱신해야 함
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// 목표 위치의 이전 노드와 해당 위치의 노드를 찾기
	// 새 노드를 만들고 링크를 다시 연결하기
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// 제거할 수 있는 가장 큰 인덱스는 size-1임
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드를 제거하는 경우 head 포인터를 갱신해야 함
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// 목표 위치의 이전 노드와 다음 노드를 찾기
	// 대상 노드를 해제하고 링크를 다시 연결하기
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
