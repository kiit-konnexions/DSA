#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *link;
}*head, *rev, *temp;

void display(struct node *start){
    if(start == NULL){
        printf("Empty node\n");
        return;
    }
    temp = start;
    while(temp){
        printf("%d ",temp->data);
        temp = temp->link;
    }
}

void create(){
    struct node *new, *tail; int in;
    printf("Input(-1 to exit) : ");
    while(1){
        scanf("%d",&in);
        if(in == -1) break;
        new = malloc(sizeof(struct node));
        temp = malloc(sizeof(struct node));
        new->data = in; new->link = NULL;
        temp->data = in; temp->link = NULL;
        if(head == NULL){
            head = new; rev = temp; tail = new;
        }
        else{
            tail->link = new; tail = new;
            temp->link = rev; rev = temp;
        }
    }
    printf("Input : ");
    display(head);
}

void res(){
    struct node *nxth, *nxtr, *tmph, *tmpr;
    tmph = head; tmpr = rev;
    nxth = head->link; nxtr = rev->link;
    int flag = 1;
    while(tmph->link){
        if(flag){
            tmph->link = nxtr;
            flag = 0;
        }
        else{
            tmpr->link = nxth;
            flag = 1;
        }
        tmph = tmph->link;
        tmpr = tmpr->link;
        nxth = nxth->link;
        nxtr = nxtr->link;
    }
    printf("\nOutput : ");
    display(head);
}

int main(){
    create();
    //display(rev);
    (head == NULL) ? printf("Empty List") : res();
    return 0;
}