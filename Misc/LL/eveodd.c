//segregate eve then odd
#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node* link;
}Node;
typedef struct list{
    Node *head, *tail;
}List;
int count = 0;

void display(List *l){
    if(l->head == NULL)
        printf("Empty node\n");
    else{
        Node *temp = l->head;
        while(temp){
            printf("%d ",temp->data);
            temp = temp->link;
        }
    }
}

void create(List *l){
    printf("Input(-1 to exit) : ");
    while(1){
        int in; scanf("%d",&in);
        if(in == -1) break;
        Node *new = malloc(sizeof(struct node));
        new->data = in; new->link = NULL;
        printf("HI");
        if(l->head == NULL){
            printf("hi");
            l->head = new;
        }
        else{
            printf("Hello");
            l->tail->link = new;
        }
        l->tail = new;
        count++;
    }
    printf("List : ");
    display(l);
}

void arrange(List *l){
    Node *end, *prev, *curr;
    end=l->tail; curr=l->head;
    Node *new_end=end; prev=NULL;

    while (curr->data%2 && curr!=end){
        new_end->link = curr;
        curr = curr->link;
        new_end->link->link = NULL;
        new_end = new_end->link;
    }
    
    if (curr->data%2 == 0){
        l->head = curr;
        while (curr != end){
            if ((curr->data)%2==0){
                prev = curr;
                curr = curr->link;
            }
            else{
                prev->link = curr->link;
                curr->link = NULL;
                new_end->link = curr;
                new_end = curr;
                curr = prev->link;
            }
        }
    }
    else prev = curr;
    if (new_end!=end && (end->data)%2){
        prev->link = end->link;
        end->link = NULL;
        new_end->link = end;
    }
    return;
}

int main(){
    List *l; create(l);
    (l->head==NULL) ? printf("Empty node\n") : arrange(l);
    printf("\nOut : "); display(l);
    return 0;
}