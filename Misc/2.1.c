#include<stdio.h>
#include<stdlib.h>
struct Queue {
    int *arr, size;
    int front, rear;
};
struct Queue *createQueue(int size){
    struct Queue *queue = malloc(sizeof(struct Queue));
    queue->size = size; queue->front = queue->rear = -1;
    queue->arr = (int*)malloc(queue->size * sizeof(int));
    return queue;
}

int isEmpty(struct Queue *queue){
    if(queue->front==-1){
        printf("Queue underflow\n");
        return 1;
    }
    return 0;
}
int isFull(struct Queue *queue){
    if((queue->front == 0 && queue->rear == queue->size-1) 
        || (queue->rear == queue->front-1)){
        printf("Queue overflow\n");
        return 1;
    }
    return 0;
}

void enQueue(struct Queue *queue, int num){
    if(isFull(queue)) return;
    else if (queue->front == -1)
        queue->front = queue->rear = 0;
    else if (queue->rear == queue->size-1)
        queue->rear = 0;
    else
        queue->rear++;
    queue->arr[queue->rear] = num;
}
int deQueue(struct Queue *queue){
    if(isEmpty(queue)) return -1;
    int val = queue->arr[queue->front];
    if(queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else if (queue->front == queue->size-1)
        queue->front=0;
    else queue->front++;
    return val;
}

void peek(struct Queue *queue){
    if(isEmpty(queue)) return;
    printf("First element : %d\n",queue->arr[queue->front]);
    printf("Last element : %d\n",queue->arr[queue->rear]);
}
void display(struct Queue *queue){
    if(isEmpty(queue)) return;
    if(queue->rear >= queue->front)
        for(int i=queue->front;i<=queue->rear;i++)
            printf("%d ",queue->arr[i]);
    else{
        for(int i=queue->front;i<queue->size;i++)
            printf("%d ",queue->arr[i]);
        for(int i=0;i<=queue->rear;i++)
            printf("%d ",queue->arr[i]);
    }
    printf("\n");
}

void main(){
    int ch, num;
    printf("Enter size of the queue : ");
    scanf("%d",&num);
    struct Queue *queue=createQueue(num);
    printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n0. Exit\n");  
    while(1){  
        printf("\nEnter your choice : ");
        scanf("%d",&ch);
        if(ch==1){
            printf("Enter the value : ");
            scanf("%d",&num);
            enQueue(queue, num);
        }
        else if (ch==2){
            int val=deQueue(queue);
            if(val!=-1)
                printf("Dequeued Element : %d\n",val);
        }
        else if (ch==3) peek(queue);
        else if (ch==4) display(queue);
        else if (ch==0) break;
        else printf("Please Enter valid choice\n");
    }
}