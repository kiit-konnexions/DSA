#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* link;
}; int count = 0;

struct node *newNode(int info){
    struct node *new = malloc(sizeof(struct node));
    new->data = info; new->link = NULL;
    count++; return new;
}
int indch(int p){
    if(p<0 || p>count){
        printf("Index out of bound\n");
        return 1;
    }
    return 0;
}
int isNull(struct node *head){
    if(head != NULL) return 0;
    printf("Empty list\n");
    return 1;
}

void display(struct node *head){
    if(isNull(head)) return;
    struct node *temp = head;
    printf("List : ");
    while(temp){
        printf("%d ",temp->data);
        temp = temp->link;
    }
    printf("\n");
}
struct node *createList(){
    struct node *head, *temp;
    head = temp = NULL; int info;
    printf("Input (-1 to exit) : ");
    while(1){
        scanf("%d",&info);
        if(info == -1) break;
        struct node *new = newNode(info);
        if(head == NULL) head = new;
        else temp->link = new;
        temp = new;
    }
    display(head); return head;
}

void insert(struct node **head, int info, int ind){
    if(indch(ind)) return;
    struct node *new = newNode(info);
    printf("%d",count);
    if((*head) == NULL) *head = new;
    else if(ind == 0) {
        new->link = *head; *head = new;
    }
    else {
        struct node *temp = *head, *prev;
        for(int i=1; i<=ind; i++) {
            prev = temp;
            temp = temp->link;
        }
        prev->link = new;
        new->link = temp;
    }
    display(*head);
}
//i<pos : at position, i<=pos : at index
void delete(struct node **head, int ind){
    if(isNull(*head)) return;
    if(indch(ind+1)) return;
    struct node *temp = *head, *prev;
    if(ind==0) *head = temp->link;
    else {
        for(int i=1; i<=ind; i++) {
            prev = temp;
            temp = temp->link;
        }
        prev->link = temp->link;
    }
    printf("Element Deleted : %d\n",temp->data);
    free(temp); count--; display(*head); 
}

int search(struct node *head, int info){
    if(isNull(head)) return -1;
    struct node *temp = head;
    for(int i=0; temp; i++){
        if(temp->data == info) return i;
        temp = temp->link;
    }
    return -1;
}
void update(struct node **head, int info, int ind){
    if(isNull(*head)) return;
    if(indch(ind+1)) return;
    struct node *temp = *head;
    for(int i=0; i<ind; i++)
        temp = temp->link;
    temp->data = info;
    display(*head);
}
void sort(struct node **head){
    if(isNull(*head)) return;
    struct node *cur, *temp; int tmp;
    for(temp=*head; temp; temp=temp->link)
		for(cur=temp->link; cur; cur=cur->link)
			if(temp->data > cur->data) {
				tmp = temp->data;
				temp->data = cur->data;
				cur->data = tmp;
			}
    display(*head);
}

void reverse(struct node **head){
    if(isNull(*head)) return;
    struct node *temp, *prev, *next;
    temp = *head; next = prev = NULL;
    while(temp){
        next = temp->link;
        temp->link = prev;
        prev = temp; temp = next;
    }
    *head = prev; display(*head);
}
void rotate(struct node **head, int k){
    struct node *temp = *head;
    for(int i=1; i<k; i++)
        temp = temp->link;
    struct node *tail = temp;
    while(tail->link)
        tail = tail->link;
    tail->link = *head;
    *head = temp->link;
    temp->link = NULL;
    display(*head);
}
void remDup(struct node **head){
    struct node *t1 = *head;
    while (t1->link){
        struct node *t2 = t1;
        while(t2->link){
            if (t1->data == t2->link->data) {
                struct node *dup = t2->link;
                t2->link = dup->link;
                free(dup);
            }
            else t2 = t2->link;
        }
        t1 = t1->link;
    }
    display(*head);
}

int main(){
    struct node *head;
    int ch, info, pos;
    printf("\n1. Create a list");
    printf("\n2. Insert an element");
    printf("\n3. Delete an element");
    printf("\n4. Search an element");
    printf("\n5. Update an element");
    printf("\n6. Sort the list");
    printf("\n7. Reverse the list");
    printf("\n8. Rotate the list");
    printf("\n9. Remove duplicates");
    printf("\n10. Delete a key");
    printf("\n0. Exit program\n");

    while(1){
        printf("\nEnter Choice : ");
        scanf("%d",&ch);
        if(ch == 1) head = createList();
        else if(ch == 2) {
            printf("Enter data & index : ");
            scanf("%d%d",&info,&pos);
            insert(&head, info, pos);
        }
        else if(ch == 3) {
            printf("Enter index : ");
            scanf("%d",&pos);
            delete(&head, pos);
        }
        else if(ch == 4) {
            printf("Enter element : ");
            scanf("%d",&info);
            pos = search(head, info);
            if(pos != -1)
                printf("Found at index :%d\n",pos);
            else
                printf("Element not found\n");
        }
        else if(ch == 5) {
            printf("Enter data & index : ");
            scanf("%d%d",&info,&pos);
            update(&head, info, pos);
        }
        else if(ch == 6) sort(&head);
        else if(ch == 7) reverse(&head);
        else if(ch == 8) {
            printf("Enter the shift : ");
            scanf("%d",&info); info%=count;
            rotate(&head, info);
        }
        else if(ch == 9) remDup(&head);
        else if(ch == 10) {
            printf("Enter key : ");
            scanf("%d",&info);
            int ind = search(head, info);
            if(ind == -1) printf("Element not found\n");
            else delete(&head, ind);
        }
        else if(ch == 0) break;
        else printf("Wrong Input\n");
    }
    return 0;
}