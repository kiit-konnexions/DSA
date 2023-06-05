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
Tree *search(Tree *root, int key){
    if (root == NULL || root->data == key)
       return root;
    if (root->data < key)
       return search(root->right, key);
    return search(root->left, key);
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

int height(Tree *node){
    if (node == NULL) return 0;
	int lheight = height(node->left);
	int rheight = height(node->right);
	return (lheight > rheight)? (lheight + 1) : (rheight + 1);
}
void printCurrentLevel(Tree *root, int level){
    if (root == NULL) return;
    if (level == 1) printf("%d ", root->data);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}
void printLevelorder(Tree *root){
    int h = height(root);
    for (int i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}

int main(){
	Tree* root = NULL; int ch, in;
	printf("1. Insert Node\n2. Height\n3. Search\n4. Delete\n");
	printf("5. Pre Order\n6. In Order\n7. Post Order\n8. Level Order\n0. Exit\n");
	while(1){
		printf("\nEnter Choice : ");
		scanf("%d", &ch);
		if(ch == 1){
			printf("Enter Data to be inserted : ");
			scanf("%d", &in);
			insert(&root, newNode(in));
		}
		else if(ch == 2) printf("Height of the tree : %d\n", height(root));
		else if(ch == 3){
			printf("Enter Data to be searched : ");
			scanf("%d", &in);
			if(search(root, in)->data == in)
				printf("%d is present in the tree\n",in);
			else printf("Not found in the tree\n");
		}
		else if(ch == 4){
			printf("Enter Data to be deleted: ");
			scanf("%d", &in);
			root = deleteNode(&root, in);
		}
		else if(ch == 5){
			printf("Preorder traversal : ");
			printPreorder(root); printf("\n");
		}
		else if(ch == 6){
			printf("Inorder traversal : ");
			printInorder(root); printf("\n");
		}
		else if(ch == 7){
			printf("Postorder traversal : ");
			printPostorder(root); printf("\n");
		}
		else if(ch == 8){
			printf("Levelorder traversal : ");
			printLevelorder(root); printf("\n");
		}
		else if(ch == 0) break;
		else printf("Wrong Choice. ");
	}
	return 0;
}