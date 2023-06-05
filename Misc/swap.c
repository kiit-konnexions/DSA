#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* link;
}*head = NULL;
int count = 0;

void display(){
    if(!head){
        printf("Empty List\n");
        return;
    }
    struct node *temp = head;
    printf("List : ");
    do{
        printf("%d ",temp->data);
        temp = temp->link;
    }while(temp != head);
    printf("\n");
}
void create(){
    struct node *temp = NULL; int info;
    printf("Input (-1 to exit) : ");
    while(1){
        scanf("%d",&info);
        if(info == -1) break;
        struct node *new = malloc(sizeof(struct node));
        new->data = info; new->link = NULL;
        if(head == NULL) head = new;
        else temp->link = new;
        temp = new;
    } temp->link = head;
    display();
}

void swap1(){
    struct node *temp = head;
    while(temp->link != head)
        temp = temp->link;
    temp->link = head->link;
    temp = temp->link;
    head->link = temp->link;
    temp->link = head;
    head = temp;
    display();
}
void swap2(){
    struct node *temp = head;
    while(temp->link->link->link != head)
        temp = temp->link;
    struct node *prev = temp->link;
    temp->link = prev->link;
    temp = temp->link;
    prev->link = temp->link;
    temp->link = prev;
    display();
}

int main(){
    create();
    swap1();
    swap2();
    return 0;
}