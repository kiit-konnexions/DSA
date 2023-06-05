#include <stdio.h>  
#include <stdlib.h>    
struct node{  
    int data;  
    struct node *link;  
}*head,*tail;  
int count=0;
struct node *newnode(){
    struct node *new=malloc(sizeof(struct node));
    printf("Enter data : ");
    scanf("%d",&new->data);
    new->link=NULL; count++; return new;
}
int indch(int p){
    if(p<0 || p>count){
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
    new->link=head;
    head=new;
}
void insend(struct node *new){
    tail->link=new;
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
    else if(pos==count-1)  insend(new);
    else {
        struct node *temp=head, *prev;
        for(int i=1;i<=pos;i++) {
            prev=temp;
            temp=temp->link;
        }
        prev->link=new;
        new->link=temp;
    }
    tail->link=head;
}

struct node *delbeg(){
    struct node *temp=head;
    tail->link=temp->link;
    head=temp->link; return temp;
}
struct node *delend(){
    struct node *temp=head, *prev;
    while(temp->link!=head) {
        prev=temp;
        temp=temp->link;
    }
    prev->link=head; return temp;
}
void delete(){
    if(isnull()) return;
    printf("Enter Index : ");
    int pos; scanf("%d",&pos);
    if(indch(pos+1)) return;
    struct node *del;
    if(head==tail){
        head=NULL; del=head;
    }
    else if(pos==0)  del=delbeg();
    else if(pos==count-1) del=delend();
    else{
        struct node *temp=head, *prev;
        for(int i=1;i<=pos;i++) {
            prev=temp;
            temp=temp->link;
        }
        prev->link=temp->link; del=temp;
    }
    printf("Element Deleted : %d\n",del->data);
    free(del); count--;
}

void display(){
    if(isnull()) return;
    struct node *temp=head;
    printf("List : ");
    do{
        printf("%d ",temp->data);
        temp=temp->link;
    }while(temp!=head);
    printf("\n");
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

int main(){
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
    return 0;
}