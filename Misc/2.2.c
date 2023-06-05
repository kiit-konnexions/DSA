#include <stdio.h>
#include <stdlib.h>
typedef struct Tnode {
	int data;
	struct Tnode *left, *right;
}Tree;
Tree *newNode(int data){
	Tree *node = malloc(sizeof(Tree));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}
void insert(Tree **root, Tree *new){
	if(*root == NULL) *root = new;
    if(new->data < (*root)->data)
		insert(&((*root)->left), new);
	if(new->data > (*root)->data)
		insert(&((*root)->right), new);
}

void printInorder(Tree *root){
	if (root == NULL) return;
    printInorder(root->left);
    printf("%d ", root->data);
    printInorder(root->right);
}
int minValueNode(Tree *node){
    if (node && node->left != NULL)
        minValueNode(node->left);
    else return node->data;
}
int maxValueNode(Tree *node){
    if (node && node->right != NULL)
        maxValueNode(node->right);
    else return node->data;
}

int main(){
	Tree* root = NULL; int in;
	printf("Enter Data to be inserted (Exits if -1 is inserted) : ");
	while(1){
		scanf("%d", &in);
		if(in == -1) break;
		insert(&root, newNode(in));
	}
    printf("Inorder traversal : ");
	printInorder(root); printf("\n");
    int s = minValueNode(root);
    int l = maxValueNode(root);
    printf("Smallest Element : %d\n",s);
    printf("Largest Element : %d\n",l);
    printf("Sum : %d", s+l);
	return 0;
}