//IMPLEMENT BST data structure

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
	int val;
	struct Node *left;
	struct Node *right;
};
struct ListNode
{
	struct Node* treeNode;
	struct ListNode * next;
};
//Global Linked List Head for Level Order Traversal
struct ListNode* queue;
struct ListNode* head = NULL;
struct ListNode* tail = NULL;

//******FUNCTION PROTOTYPES***********
void insertInQueue(struct Node* ptr);
void pop();
struct Node* front();
bool isEmpty();
struct Node* getNewNode(int val);
struct ListNode* getNewListNode(struct Node* ptr);
struct Node* insertNode(struct Node* root,int val);
void printInorder(struct Node* root);
void printPostOrder(struct Node* root);
void printPreOrder(struct Node* root);
void printLevelOrder(struct Node* root);
bool search(struct Node* root,int val);
void destroyTree(struct Node *root);
//************************************

/*
* Queue Implementation Using Linked List
* Functioanlity:
* 1. Insert
* 2. Pop
* 3. Front
* 4. Destroy
* 5. isEmpty
*/

void insertInQueue(struct Node* ptr)
{
	if(head == NULL)
	{
		//no element
		head = queue;
		tail = queue;
		queue->treeNode = ptr;
		return;
	}
	else if(head == tail)
	{
		queue->next = getNewListNode(ptr);
		tail = queue->next;
		return;
	}
	else
	{
		tail->next = getNewListNode(ptr);
		tail = tail->next;
		return;
	}
}

void pop()
{
	if(head == NULL)
	{
		return;
	}
	else if(head == tail)
	{

		head->treeNode = NULL;
		head->next = NULL;
		head = NULL;
		tail = NULL;
		return;
	}
	else
	{
		struct ListNode* temp = head;
		head = head->next;
		free(temp);
		return;
	}
}

struct Node* front()
{
	return head->treeNode;
}
bool isEmpty()
{
	if(head == NULL)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
//************END QUEUE IMPLEMENTATION****************************

//Allocate Memory for New Node
struct Node* getNewNode(int val)
{
	struct Node * ptr = (struct Node*)malloc(sizeof(struct Node));
	ptr->val = val;
	ptr->left = NULL;
	ptr->right = NULL;
	return ptr;
}
struct ListNode* getNewListNode(struct Node* ptr)
{
	struct ListNode* newNode = (struct ListNode *) malloc(sizeof(struct ListNode));
	newNode->treeNode = ptr;
	newNode->next = NULL;
	return newNode;
}
//Insert Node in Binary Search Tree
struct Node* insertNode(struct Node* root,int val)
{
	if(root == NULL)
	{
		root = getNewNode(val);
	}
	else if(val <= root->val)
	{
		root->left = insertNode(root->left,val);
	}
	else
	{
		root->right = insertNode(root->right,val);
	}
	return root;

}
void printInorder(struct Node* root)
{
	if(root == NULL) return;
	printInorder(root->left);
	printf("%d ",root->val);
	printInorder(root->right);
}
void printPostOrder(struct Node* root)
{
	if(root == NULL) return;
	printPostOrder(root->left);
	printPostOrder(root->right);
	printf("%d ",root->val);
}
void printPreOrder(struct Node*root)
{
	if(root == NULL) return;
	printf("%d ",root->val);
	printPreOrder(root->left);
	printPreOrder(root->right);
}
void printLevelOrder(struct Node* root)
{
	if(root == NULL)
	{
		return;
	}
	insertInQueue(root);
	while(!isEmpty())
	{
		struct Node* current = front();
		printf("%d ",current->val);
		if(current->left != NULL)
		{
			insertInQueue(current->left);
		}
		if(current->right != NULL)
		{
			insertInQueue(current->right);
		}
		pop();
	}


}
bool search(struct Node* root,int val)
{
	if(root == NULL)
	{
		return false;
	}
	else if(val == root->val)
	{
		return true;
	}
	else if(val < root->val)
	{
		return search(root->left,val);
	}
	else
	{
		return search(root->right,val);
	}
}
void destroyTree(struct Node * root)
{
	if(root == NULL)
	{
		return;
	}
	destroyTree(root->left);
	destroyTree(root->right);
	free(root);
}
void findKthSmallest(struct Node * root, int *returnValue,int * k)
{
	if(root == NULL || (*k) <=0)
	{
		return;
	}

	findKthSmallest(root->left,returnValue,k);

	if((*k)<=0)
	{
		return;
	}
	(*k)--;
	if((*k)==0)
	{
		*returnValue = root->val;
		return;
	}
	findKthSmallest(root->right,returnValue,k);
}
void findKthLargest(struct Node * root, int *returnValue,int * k)
{
	if(root == NULL || (*k) <=0)
	{
		return;
	}

	findKthLargest(root->right,returnValue,k);

	if((*k)<=0)
	{
		return;
	}
	(*k)--;
	if((*k)==0)
	{
		*returnValue = root->val;
		return;
	}
	findKthLargest(root->left,returnValue,k);
}
int main(void)
{
	queue = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct Node * root = NULL; //Tree is Empty
	root = insertNode(root,15);
	root = insertNode(root,10);
	root = insertNode(root,8);
	root = insertNode(root,12);
	root = insertNode(root,20);
	root = insertNode(root,17);
	root = insertNode(root,25);
	
	printf("Printing In-Order: \n");
	printInorder(root);
	printf("\nPrinting Post-Order: \n");
	printPostOrder(root);
	printf("\nPrinting Pre-Order: \n");
	printPreOrder(root);
	printf("\nPrinting Level-Order: \n");
	printLevelOrder(root);
	printf("\n");

	printf("Enter Value for Kth Smallest: ");
	int k;
	scanf("%d",&k);
	int returnValue = 0;
	findKthSmallest(root,&returnValue,&k);
	printf("The %dth smallest Element is %d\n",k,returnValue);
	

	printf("\nEnter Value for Kth Largest: ");
	scanf("%d",&k);
	returnValue = 0;
	findKthLargest(root,&returnValue,&k);
	printf("The %dth largest Element is %d\n",k,returnValue);



	// if(search(root,11))
	// {
	// 	printf("Value Found\n");
	// }
	// else
	// {
	// 	printf("Value Not Found\n");
	// }
	destroyTree(root);
	return 0;
}
