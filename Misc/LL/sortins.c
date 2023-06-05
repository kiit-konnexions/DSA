//insert according to sort
#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* link;
}*head, *temp, *new;
int count = 0;

void display(){
    if(head == NULL)
        printf("Empty node\n");
    else{
        temp = head;
        while(temp){
            printf("%d ",temp->data);
            temp = temp->link;
        }
    }
}

void create(){
    printf("Input(-1 to exit) : ");
    while(1){
        int in; scanf("%d",&in);
        if(in == -1) break;
        new = malloc(sizeof(struct node));
        new->data = in; new->link = NULL;
        if(head == NULL){
            head = new; temp = new;
        }
        else{
            temp->link = new; temp = new;
        }
        count++;
    }
    printf("List : ");
    display();
}

/*void sort(){
    struct node *cur; int tmp;
    for(temp = head;temp;temp = temp->link)
		for(cur = temp->link;cur;cur = cur->link)
			if(temp->data > cur->data) {
				tmp = temp->data;
				temp->data = cur->data;
				cur->data = tmp;
			}
}*/

void sortins(){
    //sort();
    int in, flag = 1;
    new = malloc(sizeof(struct node));
    printf("\nEnter data : ");
    scanf("%d",&in);
    new->data = in; new->link = NULL;
    struct node *next;
    temp = head;
    if(in<head->data){
        new->link = head;
        head = new;
        return;
    }
    while(temp->link){
        if(temp->data<in && temp->link->data>in){
            next = temp->link;
            temp->link = new;
            new->link = next;
            flag = 0;
            break;
        }
        temp = temp->link;
    }
    if(flag){
        temp->link = new;
    }
}

int main(){
    create();
    (head == NULL)?printf("Empty node\n"):sortins();
    display();
    return 0;
}