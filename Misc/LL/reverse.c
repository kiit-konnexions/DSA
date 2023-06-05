#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* link;
}*head,*temp;
int count=0;

void display(){
    if(head==NULL)
        printf("Empty node\n");
    else{
        temp=head;
        while(temp){
            printf("%d ",temp->data);
            temp=temp->link;
        }
    }
}

void create(){
    struct node *new; int in;
    printf("Input(-1 to exit) : ");
    while(1){
        scanf("%d",&in);
        if(in==-1) break;
        new=malloc(sizeof(struct node));
        new->data=in; new->link=NULL;
        if(head==NULL){
            head=new; temp=new;
        }
        else{
            temp->link=new; temp=new;
        }
        count++;
    }
    printf("List : ");
    display();
}

void reverse(){
    struct node *prev,*next;
    prev=NULL;temp=head;next=NULL;
    while(temp){
        next=temp->link;
        temp->link=prev;
        prev=temp;temp=next;
    }head=prev;
    printf("\nReverse : ");
    display();
}

int main(){
    create();
    (head==NULL)?printf("Empty node\n"):reverse();
    return 0;
}