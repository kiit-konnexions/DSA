//search, delete, insbeg
#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* link;
}*head, *new, *temp;
int count = 0;

void display(){
    if(head == NULL)
        printf("Empty node\n");
    else{
        temp = head;
        while(temp){
            printf("%d ",temp->data);
            temp = temp->link;
        }
    }
}

void create(){
    printf("Input(-1 to exit) : ");
    while(1){
        int in; canf("%d",&in);
        if(in == -1) break;
        new = malloc(sizeof(struct node));
        new->data = in; new->link = NULL;
        if(head == NULL){
            head = new; temp = new;
        }
        else{
            temp->link = new; temp = new;
        }
        count++;
    }
    printf("List : ");
    display();
}

void search(){
    printf("\nEnter element : ");
    int in; scanf("%d",&in); temp = head;
    struct node *prev = NULL;
    for(int i=0; temp; i++){
        if(temp->data == in){
            printf("Found at index %d\n",i);
            if(temp == head) return;
            prev->link = temp->link;
            temp->link = head;
            head = temp;
            return;
        }
        prev = temp;
        temp = temp->link;
    }
    printf("Element not found\n");
}

int main(){
    create();
    (head == NULL)?printf("Empty node\n"):search();
    display(); 
    return 0;
}