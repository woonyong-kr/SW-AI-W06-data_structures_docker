//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 자료구조
랩 테스트: 섹션 F - 이진 탐색 트리 문제
목적: 문제 3에 필요한 함수를 구현하기 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // BSTNode의 정의는 변경하면 안 됩니다

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // StackNode의 정의는 변경하면 안 됩니다

typedef struct _stack
{
	StackNode *top;
}Stack; // Stack의 정의는 변경하면 안 됩니다

///////////////////////// 함수 원형 ////////////////////////////////////

// 이 함수들의 원형은 변경하면 안 됩니다
void preOrderIterative(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

// 아래 함수를 사용해도 되고 직접 작성해도 됩니다
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// 이진 탐색 트리를 빈 이진 탐색 트리로 초기화
	BSTNode * root;
	root = NULL;

	printf("1: 이진 탐색 트리에 정수를 삽입;\n");
	printf("2: 이진 탐색 트리의 전위 순회 결과를 출력;\n");
	printf("0: 종료;\n");


	while (c != 0)
	{
		printf("원하는 작업을 입력하세요(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("이진 탐색 트리에 삽입할 정수를 입력하세요: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("이진 탐색 트리의 전위 순회 결과: ");
			preOrderIterative(root); // 이 함수는 직접 구현해야 합니다
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("알 수 없는 선택입니다.\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
void preOrderIterative(BSTNode *root)
{
	 // Todo: 스택을 사용한 반복 전위 순회를 구현하세요.
	 // 노드를 pop할 때 출력하고, 오른쪽 자식 먼저 push한 뒤 왼쪽 자식을 push하면 preorder 순서를 유지할 수 있습니다.
	 /* 여기에 코드를 작성하세요 */
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
