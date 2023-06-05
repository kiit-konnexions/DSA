//detect loop
#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node *link;
}Node;

void create(Node **head){
    int in = 4; Node *temp = *head = NULL;
    while(1){
        if(in == -1) break;
        Node *new = malloc(sizeof(Node));
        new->data = in; new->link = NULL;
        if(*head == NULL)
            *head = new;
        else
            temp->link = new; 
        temp = new; in--;
    }
}
void display(Node *head){
    Node *temp = head;
    while(temp){
        printf("%d ",temp->data);
        temp = temp->link;
    }
}
void check(Node *head){
    Node *slow, *fast;
    slow = head; fast = head;
    int flag = 1;
    while(fast->link && fast->link->link){
        slow = slow->link;
        fast = fast->link->link;
        if(slow == fast){
            flag = 0; break;
        }
    }
    if(flag) display(head);
    else printf("\nLoop Detected\n");
}
int main(){
    Node *head = NULL;
    create(&head);
    check(head);
    head->link->link->link = head->link;
    check(head);
    return 0;
}