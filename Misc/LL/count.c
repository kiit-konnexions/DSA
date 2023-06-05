//count no. of occurence of elements
#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* link;
};
int count=0;

void display(struct node *head){
    if(head == NULL)
        printf("Empty node\n");
    else{
        struct node *temp = head;
        while(temp){
            printf("%d ",temp->data);
            temp = temp->link;
        }
    }
}

struct node *create(){
    struct node *head = NULL, *temp = head;
    printf("Input(-1 to exit) : ");
    while(1){
        int in; scanf("%d",&in);
        if(in == -1) break;
        struct node *new = malloc(sizeof(struct node));
        new->data = in; new->link = NULL;
        if(head == NULL)
            head = new;
        else
            temp->link = new;
        temp = new;
        count++;
    }
    printf("List : ");
    display(head);
    return head;
}

void sort(struct node *head){
    struct node *cur, *temp; int tmp;
    for(temp=head; temp; temp=temp->link)
		for(cur=temp->link; cur; cur=cur->link)
			if(temp->data > cur->data) {
				tmp = temp->data;
				temp->data = cur->data;
				cur->data = tmp;
			}
}

void countNodes(struct node *head){
    sort(head);
    struct node *temp = head;
    while(temp){
        int c = 0;
        while(temp->link && temp->data==temp->link->data){
            c++; temp = temp->link;
        }
        printf("\nNo of. %d in list is %d",temp->data,c+1);
        temp = temp->link;
    }
}

int main(){
    struct node *head = create();
    (head == NULL) ? printf("Empty node\n") : countNodes(head);
    return 0;
}