//node from last
#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node* link;
}Node;
int count = 0;

void display(Node *head){
    if(head == NULL)
        printf("Empty node\n");
    else{
        Node *temp = head;
        while(temp){
            printf("%d ",temp->data);
            temp = temp->link;
        }
    }
}

Node *create(Node *head){
    Node *temp; int in;
    printf("Input(-1 to exit) : ");
    while(1){
        scanf("%d",&in);
        if(in == -1) break;
        Node *new = malloc(sizeof(Node));
        new->data = in; new->link = NULL;
        if(!head)  head = new;
        else
            temp->link = new;
        temp = new;
        count++;
    }
    printf("List : "); display(head);
    return head;
}

void mlast(Node *head){
    printf("\nEnter m : ");
    int m; scanf("%d",&m);
    if(m>count || m<1) printf("Invalid input\n");
    else{
        Node *temp = head;
        for(int i=0; i<count-m; i++)
            temp = temp->link;
        printf("Data at %d node from last : %d\n",m,temp->data);
    }
}

int main(){
    Node *head = create(head);
    mlast(head);
    return 0;
}