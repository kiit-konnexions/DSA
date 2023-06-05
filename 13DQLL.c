#include <stdio.h>
#include <stdlib.h>
struct QNode {
	int key;
	struct QNode *next, *prev;
};
struct Queue {
	struct QNode *front, *rear;
};

struct QNode *newNode(int k){
	struct QNode *temp = malloc(sizeof(struct QNode));
	temp->key = k; temp->next = temp->prev = NULL;
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

void insertfront(struct Queue* q, int k){
    struct QNode* temp = newNode(k);
    if (q->front == NULL) 
		q->front = temp;
	else{
        temp->next = q->front;
        q->front->prev = temp;
    }
	q->front = temp;
    q->rear->next = q->front;
    q->front->prev = q->rear;
}
void insertrear(struct Queue* q, int k){
    struct QNode* temp = newNode(k);
    if (q->front == NULL) 
		q->front = temp;
	else{
        q->rear->next = temp;
        temp->prev = q->rear;
    }
	q->rear = temp;
    q->rear->next = q->front;
    q->front->prev = q->rear;
}

int deletefront(struct Queue* q){
	if(isEmpty(q)) return -1;
    struct QNode* temp = q->front;
    int val = temp->key;
    if (q->front == q->rear) {
        free(temp);
        q->front = q->rear = NULL;
    }
    else {
        q->front = q->front->next;
        q->rear->next = q->front;
        q->front->prev = q->rear;
        free(temp);
    }
    return val;
}
int deleterear(struct Queue* q){
	if(isEmpty(q)) return -1;
    struct QNode* temp = q->rear;
    int val = temp->key;
    if (q->front == q->rear) {
        free(temp);
        q->front = q->rear = NULL;
    }
    else {
        q->rear = q->rear->prev;
        q->rear->next = q->front;
        q->front->prev = q->rear;
        free(temp);
    }
    return val;
}

void display(struct Queue* q){
    if (isEmpty(q)) return;
    struct QNode* temp = q->front;
    do{
        printf("%d ",temp->key);
        temp = temp->next;
    }while(temp!=q->front);
    printf("\n");
}
void peek(struct Queue* q){
    if (isEmpty(q)) return;
    printf("Front : %d\n",q->front->key);
    printf("Rear : %d\n",q->rear->key);
}

void IRD(){
    int ch, num;
    struct Queue* q = createQueue();
    printf("1. Enqueue\n2. Dequeue (front)\n3. Dequeue (rear)\n");
    printf("4. Peek\n5. Display\n0. Exit\n");  
    while(1){  
        printf("\nEnter your choice : ");
        scanf("%d",&ch);
        if(ch == 1){
            printf("Enter the value : ");
            scanf("%d",&num);
            insertrear(q, num);
        }
        else if (ch == 2){
            int val = deletefront(q);
            if(val != -1)
                printf("Dequeued Element : %d\n",val);
        }
        else if (ch == 3){
            int val = deleterear(q);
            if(val != -1)
                printf("Dequeued Element : %d\n",val);
        }
        else if (ch == 4) peek(q);
        else if (ch == 5) display(q);
        else if (ch == 0) break;
        else printf("Please Enter valid choice\n");
    }
}
void ORD(){
    int ch, num;
    struct Queue* q = createQueue();
    printf("1. Enqueue (rear)\n2. Enqueue (front)\n3. Dequeue\n");
    printf("4. Peek\n5. Display\n0. Exit\n");  
    while(1){  
        printf("\nEnter your choice : ");
        scanf("%d",&ch);
        if(ch == 1){
            printf("Enter the value : ");
            scanf("%d",&num);
            insertrear(q, num);
        }
        else if (ch == 2){
            printf("Enter the value : ");
            scanf("%d",&num);
            insertfront(q, num);
        }
        else if (ch == 3){
            int val = deletefront(q);
            if(val != -1)
                printf("Dequeued Element : %d\n",val);
        }
        else if (ch == 4) peek(q);
        else if (ch == 5) display(q);
        else if (ch == 0) break;
        else printf("Please Enter valid choice\n");
    }
}

int main(){
	printf("1. Input Restricted Deque\n");
    printf("2. Output Restricted Deque\n");
    printf("\nEnter your choice : ");
    check:
    int ch; scanf("%d",&ch);
    if(ch == 1) IRD();
    else if(ch == 2) ORD();
    else {
        printf("Please Enter valid choice : ");
        goto check;
    }
	return 0;
}