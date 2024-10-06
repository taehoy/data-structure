//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
int getIndexByNode(ListNode *head, ListNode *node);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{
    /* add your code here */
	if((*ptrHead) == NULL){
		return -1;
	}

	ListNode *cur = (*ptrHead); // 첫번째 노드
	ListNode *maxNode = cur; // 최대값을 담은 노드 포인터 (초기화 : head)
	ListNode *temp = NULL; // maxNode 이전 노드

	while(cur->next != NULL){
		if(maxNode->item < cur->next->item){
			temp = cur;
			maxNode = cur->next;
		}
		cur = cur->next;
	}

	// 최대값이 첫번째일 경우 
	if(maxNode == *ptrHead){
		printf("%c\n", 'a');
		return 0;
	}

	// maxNode가 맨 뒤일 경우, maxNode->next = NULL
	if(maxNode->next == NULL){
		// maxNode의 다음을 첫번째 헤드 주소로 변경
		maxNode->next = *ptrHead;
		// maxNode를 head로 지정
		*ptrHead = maxNode;
		// maxNode의 이전 노드의 next를 NULL로 지정
		temp->next = NULL;
	} 
	// maxNode가 중간일 경우
	else {
		// maxNode의 이전 노드의 next를 maxNode의 next값으로 변경
		temp->next = maxNode->next;
		// maxNode의 다음을 첫번쨰 헤드 주소로 변경
		maxNode->next = *ptrHead;
		// maxNode를 head로 지정
		*ptrHead = maxNode;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int getIndexByNode(ListNode *head, ListNode *node){
	printf("%d\n", 1111);

	if (head == NULL){
		return -1;
	}

	int index = 0; // 반환할 인덱스
	ListNode *cur; // 현재 위치 노드
	cur = head;

	while(cur->next != NULL){
		// 입력한 노드가 갖고 있는 주소와 cur->next의 주소가 같으면 같은 노드임.
		if(cur->next == node){
			return index+1;
		}
		cur = cur->next;
		index++;
	}

	return index;
}

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
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

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
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
