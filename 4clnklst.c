#include <stdio.h>  
#include <stdlib.h>    
typedef struct node{  
    int data;  
    struct node *link;  
}Node;
typedef struct {
    int count;
    Node *head, *tail;
}LL;

Node *newNode(LL *list, int info){
    Node *new = malloc(sizeof(Node));
    new->data = info; new->link = NULL;
    list->count++; return new;
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
    printf("List : ");
    do{
        printf("%d ",temp->data);
        temp = temp->link;
    }while(temp != list->head);
    printf("\n");
}
LL *create(LL *list){
    printf("Input (-1 to exit) : ");
    while(1){
        int info; scanf("%d",&info);
        if(info == -1) break;
        Node *new = newNode(list, info);
        if(!(list->head)) list->head = new;
        else list->tail->link = new;
        list->tail = new;
        list->tail->link = list->head;
    }
    display(list); return list;
}

LL *insert(LL *list, int info, int ind){
    if(indch(list, ind)) return list;
    Node *new = newNode(list, info);
    if(!(list->head)) list->head = new;
    else if(ind == 0) {
        new->link = list->head; 
        list->head = new;
    }
    else if(ind == list->count-1){
        list->tail->link = new;
        list->tail = new;
    }
    else {
        Node *temp = list->head, *prev;
        for(int i=1; i<=ind; i++) {
            prev = temp;
            temp = temp->link;
        }
        prev->link = new;
        new->link = temp;
    }
    list->tail->link = list->head;
    display(list); return list;
}
LL *delete(LL *list, int ind){
    if(isNull(list)) return list;
    if(indch(list, ind+1)) return list;
    struct node *temp = list->head, *prev;
    if(list->head == list->tail) list->head = NULL;
    else if(ind == 0)
        list->head = temp->link;
    else{
        for(int i=1; i<=ind; i++) {
            prev = temp;
            temp = temp->link;
        }
        if(temp->link == NULL) list->tail = prev;
        else prev->link = temp->link;
    } list->tail->link = list->head;
    printf("Element Deleted : %d\n",temp->data);
    list->count--; display(list); return list;
}

int search(LL *list, int info){
    if(isNull(list)) return -1;
    Node *temp = list->head; int i=0;
    do{
        if(temp->data == info) return i;
        temp = temp->link; i++;
    }while(temp != list->head);
    return -1;
}
void update(LL *list, int info, int ind){
    if(isNull(list)) return;
    if(indch(list, ind+1)) return;
    struct node *temp = list->head;
    for(int i=0; i<ind; i++)
        temp = temp->link;
    temp->data = info;
    display(list);
}
void sort(LL *list){
    if(isNull(list)) return;
    Node *index, *temp = list->head; int tmp;
    do{
        index = temp->link;  
        while(index != list->head) {
            if(temp->data > index->data) {  
                tmp = temp->data;  
                temp->data = index->data;  
                index->data = tmp;  
            }  
            index = index->link;
        }
        temp = temp->link;  
    }while(temp->link != list->head);   
    display(list);
}

void reverse(LL *list){
    if(isNull(list)) return;
    Node *curr, **ref = &(list->head);
    Node *next, *prev = NULL; curr = *ref; 
    do{
        next = curr->link;
        curr->link = prev;
        prev = curr; curr = next;
    }while(curr != *ref);
    (*ref)->link = prev;
    *ref = prev; display(list);
}
void rotate(LL *list, int k){
    Node *temp = list->head;
    for(int i=1; i<k; i++)
        temp = temp->link;
    list->tail = temp; list->head = temp->link;
    display(list);
}
void remDup(LL *list){
    Node *t1 = list->head;
    while (t1->link != list->head){
        struct node *t2 = t1;
        while(t2->link != list->head){
            if (t1->data == t2->link->data) {
                struct node *dup = t2->link;
                t2->link = dup->link;
                free(dup);
            }
            else t2 = t2->link;
        }
        t1 = t1->link;
    }
    list->tail->link = list->head;
    display(list);
}

int main(){
    LL *list; int ch, info, pos;
    list = malloc(sizeof(LL));
    list->head = list->tail = NULL;
    list->count = 0;
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
        else if(ch == 5) {
            printf("Enter data & index : ");
            scanf("%d%d",&info,&pos);
            update(list, info, pos);
        }
        else if(ch == 6) sort(list);
        else if(ch == 7) reverse(list);
        else if(ch == 8) {
            printf("Enter the shift : ");
            scanf("%d",&info); info %= list->count;
            rotate(list, info);
        }
        else if(ch == 9) remDup(list);
        else if(ch == 10) {
            printf("Enter key : ");
            scanf("%d",&info);
            int ind = search(list, info);
            if(ind == -1) printf("Element not found\n");
            else delete(list, ind);
        }
        else if(ch == 0) break;
        else printf("Wrong Input\n");
    }
    return 0;
}