#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node *prev, *next;
}Node;
typedef struct List {
    Node *head, *tail;
}LL;
Node *newNode(int info) {
    Node *new = malloc(sizeof(Node));
    new->data = info;
    new->prev = new->next = NULL;
    return new;
}
int isNull(LL *list) {
    if(list->head) return 0;
    printf("Empty list\n");
    return 1;
}

void display(LL *list) {
    if(isNull(list)) return;
    Node *temp = list->head;
    printf("List (from start) : ");
    do {
        printf("%d ",temp->data);
        temp = temp->next;
    } while(temp != list->head);
    printf("\n");
    
    temp = list->tail;
    if(isNull(list)) return;
    printf("List (from end) : ");
    do {
        printf("%d ",temp->data);
        temp = temp->prev;
    } while(temp != list->tail);
    printf("\n");
}
LL* create(LL *list){
    list = malloc(sizeof(LL));
    list->head = list->tail = NULL; int info;
    printf("\nInput (-1 to exit) : ");
    while(1) {
        scanf("%d",&info);
        if(info == -1) break;
        Node *new = newNode(info);
        if (list->head == NULL) list->head = new;
        else {
            list->tail->next = new;
            new->prev = list->tail;
        } list->tail = new;
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }
    return list;
}
LL* merge(LL *out, LL *list1, LL *list2){
    out = malloc(sizeof(LL));
    list1->tail->next = list2->head;
    list2->head->prev = list1->tail;
    list2->tail->next = list1->head;
    list1->head->prev = list2->tail;
    out->head = list1->head;
    out->tail = list2->tail;
    return out;
}
int main(){
    LL *list1, *list2, *out; 
    list1 = create(list1);
    printf("List 1 : ");
    display(list1);
    
    list2 = create(list2);
    printf("List 2 : ");
    display(list2);
    
    out = merge(out, list1, list2);
    printf("\nOutput : ");
    display(out);
    return 0;
}