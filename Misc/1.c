#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *link, *multiply;
}*head=NULL; int count=0;

void display(){
    if(!head){
        printf("Empty List\n");
        return;
    }
    struct node *temp=head;
    printf("List : ");
    while(temp){
        printf("%d ",temp->data);
        if(temp->multiply)
            printf("%d ",temp->multiply->data);
        temp=temp->link;
        printf("\n");
    }
}
void create(){
    struct node *temp=NULL; int info;
    printf("Input (-1 to exit) : ");
    while(1){
        scanf("%d",&info);
        if(info==-1) break;
        struct node *new=malloc(sizeof(struct node));
        new->data=info; new->link=NULL;
        if(head==NULL) head=new;
        else temp->link=new;
        temp=new;
    }
    display();
}

void point(){
    struct node *temp=head;
    while(temp->link){
        struct node *next=temp->link;
        while(next){
            if(next->data%temp->data==0){
                temp->multiply=next; break;
            }
            next=next->link;
        }
        temp=temp->link;
    }
    display(); 
}
void remodd(){
    int arr[5]={1,3,6,5,9};
    int curr=0;
    for(int i=0;i<5;i++){
        if(arr[i]%2==0)
            arr[curr++]=arr[i];
    }
    for(int i=curr;i<5;i++) arr[i]=0;
    for(int i=0;i<curr;i++)
        printf("%d ",arr[i]);
    printf("\n");
    for(int i=0;i<5;i++)
        printf("%d ",arr[i]);
}
int main(){
    //create();
    //point();
    remodd();
    return 0;
}