#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *prev, *next;
}*head,*tail;
int count=0;
struct node *newnode(){
    struct node *new=malloc(sizeof(struct node));
    printf("Enter data : ");
    scanf("%d",&new->data);
    new->next= new->prev =NULL; 
    count++; return new;
}
int indch(int pos){
    if(pos<0 || pos>count){
        printf("Index out of bound\n");
        return 1;
    }
    return 0;
}
int isnull(){
    if(head) return 0;
    printf("Empty list\n");
    return 1;
}

void insbeg(struct node *new){
    new->next=head;
    head->prev=new;
    head=new;
}
void insend(struct node *new){
    tail->next=new;
    new->prev=tail;
    tail=new;
}
void insert(){
    struct node *new; int pos;
    printf("Enter index : ");
    scanf("%d",&pos);
    if(indch(pos)) return;
    new=newnode();
    if(!head) head=new;
    else if(pos==0) insbeg(new);
    else if(pos==count-1) insend(new); 
    else {
        struct node *temp=head;
        for(int i=1;i<=pos;i++)
            temp=temp->next;
        new->next=temp;
        new->prev=temp->prev;
        temp->prev->next=new;
        temp->prev=new;
    }
}

struct node *delbeg(){
    struct node *temp=head;
    head=head->next;
    head->prev=NULL;
    return temp;
}
struct node *delend(){
    struct node *temp=tail;
    tail=temp->prev;
    tail->next=NULL;
    return temp;
}
void delete(){
    if(isnull()) return;
    printf("Enter index : ");
    int pos; scanf("%d",&pos);
    struct node *del;
    if(indch(pos+1)) return;
    else if(pos==0) del=delbeg();
    else if(pos==count-1) del=delend();
    else{
        struct node *temp=head;
        for(int i=1;i<=pos;i++)
            temp=temp->next;
        temp->next->prev=temp->prev;
        temp->prev->next=temp->next;
        del=temp;
    }
    printf("Element deleted : %d\n",del->data);
    free(del); count--;
}

void create(){
    int flag;
    printf("Enter 1 to insert at end\n");
    printf("Enter -1 to insert at begin\n");
    printf("Enter 0 to exit create\n");
    while(1){
        chf:
        printf("Enter position : ");
        scanf("%d",&flag);
        if(flag<-1 || flag>1){
            printf("Invalid input. ");
            goto chf;
        }
        if(flag==0) break;
        struct node *new=newnode();
        if(!(head)) head=tail=new;
        else if(flag==1) insend(new);
        else if(flag==-1) insbeg(new);
    }
    printf("count : %d\n",count);
}
void display(){
    if(isnull()) return;
    struct node *temp=head;
    printf("List (from start) : ");
    while(temp){
        printf("%d ",temp->data);
        temp=temp->next;
    }printf("\n");

    temp=tail;
    printf("List (from end) : ");
    while(temp){
        printf("%d ",temp->data);
        temp=temp->prev;
    }printf("\n");
}

void main(){
    int ch;
    printf("\n1. Create a list");
    printf("\n2. Display the list");
    printf("\n3. Insert at a position");
    printf("\n4. Delete at a position");
    printf("\n0. Exit\n");
    while (1){
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        if(ch==1) create();
        else if(ch==2) display();
        else if(ch==3) insert();
        else if(ch==4) delete();
        else if(ch==0) break;
        else printf("\n Wrong choice");
    }
}