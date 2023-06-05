#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node *prev, *next;
}Node;
typedef struct {
    int count;
    Node *head, *tail;
}LL;

Node *newNode(LL *list, int info){
    Node *new = malloc(sizeof(Node));
    new->data = info; list->count++;
    new->prev = new->next = NULL;
    return new;
}
int indch(LL *list, int pos){
    if(pos<0 || pos>list->count){
        printf("Index out of bound\n");
        return 1;
    }
    return 0;
}
int isNull(LL *list){
    if(list->head) return 0;
    printf("Empty list\n");
    return 1;
}

void display(LL *list){
    if(isNull(list)) return;
    Node *temp = list->head;
    printf("List (from start) : ");
    while(temp){
        printf("%d ",temp->data);
        temp = temp->next;
    }printf("\n");

    temp = list->tail;
    printf("List (from end) : ");
    while(temp){
        printf("%d ",temp->data);
        temp = temp->prev;
    }printf("\n");
}
LL *create(LL *list){
    list = malloc(sizeof(LL));
    list->head = list->tail = NULL;
    list->count = 0;
    printf("Input (-1 to exit) : ");
    while(1){
        int info; scanf("%d",&info);
        if(info == -1) break;
        Node *new = newNode(list, info);
        if(list->head == NULL) list->head = new;
        else{
            list->tail->next = new;
            new->prev = list->tail;
        } list->tail = new;
    }
    display(list); return list;
}

LL *insert(LL *list, int info, int ind){
    if(indch(list, ind)) return list;
    Node *new = newNode(list, info);
    if(list->head == NULL) list->head = new;
    else if(ind == 0) {
        new->next = list->head; 
        list->head->prev = new;
        list->head = new;
    }
    else if(ind == list->count){
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;
    }
    else {
        Node *temp = list->head;
        for(int i=1;i<=ind;i++)
            temp = temp->next;
        temp->prev->next = new;
        new->prev = temp->prev;
        temp->prev = new;
        new->next = temp;
    }
    display(list); return list;
}
LL *delete(LL *list, int ind){
    if(isNull(list)) return list;
    if(indch(list, ind+1)) return list;
    Node *temp = list->head;
    if(ind == 0) {
        list->head = temp->next;
        list->head->prev = NULL;
    }
    else if(ind == list->count-1){
        temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    else {
        for(int i=1; i<=ind; i++) 
            temp = temp->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    printf("Element Deleted : %d\n",temp->data);
    list->count--; display(list); 
}

int search(LL *list, int info){
    if(isNull(list)) return -1;
    Node *temp = list->head;
    for(int i=0; temp; i++){
        if(temp->data == info) return i;
        temp = temp->next;
    }
    return -1;
}
void update(LL *list, int info, int ind){
    if(isNull(list)) return;
    if(indch(list, ind+1)) return;
    Node *temp = list->head;
    for(int i=0; i<ind; i++)
        temp = temp->next;
    temp->data = info;
    display(list);
}
void sort(LL *list){
    if(isNull(list)) return;
    Node *cur, *temp; int tmp;
    for(temp=list->head; temp; temp=temp->next)
		for(cur=temp->next; cur; cur=cur->next)
			if(temp->data > cur->data) {
				tmp = temp->data;
				temp->data = cur->data;
				cur->data = tmp;
			}
    display(list);
}

void reverse(LL *list){
    if(isNull(list)) return;
    int n = list->count, tmp;
    Node *tmph = list->head, *tmpt = list->tail;
    for(int i=0; i<n/2; i++){
        tmp = tmph->data;
        tmph->data = tmpt->data;
        tmpt->data = tmp;
        tmph = tmph->next;
        tmpt = tmpt->prev;
    }
    display(list);
}
void rotate(LL *list, int k){
    Node *temp = list->head;
    for(int i=1; i<k; i++)
        temp = temp->next;
    list->head->prev = list->tail;
    list->tail->next = list->head;
    list->head = temp->next; list->tail = temp;
    list->tail->next = list->head->prev = NULL;
    display(list);
}
void remDup(LL *list){
    Node *t1 = list->head;
    while (t1->next){
        Node *t2 = t1;
        while(t2->next){
            if (t1->data == t2->next->data) {
                Node *dup = t2->next;
                t2->next = dup->next;
                dup->next->prev = t2;
            }
            else t2 = t2->next;
        }
        t1 = t1->next;
    }
    display(list);
}

int main(){
    LL *list; int ch, info, pos;
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
        if(ch == 1) list = create(list);
        else if(ch == 2) {
            printf("Enter data & index : ");
            scanf("%d%d",&info,&pos);
            list = insert(list, info, pos);
        }
        else if(ch == 3) {
            printf("Enter index : ");
            scanf("%d",&pos);
            list = delete(list, pos);
        }
        else if(ch == 4) {
            printf("Enter element : ");
            scanf("%d",&info);
            pos = search(list, info);
            if(pos != -1)
                printf("Found at index : %d\n",pos);
            else
                printf("Element not found\n");
        }
        else if(ch== 5) {
            printf("Enter data & index : ");
            scanf("%d%d",&info,&pos);
            update(list, info, pos);
        }
        else if(ch == 6) sort(list);
        else if(ch == 7) reverse(list);
        else if(ch == 8) {
            printf("Enter the shift : ");
            scanf("%d",&info);
            info %= list->count;
            rotate(list,info);
        }
        else if(ch == 9) remDup(list);
        else if(ch == 10) {
            printf("Enter key : ");
            scanf("%d",&info);
            delete(list, search(list, info));
        }
        else if(ch == 0) break;
        else printf("Wrong Input\n");
    }
    return 0;
}