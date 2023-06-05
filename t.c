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
Tree *minValueNode(Tree *node){
    Tree *current = node;
	while (current && current->left != NULL)
        current = current->left;
    return current;
}
Tree *deleteNode(Tree **root, int key){
	if (*root == NULL) return *root;
	if (key < (*root)->data)
        (*root)->left = deleteNode(&((*root)->left), key);
	else if (key > (*root)->data)
        (*root)->right = deleteNode(&((*root)->right), key);
	else {
		if ((*root)->left == NULL) {
            Tree *temp = (*root)->right;
            free(*root); return temp;
        }
        else if ((*root)->right == NULL) {
            Tree *temp = (*root)->left;
            free(*root); return temp;
        }
		Tree *temp = minValueNode((*root)->right);
		(*root)->data = temp->data;
		(*root)->right = deleteNode(&((*root)->right), temp->data);
    }
    return *root;
}

void printPostorder(Tree *root){
	if (root == NULL) return;
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d ", root->data);
}
void printInorder(Tree *root){
	if (root == NULL) return;
    printInorder(root->left);
    printf("%d ", root->data);
    printInorder(root->right);
}
void printPreorder(Tree *root){
	if (root == NULL) return;
    printf("%d ", root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

int main(){
	Tree* root = NULL; int ch, in;
	printf("1. Insert Node\n2. Delete\n");
	printf("3. Pre Order\n4. In Order\n5. Post Order\n0. Exit\n");
	while(1){
		printf("\nEnter Choice : ");
		scanf("%d", &ch);
		if(ch == 1){
			printf("Enter Data to be inserted (Exits if -1 is inserted) : ");
			while(1){
				scanf("%d", &in);
				if(in == -1) break;
				insert(&root, newNode(in));
			}
		}
		else if(ch == 2){
            printf("Enter Data to be deleted: ");
			scanf("%d", &in);
			root = deleteNode(&root, in);
		}
		else if(ch == 3){
			printf("Preorder traversal : ");
			printPreorder(root); printf("\n");
		}
		else if(ch == 4){
			printf("Inorder traversal : ");
			printInorder(root); printf("\n");
		}
		else if(ch == 5){
			printf("Postorder traversal : ");
			printPostorder(root); printf("\n");
		}
		else if(ch == 0) break;
		else printf("Wrong Choice. ");
	}
	return 0;
}