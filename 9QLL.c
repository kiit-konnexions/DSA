#include <stdio.h>
#include <stdlib.h>
struct QNode {
    int key;
    struct QNode* link;
};
struct Queue {
    struct QNode *front, *rear;
};
 
struct QNode *newNode(int k){
    struct QNode *temp = malloc(sizeof(struct QNode));
    temp->key = k; temp->link = NULL;
    return temp;
}
struct Queue *createQueue(){
    struct Queue *q = malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(struct Queue* q){
    if (q->front == NULL){
        printf("Queue is empty\n");
        return 1;
    }
    return 0;
}

void enQueue(struct Queue* q, int k){
    struct QNode* temp = newNode(k);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->link = temp;
    q->rear = temp;
}
int deQueue(struct Queue* q){
    if (isEmpty(q)) return -1;
    struct QNode* temp = q->front;
    int val = temp->key;
    q->front = q->front->link;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return val;
}

void display(struct Queue* q){
    if (isEmpty(q)) return;
    struct QNode* temp = q->front;
    while(temp){
        printf("%d ",temp->key);
        temp = temp->link;
    }
    printf("\n");
}
void peek(struct Queue* q){
    if (isEmpty(q)) return;
    printf("Front : %d\n",q->front->key);
    printf("Rear : %d\n",q->rear->key);
}

int main(){
	struct Queue* q = createQueue();
	int ch,in;
    printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Peek\n0. Exit\n");
    while(1){
        printf("\nEnter your choice : ");
        scanf("%d",&ch);
        if(ch == 1){
            printf("Enter the value : ");
            scanf("%d",&in);
            enQueue(q, in);
        }
        else if(ch == 2) {
            in = deQueue(q); if(in!=-1)
            printf("Dequeued Element : %d\n",in);
        }
        else if(ch == 3) display(q);
        else if(ch == 4) peek(q);
        else if(ch == 0) break;
        else printf("Please Enter valid choice\n");
    }
    return 0;
}