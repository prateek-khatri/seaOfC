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

//Allocate Memory for New Node
struct Node* getNewNode(int val)
{
	struct Node * ptr = (struct Node*)malloc(sizeof(struct Node));
	ptr->val = val;
	ptr->left = NULL;
	ptr->right = NULL;
	return ptr;
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
	printf("%d\n",root->val);
	printInorder(root->right);
}
void printPostOrder(struct Node* root)
{
	if(root == NULL) return;
	printInorder(root->left);
	printInorder(root->right);
	printf("%d\n",root->val);
}
void printPreOrder(struct Node*root)
{
	if(root == NULL) return;
	printf("%d\n",root->val);
	printInorder(root->left);
	printInorder(root->right);
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
int main(void)
{
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
	printf("Printing Post-Order: \n");
	printPostOrder(root);
	printf("Printing Pre-Order: \n");
	printPreOrder(root);

	if(search(root,11))
	{
		printf("Value Found\n");
	}
	else
	{
		printf("Value Not Found\n");
	}

	return 0;
}