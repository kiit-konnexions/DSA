#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct node {
	int key;
	struct node* link;
};
struct node *newNode(int data) {
    struct node *new = malloc(sizeof(struct node));
    new->key = data; new->link = NULL;
    return new;
}
struct node *insertNode(struct node *head, int info) {
    struct node *temp = head;
    if(head == NULL) head = newNode(info);
    else{
        while(temp->link) temp = temp->link;
        temp->link = newNode(info);
    }
    return head;
}
void display(struct node *list){
    struct node *temp = list;
    while(temp){
        printf("%d ", temp->key);
        temp = temp->link;
    }
    printf("\n");
}

int isPrime(int n) {
    for (int i = 2; i <= sqrt(n); i++) 
        if (n % i == 0) return 0;
    if (n <= 1) return 0;
    return 1;
}
struct node *split(struct node *list) {
    struct node *temp = list;
    struct node *prime = NULL, *comp = NULL;
    while(temp){
        if(isPrime(temp->key))
            prime = insertNode(prime, temp->key);
        else
            comp = insertNode(comp, temp->key);
        temp = temp->link;
    }
    temp = comp;
    while(temp->link) temp = temp->link;
    temp->link = prime;
    return comp;
}

int main(){
    struct node *list = NULL; int info;
    printf("Enter nodes (-1 to exit) : ");
    do {
        scanf("%d", &info);
        if(info!=-1)
            list = insertNode(list, info);
    } while(info!=-1);
    display(list);
    struct node *out = split(list);
    display(out);
    return 0;
}