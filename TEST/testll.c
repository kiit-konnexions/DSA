#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* link;
}; int count=0;

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
int isnull(struct node *head){
    if(head) return 0;
    printf("Empty list\n");
    return 1;
}

void insbeg(struct node **head, struct node *new){
    new->link=*head; *head=new;
}
void insend(struct node **head, struct node *new){
    struct node *temp=*head;
    while(temp->link) temp=temp->link;
    temp->link=new;
}
void insert(struct node **head){
    struct node *new; int pos;
    printf("Enter index : ");
    scanf("%d",&pos); 
    if(indch(pos)) return;
    new=newnode();
    if(!head) *head=new;
    else if(pos==0) insbeg(head, new);
    else if(pos==count-1)  insend(head, new);
    else {
        struct node *temp=*head, *prev;
        for(int i=1;i<=pos;i++) {
            prev=temp;
            temp=temp->link;
        }
        prev->link=new;
        new->link=temp;
    }
}
//i<pos : at position, i<=pos : at index
struct node *delbeg(struct node **head){
    struct node *temp=*head;
    *head=temp->link; return temp;
}
struct node *delend(struct node **head){
    struct node *temp=*head, *prev;
    while(temp->link){
        prev=temp;
        temp=temp->link;
    }
    prev->link=NULL; return temp;
}
void delete(struct node **head){
    if(isnull(*head)) return;
    printf("Enter index : ");
    int pos; scanf("%d",&pos);
    struct node *del;
    if(indch(pos+1)) return;
    else if(pos==0) del=delbeg(head);
    else if(pos==count-1) del=delend(head);
    else{
        struct node *temp=*head, *prev;
        for(int i=1;i<=pos;i++) {
            prev=temp;
            temp=temp->link;
        }
        prev->link=temp->link; del=temp;
    }
    printf("Element Deleted : %d\n",del->data);
    free(del); count--;;
}

struct node *create(){
    struct node *head=NULL; int flag;
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
        if(!(head)) head=new;
        else if(flag==1) insend(&head, new);
        else if(flag==-1) insbeg(&head, new);
    }
    printf("count : %d\n",count); return head;
}
void display(struct node *head){
    struct node *temp=head;
    if(isnull(head)) return;
    printf("List : ");
    while(temp){
        printf("%d ",temp->data);
        temp=temp->link;
    }
    printf("\n");
}

int main(){
    struct node *head; int ch;
    printf("\n1. Create a list");
    printf("\n2. Display the list");
    printf("\n3. Insert an element");
    printf("\n4. Delete an element");
    printf("\n0. Exit program\n");
    while(1){
        printf("\nEnter Choice : ");
        scanf("%d",&ch);
        if(ch==1) head=create();
        else if(ch==2) display(head);
        else if(ch==3) insert(&head);
        else if(ch==4) delete(&head);
        else if(ch==0) break;
        else printf("Wrong Input\n");
    }
    return 0;
}