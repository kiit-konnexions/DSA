#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define MIN 1
typedef struct node {
	int count;
	int value[MAX+1];
	struct node *child[MAX+1];
}Node;

//searches the node
int searchnode(int val, Node *n, int *pos) {
    if (val < n->value[1]) {
		*pos = 0;
		return 0;
	}
    else {
		*pos = n->count;
        while ((val < n->value[*pos]) && *pos > 1)
			(*pos)--;
		return (val == n->value[*pos]) ? 1 : 0;
	}
}
// Searches value in the node
Node *search(int val, Node *root, int *pos) {
    if (root == NULL) return NULL;
	else {
        if (searchnode(val, root, pos))
			return root;
        else
			return search(val, root->child[*pos], pos);
	}
}

// Adjusts the value of the node by shifting 1 position
void fillnode(int val, Node *c, Node *n, int k) {
	for (int i = n->count; i > k; i--) {
		n->value[i + 1] = n->value[i];
		n->child[i + 1] = n->child[i];
	}
	n->value[k + 1] = val;
	n->child[k + 1] = c;
	n->count++;
}
// Splits the node
void split(int val, Node* c, Node* n,
		int k, int* y, Node** newnode) {
	int mid = (k <= MIN) ? MIN : MIN + 1;

	// Allocating the memory for a new node
	*newnode = malloc(sizeof(Node));
	for (int i = mid + 1; i <= MAX; i++) {
		(*newnode)->value[i - mid] = n->value[i];
		(*newnode)->child[i - mid] = n->child[i];
	}

	(*newnode)->count = MAX - mid;
	n->count = mid;
    if (k <= MIN)
		fillnode(val, c, n, k);
	else
		fillnode(val, c, *newnode, k - mid);

	*y = n->value[n->count];
	(*newnode)->child[0] = n->child[n->count];
	n->count--;
}
// Sets the value in the node
int setval(int val, Node *n, int *p, Node **c) {
	int k;
    if (n == NULL) {
		*p = val; *c = NULL;
		return 1;
	}
	else {
        if (searchnode(val, n, &k))
			printf("Key value already exists\n");
        if (setval(val, n->child[k], p, c)) {
            if (n->count < MAX) {
				fillnode(*p, *c, n, k);
				return 0;
			}
			else {
                split(*p, *c, n, k, p, c);
				return 1;
			}
		}
		return 0;
	}
}
// Inserts a value in the m-Way Node
Node *insert(int val, Node *root) {
	int i, flag;
	Node *c, *n;
    flag = setval(val, root, &i, &c);
	if (flag) {
		n = malloc(sizeof(Node));
		n->count = 1;
		n->value[1] = i;
		n->child[0] = root;
		n->child[1] = c;
		return n;
	}
	return root;
}

// Removes the value from the node and adjusts the values
void clear(Node *m, int k) {
	for (int i = k + 1; i <= m->count; i++) {
		m->value[i - 1] = m->value[i];
		m->child[i - 1] = m->child[i];
	}
	m->count--;
}
// Copies the successor of the value that is to be deleted
void copysucc(Node *p, int i) {
	Node* temp;
	temp = p->child[i];
	while (temp->child[0])
		temp = temp->child[0];
	p->value[i] = temp->value[i];
}
// Adjusts the values and children while shifting the value from parent to right child
void rightshift(Node *m, int k) {
    Node* temp = m->child[k];
    for (int i = temp->count; i > 0; i--) {
		temp->value[i + 1] = temp->value[i];
		temp->child[i + 1] = temp->child[i];
	}
	temp->child[1] = temp->child[0];
	temp->count++;
	temp->value[1] = m->value[k];

	temp = m->child[k - 1];
	m->value[k] = temp->value[temp->count];
	m->child[k]->child[0] = temp->child[temp->count];
	temp->count--;
}

// Adjusts the values and children while shifting the value from parent to left child
void leftshift(Node *m, int k) {
    Node *temp = m->child[k - 1];
	temp->count++;
	temp->value[temp->count] = m->value[k];
	temp->child[temp->count] = m->child[k]->child[0];

	temp = m->child[k];
	m->value[k] = temp->value[1];
	temp->child[0] = temp->child[1];
	temp->count--;

	for (int i = 1; i <= temp->count; i++) {
		temp->value[i] = temp->value[i + 1];
		temp->child[i] = temp->child[i + 1];
	}
}
// Merges two nodes
void merge(Node *m, int k) {
    Node *temp1 = m->child[k];
	Node *temp2 = m->child[k - 1];
	temp2->count++;
	temp2->value[temp2->count] = m->value[k];
	temp2->child[temp2->count] = m->child[0];

	for (int i = 0; i <= temp1->count; i++) {
		temp2->count++;
		temp2->value[temp2->count] = temp1->value[i];
		temp2->child[temp2->count] = temp1->child[i];
	}
	for (int i = k; i < m->count; i++) {
		m->value[i] = m->value[i + 1];
		m->child[i] = m->child[i + 1];
	}
	m->count--; free(temp1);
}
// Adjusts the node
void restore(Node *m, int i) {
	if (i == 0) {
		if (m->child[1]->count > MIN)
			leftshift(m, 1);
		else
			merge(m, 1);
	}
	else {
		if (i == m->count) {
			if (m->child[i - 1]->count > MIN)
				rightshift(m, i);
			else
				merge(m, i);
		}
		else {
			if (m->child[i - 1]->count > MIN)
				rightshift(m, i);
			else {
				if (m->child[i + 1]->count > MIN)
					leftshift(m, i + 1);
				else
					merge(m, i);
			}
		}
	}
}
// Helper function for del()
int delhelp(int val, Node* root) {
	if (root == NULL) return 0;
	else {
        int i, flag = searchnode(val, root, &i);
        if (flag) {
			if (root->child[i - 1]) {
				copysucc(root, i);
				// delhelp() is called recursively
				flag = delhelp(root->value[i], root->child[i]);
				if (!flag) {
					printf("\n");
					printf("value %d not found.\n", val);
				}
			}
			else
				clear(root, i);
		}
		else flag = delhelp(val, root->child[i]);

		if (root->child[i] != NULL) {
			if (root->child[i]->count < MIN)
				restore(root, i);
		}
		return flag;
	}
}
// Deletes value from the node
Node* del(int val, Node* root) {
	Node* temp;
	if (!delhelp(val, root)) {
		printf("\n");
		printf("value %d not found.\n", val);
	}
	else {
		if (root->count == 0) {
			temp = root;
			root = root->child[0];
			free(temp);
		}
	}
	return root;
}
int main(){
	Node *root = NULL; int ch, in;
	printf("1. Insert Node\n2. Delete\n");
	printf("3. Display\n0. Exit\n");
	while(1){
		printf("\nEnter Choice : ");
		scanf("%d", &ch);
		if(ch == 1){
			printf("Enter Data to be inserted : ");
			scanf("%d", &in);
			insert(in, root);
		}
        else if(ch == 2){
			printf("Enter Data to be deleted: ");
			scanf("%d", &in);
			root = del(in, root);
		}
		else if(ch == 3){
            
		}
		else if(ch == 0) break;
		else printf("Wrong Choice. ");
	}
	return 0;
}