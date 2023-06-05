#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *link, *multiply;
}*start = NULL;
void display(){
    struct node *temp = start;
    while(temp){
        printf("%d ", temp->data);
        if(temp->multiply)
            printf("%d\n", temp->multiply->data);
        else printf("\n");
        temp = temp->link;
    }
}
struct node *newNode(int info){
    struct node *new = malloc(sizeof(struct node));
    new->data = info; new->link = NULL;
    new->multiply = NULL; return new;
}
void createList(){
    struct node *temp = start; int info;
    printf("Input (-1 to exit) : ");
    while(1){
        scanf("%d",&info);
        if(info == -1) break;
        struct node *new = newNode(info);
        if(start == NULL) start = new;
        else temp->link = new;
        temp = new;
    }
    printf("List :\n");
    display();
}
void point(){
    struct node *temp = start;
    while(temp->link){
        struct node *next = temp->link;
        while(next != NULL){
            if(next->data % temp->data == 0){
                temp->multiply = next; break;
            }
            next = next->link;
        }
        temp = temp->link;
    }
}
int main(){
    createList();
    point();
    printf("\nAfter Point :\n");display();
    return 0;
}