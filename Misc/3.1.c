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

int LeafCount(Tree *root){
    if(root== NULL) return 0;
    if(root->left == NULL && root->right==NULL)
        return 1;           
    else
        return LeafCount(root->left)+LeafCount(root->right);     
}

int countNodes(Tree *root){
    if (root == NULL) return 0;
    else
		return (countNodes(root->right) + countNodes(root->left) + 1);
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
    int external = LeafCount(root);
    int total = countNodes(root);
    int internal = total - external;
    printf("Total Internal Nodes : %d\n",internal);
    printf("Total External Nodes : %d\n",external);
    printf("Difference : %d",external - internal);
	return 0;
}